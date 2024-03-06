# Raycasting Game Engine

A raycasting game engine inspired by *Wolfenstein 3D*, built with C and SDL.

![js-prototype](https://github.com/Nico-Posateri/c-and-js-raycast-engine/assets/141705409/f522b7d8-7144-4a0b-a7fa-3bf18a38a31e)
> [!NOTE]
> The C engine is not yet properly optimized for building a complete game.
> I plan to add the following features soon:
> - [ ] Textured floor and ceiling
> - [ ] Distance fog
> - [ ] Sprite animation

## Directory Information

The **c-rc-engine** folder contains the C raycasting engine. This engine uses [SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) as well as [elanthis' upng](https://github.com/elanthis/upng), a png decoder for my custom textures created in [Aseprite](https://www.aseprite.org/). This engine attempts to closely emulate *Wolfenstein 3D*'s engine with some improvements, including floor and ceiling textures.

The **js-prototype** folder contains a prototype of the raycasting engine built with JavaScript, rendered in-browser.

## Additional Information

Again, the textures and sprites used in the **c-rc-engine** build were made by myself, using [Aseprite](https://www.aseprite.org/).

[Raycasting Engine course](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript) taught by [Gustavo Pezzi](https://github.com/gustavopezzi).
