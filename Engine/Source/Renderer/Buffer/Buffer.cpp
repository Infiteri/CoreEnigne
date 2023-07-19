#include "Buffer.h"
#include "glad/glad.h"

namespace Core
{
    VertexBuffer::VertexBuffer(float *vertices, uint32_t size)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        stride = 0;
    }

    VertexBuffer::~VertexBuffer()
    {
        Unbind();
        Destroy();
    }

    void VertexBuffer::Destroy()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);

        for (BufferLayout l : layouts)
        {
            glVertexAttribPointer(l.location, l.size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (const void *)(l.offset * sizeof(float)));
            glEnableVertexAttribArray(l.location);
        }
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Draw()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3); // TODO: Stride
    }

    void VertexBuffer::AddLayout(int location, int offset, int size)
    {
        BufferLayout l;
        l.location = location;
        l.offset = offset;
        l.size = size;

        stride += size;

        this->layouts.push_back(l);
    }

    uint32_t VertexBuffer::GetID()
    {
        return id;
    }

    //? ------------------------------------------------
    //? - INDEX BUFFER ---------------------------------
    //? ------------------------------------------------

    IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t size)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        this->size = size;
    }

    IndexBuffer::~IndexBuffer()
    {
        Unbind();
        Destroy();
    }

    void IndexBuffer::Destroy()
    {
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Draw()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    uint32_t IndexBuffer::GetID()
    {
        return id;
    }

}