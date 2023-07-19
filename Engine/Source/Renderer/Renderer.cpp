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

        // No camera = no rendering
        if (state.currentCamera == nullptr)
            return;

        state.mainShader->Use();
        state.mainShader->Mat4("uProjection", state.currentCamera->GetProjection()->data);
        state.mainShader->Mat4("uView", state.currentCamera->GetInvertedView()->data);

        // Calculate the renderer's view ability
        state.viewAbility.x = state.currentCamera->GetPosition()->x;
        state.viewAbility.y = state.currentCamera->GetPosition()->y;
        state.viewAbility.Width = state.currentCamera->GetViewExtentMaxX();
        state.viewAbility.height = state.currentCamera->GetViewExtentMaxY();
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

    void Renderer::UseTransform(Transform *transform)
    {
        state.mainShader->Mat4("uTransform", transform->GetTransformMatrix()->data);
    }

    OrthographicCamera *Renderer::GetCurrentCamera()
    {
        return state.currentCamera;
    }

    Shader *Renderer::GetColorShader()
    {
        return state.mainShader;
    }

    ViewAbility *Renderer::GetViewAbility()
    {
        return &state.viewAbility;
    }

}