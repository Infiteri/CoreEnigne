#pragma once

#include "Core/Base.h"
#include "Core/CEPCH.h"

namespace Core
{
    class CE_API Shader
    {
    private:
        uint32_t id;

    public:
        Shader(const std::string &vertexSource, const std::string &fragSource);
        ~Shader();

        void Destroy();

        void Use();
        void Detach();

        uint32_t GetUniformLocation(const char *name);
        void Mat4(const char *name, float *data);

        uint32_t GetID();
    };
}