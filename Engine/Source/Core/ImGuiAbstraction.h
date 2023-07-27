#pragma once

#include "Base.h"

namespace Core
{
    class CE_API ImGuiAbstraction
    {
    public:
        ImGuiAbstraction();
        ~ImGuiAbstraction();

        static void Begin();
        static void PreRender();
        static void PostRender();
        static void End();

        static void SetDarkThemeColors();

        static void SetupDockSpace();
    };
}
