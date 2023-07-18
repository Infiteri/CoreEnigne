#pragma once

#include "Core/Base.h"

namespace Core
{

    /// @brief Structure that defines the application configuration, used by the engine to setup window.
    struct ApplicationConfiguration
    {
        bool StartMaximized = false;

        /// @brief The start window position X.
        int x = 100.0f;

        /// @brief The start window position Y.
        int y = 100.0f;

        /// @brief The start window Width.
        int width = 1024.0f;

        /// @brief The start window Height.
        int height = 576.0f;

        /// @brief The start window title
        const char *title = "DEFAULT TITLE";
    };

    /// @brief Class that should be inherited by the user.
    class CE_API Application
    {
    protected:
        ApplicationConfiguration p_Configuration;

    public:
        Application();
        ~Application();

        /// @brief Used only for setting up the p_Configuration for the application configuration.
        virtual void OnPreInit();

        /// @brief Used for setting up the layers.
        virtual void OnInit();

        /// @brief Any wanted updating code, if needed.
        virtual void OnRun();

        /// @brief Any wanted shutdown code, if needed.
        virtual void OnShutdown();

        ApplicationConfiguration *GetConfiguration() { return &p_Configuration; };
    };

    Application *CreateApplication();
}