#pragma once

#include "Core/Base.h"

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
    };
}