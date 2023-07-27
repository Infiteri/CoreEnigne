#pragma once

#include "Core/Base.h"
#include "Core/CEPCH.h"

#include "Entity.h"

namespace Core
{
    enum class SceneState
    {
        Created,
        Uninitialized,
        Initialized,
        Started,
        Stopped,
        Destroyed
    };

    class CE_API Scene
    {
    private:
        SceneState state;

        std::vector<Entity *> entities;

    public:
        Scene();
        ~Scene();

        /// @brief Internal
        void Init();

        /// @brief Starts the actual scene, initializes the entities.
        void Start();

        void Render();

        void Update();

        void Stop();

        void Destroy();

        void Restart();

        void OnRuntimeStart();

        void OnRuntimeStop();

        Entity *GetEntityByName(const std::string &searchValue);
        std::vector<Entity *> GetAllEntities();

        void AddEntity(Entity *entity);

        void RemoveEntityByName(const std::string &name);

        static Scene *Copy(Scene *from);
    };
}