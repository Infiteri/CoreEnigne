#pragma once

#include "Core/Base.h"

namespace Core
{
    class CE_API Vector4
    {
    public:
        Vector4(float x, float y, float z, float w);
        ~Vector4(){};

        float x;
        float y;
        float z;
        float w;
    };
}
