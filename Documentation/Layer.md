# Layers

Assuming that you read the README file and setup an application class, this will guide you how to add a layer.

Back in the main cpp file where your main class lives lets make sure we have the OnInit function declared, which is present on the base Core::Application class.

```c++
...

class Test : public Core::Application
{
public:
    ...

    // The function where the layers will be pushed
    void OnInit()
    {
    }

...
}
```

After adding the OnInit function to your class you can begin adding the layers that you want.

## How to crete a layer:

The layer class is present once you include "Core.h".

```c++
#include "Core.h"

// Main layer
class ExampleLayer : public Core::Layer
{
public:
    // NO CODE SHOULD BE PUT HERE
    ExampleLayer(){};

    // NO CODE SHOULD BE PUT HERE
    ~ExampleLayer(){};

    // Runs once the layer is attached to the LayerStack
    void OnAttach() {};

    // Runs when any rendering can be done.
    void OnRender() {};

    // Runs once a frame
    void OnUpdate() {};

    // Runs once a frame, when ImGui is setup and ready to render. This function will be described later.
    void OnImGuiRender() {};

    // Runs once this layer is detached from the LayerStack.
    void OnDetach() {};
};

```

This is a simple definition of a Layer SubClass. Each method is virtual and doesn't need to be implemented.

## How to add a layer to your application

```c++
class Test : public Core::Application
{
public:
    ...

    void OnInit()
    {
        // Adds a new layer to the layer stack, runs the OnAttach automatically.
        Core::LayerStack::PushLayer(new ExampleLayer());
    }
...
}
```
