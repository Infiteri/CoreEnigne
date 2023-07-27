#include "Input.h"
#include "Logger.h"
#include "CEPCH.h"
#include "Engine.h"

namespace Core
{
    /// @brief Current keyboard state
    static std::unordered_map<InputKey, bool> keys;

    /// @brief Current mouse state
    static std::unordered_map<InputMouseButton, bool> buttons;

    static InputMouseMode lastFrameMode = InputMouseMode::Visible;

    struct InputMouseState
    {
        float x;
        float y;

        float lastX;
        float lastY;

        float deltaX;
        float deltaY;

        InputMouseMode mode;

        bool isMoving = false;
    };

    static InputMouseState MouseState;

    void Input::Init()
    {
    }

    void Input::Shutdown()
    {
    }

    bool Input::GetKey(InputKey key)
    {
        return keys[key] != false;
    }

    bool Input::GetMouseButton(InputMouseButton button)
    {
        return buttons[button] != false;
    }

    MouseVector Input::GetMousePos()
    {
        return {MouseState.x, MouseState.y};
    }

    MouseVector Input::GetMouseDelta()
    {
        return {MouseState.deltaX, MouseState.deltaY};
    }

    void Input::SetMouseMode(InputMouseMode mode)
    {
        MouseState.mode = mode;
    }

    void Input::Update()
    {
        if (lastFrameMode != MouseState.mode)
        {
            lastFrameMode = MouseState.mode;
            GLFWwindow *window = Engine::Get()->GetWindow()->GetHandle();

            int glfwMouseMode = 0;

            switch (MouseState.mode)
            {
            case InputMouseMode::Visible:
                glfwMouseMode = GLFW_CURSOR_NORMAL;
                break;

            case InputMouseMode::Hidden:
                glfwMouseMode = GLFW_CURSOR_HIDDEN;
                break;

            case InputMouseMode::Captured:
                glfwMouseMode = GLFW_CURSOR_DISABLED;
                break;
            }

            glfwSetInputMode(window, GLFW_CURSOR, glfwMouseMode);
        }

        if (MouseState.lastX != MouseState.x || MouseState.lastY != MouseState.y)
            MouseState.isMoving = true;
        else
            MouseState.isMoving = false;
    }

    bool Input::IsMouseMoving()
    {
        return MouseState.isMoving;
     }

    void InputOnKeyEv(InputKey key, bool pressed)
    {
        keys[key] = pressed;
    }

    void InputOnMouseClickEv(InputMouseButton button, bool pressed)
    {
        buttons[button] = pressed;
    }

    void InputUpdateMouse(int x, int y)
    {
        MouseState.deltaX = x - MouseState.lastX;
        MouseState.deltaY = y - MouseState.lastY;

        MouseState.lastX = MouseState.x;
        MouseState.lastY = MouseState.y;

        MouseState.x = (float)x;
        MouseState.y = (float)y;
    }
}