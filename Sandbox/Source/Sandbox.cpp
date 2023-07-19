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

        const int spriteSize = 100;

        for (int y = 0; y < gridSize; y++)
        {
            for (int x = 0; x < gridSize; x++)
            {
                Core::Sprite *sprite = new Core::Sprite();

                sprite->GetTransform()->position.x = x * spriteSize;
                sprite->GetTransform()->position.y = y * spriteSize;

                // Calculate smooth gradient colors using lerp
                float tX = static_cast<float>(x) / (gridSize - 1); // Percentage of completion for x
                float tY = static_cast<float>(y) / (gridSize - 1); // Percentage of completion for y

                int red = static_cast<int>(lerp(0, 255, tX));   // Varies the red component between 0 and 255
                int green = static_cast<int>(lerp(0, 255, tY)); // Varies the green component between 0 and 255
                int blue = 128;                                 // Constant blue component to keep it cool, you can adjust this value as desired

                sprite->GetMaterial()->GetColor()->r = red;
                sprite->GetMaterial()->GetColor()->g = green;
                sprite->GetMaterial()->GetColor()->b = blue;

                sprites.push_back(sprite);
            }
        }

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
        ImGui::Text("Draw calls: %i", gridSize * gridSize);
        if (ImGui::DragFloat("Zoom", &movement->zoomSpeed))
        {
        }

        if (ImGui::DragInt("GridSize", &gridSize, 1.0f, 1.0f, 50.0f))
        {
            sprites.clear();

            const int spriteSize = 100;

            for (int y = 0; y < gridSize; y++)
            {
                for (int x = 0; x < gridSize; x++)
                {
                    Core::Sprite *sprite = new Core::Sprite();

                    sprite->GetTransform()->position.x = x * spriteSize;
                    sprite->GetTransform()->position.y = y * spriteSize;

                    // Calculate smooth gradient colors using lerp
                    float tX = static_cast<float>(x) / (gridSize - 1); // Percentage of completion for x
                    float tY = static_cast<float>(y) / (gridSize - 1); // Percentage of completion for y

                    int red = static_cast<int>(lerp(0, 255, tX));   // Varies the red component between 0 and 255
                    int green = static_cast<int>(lerp(0, 255, tY)); // Varies the green component between 0 and 255
                    int blue = 128;                                 // Constant blue component to keep it cool, you can adjust this value as desired

                    sprite->GetMaterial()->GetColor()->r = red;
                    sprite->GetMaterial()->GetColor()->g = green;
                    sprite->GetMaterial()->GetColor()->b = blue;

                    sprites.push_back(sprite);
                }
            }

            numSprites = sprites.size();
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