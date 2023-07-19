#include "Sprite.h"
#include "Core/Engine.h"
#include "Renderer/Renderer.h"
#include "Renderer/OrthographicCamera.h"
#include "glad/glad.h"

float vertices[] = {
    100.0f, 100.0f, 0.0f,   // top right
    100.0f, -100.0f, 0.0f,  // bottom right
    -100.0f, -100.0f, 0.0f, // bottom left
    -100.0f, 100.0f, 0.0f   // top left
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
        array = new VertexArray();
        transform = new Transform();
        material = new Material();

        array->GenIndexBuffer(indices, sizeof(indices));
        array->GetIndexBuffer()->Bind();

        array->GenVertexBuffer(vertices, sizeof(vertices));
        array->AddVertexLayout(0, 0, 3);
        array->GetVertexBuffer()->Bind();
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Init()
    {
    }

    void Sprite::Render()
    {
        OrthographicCamera *camera = Renderer::GetCurrentCamera();

        if (camera->GetPosition()->x > transform->position.x || camera->GetViewExtentMaxX() < transform->position.x ||
            camera->GetPosition()->y > transform->position.y || camera->GetViewExtentMaxY() < transform->position.y)
            return;

        material->Use();

        Renderer::UseTransform(transform);

        array->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        material->PostUse();
    }

    void Sprite::Update()
    {
    }
}