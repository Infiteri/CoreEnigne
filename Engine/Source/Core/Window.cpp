#include "Window.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
    Window::Window(ApplicationConfiguration *configuration)
    {
        // State
        x = configuration->x;
        y = configuration->y;
        width = configuration->width;
        height = configuration->height;
        title = configuration->title;

        // Setup
        glfwInit();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        handle = glfwCreateWindow(width, height, title, NULL, NULL);
        glfwMakeContextCurrent(handle);
        glfwSetWindowPos(handle, x, y);
        glfwSwapInterval(1); // TODO: Maybe configurable

        if (configuration->StartMaximized)
        {
            glfwMaximizeWindow(handle);
        }
        else
        {
            // Center the window
            GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *vidMode = glfwGetVideoMode(primaryMonitor);

            int xPos = (vidMode->width - width) / 2;
            int yPos = (vidMode->height - height) / 2;

            glfwSetWindowPos(handle, xPos, yPos);
        }

        glfwGetWindowSize(handle, &width, &height);

        // Bind window events
        glfwSetKeyCallback(handle, [](GLFWwindow *w, int keycode, int scancode, int action, int mods)
                           { InputOnKeyEv(((InputKey)keycode), action == GLFW_PRESS || action == GLFW_REPEAT); });

        glfwSetMouseButtonCallback(handle, [](GLFWwindow *w, int button, int action, int mods)
                                   { bool pressed = action == GLFW_PRESS || action == GLFW_REPEAT;  InputOnMouseClickEv((InputMouseButton)button, pressed); });

        glfwSetWindowSizeCallback(handle, [](GLFWwindow *w, int width, int height)
                                  { Renderer::Viewport(width, height); });

        // Load glad
        glfwShowWindow(handle);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    Window::~Window()
    {
    }

    bool Window::ShouldUpdate()
    {
        return !glfwWindowShouldClose(handle);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(handle);

        double x, y;
        glfwGetCursorPos(handle, &x, &y);
        InputUpdateMouse((int)x, (int)y);

        glfwGetWindowSize(handle, &width, &height);
    }

    float Window::GetWidth()
    {
        return (float)width;
    }

    float Window::GetHeight()
    {
        return (float)height;
    }

    GLFWwindow *Window::GetHandle()
    {
        return handle;
    }
} // namespace Core