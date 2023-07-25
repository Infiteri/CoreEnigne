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

Added a ViewAbility structure that represents the bounds of the camera's viewport, related to whichever camera the renderer is currently using while the engine is running.

Added very basic Texture support. Ability to swap textures under the same class.

TODO: TextureManager / AssetManager

(Pushed on July 20, 2023, no changes made when pushed since July 19, 2023);

## July 20, 2023.

Integrated the texture into the Material class.

[Material.cpp](Engine/Source/Renderer/Material.cpp)

Added documentation.

## July 21, 2023.

Moved sprite setup code in Init. Sprites can now be instanced outside of the OnAttach method of a layer.

#### Push nr. 2.

Added sizes to sprites, the ability to change them before and after Init is called.

#### Push nr. 3.

Added FrameBuffers started the Editor, sandbox doesn't work yet, hopefully I will fix it.
Started working on scenes, entities and components, don not judge my entity class pls.

Small entity API and scene API, still WIP.

## July 22, 2023.

Working on the scene Serializer / Deserializer. WIP

# July 24, 2023

Starting a little particle system, inspired by cherno lol. WIP Still, not working with parent transform, FIX-IT!
