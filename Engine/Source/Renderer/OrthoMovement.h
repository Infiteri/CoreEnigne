#pragma once

#include "OrthographicCamera.h"

#include "Core/Base.h"

namespace Core
{
    //? Orthographic Camera Movement
    class CE_API OrthoMovement
    {
    private:
        OrthographicCamera *camera;
        float speed;

    public:
        OrthoMovement(OrthographicCamera *target, float speed);
        ~OrthoMovement();

        void SetSpeed(float value);

        void Update();
    };
}