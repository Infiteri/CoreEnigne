#pragma once

#include "Core/Base.h"
#include "Math/Transform.h"
#include "Buffer/VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Core
{

    /// @brief What the current camera is capable of seeing.
    struct ViewAbility
    {
        int x;
        int y;
        int Width;
        int height;
    };

    struct RendererState
    {
        Shader *mainShader;
        OrthographicCamera *camera;
        OrthographicCamera *currentCamera = nullptr;
        ViewAbility viewAbility;
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

        /// @brief Uses the passed in transform for the upcoming draw calls, changes once this function is called again with a different transform.
        /// @param transform The transform to use.
        static void UseTransform(Transform *transform);

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

        static OrthographicCamera *GetCurrentCamera();
        static Shader *GetColorShader();
        static ViewAbility *GetViewAbility();
    };
}