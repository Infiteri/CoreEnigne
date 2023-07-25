#pragma once

#include "Core/Base.h"

#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Color.h"
#include "Renderer/Material.h"
#include "Math/Transform.h"
#include "ParticleSystem.h"

namespace Core
{
    struct ParticleProprieties
    {
        Transform transform;
        Vector3 positionOffset{0.0f, 0.0f, 0.0f};

        Vector3 velocity{1.0f, 1.0f, 0.0f};

        Color colorBegin{255, 255, 255, 255};

        // Alpha doesn't matter
        Color colorEnd{0, 0, 0, 0};

        // In seconds
        float lifeTime = 1.0f;
    };

    class CE_API Particle
    {
    private:
        VertexArray *array;

        Transform transform;
        Transform *parentTransform;
        Vector3 velocity{1.0f, 1.0f, 0.0f};
        Vector3 positionOffset{0.0f, 0.0f, 0.0f};
        Color colorBegin{255, 255, 255, 255};
        Color colorEnd{0, 0, 0, 0};
        float lifeTime = 1.0f;
        float lifeRemaining = 1.0f;

        bool isInitialized = false;

        friend class ParticleSystem;

        Material material;
        bool active = false;

    public:
        Particle();
        Particle(const ParticleProprieties &props);
        ~Particle();

        void UseProps(const ParticleProprieties &props);

        void Init();

        void Render();

        // Getter for 'transform'
        Transform *GetTransform()
        {
            return &transform;
        }

        // Getter for 'velocity'
        Vector3 *GetVelocity()
        {
            return &velocity;
        }

        // Getter for 'colorBegin'
        Color *GetColorBegin()
        {
            return &colorBegin;
        }

        // Getter for 'colorEnd'
        Color *GetColorEnd()
        {
            return &colorEnd;
        }

        // Getter for 'lifeTime'
        float GetLifeTime() const
        {
            return lifeTime;
        }

        bool IsInit() { return isInitialized; };
    };
}