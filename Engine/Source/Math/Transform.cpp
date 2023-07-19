#include "Transform.h"

namespace Core
{
    Transform::Transform()
    {
    }

    Transform::~Transform()
    {
    }

    Matrix4 *Transform::GetTransformMatrix()
    {
        Matrix4 *translation = Matrix4::Translation(&position);
        Matrix4 *rot = Matrix4::RotationXYZ(rotation.x, rotation.y, rotation.z);
        Matrix4 *scaling = Matrix4::Scale(&scale);

        return Matrix4::Multiply(Matrix4::Multiply(translation, rot), scaling);
    }
}