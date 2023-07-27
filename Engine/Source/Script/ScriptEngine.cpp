#include "ScriptEngine.h"

#include "Platform/Platform.h"

#include "Scene/Components.h"

#include "vector"

namespace Core
{
    static DLLLibrary library;

    static std::vector<ScriptComponent *> scriptComponents;
    static std::vector<EntityScript *> scriptInstances;

    void ScriptEngine::Init(const ScriptEngineConfiguration &config)
    {
        // Load up the library
        library = Platform::LoadDLL(config.ProjectDLLFileName);
    }

    void ScriptEngine::Shutdown()
    {
    }

    void ScriptEngine::Update()
    {
    }

    void ScriptEngine::OnRuntimeStart()
    {
        for (ScriptComponent *sc : scriptComponents)
        {
            std::string name = "";
            name += "Create";
            name += sc->className.c_str();

            EntityScript *es = Platform::LoadClass<EntityScript>(name.c_str(), &library);

            if (es == nullptr)
            {
                CE_ERROR("Unable to setup script instance: %s", sc->className.c_str());
                continue;
            }

            es->parent = sc->parent;
            scriptInstances.push_back(es);
        }

        for (EntityScript *sc : scriptInstances)
        {
            sc->OnStart();
        }
    }

    void ScriptEngine::OnRuntimeUpdate()
    {
        for (EntityScript *sc : scriptInstances)
        {
            sc->OnUpdate();
        }
    }

    void ScriptEngine::OnRuntimeStop()
    {
        scriptComponents.clear();

        for (EntityScript *sc : scriptInstances)

        {
            sc->OnDestroy();
            delete sc;
        }

        scriptInstances.clear();
    }

    void ScriptEngine::RegisterScriptComponent(ScriptComponent *component, Entity *parent)
    {
        component->parent = parent;
        scriptComponents.push_back(component);
    }
}