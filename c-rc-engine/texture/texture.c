#include "texture.h"

static const char* textureFileNames[NUM_TEXTURES] = {
    // Environment textures:
    // Blank space              // Map grid code [0]
    "./images/wallA.png",       // Map grid code [1]
    "./images/wallB.png",       // Map grid code [2]
    "./images/wallC.png",       // Map grid code [3]
    "./images/wallD.png",       // Map grid code [4]
    "./images/wallE.png",       // Map grid code [5]
    "./images/wallF.png",       // Map grid code [6]
    "./images/doorA.png",       // Map grid code [7]
    "./images/doorB.png",       // Map grid code [8]
    "./images/floor.png",       // Map grid code [9]
    "./images/ceiling.png",     // Map grid code [10]
    // Object sprites:
    "./images/armor.png",       // Sprite texture code [10]
    "./images/table.png",       // Sprite texture code [11]
    "./images/lantern.png"      // Sprite texture code [12]
};

void loadTextures(void) {
    for (int i = 0; i < NUM_TEXTURES; i++) {
        upng_t* upng = upng_new_from_file(textureFileNames[i]);
        if (upng != NULL) {
            upng_decode(upng);
            if (upng_get_error(upng) == UPNG_EOK) {
                textures[i] = upng;
            }
            else {
                printf("Error decoding texture file %s \n", textureFileNames[i]);
            }
        }
        else {
            printf("Error loading texture %s \n", textureFileNames[i]);
        }
    }
}

void freeTextures(void) {
    for (int i = 0; i < NUM_TEXTURES; i++) {
        upng_free(textures[i]);
    }
}