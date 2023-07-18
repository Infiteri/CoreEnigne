#pragma once

#include "Core/Base.h"

#include "Vector3.h"
#include "Matrix4.h"

namespace Core
{
    class CE_API Transform
    {
    public:
        Vector3 *position;
        Vector3* rotation;
        Vector3* scale;

        Transform();
        ~Transform();

        Matrix4 *GetTransformMatrix();
    };
}
