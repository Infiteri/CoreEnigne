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

## How to launch:

1. Build. (Shown above).
2. Go in the Bin folder and run the Test.exe (or whatever name you gave it).

I am 14 years old if anyone cares.
