#pragma once

#include "Core/Base.h"
#include "Core/CEPCH.h"
#include "stdint.h"

namespace Core
{
    struct BufferLayout
    {
        int location;
        int offset;
        int size;
    };

    class CE_API VertexBuffer
    {
    private:
        uint32_t id;
        uint32_t stride;
        std::vector<BufferLayout> layouts;

    public:
        VertexBuffer(float *vertices, uint32_t size);
        ~VertexBuffer();

        void Destroy();

        void Bind();

        void Unbind();

        void Draw();

        void AddLayout(int location, int offset, int size);

        uint32_t GetID();
    };

    class CE_API IndexBuffer
    {

    private:
        uint32_t id;
        uint32_t size;

    public:
        IndexBuffer(uint32_t *indices, uint32_t size);
        ~IndexBuffer();

        void Destroy();

        void Bind();

        void Unbind();

        void Draw();

        uint32_t GetID();
    };
}