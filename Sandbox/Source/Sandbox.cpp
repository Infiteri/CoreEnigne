#include "Core.h"
#include "Core/Launch.h"
#include "imgui.h"
#include <cmath>

static Core::OrthoMovement *movement;
static std::vector<Core::Sprite *> sprites;
int numSprites = sprites.size();

class ExampleLayer : public Core::Layer
{
public:
    ExampleLayer(){};
    ~ExampleLayer(){};

    void OnAttach()
    {
        CE_INFO("Layer on attach");

        Core::Renderer::SetClearColor(0, 0, 0.1, 0.5);

        movement = new Core::OrthoMovement(Core::Renderer::GetCurrentCamera(), 10.0f);

        sprites.push_back(new Core::Sprite());

        numSprites = sprites.size();
    };

    void OnRender()
    {
        movement->Update();

        for (int j = 0; j < numSprites; j++)
        {
            sprites[j]->Render();
        }
    };

    void OnImGuiRender()
    {
        ImGui::Begin("Test");
        ImGui::Text("FPS: %i", (int)(1.0f / Core::Engine::Get()->GetDelta()));
        if (ImGui::DragFloat("Zoom", &movement->zoomSpeed))
        {
        }

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
        this->p_Configuration.StartMaximized = false;
        this->p_Configuration.title = "Game";
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