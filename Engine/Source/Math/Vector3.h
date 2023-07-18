#pragma once

#include "Core/Base.h"

namespace Core
{
    class CE_API Vector3
    {
    public:
        Vector3(float x, float y, float z);
        ~Vector3(){};

        float x;
        float y;
        float z;

        void Set(float x, float y, float z);
    };
}
