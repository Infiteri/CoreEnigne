#include "Logger.h"
#include "Utils/Utils.h"
#include "Platform/Platform.h"
#include "Platform/FileSystem.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace Core
{
    static bool isInitialized = false;

    void Logger::Init()
    {
        if (isInitialized)
        {
            return;  
        }

        // Set the flag for initialized to true;
        isInitialized = true;

        // WIP: Create console.log file
        FileSystem::Create("Console.log");
    }

    void Logger::Log(LoggingLevel level, const char *message, ...)
    {
        if (!isInitialized)
            return;

        const char *Levels[6] = {"[INFO]:  ", "[WARN]:  ", "[ERROR]: ", "[FATAL]: ", "[DEBUG]: ", "[TRACE]: "};

        char OutMessage[32000];
        memset(OutMessage, 0, 32000);

        __builtin_va_list ArgPtr;
        va_start(ArgPtr, message);
        vsnprintf(OutMessage, 32000, message, ArgPtr);
        va_end(ArgPtr);

        // Set console color based on logging level
        PlatformConsoleColor color = PlatformConsoleColor::White;
        switch (level)
        {
        case LoggingLevel::Info:
            color = CE_LOG_INFO_COLOR;
            break;
        case LoggingLevel::Warn:
            color = CE_LOG_WARN_COLOR;
            break;
        case LoggingLevel::Error:
            color = CE_LOG_RED_COLOR;
            break;
        case LoggingLevel::Fatal:
            color = CE_LOG_FATAL_RED_COLOR;
            break;
        case LoggingLevel::Debug:
            color = CE_LOG_DEBUG_COLOR;
            break;
        case LoggingLevel::Trace:
            color = CE_LOG_TRACE_COLOR;
            break;
        }

        Platform::SetConsoleColor(color);
        FileSystem::Write("Console.log", OutMessage);

        printf("%s %s\n", Levels[(int)level], OutMessage);
    }

    void Logger::Shutdown()
    {
        isInitialized = false;
    }

}