#ifdef CORE_WINDOWS_PLATFORM

#include "Platform.h"
#include "Core/Engine.h"
#include "stdio.h"
#include "string.h"
#include <tchar.h>

#include "Shlwapi.h"
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

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

    std::string Platform::OpenFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::Get()->GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;

        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }

    std::string Platform::SaveFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        CHAR currentDir[256] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *)Engine::Get()->GetWindow()->GetHandle());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

        // Sets the default extension by extracting it from the filter
        ofn.lpstrDefExt = strchr(filter, '\0') + 1;

        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }

    std::vector<std::string> Platform::GetFilePathsInDirectory(const std::string &directoryPath)
    {
        std::vector<std::string> filePaths;

        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            return filePaths;
        }

        do
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                filePaths.push_back(directoryPath + "/" + findData.cFileName);
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);

        return filePaths;
    }

    std::vector<std::string> Platform::GetFolderPathsInDirectory(const std::string &directoryPath)
    {
        std::vector<std::string> folderNames;

        WIN32_FIND_DATA findData;
        HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            return folderNames;
        }

        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                std::string folderName = findData.cFileName;
                if (folderName != "." && folderName != "..")
                {
                    folderNames.push_back(folderName);
                }
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);

        return folderNames;
    }

    std::vector<DirectoryEntry> Platform::GetDirectoryEntries(const std::string &directoryPath)
    {
        std::vector<DirectoryEntry> paths;
        std::vector<std::string> filePaths = GetFilePathsInDirectory(directoryPath);
        std::vector<std::string> folderPaths = GetFolderPathsInDirectory(directoryPath);

        for (std::string fP : folderPaths)
        {
            DirectoryEntry p;
            p.path = fP;
            p.directory = true;

            paths.emplace_back(p);
        }

        for (std::string fP : filePaths)
        {
            DirectoryEntry p;
            p.path = fP;
            p.directory = false;

            paths.emplace_back(p);
        }

        return paths;
    }

    DLLLibrary Platform::LoadDLL(const char *name)
    {
        DLLLibrary lib;
        lib.internal = malloc(sizeof(DLLLibraryWin32Internal));
        DLLLibraryWin32Internal *state = (DLLLibraryWin32Internal *)lib.internal;

        HMODULE dllHandle = LoadLibrary(name);
        state->hModule = dllHandle;

        if (dllHandle == nullptr)
        {
            CE_FATAL("Unable to load library: %s", name);
            return lib;
        }

        return lib;
    }

    void Platform::UnloadDLL(DLLLibrary *lib)
    {
        DLLLibraryWin32Internal *internal = (DLLLibraryWin32Internal *)lib->internal;
        FreeLibrary(internal->hModule);
    }
}

#endif