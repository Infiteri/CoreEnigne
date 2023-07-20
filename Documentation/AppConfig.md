# How to configure an Application.

## The application configuration is still marked as WORK IN PROGRESS (WIP), things like VSync are not optional, window resizing is always allowed

```c++

class Test : public Core::Application
{
public:
    Test(){};
    ~Test(){};

    // Setup configuration
    // The configuration structure is in Engine/Source/Core/Application.h
    // The configuration structure is a variable inside the Core::Application class named p_Configuration, this can be modified to represent the application's configuration.
    void OnPreInit()
    {
        this->p_Configuration.x = 100; // Int, represents the windows X position.
        this->p_Configuration.y = 100; // Int, represents the windows Y position.
        this->p_Configuration.width = 1024; // Int, represents the windows start width.
        this->p_Configuration.height = 576; // Int, represents the windows start height.
        this->p_Configuration.title = "my Game"; // const char*, represents the windows title.

        this->p_Configuration.StartMaximized = true; // Bool, represents if the window should begin maximized.
    };
}

```

```
This section is still WIP!
```
