#pragma once

#include "Core/Engine.h"
#include "Math/Transform.h"
#include "Renderer/Objects/Sprite.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Particle/Particle.h"

namespace Core
{
#define CE_COMPONENT_TYPE(component) \
    bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(component); }

    class Entity;

    struct Component
    {
        Entity *parent;

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

    struct ParticleEmitterComponent : public Component
    {
        ParticleProprieties props;

        float amountPerFrame = 1.0f;

        ParticleEmitterComponent(){};

        bool IsType(const std::type_info &typeInfo) const override { return typeInfo == typeid(ParticleEmitterComponent); }
    };
}
