#pragma once

#include "Core/Base.h"
#include "Color.h"
#include "Texture.h"

namespace Core
{
    class CE_API Material
    {
    private:
        Color *color;
        Texture *texture;

    public:
        Material();
        ~Material();

        void Use();

        void PostUse();

        inline Color *GetColor() { return color; };
        inline Texture *GetTexture() { return texture; };
    };
}