#pragma once

#include "Core/Base.h"
#include "Core/CEPCH.h"

namespace Core
{
    class CE_API FileSystem
    {
    public:
        FileSystem();
        ~FileSystem();

        static std::string Read(const char *path);
        static void Write(const char *path, const char *data);
        static void Create(const char *path);
        static void Destroy(const char *path);
    };
}