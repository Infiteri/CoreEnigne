#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Core/Logger.h"
#include "Core/Layer/LayerStack.h"
#include "ImGuiAbstraction.h"
#include "Input.h"

namespace Core
{
    static Window *gWindow = nullptr;
    static Engine *s_Instance;

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
        Renderer::Init();

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

        // Update the systems
        Input::Update();
        LayerStack::Update();

        // Scene rendering
        Renderer::Render();

        LayerStack::Render();

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