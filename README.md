# Core Game Engine

Mini project that I hope I can grow.

# Requirements

Win32 and Make.

# How to Build

1. Clone the repo.
2. Run the Build.bat. (Only works if you have make and MinGW / g++).

# Vendor

1. Glfw, using 64-bit, pre-build.
2. Glad, using 4.6, not built.
3. ImGui.

# How to use the engine:

## How to start an application.

```c++
#include "Core.h" // Main stuff
#include "Core/Launch.h" // Only once included

class Test : public Core::Application
{
public:
    Test(){};
    ~Test(){};

    // Setup configuration
    void OnPreInit()
    {
        this->p_Configuration.StartMaximized = true;
    };

    void OnInit()
    {
        // Add layers and other stuff
    }
}

// VERY IMPORTANT REPRESENTS THE APPLICATION TO USE, CRASH OCCURS IF NOT DONE RIGHT
Core::Application* Core::CreateApplication() {
    return new Test();
};
```

## How to build:

1. Open a Command Prompt.
2. cd Into the directory where the Engine Folder and your code lives.
3. Create a folder named Bin. (Manually or use "mkdir Bin" with cmd).
4. Run: "g++ -DCORE_WINDOWS_PLATFORM -g YOUR_SOURCE_CODE_PATH/\*.cpp -IYOUR_SOURCE_CODE_PATH -IEngine/Source -IEngine/Vendor/GLFW/include -IEngine/Vendor/ImGui -LBin -lEngine -lImGui -o Bin/Test"

Including GLFW for the Input system. Using ImGui only if wanted, recommended.

5. Run the bat file

## How to launch:

1. Build. (Shown above).
2. Go in the Bin folder and run the Test.exe (or whatever name you gave it).

---

# Change Log:

POST MAIN REPO;

## July 18, 2023

Added cameras, shaders, Renderer API, buffers and vertex arrays.
Rendering a triangle.

## July 18, 2023, Push Nr. 2

Added OrthoMovement class. Allows for very basic orthographic camera movement.

## July 19, 2023.

Notes:
Calling glDrawArray 62500 times results in about 1 - 5 FPS; 2500 - 28 - 30 FPS with peeks of 60FPS; (with VSync)
Calling glDrawArray 10000 times results in about 15 - 20 FPS; About 40000 - 5 FPS; (without VSync)
250000 glDrawArrays results in 0 FPS;
So far only triangles have been pushed, lets do squares.
DO NOT GO FOR LIKE 1000 IT WILL CRASH AND SOMEHOW USED 3GB OF MY C DISK SPACE, I HAVE 8GB RAM LOL.

Added sprites, with hardcoded sizes (WIP); Added controls for adding sprites added a check that doesn't render the object if its not in the viewport sizes.
Also Added the ability to add and modify the amount of sprites that appear on the screen.

###### ABOUT THE SPRITE RENDERING:

###### If the cameras view bounds are within a area with sprites only those sprites get rendered, the sprites outside do not get rendered. The "fix" is in [Sprite.cpp](Engine/Source/Renderer/Objects/Sprite.cpp) in the render function.

I am 14 years old if anyone cares.
