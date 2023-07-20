#include "Core.h"
#include "Core/Launch.h"
#include "imgui.h"
#include <cmath>

static Core::OrthoMovement *movement;
static std::vector<Core::Sprite *> sprites;
int numSprites = sprites.size();
int gridSize = 20;

// Function to perform linear interpolation between two values
float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

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

        static char *textures[6] = {"EngineResources/Images/crate.png", "EngineResources/Images/wall.jpg", "EngineResources/Images/wall1.jfif", "EngineResources/Images/wall2.jfif", "EngineResources/Images/wall3.jfif", "EngineResources/Images/wall4.jfif"};
        static char *texture = textures[0];

        if (ImGui::BeginCombo("Texture", texture))
        {
            for (int i = 0; i < 6; i++)
            {
                bool isSelected = false;

                if (ImGui::Selectable(textures[i], isSelected))
                {
                    texture = textures[i];
                    sprites[0]->texture->Swap(texture);
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
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