#include "Engine.h"

#include "Core/Layer/LayerStack.h"
#include "Core/ImGuiAbstraction.h"
#include "Core/Input.h"

#include "Core/Logger.h"
#include "Platform/Platform.h"

#include "Renderer/Renderer.h"

#include "Script/ScriptEngine.h"

namespace Core
{
    static Window *gWindow = nullptr;
    static Engine *s_Instance;
    static float Delta = 0.0f;
    static double prevTime = 0.0;
    static DLLLibrary library;

    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::PreInit()
    {
        Logger::Init();
        LayerStack::Init();

        ScriptEngineConfiguration config;
        config.ProjectDLLFileName = "Project.dll";
        ScriptEngine::Init(config); // TODO: Here ?

        /// Load
        // library = Platform::LoadDLL("Project.dll");
        // EntityScript *script = Platform::LoadClass<EntityScript>("CreateTest", &library);

        s_Instance = this;
    }

    void Engine::Init()
    {
    }

    void Engine::Update()
    {
        if (gWindow != nullptr)
            gWindow->Update();

        s_Instance = this;

        float currentTime = (float)glfwGetTime();
        Delta = currentTime - prevTime;
        prevTime = currentTime;

        // Update the systems
        Input::Update();

        // Scene rendering
        Renderer::BeginFrame();
        Renderer::Render();
        LayerStack::Render();

        // Updating
        ScriptEngine::Update();
        LayerStack::Update();

        Renderer::EndFrame();

        // ImGui
        ImGuiAbstraction::PreRender();
        LayerStack::RenderImGui();
        ImGuiAbstraction::PostRender();
    }

    void Engine::Shutdown()
    {
        ImGuiAbstraction::End();
        Logger::Shutdown();
        Renderer::Shutdown();
        LayerStack::Destroy();
    }

    void Engine::StartWindow(ApplicationConfiguration *configuration)
    {
        gWindow = new Window(configuration);
        Renderer::Init();
    }

    float Engine::GetDelta()
    {
        return Delta;
    }

    Window *Engine::GetWindow()
    {
        return gWindow;
    }

    Engine *Engine::Get()

    {
        return s_Instance;
    }
}