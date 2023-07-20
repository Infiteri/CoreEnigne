# How to render your first sprite using Core.

###### This is a step that must be followed AFTER adding layers.

After the main setup of the application, the first bits of rendering can be started.
The rendering is done in the layer's OnRender function

## Important: Any instancing of objects (sprites and other OpenGL related objects) can only be done in the OnAttach method

```cpp
class ExampleLayer : public Core::Layer
{
public:
    ExampleLayer(){};
    ~ExampleLayer(){};

    // Setup instances
    void OnAttach() {};

    // Runs when any rendering can be done. Here the sprites can be rendered
    void OnRender() {};
};
```

### How to define a sprite

```cpp
Core::Sprite* sprite = nullptr;
```

### How to instance a sprite

```cpp

// Inside the layer's OnAttach method
void OnAttach() {
    sprite = new Core::Sprite();
    sprite->Init();
};
```

### How to render a sprite

```cpp
// Inside the layer's OnRender method
void OnRender() {
    sprite->Render();
};
```

### Final code

```cpp
Core::Sprite* sprite = nullptr;

class ExampleLayer : public Core::Layer
{
public:
    ExampleLayer(){};
    ~ExampleLayer(){};

    // Setup instances
    void OnAttach() {
        sprite = new Core::Sprite();
        sprite->Init();
    };

    // Runs when any rendering can be done. Here the sprites can be rendered
    void OnRender() {
        sprite->Render();
    };
};
```

# Why inside OnAttach?

The sprites constructor initializes some important things:
A material
A vertex array object.
A transform.

The vertex array relies on OpenGL code, OpenGL gets loaded in a way thats not instantly, and that results in crashes.

In the future, OpenGL code will probably be moved in a Init method but for now this is how its done.
