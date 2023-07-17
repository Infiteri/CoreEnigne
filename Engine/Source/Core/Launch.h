#pragma once

#include "Core/EngineLoop.h"

extern Core::Application *Core::CreateApplication();

//!!! Entry point
int main(int argc, char const *argv[])
{
    Core::EngineLoop EngineLoop;

    EngineLoop.PreInit(Core::CreateApplication());

    EngineLoop.Init();

    while (EngineLoop.ShouldUpdate())
    {
        EngineLoop.Update();
    }

    EngineLoop.Shutdown();

    return 0;
}
