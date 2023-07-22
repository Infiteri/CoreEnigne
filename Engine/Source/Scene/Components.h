#pragma once

#include "Core/Engine.h"
#include "Math/Transform.h"
#include "Renderer/Objects/Sprite.h"
#include "Renderer/OrthographicCamera.h"

namespace Core
{
#define CE_COMPONENT_TYPE(component) \
    bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(component); }

    struct Component
    {
        virtual ~Component() {}
        virtual bool IsType(const std::type_info &typeInfo) const
        {
            return false;
        }
    };

    struct TransformComponent : public Component
    {
        Transform transform;

        TransformComponent(){};

        bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(TransformComponent); }
    };

    struct SpriteComponent : public Component
    {
        Sprite sprite;

        SpriteComponent(){};

        bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(SpriteComponent); }
    };

    struct CameraComponent : public Component
    {
        OrthographicCamera camera;

        CameraComponent() : camera(Engine::Get()->GetWindow()->GetWidth(), Engine::Get()->GetWindow()->GetHeight(), -100.0f, 100.0f){};

        bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(CameraComponent); }
    };
}
