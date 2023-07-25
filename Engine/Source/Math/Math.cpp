#include "Math.h"
#include "Core/CEPCH.h"
#include "Core/Logger.h"

namespace Core
{
    namespace Math
    {
        float Sqrt(float num)
        {
            return sqrtf(num);
        }

        float Abs(float num)
        {
            return fabsf(num);
        }

        void DecomposeTransform(Matrix4 *m, Vector3 *translation, Vector3 *rotation, Vector3 *scale)
        {
            DecomposeTransform(m->data, translation, rotation, scale);
        }

        void DecomposeTransform(float *data, Vector3 *translation, Vector3 *rotation, Vector3 *scale)
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

        float Lerp(float start, float end, float t)
        {
            return start + t * (end - start);
        }

        void DecomposePosition(float *data, Vector3 *out)
        {
            out->x = data[12];
            out->y = data[13];
            out->z = data[14];
        }

        void DecomposeRotation(float *data, Vector3 *out)
        {
            float m00 = data[0];
            float m01 = data[1];
            float m02 = data[2];
            float m10 = data[4];
            float m11 = data[5];
            float m12 = data[6];
            float m20 = data[8];
            float m21 = data[9];
            float m22 = data[10];

            // Calculate the scaling factors
            float scaleX = Sqrt(m00 * m00 + m01 * m01 + m02 * m02);
            float scaleY = Sqrt(m10 * m10 + m11 * m11 + m12 * m12);
            float scaleZ = Sqrt(m20 * m20 + m21 * m21 + m22 * m22);

            // Remove scaling from the matrix to extract the rotation part
            m00 /= scaleX;
            m01 /= scaleX;
            m02 /= scaleX;

            m10 /= scaleY;
            m11 /= scaleY;
            m12 /= scaleY;

            m20 /= scaleZ;
            m21 /= scaleZ;
            m22 /= scaleZ;

            // Calculate rotation angles using the extracted rotation matrix
            float angleX = atan2f(m12, m22);
            float angleY = atan2f(-m02, sqrtf(m00 * m00 + m01 * m01));
            float angleZ = atan2f(m01, m00);

            // Convert angles from radians to degrees if desired
            const float radiansToDegrees = 180.0f / 3.14159265358979323846f;
            angleX *= radiansToDegrees;
            angleY *= radiansToDegrees;
            angleZ *= radiansToDegrees;

            out->x = angleX;
            out->y = angleY;
            out->z = angleZ;
        }

        void DecomposeScale(float *data, Vector3 *out, float rZ)
        {
            float m00 = cosf(rZ);
            float m01 = -sinf(rZ);
            float m10 = sinf(rZ);
            float m11 = cosf(rZ);

            // Calculate the scaling factors
            float scaleX = Sqrt(data[0] * data[0] + data[1] * data[1]);
            float scaleY = Sqrt(data[4] * data[4] + data[5] * data[5]);

            out->x = scaleX;
            out->y = scaleY;
        }
    }
}