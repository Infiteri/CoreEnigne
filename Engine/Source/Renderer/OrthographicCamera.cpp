#include "OrthographicCamera.h"

namespace Core
{
    OrthographicCamera::OrthographicCamera(float width, float height, float zNear, float zFar)
    {
        this->zNear = zNear;
        this->zFar = zFar;

        projection = Matrix4::Identity();
        view = Matrix4::Identity();

        UpdateProjection(width, height);
        UpdateView();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::UpdateView()
    {
        view = Matrix4::Translation(&position);
    }

    void OrthographicCamera::UpdateProjection(float width, float height)
    {
        projection = Matrix4::Ortho(0, width, 0, height, zNear, zFar);
    }
} 