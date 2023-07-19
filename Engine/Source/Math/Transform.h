#pragma once

#include "Core/Base.h"

#include "Vector3.h"
#include "Matrix4.h"

namespace Core
{
    class CE_API Transform
    {
    public:
        Vector3 position{0.0f, 0.0f, 0.0f};
        Vector3 rotation{0.0f, 0.0f, 0.0f};
        Vector3 scale{1.0f, 1.0f, 1.0f};

        Transform();
        ~Transform();

        Matrix4 *GetTransformMatrix();
    };
}
