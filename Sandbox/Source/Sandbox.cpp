#include "Core.h"
#include "Core/Launch.h"
#include "imgui.h"
#include "glad/glad.h"

static Core::VertexArray *s_vertexArray;
static Core::Shader *shader;
static Core::OrthographicCamera *camera;

class ExampleLayer : public Core::Layer
{
public:
    ExampleLayer(){};
    ~ExampleLayer(){};

    void OnAttach()
    {
        CE_INFO("Layer on attach");

        camera = new Core::OrthographicCamera(Core::Engine::Get()->GetWindow()->GetWidth(), Core::Engine::Get()->GetWindow()->GetHeight(), -1.0f, 1.0f);

        Core::Renderer::SetClearColor(0, 0, 0.1, 0.5);

        float vertices[3 * 3] = {
            -100.0f, -100.0, 0.0f,
            100.0f, -100.0f, 0.0f,
            0.0f, 100.0f, 0.0f};

        s_vertexArray = new Core::VertexArray();
        s_vertexArray->GenVertexBuffer(vertices, sizeof(vertices));
        s_vertexArray->AddVertexLayout(0, 0, 3);

        shader = new Core::Shader("EngineResources/Shaders/Main.vs", "EngineResources/Shaders/Main.fs");
    };

    void OnRender()
    {
        shader->Use();
        shader->Mat4("uProjection", camera->GetProjection()->data);
        shader->Mat4("uView", camera->GetInvertedView()->data);

        if (Core::Input::GetKey(Core::InputKey::A))
        {
            camera->GetPosition()->x -= 10;
            camera->UpdateView();
        }

        if (Core::Input::GetKey(Core::InputKey::D))
        {
            camera->GetPosition()->x += 10;
            camera->UpdateView();
        }

        if (Core::Input::GetKey(Core::InputKey::W))
        {
            camera->GetPosition()->y -= 10;
            camera->UpdateView();
        }

        if (Core::Input::GetKey(Core::InputKey::S))
        {
            camera->GetPosition()->y += 10;
            camera->UpdateView();
        }

        camera->UpdateProjection(Core::Engine::Get()->GetWindow()->GetWidth(), Core::Engine::Get()->GetWindow()->GetHeight());

        Core::Renderer::SubmitVertex(s_vertexArray);
    };

    void OnImGuiRender()
    {
        ImGui::Begin("Test");

        ImGui::End();
    };
};

class Sandbox : public Core::Application
{
public:
    Sandbox(){};
    ~Sandbox(){};

    void OnPreInit()
    {
        this->p_Configuration.StartMaximized = true;
    };

    void OnInit()
    {
        Core::LayerStack::PushLayer(new ExampleLayer());
    }
};

Core::Application *Core::CreateApplication()
{
    return new Sandbox();
};