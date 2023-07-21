#include "Sprite.h"
#include "Core/Engine.h"
#include "Renderer/Renderer.h"
#include "Renderer/OrthographicCamera.h"
#include "glad/glad.h"

float vertices[] = {
    100.0f, 100.0f, 0.0f, 1.0f, 1.0f,   // top right
    100.0f, -100.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -100.0f, -100.0f, 0.0f, 0.0f, 0.0f, // bottom left
    -100.0f, 100.0f, 0.0f, 0.0f, 1.0f   // top left
};
unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

namespace Core
{
    Sprite::Sprite()
    {
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Init()
    {
        transform = new Transform();
        material = new Material();
        array = new VertexArray();

        array->GenIndexBuffer(indices, sizeof(indices));
        array->GetIndexBuffer()->Bind();

        array->GenVertexBuffer(vertices, sizeof(vertices));
        array->AddVertexLayout(0, 0, 3);
        array->AddVertexLayout(1, 3, 2);
        array->GetVertexBuffer()->Bind();
    }

    void Sprite::Render()
    {
        if (array == nullptr)
            return;

        ViewAbility *view = Renderer::GetViewAbility();

        // Dont render the sprite if not in bounds
        // TODO: Replace 100 with width / height
        if (view->x - 100.0f > transform->position.x || view->Width + 100.0f < transform->position.x ||
            view->y - 100.0f > transform->position.y || view->height + 100.0f < transform->position.y)
            return;

        material->Use();

        Renderer::UseTransform(transform);

        array->Bind();
        array->DrawIndex();

        material->PostUse();
    }

    void Sprite::Update()
    {
    }
}