#pragma once

#include "Core/Base.h"
#include "stdint.h"

namespace Core
{
    class CE_API Texture
    {
    private:
        int width;
        int height;
        int channels;

        uint32_t id;
        uint32_t generation;

    public:
        Texture();
        ~Texture();

        void FromPath(const char *path);
        void Swap(const char *path);

        void Bind();
        void Unbind();
        void Destroy();
        void Use();

        inline uint32_t GetWidth() { return width; };
        inline uint32_t GetHeight() { return height; };

        uint32_t GetID();
        uint32_t GetGeneration();
    };
}