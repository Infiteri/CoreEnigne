#include "Utils.h"

#include <stdarg.h>
#include <stdio.h>

// Max size of a string buffer when formatting
#define STRING_FORMAT_MAX_BUFFER 32000

namespace Core
{
    std::string Utils::GetFileExtension(const std::string &filePath)
    {
        size_t dotPos = filePath.find_last_of('.');
        if (dotPos != std::string::npos && dotPos < filePath.length() - 1)
        {
            return filePath.substr(dotPos + 1);
        }

        return "";
    }

    std::string Utils::GetFileNameNoExtension(const std::string &filePath)
    {
        size_t lastSeparatorIndex = filePath.find_last_of("/\\");

        if (lastSeparatorIndex == std::string::npos)
        {
            return filePath;
        }

        return filePath.substr(lastSeparatorIndex + 1, filePath.find_last_of('.') - lastSeparatorIndex - 1);
    }

    bool Utils::FileHasExtension(const std::string &filePath, const char *ext)
    {
        return GetFileExtension(filePath).compare(ext) == 0;
    }
}