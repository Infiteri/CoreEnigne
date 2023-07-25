#pragma once

#include "Core/Base.h"
#include "glfw/glfw3.h"

namespace Core
{
    /// @brief An enum of all the keys. Pleas keep in mind that K0, K1 ... K9 mean the keys at the top of the keyboard, while kP_0, KP_1, ... KP_Equal are the keypad keys.
    enum class InputKey
    {
        // Printable keys
        Space = GLFW_KEY_SPACE,
        Apostrophe = GLFW_KEY_APOSTROPHE,
        Comma = GLFW_KEY_COMMA,
        Minus = GLFW_KEY_MINUS,
        Period = GLFW_KEY_PERIOD,
        Slash = GLFW_KEY_SLASH,
        K0 = GLFW_KEY_0,
        k1 = GLFW_KEY_1,
        k2 = GLFW_KEY_2,
        k3 = GLFW_KEY_3,
        k4 = GLFW_KEY_4,
        k5 = GLFW_KEY_5,
        k6 = GLFW_KEY_6,
        k7 = GLFW_KEY_7,
        k8 = GLFW_KEY_8,
        k9 = GLFW_KEY_9,
        Semicolon = GLFW_KEY_SEMICOLON,
        Equal = GLFW_KEY_EQUAL,
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        LeftBracket = GLFW_KEY_LEFT_BRACKET,
        Backslash = GLFW_KEY_BACKSLASH,
        RightBracket = GLFW_KEY_RIGHT_BRACKET,
        GraveAccent = GLFW_KEY_GRAVE_ACCENT,
        World1 = GLFW_KEY_WORLD_1,
        World2 = GLFW_KEY_WORLD_2,

        // Function keys
        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        Tab = GLFW_KEY_TAB,
        Backspace = GLFW_KEY_BACKSPACE,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,
        Right = GLFW_KEY_RIGHT,
        Left = GLFW_KEY_LEFT,
        Down = GLFW_KEY_DOWN,
        Up = GLFW_KEY_UP,
        PageUp = GLFW_KEY_PAGE_UP,
        PageDown = GLFW_KEY_PAGE_DOWN,
        Home = GLFW_KEY_HOME,
        End = GLFW_KEY_END,
        CapsLock = GLFW_KEY_CAPS_LOCK,
        ScrollLock = GLFW_KEY_SCROLL_LOCK,
        NumLock = GLFW_KEY_NUM_LOCK,
        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,

        // Keypad keys
        KP_P0 = GLFW_KEY_KP_0,
        KP_P1 = GLFW_KEY_KP_1,
        KP_P2 = GLFW_KEY_KP_2,
        KP_P3 = GLFW_KEY_KP_3,
        KP_P4 = GLFW_KEY_KP_4,
        KP_P5 = GLFW_KEY_KP_5,
        KP_P6 = GLFW_KEY_KP_6,
        KP_P7 = GLFW_KEY_KP_7,
        KP_P8 = GLFW_KEY_KP_8,
        KP_P9 = GLFW_KEY_KP_9,
        KP_PDecimal = GLFW_KEY_KP_DECIMAL,
        KP_PDivide = GLFW_KEY_KP_DIVIDE,
        KP_PMultiply = GLFW_KEY_KP_MULTIPLY,
        KP_PSubtract = GLFW_KEY_KP_SUBTRACT,
        KP_PAdd = GLFW_KEY_KP_ADD,
        KP_PEnter = GLFW_KEY_KP_ENTER,
        KP_PEqual = GLFW_KEY_KP_EQUAL,

        // Modifier keys
        LeftShift = GLFW_KEY_LEFT_SHIFT,
        LeftControl = GLFW_KEY_LEFT_CONTROL,
        LeftAlt = GLFW_KEY_LEFT_ALT,
        LeftSuper = GLFW_KEY_LEFT_SUPER,
        RightShift = GLFW_KEY_RIGHT_SHIFT,
        RightControl = GLFW_KEY_RIGHT_CONTROL,
        RightAlt = GLFW_KEY_RIGHT_ALT,
        RightSuper = GLFW_KEY_RIGHT_SUPER,
        Menu = GLFW_KEY_MENU
    };

    /// @brief An enum that represents the mouse buttons.
    enum class InputMouseButton
    {
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Middle = GLFW_MOUSE_BUTTON_MIDDLE,
        Right = GLFW_MOUSE_BUTTON_RIGHT
    };

    enum class InputMouseMode
    {
        Visible,
        Hidden,
        Captured
    };

    /// @brief A mouse vector, separate of Vector2 because Vector2 has functionality that the mouse vector doesn't need.
    struct MouseVector
    {
        float x;
        float y;
    };

    class CE_API Input
    {
    public:
        Input(){};
        ~Input(){};

        static void Init();
        static void Shutdown();

        /// @brief Checks if a key is pressed or not.
        /// @param key The key to check.
        /// @return True if is pressed, otherwise false.
        static bool GetKey(InputKey key);

        /// @brief Checks if the passed in mouse button is pressed;
        /// @param button The button to check.
        /// @return True if is pressed, otherwise false.
        static bool GetMouseButton(InputMouseButton button);

        /// @brief Returns the current mouse position;
        /// @return A MouseVector struct with the x and y values set.
        static MouseVector GetMousePos();

        /// @brief Returns the current mouse delta;
        /// @return A MouseVector struct with the x and y values set.
        static MouseVector GetMouseDelta();

        /// @brief Sets the mouse mode. DO NOT CALL THIS FUNCTION IN THE OnPreInit INSIDE THE APPLICATION AS IT WILL NOT WORK.
        /// @param mode The mode.
        static void SetMouseMode(InputMouseMode mode);

        static void Update();

        static bool IsMouseMoving();
    };

    // Internal updating
    void InputOnKeyEv(InputKey key, bool pressed);

    void InputOnMouseClickEv(InputMouseButton button, bool pressed);

    void InputUpdateMouse(int x, int y);
}