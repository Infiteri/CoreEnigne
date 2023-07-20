#pragma once

#include "Core/Base.h"

namespace Core
{

    /// @brief Structure that defines the application configuration, used by the engine to setup window.
    struct ApplicationConfiguration
    {

        /// @brief The start window position X.
        int x = 100;

        /// @brief The start window position Y.
        int y = 100;

        /// @brief The start window Width.
        int width = 1024;

        /// @brief The start window Height.
        int height = 576;

        /// @brief The start window title
        const char *title = "DEFAULT TITLE";

        /// @brief If the window should be maximized, Width and height are not taken into account if set to true.
        bool StartMaximized = false;
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