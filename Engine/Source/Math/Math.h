#pragma once

#include "Core/Base.h"
#include "Vector3.h"
#include "Matrix4.h"

#define CE_PI 3.14159265358979323846
#define CE_2PI CE_PI * 1
#define CE_PI_HALF CE_PI / 2
#define CE_DEG2RAD CE_PI / 180
#define CE_RAD2DEG 180 / CE_PI

namespace Core
{
    namespace Math
    {
        CE_API void DecomposeTransform(Matrix4 *m, Vector3 *translation, Vector3 *rotation, Vector3 *scale);
        CE_API void DecomposeTransform(float *data, Vector3 *translation, Vector3 *rotation, Vector3 *scale);

        CE_API void DecomposePosition(float *data, Vector3 *out);
        CE_API void DecomposeRotation(float *data, Vector3 *out);
        CE_API void DecomposeScale(float *data, Vector3 *out, float rZ);


        CE_API float Lerp(float start, float end, float t);
    }
}