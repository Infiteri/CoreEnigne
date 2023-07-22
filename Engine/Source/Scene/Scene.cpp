#include "Scene.h"
#include "Core/Logger.h"

namespace Core
{
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
    }

    void Scene::Stop()
    {
        state = SceneState::Stopped;
    }

    void Scene::Destroy()
    {
        state = SceneState::Destroyed;
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
}