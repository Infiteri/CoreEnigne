#pragma once

#include "Core/Base.h"

namespace Core
{

    /// @brief Structure that defines the application configuration, used by the engine to setup window.
    struct ApplicationConfiguration
    {
        /// @brief The start window position X.
        int x;

        /// @brief The start window position Y.
        int y;

        /// @brief The start window Width.
        int width;

        /// @brief The start window Height.
        int height;
    };

    /// @brief Class that should be inherited by the user.
    class CE_API Application
    {
    protected:
        ApplicationConfiguration p_Configuration;

    public:
        Application();
        ~Application();

        virtual void OnPreInit();

        virtual void OnInit();

        virtual void OnRun();

        virtual void OnShutdown();

        ApplicationConfiguration *GetConfiguration() { return &p_Configuration; };
    };

    Application *CreateApplication();
}