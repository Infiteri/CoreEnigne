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

        FrameBufferSpecification specification;
        specification.Width = 1280;
        specification.Height = 720;

        specification.Attachment = {FrameBufferTextureFiltering::Rgba8, FrameBufferTextureFiltering::RedInteger, FrameBufferTextureFiltering::Depth24Stencil8};

        state.fBuffer = new FrameBuffer(specification);
        state.fBuffer->Bind();

        // Setup OpenGL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ParticleSystem::Init();
    }

    void Renderer::Render()
    {
        Clear();

        // If no camera is present no rendering is done, puts a empty matrix as its projection / view
        state.mainShader->Use();

        if (state.currentCamera != nullptr)
        {
            state.mainShader->Mat4("uProjection", state.currentCamera->GetProjection()->data);
            state.mainShader->Mat4("uView", state.currentCamera->GetInvertedView()->data);

            // Calculate the renderer's view ability
            state.viewAbility.x = state.currentCamera->GetPosition()->x;
            state.viewAbility.y = state.currentCamera->GetPosition()->y;
            state.viewAbility.Width = state.currentCamera->GetViewExtentMaxX();
            state.viewAbility.height = state.currentCamera->GetViewExtentMaxY();
        }
        else
        {
            state.mainShader->Mat4("uProjection", Matrix4::Empty()->data);
            state.mainShader->Mat4("uView", Matrix4::Empty()->data);

            state.viewAbility.x = 0;
            state.viewAbility.y = 0;
            state.viewAbility.Width = 0;
            state.viewAbility.height = 0;
        }

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
        if (state.currentCamera != nullptr)
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

        if (newCamera != nullptr)
        {
            state.currentCamera->UpdateView();
            state.currentCamera->UpdateProjection(state.fBuffer->specification.Width, state.fBuffer->specification.Height); //? XD
        }
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