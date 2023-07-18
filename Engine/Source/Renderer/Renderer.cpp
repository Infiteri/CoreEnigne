#include "Renderer.h"
#include "glad/glad.h"

namespace Core
{
    void Renderer::Init()
    {
    }

    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::SetClearColor(int r, int g, int b, int a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer::Viewport(float width, float height)
    {
        glViewport(0, 0, width, height);

        // TODO: Camera state
    }
}