#include "Sandbox2D.h"

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