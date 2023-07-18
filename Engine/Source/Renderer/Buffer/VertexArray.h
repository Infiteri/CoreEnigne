#pragma once

#include "Core/Base.h"
#include "Buffer.h"
#include "stdint.h"

namespace Core
{
    class CE_API VertexArray
    {
    private:
        uint32_t id;
        VertexBuffer *vertexBuffer = nullptr;
        IndexBuffer *indexBuffer = nullptr;

    public:
        VertexArray();
        ~VertexArray();

        void Destroy();

        void Bind();

        void Unbind();

        void GenVertexBuffer(float *vertices, uint32_t size);
        void GenIndexBuffer(uint32_t *indices, uint32_t size);

        inline VertexBuffer *GetVertexBuffer() { return vertexBuffer; };
        inline IndexBuffer *GetIndexBuffer() { return indexBuffer; };

        void DrawIndex();

        void DrawVertex();

        void AddVertexLayout(int location, int offset, int size);

        uint32_t GetID();
    };

}