#pragma once

#include "Core/Base.h"
#include "Scene/Entity.h"
#include "ScriptEngine.h"

namespace Core
{
    class CE_API EntityScript
    {
    protected:
        Entity *parent;

        friend class ScriptEngine;

    public:
        EntityScript();
        ~EntityScript();

        virtual void OnStart();

        virtual void OnUpdate();

        virtual void OnDestroy();

        template <typename T>
        T *AddComponent()
        {
            return parent->AddComponent<T>();
        };

        template <typename T>
        bool HasComponent()
        {
            return parent->HasComponent<T>();
        };

        template <typename T>
        T *GetComponent()
        {
            return parent->GetComponent<T>();
        };
    };
}
