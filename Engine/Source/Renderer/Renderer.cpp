#include "Renderer.h"
#include "Core/Engine.h"

#include <glad/glad.h>

namespace Core
{
    static RendererState state;

    void Renderer::Init()
    {
        state.mainShader = new Shader("EngineResources/Shaders/Main.vs", "EngineResources/Shaders/Main.fs");
        state.camera = new OrthographicCamera(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight(), -50.0f, 50.0f);
        state.currentCamera = state.camera;
    }

    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        state.mainShader->Use();
        state.mainShader->Mat4("uProjection", state.currentCamera->GetProjection()->data);
        state.mainShader->Mat4("uView", state.currentCamera->GetInvertedView()->data);
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::SetClearColor(int r, int g, int b, int a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer::Viewport(float width, float height)
    {
        glViewport(0, 0, width, height);

        // WIP: Camera state
        state.camera->UpdateProjection(width, height);
    }

    OrthographicCamera *Renderer::GetCurrentCamera()
    {
        return state.currentCamera;
    }
} 