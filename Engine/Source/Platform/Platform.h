#pragma once

#include "Core/Base.h"
#include "Core/Logger.h"

#include <string>
#include "vector"

#ifdef CORE_WINDOWS_PLATFORM
#include <windows.h>
#endif

namespace Core
{
    /// @brief Enum of all console colors that the platform supports
    enum class PlatformConsoleColor
    {
        /// @brief Represents the color white.
        White,

        /// @brief Represents the color green.
        Green,

        /// @brief Represents the color yellow.
        Yellow,

        /// @brief Represents the color red.
        Red,

        /// @brief Represents the color red used for fatal errors.
        FatalRed,

        /// @brief Represents the color blue.
        Blue,

        /// @brief Represents the color gray.
        Gray,
    };

    struct FileHandle
    {
        void *internal;
        const char *name;
    };

#ifdef CORE_WINDOWS_PLATFORM
    struct Win32FileHandleInternal
    {
        HANDLE handle;
    };
#endif

    struct DirectoryEntry
    {
        std::string path;
        bool directory;
    };

    struct DLLLibrary
    {
        void *internal;
    };

#ifdef CORE_WINDOWS_PLATFORM
    struct DLLLibraryWin32Internal
    {
        HMODULE hModule;
    };
#endif

    class CE_API Platform
    {
    public:
        Platform();
        ~Platform();

        /// @brief Sets the color of the text of console.
        /// @param color The color to use.
        static void SetConsoleColor(PlatformConsoleColor color);

        /// @brief Creates a file handle, creates the actual file and allows for writing to it.
        /// @param name The file name;
        /// @return A file handle struct object.
        static FileHandle CreateFileHandle(const char *name);
        static void OpenFileHandle(FileHandle *handle);
        static void WriteToHandle(FileHandle *handle, const char *data, ...);
        static void CloseFileHandle(FileHandle *handle);
        static void DeleteFileFromHandle(FileHandle *handle);

        static std::string OpenFile(const char *filter);
        static std::string SaveFile(const char *filter);

        static std::vector<std::string> GetFilePathsInDirectory(const std::string &directoryPath);
        static std::vector<std::string> GetFolderPathsInDirectory(const std::string &directoryPath);
        static std::vector<DirectoryEntry> GetDirectoryEntries(const std::string &directoryPath);

        static DLLLibrary LoadDLL(const char *name);
        static void UnloadDLL(DLLLibrary *lib);

        template <typename T>
        static T *LoadClass(const char *loadProc, DLLLibrary *lib)
        {
#ifdef CORE_WINDOWS_PLATFORM
            DLLLibraryWin32Internal *internal = (DLLLibraryWin32Internal *)lib->internal;

            if (internal->hModule == nullptr)
            {
                CE_FATAL("Library not loaded!");
                return nullptr;
            }

            using CreateClass = T *(*)();

            CreateClass createClass = (CreateClass)GetProcAddress(internal->hModule, loadProc);

            if (createClass == nullptr)
            {
                CE_ERROR("Create class handle reject: %s", loadProc);
                return nullptr;
            }

            T *inst = createClass();

            if (inst == nullptr)
            {
                CE_ERROR("Class instance not valid.");
                return nullptr;
            }

            return inst;
#endif
        };
    };
}