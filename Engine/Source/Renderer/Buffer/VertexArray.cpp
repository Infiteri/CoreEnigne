#include "VertexArray.h"
#include "glad/glad.h"

namespace Core
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }

    VertexArray::~VertexArray()
    {
        Unbind();
        Destroy();
    }

    void VertexArray::Destroy()
    {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::GenVertexBuffer(float *vertices, uint32_t size)
    {
        vertexBuffer = new VertexBuffer(vertices, size);
    }

    void VertexArray::GenIndexBuffer(uint32_t *indices, uint32_t size)
    {
        indexBuffer = new IndexBuffer(indices, size);
    }

    void VertexArray::DrawIndex()
    {
        if (indexBuffer == nullptr)
            return;

        indexBuffer->Draw();
    }

    void VertexArray::DrawVertex()
    {
        if (vertexBuffer == nullptr)
            return;

        vertexBuffer->Bind();
        vertexBuffer->Draw();
    }

    void VertexArray::AddVertexLayout(int location, int offset, int size)
    {
        vertexBuffer->AddLayout(location, offset, size);
    }

    uint32_t VertexArray::GetID()
    {
        return id;
    }
}