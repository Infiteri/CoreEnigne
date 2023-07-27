#pragma once

#include "Core/Base.h"
#include "EntityScript.h"
#include "Scene/Entity.h"

namespace Core
{
    struct ScriptComponent;

    struct ScriptEngineConfiguration
    {
        const char *ProjectDLLFileName = "Game.dll";
    };

    class CE_API ScriptEngine
    {
    public:
        ScriptEngine(){};
        ~ScriptEngine(){};

        static void Init(const ScriptEngineConfiguration &config);

        static void Shutdown();

        static void Update();

        static void OnRuntimeStart();
        static void OnRuntimeUpdate();
        static void OnRuntimeStop();

        static void RegisterScriptComponent(ScriptComponent *component,Entity* parent);
    };
}