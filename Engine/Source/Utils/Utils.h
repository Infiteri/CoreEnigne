#pragma once

#include "Core/Base.h"
#include "string"

namespace Core
{
    namespace Utils
    {
        CE_API std::string GetFileExtension(const std::string &filePath);
        CE_API std::string GetFileNameNoExtension(const std::string &filePath);
        CE_API bool FileHasExtension(const std::string &filePath, const char *ext);
    }
}