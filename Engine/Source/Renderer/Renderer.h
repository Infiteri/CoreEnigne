#pragma once

#include "Core/Base.h"
#include "Math/Transform.h"
#include "Math/Vector4.h"
#include "Buffer/VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "FrameBuffer.h"

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
        FrameBuffer *fBuffer;
        Vector4 colorValues{0, 0, 0, 0};
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

        static void BeginFrame();
        static void EndFrame();

        static void Viewport(float width, float height);
        static void Clear();

        static void SetCurrentCamera(OrthographicCamera* newCamera);
        static void SetCurrentCameraDefault();

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
        static FrameBuffer *GetFrameBuffer();
    };
}