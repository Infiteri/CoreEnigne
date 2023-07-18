#pragma once

#include "Core/Base.h"
#include "Buffer/VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Core
{
    struct RendererState
    {
        Shader *mainShader;
        OrthographicCamera *camera;
        OrthographicCamera *currentCamera = nullptr;
    };

    class CE_API Renderer
    {
    public:
        Renderer(){};
        ~Renderer(){};

        /// @brief Main Setup, post window creation
        static void Init();
        static void Render();
        static void Shutdown();
        static void SetClearColor(int r, int g, int b, int a);

        static void Viewport(float width, float height);

        static inline void SubmitIndex(VertexArray *array)
        {
            array->Bind();
            array->DrawIndex();
        };

        static inline void SubmitVertex(VertexArray *array)
        {
            array->Bind();
            array->DrawVertex();
        };

   static     OrthographicCamera* GetCurrentCamera();
    };
}