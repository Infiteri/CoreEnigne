#pragma once

#include "Core/Base.h"
#include <string>

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
    };
}