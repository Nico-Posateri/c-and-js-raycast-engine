#include "map.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 4, 2, 1, 1, 2, 2, 1, 6, 5, 6, 2, 1, 1, 1, 8, 6, 2, 3},
    {3, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2},
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {6, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 5},
    {2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4},
    {2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 2},
    {4, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3},
    {2, 0, 2, 1, 1, 2, 1, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 4},
    {1, 1, 4, 1, 3, 1, 6, 7, 6, 1, 2, 2, 1, 1, 3, 6, 7, 6, 3, 1}
};

bool mapHasWallAt(float x, float y) {
    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE) {
        return true;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

bool isInsideMap(float x, float y) {
    return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

int getMapAt(int i, int j) {
    return map[i][j];
}

void renderMapGrid(void) {
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            uint32_t tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

            drawRect(
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor
            );
        }
    }
}