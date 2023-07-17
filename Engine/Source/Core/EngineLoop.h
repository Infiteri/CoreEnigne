#pragma once

#include "Core/Base.h"
#include "Application.h"

namespace Core
{

    /// @brief Heavealy inspired by Unreal Engine
    class CE_API EngineLoop
    {
    public:
        EngineLoop();
        ~EngineLoop();

        Application* instance = nullptr;

        void PreInit(Application* inst);
        void Init();
        bool ShouldUpdate();
        void Update();
        void Shutdown();
    };
}