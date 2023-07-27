#include "OrthoMovement.h"
#include "Core/Input.h"
#include "Core/Engine.h"
#include "Core/Logger.h"

namespace Core
{
    OrthoMovement::OrthoMovement(OrthographicCamera *target, float speed)
    {
        camera = target;
        this->speed = speed;
    }

    OrthoMovement::~OrthoMovement()
    {
    }

    void OrthoMovement::SetSpeed(float value)
    {
        speed = value;
    }

    void OrthoMovement::Update()
    {
        if (camera == nullptr)
            return;

        if (Input::GetKey(InputKey::Up))
        {
            camera->GetPosition()->y -= speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::Down))
        {
            camera->GetPosition()->y += speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::Left))
        {
            camera->GetPosition()->x -= speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::Right))
        {
            camera->GetPosition()->x += speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::KP_Add))
        {
            camera->AddZoom(zoomSpeed);
            camera->UpdateProjection();
        }

        if (Input::GetKey(InputKey::KP_Subtract))
        {
            if (camera->GetZoom() > 0.025f)
            {
                camera->AddZoom(-zoomSpeed);
                camera->UpdateProjection();
            }
        }

        // WIP
        //  if (Input::GetMouseButton(InputMouseButton::Right))
        //  {
        //      Input::SetMouseMode(InputMouseMode::Captured);

        //     MouseVector vec = Input::GetMouseDelta();

        //     camera->GetPosition()->x += vec.x / 50;
        //     camera->GetPosition()->y += vec.y / 50;

        //     camera->UpdateView();
        // }
        // else
        // {
        //     Input::SetMouseMode(InputMouseMode::Visible);
        // }
    }
}