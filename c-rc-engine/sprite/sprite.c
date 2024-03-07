#include "sprite.h"
#include "utils.h"
#include "ray.h"

#define NUM_SPRITES 12

static sprite_t sprites[NUM_SPRITES] = {
	{ .x = 855, .y = 600, .texture = 10 },	// Armor
	{ .x = 280, .y = 220, .texture = 10 },	// Armor
	{ .x = 915, .y = 100, .texture = 10 },	// Armor
	{ .x = 195, .y = 500, .texture = 10 },	// Armor
	{ .x = 90, .y = 730, .texture = 10 },	// Armor
	{ .x = 725, .y = 220, .texture = 11 },	// Table
	{ .x = 980, .y = 385, .texture = 11 },	// Table
	{ .x = 400, .y = 670, .texture = 11 },	// Table
	{ .x = 355, .y = 525, .texture = 11 },	// Table
	{ .x = 355, .y = 500, .texture = 12 },	// Lantern
	{ .x = 915, .y = 170, .texture = 12 },	// Lantern
	{ .x = 980, .y = 385, .texture = 12 }	// Lantern
};

void renderMapSprites(void) {
	for (int i = 0; i < NUM_SPRITES; i++) {
		drawRect(
			sprites[i].x * MINIMAP_SCALE_FACTOR,
			sprites[i].y * MINIMAP_SCALE_FACTOR,
			2,
			2,
			(sprites[i].visible) ? 0xFF0000FF : 0xFF000000
		);
	}
}

void renderSpriteProjection(void) {
	sprite_t visibleSprites[NUM_SPRITES];
	int numVisibleSprites = 0;

	// Find sprites that are within the FOV
	for (int i = 0; i < NUM_SPRITES; i++) {
		float angleSpritePlayer = player.rotationAngle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);

		// Make sure angle stays between 0 and 180 degrees
		if (angleSpritePlayer > PI) {
			angleSpritePlayer -= TWO_PI;
		}
		if (angleSpritePlayer < -PI) {
			angleSpritePlayer += TWO_PI;
		}
		angleSpritePlayer = fabs(angleSpritePlayer);

		/* If sprite angle is less than half the FOV(plus small margin for error)...
		EPSILON is the margin, allowing sprites to still be "seen" even if slightly outside of player FOV
		This looks a little silly on the minimap, and reducing it to zero will have sprite ticks
		disappear as soon as the leave the ray-cone, however, this margin prevents clearly "on-screen"
		sprites from disappearing from player view before they should
		*/
		const float EPSILON = 0.2;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
			sprites[i].visible = true;
			sprites[i].angle = angleSpritePlayer;
			sprites[i].distance = distanceBetweenPoints(sprites[i].x, sprites[i].y, player.x, player.y);
			visibleSprites[numVisibleSprites] = sprites[i];
			numVisibleSprites++;
		}
		else {
			sprites[i].visible = false;
		}
	}

	// Sort sprites by distance with an amateur bubble-sort algorithm implementation
	for (int i = 0; i < numVisibleSprites - 1; i++) {
		for (int j = i + 1; j < numVisibleSprites; j++) {
			if (visibleSprites[i].distance < visibleSprites[j].distance) {
				sprite_t temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}

	// Render only the visible sprites
	for (int i = 0; i < numVisibleSprites; i++) {
		sprite_t sprite = visibleSprites[i];

		// Calculate the perpendicular distance of the sprite, preventing fish-eye effect
		float perpDistance = sprite.distance * cos(sprite.angle);

		// Calculate the sprite projection height (width = height, as current sprites are 64x64)
		float spriteHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
		float spriteWidth = spriteHeight;

		// Calculate sprite top Y coordinate
		float spriteTopY = (WINDOW_HEIGHT / 2) - (spriteHeight / 2);
		spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;

		// Calculate sprite bottom Y coordinate
		float spriteBottomY = (WINDOW_HEIGHT / 2) + (spriteHeight / 2);
		spriteBottomY = (spriteBottomY > WINDOW_HEIGHT) ? WINDOW_HEIGHT : spriteBottomY;

		// Calculate the sprite X position on the projection plane
		float spriteAngle = atan2(sprite.y - player.y, sprite.x - player.x) - player.rotationAngle;
		float spriteScreenPosX = tan(spriteAngle) * DIST_PROJ_PLANE;

		// Calculate spriteLeftX
		float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPosX - (spriteWidth / 2);

		// Calculate spriteRightX
		float spriteRightX = spriteLeftX + spriteWidth;
		
		// Query width and height of the sprite texture
		int textureWidth = upng_get_width(textures[sprite.texture]);
		int textureHeight = upng_get_height(textures[sprite.texture]);

		// Loop through all the X values
		for (int x = spriteLeftX; x < spriteRightX; x++) {
			float texelWidth = (textureWidth / spriteWidth);
			int textureOffsetX = (x - spriteLeftX) * texelWidth;

			// Loop through all the Y values
			for (int y = spriteTopY; y < spriteBottomY; y++) {
				if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT) {
					int distanceFromTop = y + (spriteHeight / 2) - (WINDOW_HEIGHT / 2);
					int textureOffsetY = distanceFromTop * (textureHeight / spriteHeight);

					color_t* spriteTextureBuffer = (color_t*)upng_get_buffer(textures[sprite.texture]);
					color_t texelColor = spriteTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];
					
					if (sprite.distance < rays[x].distance && texelColor != 0xFFFF00FF) {
						drawPixel(x, y, texelColor);
					}
				}
			}
		}
	}
}