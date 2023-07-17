#include "Engine.h"
#include "Core/Logger.h"

namespace Core
{

    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::Init()
    {
    }

    void Engine::PreInit()
    {
        Logger::Init();
    }

    void Engine::Update()
    {
    }

    void Engine::Shutdown()
    {
    }
}