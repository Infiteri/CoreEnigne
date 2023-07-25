#include "Particle.h"

static float vertices[] = {
    100.0f, 100.0f, 0.0f, 1.0f, 1.0f,   // top right
    100.0f, -100.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -100.0f, -100.0f, 0.0f, 0.0f, 0.0f, // bottom left
    -100.0f, 100.0f, 0.0f, 0.0f, 1.0f   // top left
};
static unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};

namespace Core
{
    Particle::Particle()
    {
        parentTransform = new Transform();
        active = false;
    }

    Particle::Particle(const ParticleProprieties &props)
    {
        parentTransform = new Transform();
        UseProps(props);
        active = false;
    }

    Particle::~Particle()
    {
    }

    void Particle::UseProps(const ParticleProprieties &props)
    {
        transform = props.transform;
        velocity = props.velocity;
        colorBegin = props.colorBegin;
        colorEnd = props.colorEnd;
        lifeTime = props.lifeTime;
        positionOffset = props.positionOffset;

        lifeRemaining = lifeTime;
    }

    void Particle::Init()
    {
        if (isInitialized)
            return;

        array = new VertexArray();

        array->GenIndexBuffer(indices, sizeof(indices));
        array->GetIndexBuffer()->Bind();

        array->GenVertexBuffer(vertices, sizeof(vertices));
        array->AddVertexLayout(0, 0, 3);
        array->AddVertexLayout(1, 3, 2);
        array->GetVertexBuffer()->Bind();

        active = true;

        material.GetColor()->Set(colorBegin.r, colorBegin.g, colorBegin.b, colorBegin.a);

        isInitialized = true;
    }

    void Particle::Render()
    {
        material.Use();

        array->Bind();
        array->DrawIndex();

        material.PostUse();
    }
}