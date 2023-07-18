#include "FileSystem.h"

namespace Core
{
    std::string FileSystem::Read(const char *path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            // Handle file open error
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    void FileSystem::Write(const char *path, const char *data)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            return;
        }

        file << data << "\n";
        file.close();
    }

    void FileSystem::Create(const char *path)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            return;
        }

        file.close();
    }

    void FileSystem::Destroy(const char *path)
    {
        if (std::remove(path) != 0)
        {
            return;
        }
    }
}