#include "Entity.h"
#include "Renderer/Renderer.h"
#include "Core/Logger.h"

namespace Core
{
    static uint32_t gid = 0;

    Entity::Entity(const std::string &name)
    {
        state = EntityState::Created;

        this->name = name;

        id = gid;
        gid++;
    }

    Entity::~Entity()
    {
        Destroy();
    }

    void Entity::Init()
    {
        if (state != EntityState::Created)
        {
            CE_WARN("Init can only be called when the entity has just been created.");
            return;
        }

        if (state == EntityState::Destroyed)
        {
            CE_ERROR("A destroyed entity cannot be Init-ed");
            return;
        }

        state = EntityState::Uninitialized;

        // Setup code goes here
        CE_TRACE("Entity Init: %s", name.c_str());

        state = EntityState::Initialized;
    }

    void Entity::Start()
    {
        if (state == EntityState::Created)
        {
            CE_WARN("Calling Start without calling the Init method.");
            Init();
        }

        CE_TRACE("Entity Start: %s", name.c_str());

        state = EntityState::Started;
    }

    void Entity::Render()
    {
        if (state != EntityState::Started) // No start = no render
            return;

        if (HasComponent<TransformComponent>())
        {
            Renderer::UseTransform(&GetComponent<TransformComponent>()->transform);
        }
        if (HasComponent<SpriteComponent>())
        {
            TransformComponent *tc = GetComponent<TransformComponent>();

            if (tc != nullptr)
                GetComponent<SpriteComponent>()->sprite.Render(&tc->transform);
        }
    }

    void Entity::Update()
    {
        if (state != EntityState::Started)
            return;
    }

    void Entity::Stop()
    {
        state = EntityState::Stopped;

        CE_TRACE("Entity Stop: %s", name.c_str());
    }

    void Entity::Destroy()
    {
        state = EntityState::Destroyed;

        CE_TRACE("Entity Destroy: %s", name.c_str());

        for (Component *c : components)
        {
            delete c;
        }

        components.clear();
    }

    void Entity::OnComponentAdded()
    {
        if (HasComponent<SpriteComponent>())
            GetComponent<SpriteComponent>()->sprite.Init();
    }

    void Entity::SetName(const std::string &name)
    {
        this->name = name;
    }

}