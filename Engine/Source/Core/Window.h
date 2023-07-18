#pragma once

#include "Core/Base.h"
#include "Core/Application.h"

struct GLFWwindow;

namespace Core
{

    class CE_API Window
    {
    private:
        int x;
        int y;
        int width;
        int height;
        const char *title;

        GLFWwindow *handle;

    public:
        Window(ApplicationConfiguration *configuration);
        ~Window();

        bool ShouldUpdate();
        void Update();

        float GetWidth();
        float GetHeight();

        GLFWwindow *GetHandle();
    };
}