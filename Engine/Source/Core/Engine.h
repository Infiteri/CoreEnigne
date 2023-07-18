#pragma once

#include "Core/Base.h"
#include "Core/Window.h"

namespace Core
{
    class CE_API Engine
    {
    public:
        Engine();
        ~Engine();

        void Init();
        void PreInit();
        void Update();
        void Shutdown();

        void StartWindow(ApplicationConfiguration *configuration);

        Window *GetWindow();
        static Engine *Get();
    };
}