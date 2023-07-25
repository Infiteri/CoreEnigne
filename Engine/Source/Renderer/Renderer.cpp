#include "Renderer.h"
#include "Core/Engine.h"
#include "Particle/ParticleSystem.h"

#include <glad/glad.h>

namespace Core
{
    static RendererState state;

    void Renderer::Init()
    {
        state.mainShader = new Shader("EngineResources/Shaders/Main.vs", "EngineResources/Shaders/Main.fs");
        state.camera = new OrthographicCamera(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight(), -50.0f, 50.0f);
        state.currentCamera = state.camera;
        state.fBuffer = new FrameBuffer();
        state.fBuffer->Bind();

        // Setup OpenGL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ParticleSystem::Init();
    }

    void Renderer::Render()
    {
        Clear();

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

        ParticleSystem::Render();
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::SetClearColor(int r, int g, int b, int a)
    {
        state.colorValues.x = r;
        state.colorValues.y = g;
        state.colorValues.z = b;
        state.colorValues.w = a;
    }

    void Renderer::Viewport(float width, float height)
    {
        state.fBuffer->Resize(width, height);

        // WIP: Camera state
        state.currentCamera->UpdateProjection(width, height);

        glViewport(0, 0, width, height);
    }

    void Renderer::Clear()
    {
        glClearColor(state.colorValues.x, state.colorValues.y, state.colorValues.z, state.colorValues.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetCurrentCamera(OrthographicCamera *newCamera)
    {
        state.currentCamera = newCamera;
        state.currentCamera->UpdateView();
    }

    void Renderer::SetCurrentCameraDefault()
    {
        state.currentCamera = state.camera;
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

    FrameBuffer *Renderer::GetFrameBuffer()
    {
        return state.fBuffer;
    }

    void Renderer::BeginFrame()
    {
        state.fBuffer->Bind();
        state.mainShader->Use();
        Clear();
    }

    void Renderer::EndFrame()
    {
        // Submit
        state.fBuffer->Unbind();
    }
}