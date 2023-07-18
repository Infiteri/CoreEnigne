#pragma once

#include "Core/Base.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace Core
{
    class CE_API OrthographicCamera
    {
    private:
        Vector3 position{0.0f, 0.0f, 0.0f};

        Matrix4 *projection;
        Matrix4 *view;

        float zNear;
        float zFar;
        float zoom = 1;

    public:
        OrthographicCamera(float width, float height, float zNear, float zFar);
        ~OrthographicCamera();

        void UpdateView();
        void UpdateProjection(float width, float height);

        Vector3 *GetPosition() { return &position; };
        Matrix4 *GetProjection() { return projection; };

        /// @brief Use GetInvertedView when uploading
        Matrix4 *GetView() { return view; };

        Matrix4 *GetInvertedView() { return Matrix4::Invert(view); };

        inline float GetZoom() {return zoom;};
        void SetZoom(float value);
        void AddZoom(float value);
    };
}
