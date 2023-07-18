#include "Math.h"
#include "Core/CEPCH.h"
#include "Core/Logger.h"

void Core::Math::DecomposeTransform(Matrix4 *m, Vector3 *translation, Vector3 *rotation, Vector3 *scale)
{
    DecomposeTransform(m->data, translation, rotation, scale);
}

void Core::Math::DecomposeTransform(float *data, Vector3 *translation, Vector3 *rotation, Vector3 *scale)
{
    translation->x = data[12];
    translation->y = data[13];
    translation->z = data[14];

    scale->x = data[0];
    data[0] = 1;
    scale->y = data[5];
    data[5] = 1;
    scale->z = data[10];
    data[10] = 1;


    // Extract rotation
    rotation->y = asin(data[8]);
    if (cos(rotation->y) != 0)
    {

        rotation->x = atan2(data[9], data[10]);
        rotation->z = atan2(data[4], data[0]);
    }
    else
    {
        rotation->x = atan2(-data[2], data[5]);
        rotation->z = 0;
    }
}
