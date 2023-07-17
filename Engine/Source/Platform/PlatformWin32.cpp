#ifdef CORE_WINDOWS_PLATFORM

#include "Platform.h"
#include "Core/Logger.h"
#include "stdio.h"
#include "string.h"

namespace Core
{
    void Platform::SetConsoleColor(PlatformConsoleColor color)
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (color)
        {
        case PlatformConsoleColor::White:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case PlatformConsoleColor::Green:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
            break;
        case PlatformConsoleColor::Yellow:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case PlatformConsoleColor::Red:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            break;
        case PlatformConsoleColor::FatalRed:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case PlatformConsoleColor::Blue:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE);
            break;
        case PlatformConsoleColor::Gray:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        }
    }

    FileHandle Platform::CreateFileHandle(const char *name)
    {
        FileHandle fh;
        fh.name = name;
        fh.internal = malloc(sizeof(Win32FileHandleInternal));
        Win32FileHandleInternal *state = (Win32FileHandleInternal *)fh.internal;

        state->handle = CreateFileA(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (state->handle == INVALID_HANDLE_VALUE)
        {
            CE_ERROR("Unable to create file: %s", name);
            return fh;
        }

        return fh;
    }

    void Platform::OpenFileHandle(FileHandle *handle)
    {
        Win32FileHandleInternal *state = (Win32FileHandleInternal *)handle->internal;
        state->handle = CreateFileA(handle->name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (state->handle == INVALID_HANDLE_VALUE)
        {
            CE_ERROR("Unable to create file: %s", handle->name);
            return;
        }
    }

    void Platform::WriteToHandle(FileHandle *handle, const char *data, ...)
    {
        Win32FileHandleInternal *state = (Win32FileHandleInternal *)handle->internal;

        DWORD bytesWritten;

        char OutMessage[32000];
        memset(OutMessage, 0, 32000);

        __builtin_va_list ArgPtr;
        va_start(ArgPtr, data);
        vsnprintf(OutMessage, 32000, data, ArgPtr);
        va_end(ArgPtr);

        WriteFile(state->handle, OutMessage, strlen(OutMessage), &bytesWritten, NULL);
    }

    void Platform::CloseFileHandle(FileHandle *handle)
    {
        Win32FileHandleInternal *state = (Win32FileHandleInternal *)handle->internal;
        CloseHandle(state->handle);
    }
}

#endif