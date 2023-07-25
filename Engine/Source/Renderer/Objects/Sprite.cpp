#include "Sprite.h"
#include "Core/Engine.h"
#include "Core/Logger.h"

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
        material = new Material();
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Init()
    {
        if (isInitialized)
            return;

        array = new VertexArray();

        // Take the sizes into account.
        vertices[0] = width;
        vertices[5] = width;
        vertices[10] = -width;
        vertices[15] = -width;

        vertices[1] = height;
        vertices[6] = -height;
        vertices[11] = -height;
        vertices[16] = height;

        array->GenIndexBuffer(indices, sizeof(indices));
        array->GetIndexBuffer()->Bind();

        array->GenVertexBuffer(vertices, sizeof(vertices));
        array->AddVertexLayout(0, 0, 3);
        array->AddVertexLayout(1, 3, 2);
        array->GetVertexBuffer()->Bind();

        isInitialized = true;
    }

    void Sprite::SetSize(float width, float height)
    {
        // Same as old
        if (this->width == width && this->height == height)
            return;

        this->width = width;
        this->height = height;

        // Take the new sizes into account
        vertices[0] = width;
        vertices[5] = width;
        vertices[10] = -width;
        vertices[15] = -width;

        vertices[1] = height;
        vertices[6] = -height;
        vertices[11] = -height;
        vertices[16] = height;

        if (isInitialized)
        {
            array->GetVertexBuffer()->Destroy();
            array->GenVertexBuffer(vertices, sizeof(vertices));
            array->AddVertexLayout(0, 0, 3);
            array->AddVertexLayout(1, 3, 2);
            array->GetVertexBuffer()->Bind();
        }
    }

    void Sprite::Render(Transform *bounds)
    {
        if (!isInitialized)
        {
            CE_WARN("Calling render without calling Init. Did you call the sprite's Init method?");
            return;
        }

        if (array == nullptr || bounds == nullptr)
            return;

        ViewAbility *view = Renderer::GetViewAbility();

        // Dont render the sprite if not in bounds
        // DONE: Replace 100 with width / height
        if (view->x - this->width > bounds->position.x || view->Width + this->width < bounds->position.x ||
            view->y - this->height > bounds->position.y || view->height + this->height < bounds->position.y)
            return;

        material->Use();

        array->Bind();
        array->DrawIndex();

        material->PostUse();
    }

    void Sprite::Update()
    {
    }
}