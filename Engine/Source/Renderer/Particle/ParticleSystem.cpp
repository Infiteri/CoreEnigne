#include "ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Core/Engine.h"
#include "Math/Math.h"
#include "Core/Logger.h"

namespace Core
{
    std::vector<Particle *> particlePool;
    uint32_t maxSize = 1000;

    void ParticleSystem::Init()
    {
    }

    void ParticleSystem::Emit(const ParticleProprieties &props)
    {
        if (particlePool.size() >= maxSize)
        {
            CE_WARN("Too many particles");
            return;
        }

        Particle *p = new Particle();

        p->UseProps(props);
        p->active = true;

        particlePool.push_back(p);
    }

    void ParticleSystem::Render()
    {
        // Updating the particles
        for (auto it = particlePool.begin(); it != particlePool.end();)
        {
            auto &particle = *it;

            if (!particle->active)
            {
                // If the particle is not active, remove it from the pool.
                it = particlePool.erase(it);
                continue;
            }

            if (!particle->GetLifeTime())
            {
                // If the particle has no lifetime, skip to the next one.
                ++it;
                continue;
            }

            if (particle->lifeRemaining <= 0.0f)
            {
                // If the particle's life has ended, remove it from the pool.
                it = particlePool.erase(it);
                continue;
            }

            particle->lifeRemaining -= 0.016f;
            particle->transform.position.x += particle->velocity.x;
            particle->transform.position.y += particle->velocity.y;
            particle->transform.rotation.z += 0.1f * Engine::Get()->GetDelta();

            // Move to the next particle in the pool.
            ++it;
        }

        // Rendering
        for (auto &particle : particlePool)
        {
            if (!particle->active)
                continue;

            if (!particle->IsInit())
                particle->Init();

            // Work
            float life = particle->lifeRemaining / particle->lifeTime;
            float alpha = Math::Lerp(0, particle->colorBegin.a, life);

            Color color{
                Math::Lerp(particle->colorEnd.r, particle->colorBegin.r, life),
                Math::Lerp(particle->colorEnd.g, particle->colorBegin.g, life),
                Math::Lerp(particle->colorEnd.b, particle->colorBegin.b, life),
                alpha};

            particle->material.GetColor()->Set(color.r, color.g, color.b, color.a);

            auto originalTransform = particle->GetTransform();
            Transform *newTransform = new Transform();
            newTransform->position.x = originalTransform->position.x + particle->positionOffset.x;
            newTransform->position.y = originalTransform->position.y + particle->positionOffset.y;
            newTransform->position.z = 0;

            Renderer::UseTransform(newTransform);
            particle->Render();
        }
    }
}