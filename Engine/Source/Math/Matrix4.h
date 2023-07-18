#pragma once

#include "Core/Base.h"
#include "Vector3.h"

namespace Core
{
    class CE_API Matrix4
    {
    public:
        Matrix4()
        {
            data[0] = 1.0f;
            data[1] = 0.0f;
            data[2] = 0.0f;
            data[3] = 0.0f;
            data[4] = 0.0f;
            data[5] = 1.0f;
            data[6] = 0.0f;
            data[7] = 0.0f;
            data[8] = 0.0f;
            data[9] = 0.0f;
            data[10] = 1.0f;
            data[11] = 0.0f;
            data[12] = 0.0f;
            data[13] = 0.0f;
            data[14] = 0.0f;
            data[15] = 1.0f;
        };
        ~Matrix4(){};

        float data[4 * 4] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};

        static Matrix4 *Identity();
        static Matrix4 *Invert(Matrix4 *a);
        static Matrix4 *Translation(Vector3 *v);
        static Matrix4 *Scale(Vector3 *v);
        static Matrix4 *RotationXYZ(float rotationX, float rotationY, float rotationZ);
        static Matrix4 *RotationX(float rotation);
        static Matrix4 *RotationY(float rotation);
        static Matrix4 *RotationZ(float rotation);
        static Matrix4 *Multiply(Matrix4 *a, Matrix4 *b);
        static Matrix4 *Ortho(float left, float right, float top, float bottom, float near, float far);
        static Matrix4 *Perspective(float fov, float aspect, float near, float far);
        static Matrix4 *Empty();

        static Vector3 *Forward(Matrix4 *mat);
        static Vector3 *Right(Matrix4 *mat);

        static Vector3 *Backward(Matrix4 *mat);
        static Vector3 *Left(Matrix4 *mat);
    };
}
