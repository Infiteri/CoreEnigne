#pragma once

#include "Core/Base.h"
#include "Color.h"

namespace Core
{
    class CE_API Material
    {
    private:
        Color *color;

    public:
        Material();
        ~Material();

        void Use();

        void PostUse();

        inline Color *GetColor() { return color; };
    };
}