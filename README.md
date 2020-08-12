A small 2d game engine I work on in my spare time.
Written in C++.
## Features
* Asset Management
* "Entity Component System"
* Data driven spritesheet loading.
* Tiled map loading (Thanks to Tileson)

## Thoughts
A lot of what is here is heavily subject to change. This is mainly something I work on as a learning experience, as such many features are implemented in a simplistic easy to read and parse method. I'll probably rewrite crucial code like the Entity Component System for a more proper one when I start making more complex games with it.

## Plans
Although you can probably make games with this in its current state I still plan and continue to add new features.
* Event System
* Collision System
* Networking
* Scripting
* OpenGL Renderer

## Dependancies

[Tileson](https://github.com/SSBMTonberry/tileson) For Tiled tile map loading.
[GLM](https://glm.g-truc.net/0.9.9/index.html) For Math. 
[ImGuiSDL](https://github.com/Tyyppi77/imgui_sdl) Debug Gui (Not currently in).
[SDL2](https://www.libsdl.org/) For crossplatform development and rendering.