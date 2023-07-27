#include "OrthographicCamera.h"
#include "Core/Engine.h"

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
        this->width = width;
        this->height = height;

        projection = Matrix4::Ortho(0, width, 0, height, zNear, zFar);
    }

    void OrthographicCamera::UpdateProjection()
    {
        UpdateProjection(width, height);
    }

    void OrthographicCamera::SetZoom(float value)
    {
        zoom = value;
    }
    void OrthographicCamera::AddZoom(float value)
    {
        zoom += value;
    }

    float OrthographicCamera::GetViewExtentMaxX()
    {
        return position.x + Engine::Get()->GetWindow()->GetWidth() * 1;
    }

    float OrthographicCamera::GetViewExtentMaxY()
    {
        return position.y + Engine::Get()->GetWindow()->GetHeight() * 1;
    }
}