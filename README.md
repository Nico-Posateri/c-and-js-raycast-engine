# Raycasting Game Engine

A raycasting game engine inspired by *Wolfenstein 3D*, built with C and SDL.

![c-rc-engine](https://github.com/Nico-Posateri/c-and-js-raycast-engine/assets/141705409/6e380135-6da5-48dd-b00a-cd2172a54c26)
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

![textures](https://github.com/Nico-Posateri/c-and-js-raycast-engine/assets/141705409/36101add-106f-4fd3-b233-f6ad32c2b7f5)

I started reminiscing about the Game Boy's dot-matrix display and the monochromatic green of early handheld gaming. I went in a slightly different direction, opting for a 1-bit palette of green and blue. I like the contrast and I feel that these two tones convey a similar feeling to that of the Game Boy's dot-matrix. However, I'm tempted to go back and make textures more reminiscent of the 1989 handheld console.

![dot-matrix-examples](https://github.com/Nico-Posateri/c-and-js-raycast-engine/assets/141705409/3ebed8d0-7339-404c-8f80-065c29400c5c)

[Raycasting Engine course](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript) taught by [Gustavo Pezzi](https://github.com/gustavopezzi).
