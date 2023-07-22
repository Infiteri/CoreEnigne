#pragma once

#include "Core/Base.h"
#include "Core/CEPCH.h"
#include "Components.h"
#include <type_traits>

namespace Core
{
    enum class EntityState
    {
        Created,
        Uninitialized,
        Initialized,
        Started,
        Stopped,
        Destroyed
    };

    class Scene;

    class CE_API Entity
    {
    private:
        EntityState state;
        std::string name;

        std::vector<Component *> components;
        uint32_t id;

        friend class Scene;

    public:
        Entity(const std::string &name = "Entity");
        ~Entity();

        void Init();

        void Start();

        void Render();

        void Update();

        void Stop();

        void Destroy();

        template <typename T>
        void AddComponent()
        {
            T *newComponent = new T;
            components.push_back(newComponent);

            OnComponentAdded();
        };

        template <typename T>
        bool HasComponent()
        {
            if (components.size() == 0)
                return false;

            for (Component *component : components)
            {
                if (component->IsType(typeid(T)))
                {
                    return true;
                }
            }
            return false;
        }

        template <typename T>
        T *GetComponent()
        {
            for (Component *component : components)
            {
                if (component->IsType(typeid(T)))
                    return static_cast<T *>(component);
            }

            return nullptr;
        }

        template <typename T>
        void RemoveComponent()
        {
            components.erase(std::remove_if(components.begin(), components.end(),
                                            [](Component *comp)
                                            {
                                                return dynamic_cast<T *>(comp) != nullptr;
                                            }),
                             components.end());
        }

        void OnComponentAdded();

        inline const std::string &GetName() { return name; };
        void SetName(const std::string &name);
        uint32_t GetID() { id; };
    };
}