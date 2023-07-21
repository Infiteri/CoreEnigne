#include "Sandbox2D.h"
#include "imgui.h"

static Core::OrthoMovement *movement;
static Core::Sprite sprite;

void Sandbox2D::OnAttach()
{
    CE_INFO("Layer on attach");

    Core::Renderer::SetClearColor(0, 0, 0.1, 0.5);

    movement = new Core::OrthoMovement(Core::Renderer::GetCurrentCamera(), 10.0f);

    sprite.Init();
};

void Sandbox2D::OnRender()
{
    movement->Update();

    sprite.Render();
};

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Sandbox 2D");
    ImGui::Text("FPS: %i", 1.0f / Core::Engine::Get()->GetDelta());

    float spriteWidth = sprite.GetWidth();
    float spriteHeight = sprite.GetHeight();
    float spriteSizes[2] = {spriteWidth, spriteHeight};

    if (ImGui::DragFloat2("Sprite's Sizes", spriteSizes, 1.0f, 0.0f, 250.0f))
    {
        sprite.SetSize(spriteSizes[0], spriteSizes[1]);
    }

    ImGui::End();
}