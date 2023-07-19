#pragma once

#include "Core/Base.h"

namespace Core
{
    class CE_API Color
    {
    private:
    public:
        Color(float r, float g, float b, float a);
        ~Color(){};

        float r;
        float g;
        float b;
        float a;
        float GetR() { return r; };
        float GetRNormalized() { return r / 255; };

        float GetG() { return g; };
        float GetGNormalized() { return g / 255; };

        float GetB() { return b; };
        float GetBNormalized() { return b / 255; };

        float GetA() { return a; };
        float GetANormalized() { return a / 255; };

        void Set(float r, float g, float b, float a);
    };

}