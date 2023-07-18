#include "Core.h"
#include "Core/Launch.h"
#include "imgui.h"
#include "glad/glad.h"

static Core::VertexArray *s_vertexArray;
static Core::Shader *shader;
static Core::OrthographicCamera *camera;
static Core::OrthoMovement *movement;

class ExampleLayer : public Core::Layer
{
public:
    ExampleLayer(){};
    ~ExampleLayer(){};

    void OnAttach()
    {
        CE_INFO("Layer on attach");

        Core::Renderer::SetClearColor(0, 0, 0.1, 0.5);

        float vertices[3 * 3] = {
            -100.0f, -100.0, 0.0f,
            100.0f, -100.0f, 0.0f,
            0.0f, 100.0f, 0.0f};

        s_vertexArray = new Core::VertexArray();
        s_vertexArray->GenVertexBuffer(vertices, sizeof(vertices));
        s_vertexArray->AddVertexLayout(0, 0, 3);

        Core::OrthographicCamera *camera = Core::Renderer::GetCurrentCamera();
        movement = new Core::OrthoMovement(camera, 10.0f);
    };

    void OnRender()
    {
        movement->Update();
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