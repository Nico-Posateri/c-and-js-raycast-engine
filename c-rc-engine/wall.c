#include "wall.h"

/* Un-comment this block and the block between wall texture and floor color to implement
// Changes color intensity of vertically hit walls to create directional shadows                                             <<<
void changeColorIntensity(color_t* color, float factor) {
    color_t a = (*color & 0xFF000000);
    color_t r = (*color & 0x00FF0000) * factor;
    color_t g = (*color & 0x0000FF00) * factor;
    color_t b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}
*/

/* Un-comment this block and the block between wall texture and floor color to implement crude distance alpha
// Even cruder, post-sprite implementation
// Changes alpha of distant walls
void changeColorIntensity(color_t* color, float factor) {
    color_t alpha = (*color & 0xFF000000) * factor;
    *color = alpha;
}
*/

void renderWallProjection(void) {
    for (int x = 0; x < NUM_RAYS; x++) {
        // Calculate perpendicular distance to negate fish-eye distortion
        float perpDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);

        // Find projected wall height
        float wallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        // Find wall top Y value
        int wallTopY = (WINDOW_HEIGHT / 2) - (wallHeight / 2);
        wallTopY = wallTopY < 0 ? 0 : wallTopY;

        // Find wall bottom Y value
        int wallBottomY = (WINDOW_HEIGHT / 2) + (wallHeight / 2);
        wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;

        // Set the color of the ceiling
        for (int y = 0; y < wallTopY; y++) {
            drawPixel(x, y, 0xFF7cb494);
        }

        int textureOffsetX;
        if (rays[x].wasHitVertical)
            textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
        else
            textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;

        // Get the correct texture id number from the map content
        int texNum = rays[x].texture - 1;

        int textureWidth = upng_get_width(textures[texNum]);
        int textureHeight = upng_get_height(textures[texNum]);

        // Render the wall from wallTopY to wallBottomY
        for (int y = wallTopY; y < wallBottomY; y++) {
            int distanceFromTop = y + (wallHeight / 2) - (WINDOW_HEIGHT / 2);
            int textureOffsetY = distanceFromTop * ((float)textureHeight / wallHeight);

            // Set the color of the wall based on the color from the texture
            color_t* wallTextureBuffer = (color_t*) upng_get_buffer(textures[texNum]);
            color_t texelColor = wallTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];

            /* Un-comment to implement directional shadow, not a fan of the look with current textures
            // Sets wall color to a darker shade if it's a vertical hit, based on changeColorIntensity                       <<<
            if (rays[x].wasHitVertical) {
                changeColorIntensity(&texelColor, 0.7);
            }
            */

            /* Un-comment to implement very crude distance alpha
            // Renders the wall distance alpha
            if (perpDistance > 360) {
                changeColorIntensity(&texelColor, 0.7);
            }
            */

            drawPixel(x, y, texelColor);
        }

        // Set the color of the floor
        for (int y = wallBottomY; y < WINDOW_HEIGHT; y++) {
            drawPixel(x, y, 0xFF840c0c);
        }
    }
}