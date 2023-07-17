#include "EngineLoop.h"
#include "Core/Logger.h"
#include "Core/Engine.h"

namespace Core
{
    // State
    static bool s_Initialized = false;
    static Engine *engine;

    EngineLoop::EngineLoop()
    {
    }

    EngineLoop::~EngineLoop()
    {
    }

    void EngineLoop::PreInit(Application *inst)
    {
        if (s_Initialized)
        {
            CE_ERROR("EngineLoop: PreInit called after init.");
            return;
        }

        if (inst == nullptr)
        {
            CE_FATAL("Application CreateApplication returns nullptr!");
            return;
        }

        // Setup the global engine instance
        engine = new Engine();

        // Initialize subsystems
        engine->PreInit();

        instance = inst;
        instance->OnPreInit();

        CE_TRACE("EngineLoop: PreInit successful.");
    }

    void EngineLoop::Init()
    {
        if (s_Initialized)
        {
            CE_ERROR("Initialized already!?");
            return;
        }

        if (instance == nullptr)
        {
            CE_FATAL("Application CreateApplication returns nullptr!");
            return;
        }

        // Setting the initialized flag
        s_Initialized = true;

        // Init the core of the engine
        engine->Init();

        // Setup the engine
        instance->OnInit();

        CE_TRACE("EngineLoop: Init successful.");
    }

    bool EngineLoop::ShouldUpdate()
    {
        return true;
    }

    void EngineLoop::Update()
    {
        if (!s_Initialized)
        {
            CE_ERROR("Unable to update without calling Init!!!");
            return;
        }

        if (instance == nullptr)
        {
            CE_FATAL("Application CreateApplication returns nullptr!");
            return;
        }

        instance->OnRun();
    }

    void EngineLoop::Shutdown()
    {
        if (instance == nullptr)
        {
            CE_FATAL("Application CreateApplication returns nullptr!");
            return;
        }

        s_Initialized = false;

        Core::Logger::Shutdown();

        instance->OnShutdown();

        CE_INFO("EngineLoop: Shutdown successful.");
    }

}