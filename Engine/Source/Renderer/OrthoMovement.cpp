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

        if (Input::GetKey(InputKey::W))
        {
            camera->GetPosition()->y -= speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::S))
        {
            camera->GetPosition()->y += speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::A))
        {
            camera->GetPosition()->x -= speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::D))
        {
            camera->GetPosition()->x += speed;
            camera->UpdateView();
        }

        if (Input::GetKey(InputKey::Q))
        {
            camera->AddZoom(0.025f);
            camera->UpdateProjection(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight());
        }

        if (Input::GetKey(InputKey::E))
        {
            if (camera->GetZoom() > 0.025f)
            {
                camera->AddZoom(-0.025f);
                camera->UpdateProjection(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight());
            }
        }

        if (Input::GetMouseButton(InputMouseButton::Right))
        {
            Input::SetMouseMode(InputMouseMode::Captured);

            MouseVector vec = Input::GetMouseDelta();

            camera->GetPosition()->x += vec.x / 50;
            camera->GetPosition()->y += vec.y / 50;

            camera->UpdateView();
        }
        else
        {
            Input::SetMouseMode(InputMouseMode::Visible);
        }
    }
}
