#pragma once

#include "Core/Base.h"
#include "Particle.h"

namespace Core
{
    struct ParticleProprieties;

    class CE_API ParticleSystem
    {
    public:
        ParticleSystem(){};
        ~ParticleSystem(){};

        static void Init();

        static void Emit(const ParticleProprieties &props);

        static void Render();
    };
}