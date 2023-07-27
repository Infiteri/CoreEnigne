#pragma once

#include "Base.h"


namespace Core
{
    /// @brief Every logging case possible.
    enum class LoggingLevel
    {
        /// @brief Simple info message, shows that something was successful.
        Info,

        /// @brief Warn message, alerts that something might have gone wrong.
        Warn,

        /// @brief Error message, alerts that something went very wrong, application can somewhat continue.
        Error,

        /// @brief Fatal message, when something goes very wrong, application cannot continue normally;
        Fatal,

        /// @brief Debug message, message used for debugging that something is correct, outputting data.
        Debug,

        /// @brief Trace message, just like debug, is used for outputting data and the fact that a function has been called or condition met.
        Trace
    };

    class CE_API Logger
    {
    public:
        Logger(){};
        ~Logger(){};

        static void Init();
        static void Log(LoggingLevel level, const char *message, ...);
        static void Shutdown();
    };
}

#define CE_INFO(message, ...) Core::Logger::Log(Core::LoggingLevel::Info, message, ##__VA_ARGS__)
#define CE_WARN(message, ...) Core::Logger::Log(Core::LoggingLevel::Warn, message, ##__VA_ARGS__)
#define CE_ERROR(message, ...) Core::Logger::Log(Core::LoggingLevel::Error, message, ##__VA_ARGS__)
#define CE_FATAL(message, ...) Core::Logger::Log(Core::LoggingLevel::Fatal, message, ##__VA_ARGS__)
#define CE_DEBUG(message, ...) Core::Logger::Log(Core::LoggingLevel::Debug, message, ##__VA_ARGS__)
#define CE_TRACE(message, ...) Core::Logger::Log(Core::LoggingLevel::Trace, message, ##__VA_ARGS__)
