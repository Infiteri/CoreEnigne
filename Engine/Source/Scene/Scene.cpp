#include "Scene.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Script/ScriptEngine.h"

namespace Core
{
    static void CopyComponents(Entity *to, Entity *from);

    Scene::Scene()
    {
        state = SceneState::Created;
    }

    Scene::~Scene()
    {
        Destroy();
    }

    void Scene::Init()
    {
        if (state != SceneState::Created)
        {
            CE_WARN("Init can only be called when the scene has just been created.");
            return;
        }

        if (state == SceneState::Destroyed)
        {
            CE_ERROR("A destroyed scene cannot be Init-ed");
            return;
        }

        state = SceneState::Uninitialized;

        for (Entity *e : entities)
            e->Init();

        state = SceneState::Initialized;
    }

    void Scene::Start()
    {
        if (state == SceneState::Started)
            return;

        state = SceneState::Started;

        for (Entity *e : entities)
        {
            if (e->state == EntityState::Created)
            {
                // Means that scene Init and Start called one after another, its all fine
                e->Init();
            }

            e->Start();
        }
    }

    void Scene::Render()
    {
        if (state != SceneState::Started)
            return;

        for (Entity *e : entities)
        {
            e->Render();
        }
    }

    void Scene::Update()
    {
        if (state != SceneState::Started)
            return;

        for (Entity *e : entities)
        {
            e->Update();
        }

        ScriptEngine::OnRuntimeUpdate();
    }

    void Scene::Stop()
    {
        state = SceneState::Stopped;

        for (auto e : entities)
            e->Stop();
    }

    void Scene::Destroy()
    {
        state = SceneState::Destroyed;

        for (auto e : entities)
            e->Destroy();
    }

    void Scene::Restart()
    {
        Stop();
        Init();
        Start();
    }

    void Scene::OnRuntimeStart()
    {
        Start();

        // DONE: Setting up the camera.
        bool added = false;
        for (Entity *e : entities)
        {
            // Setup script components
            if (e->HasComponent<ScriptComponent>())
            {
                auto c = e->GetComponent<ScriptComponent>();

                CE_DEBUG("Adding script component:");
                CE_DEBUG("Class Name: %s", c->className.c_str());
                CE_DEBUG("Owner: %s", e->GetName().c_str());

                ScriptEngine::RegisterScriptComponent(c, e);
            }

            if (added)
            {
                CE_WARN("Multiple entities with a camera component.");
                continue;
            }

            if (e->HasComponent<CameraComponent>())
            {
                Renderer::SetCurrentCamera(&e->GetComponent<CameraComponent>()->camera);
                added = true;
            }
        }

        if (!added)
            Renderer::SetCurrentCamera(nullptr);

        ScriptEngine::OnRuntimeStart();

        CE_DEBUG("Runtime Start.");
    }

    void Scene::OnRuntimeStop()
    {
        CE_DEBUG("Runtime Stop.");

        ScriptEngine::OnRuntimeStop();
    }

    Entity *Scene::GetEntityByName(const std::string &searchValue)
    {
        for (Entity *ent : entities)
        {
            if (ent->GetName().compare(searchValue) == 0)
            {
                return ent;
            }
        }

        return nullptr;
    }

    std::vector<Entity *> Scene::GetAllEntities()
    {
        return entities;
    }

    void Scene::AddEntity(Entity *entity)
    {
        entities.push_back(entity);

        if (state == SceneState::Initialized)
            entity->Init();

        if (state == SceneState::Started)
        {
            if (entity->state == EntityState::Created)
            {
                // Means that scene Init and Start called one after another, its all fine
                entity->Init();
            }

            entity->Start();
        }
    }

    void Scene::RemoveEntityByName(const std::string &name)
    {

        for (auto it = entities.begin(); it != entities.end();)
        {
            Entity *ent = *it;

            if (ent->GetName().compare(name) == 0)
            {
                ent->Destroy();
                it = entities.erase(it);
                delete ent;
            }
            else
            {
                ++it;
            }
        }
    }

    Scene *Scene::Copy(Scene *from)
    {
        Scene *out = new Scene();

        for (auto entity : from->GetAllEntities())
        {
            Entity *outEntity = new Entity(entity->GetName());
            CE_INFO("Copying entity: %s", outEntity->GetName().c_str());

            // Copy components
            CopyComponents(entity, outEntity);

            out->AddEntity(outEntity);
        }

        return out;
    }

    void CopyComponents(Entity *from, Entity *to)
    {
        if (from->HasComponent<TransformComponent>())
        {
            TransformComponent *tc = to->AddComponent<TransformComponent>();
            TransformComponent *tc2 = from->GetComponent<TransformComponent>();
            tc->transform.position.x = tc2->transform.position.x;
            tc->transform.position.y = tc2->transform.position.y;
            tc->transform.position.z = tc2->transform.position.z;

            tc->transform.rotation.x = tc2->transform.rotation.x;
            tc->transform.rotation.y = tc2->transform.rotation.y;
            tc->transform.rotation.z = tc2->transform.rotation.z;

            tc->transform.scale.x = tc2->transform.scale.x;
            tc->transform.scale.y = tc2->transform.scale.y;
            tc->transform.scale.z = tc2->transform.scale.z;
        }

        if (from->HasComponent<SpriteComponent>())
        {
            SpriteComponent *c = to->AddComponent<SpriteComponent>();
            SpriteComponent *src = from->GetComponent<SpriteComponent>();

            c->sprite.SetSize(src->sprite.GetWidth(), src->sprite.GetHeight());
            c->sprite.GetMaterial()->GetColor()->Set(c->sprite.GetMaterial()->GetColor()->r, c->sprite.GetMaterial()->GetColor()->g, c->sprite.GetMaterial()->GetColor()->b, c->sprite.GetMaterial()->GetColor()->a); // TODO: Man WTF is this piece of shit you stupid c++ programer

            if (src->sprite.GetMaterial()->GetTexture()->GetPath().compare("") != 0)
                c->sprite.GetMaterial()->GetTexture()->FromPath(src->sprite.GetMaterial()->GetTexture()->GetPath().c_str());
        }

        if (from->HasComponent<CameraComponent>())
        {
            CameraComponent *c = to->AddComponent<CameraComponent>();
            CameraComponent *src = from->GetComponent<CameraComponent>();

            c->camera.SetZoom(src->camera.GetZoom());
            c->camera.GetPosition()->Set(src->camera.GetPosition()->x, src->camera.GetPosition()->y, src->camera.GetPosition()->z);
        }

        if (from->HasComponent<ScriptComponent>())
        {
            ScriptComponent *c = to->AddComponent<ScriptComponent>();
            ScriptComponent *src = from->GetComponent<ScriptComponent>();

            c->className = src->className;
        }

        // TODO: Particle emitter
    }
}