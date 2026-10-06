#ifndef WR_TEXTURE_H
#define WR_TEXTURE_H

#include <stdbool.h>
#include <raylib.h>

typedef enum {
    WR_TEXTURE_NONE = 0,

    WR_TEXTURE_BRICK_1,
    WR_TEXTURE_BRICK_2,
    WR_TEXTURE_BRICK_3,
    WR_TEXTURE_BRICK_4,
    WR_TEXTURE_BRICK_5,
    WR_TEXTURE_BRICK_6,
    WR_TEXTURE_BRICK_7,
    WR_TEXTURE_BRICK_8,

    WR_TEXTURE_CURSED_1,
    WR_TEXTURE_CURSED_2,
    WR_TEXTURE_CURSED_3,
    WR_TEXTURE_CURSED_4,
    WR_TEXTURE_CURSED_5,
    WR_TEXTURE_CURSED_6,

    WR_TEXTURE_DOORS_1,
    WR_TEXTURE_DOORS_2,
    WR_TEXTURE_DOORS_3,
    WR_TEXTURE_DOORS_4,
    WR_TEXTURE_DOORS_5,
    WR_TEXTURE_DOORS_6,
    WR_TEXTURE_DOORS_7,
    WR_TEXTURE_DOORS_8,
    WR_TEXTURE_DOORS_9,
    WR_TEXTURE_DOORS_10,

    WR_TEXTURE_SCENERY_1,
    WR_TEXTURE_SCENERY_2,

    WR_TEXTURE_STONE_1,
    WR_TEXTURE_STONE_2,
    WR_TEXTURE_STONE_3,
    WR_TEXTURE_STONE_4,
    WR_TEXTURE_STONE_5,
    WR_TEXTURE_STONE_6,
    WR_TEXTURE_STONE_7,
    WR_TEXTURE_STONE_8,
    WR_TEXTURE_STONE_9,
    WR_TEXTURE_STONE_10,
    WR_TEXTURE_STONE_11,

    WR_TEXTURE_TILES_1,
    WR_TEXTURE_TILES_2,
    WR_TEXTURE_TILES_3,
    WR_TEXTURE_TILES_4,
    WR_TEXTURE_TILES_5,
    WR_TEXTURE_TILES_6,
    WR_TEXTURE_TILES_7,
    WR_TEXTURE_TILES_8,
    WR_TEXTURE_TILES_9,
    WR_TEXTURE_TILES_10,
    WR_TEXTURE_TILES_11,

    WR_TEXTURE_WOOD_1,
    WR_TEXTURE_WOOD_2,
    WR_TEXTURE_WOOD_3,
    WR_TEXTURE_WOOD_4,

    WR_TEXTURE_COUNT
} WrTextureType;

static const char* const TEXTURE_PATHS[WR_TEXTURE_COUNT] = {
    [WR_TEXTURE_NONE] = "",
    [WR_TEXTURE_BRICK_1] = "res/texture/Brick/Brick01.png",
    [WR_TEXTURE_BRICK_2] = "res/texture/Brick/Brick02.png",
    [WR_TEXTURE_BRICK_3] = "res/texture/Brick/Brick03.png",
    [WR_TEXTURE_BRICK_4] = "res/texture/Brick/Brick04.png",
    [WR_TEXTURE_BRICK_5] = "res/texture/Brick/Brick05.png",
    [WR_TEXTURE_BRICK_6] = "res/texture/Brick/Brick06.png",
    [WR_TEXTURE_BRICK_7] = "res/texture/Brick/Brick07.png",
    [WR_TEXTURE_BRICK_8] = "res/texture/Brick/Brick08.png",
    [WR_TEXTURE_CURSED_1] = "res/texture/Cursed/Cursed01.png",
    [WR_TEXTURE_CURSED_2] = "res/texture/Cursed/Cursed02.png",
    [WR_TEXTURE_CURSED_3] = "res/texture/Cursed/Cursed03.png",
    [WR_TEXTURE_CURSED_4] = "res/texture/Cursed/Cursed04.png",
    [WR_TEXTURE_CURSED_5] = "res/texture/Cursed/Cursed05.png",
    [WR_TEXTURE_CURSED_6] = "res/texture/Cursed/Cursed06.png",
    [WR_TEXTURE_DOORS_1] = "res/texture/Doors/Doors01.png",
    [WR_TEXTURE_DOORS_2] = "res/texture/Doors/Doors02.png",
    [WR_TEXTURE_DOORS_3] = "res/texture/Doors/Doors03.png",
    [WR_TEXTURE_DOORS_4] = "res/texture/Doors/Doors04.png",
    [WR_TEXTURE_DOORS_5] = "res/texture/Doors/Doors05.png",
    [WR_TEXTURE_DOORS_6] = "res/texture/Doors/Doors06.png",
    [WR_TEXTURE_DOORS_7] = "res/texture/Doors/Doors07.png",
    [WR_TEXTURE_DOORS_8] = "res/texture/Doors/Doors08.png",
    [WR_TEXTURE_DOORS_9] = "res/texture/Doors/Doors09.png",
    [WR_TEXTURE_DOORS_10] = "res/texture/Doors/Doors10.png",
    [WR_TEXTURE_SCENERY_1] = "res/texture/Scenery/Scenery01.png",
    [WR_TEXTURE_SCENERY_2] = "res/texture/Scenery/Scenery02.png",
    [WR_TEXTURE_STONE_1] = "res/texture/Stone/Stone01.png",
    [WR_TEXTURE_STONE_2] = "res/texture/Stone/Stone02.png",
    [WR_TEXTURE_STONE_3] = "res/texture/Stone/Stone03.png",
    [WR_TEXTURE_STONE_4] = "res/texture/Stone/Stone04.png",
    [WR_TEXTURE_STONE_5] = "res/texture/Stone/Stone05.png",
    [WR_TEXTURE_STONE_6] = "res/texture/Stone/Stone06.png",
    [WR_TEXTURE_STONE_7] = "res/texture/Stone/Stone07.png",
    [WR_TEXTURE_STONE_8] = "res/texture/Stone/Stone08.png",
    [WR_TEXTURE_STONE_9] = "res/texture/Stone/Stone09.png",
    [WR_TEXTURE_STONE_10] = "res/texture/Stone/Stone10.png",
    [WR_TEXTURE_STONE_11] = "res/texture/Stone/Stone11.png",
    [WR_TEXTURE_TILES_1] = "res/texture/Tiles/Tiles01.png",
    [WR_TEXTURE_TILES_2] = "res/texture/Tiles/Tiles02.png",
    [WR_TEXTURE_TILES_3] = "res/texture/Tiles/Tiles03.png",
    [WR_TEXTURE_TILES_4] = "res/texture/Tiles/Tiles04.png",
    [WR_TEXTURE_TILES_5] = "res/texture/Tiles/Tiles05.png",
    [WR_TEXTURE_TILES_6] = "res/texture/Tiles/Tiles06.png",
    [WR_TEXTURE_TILES_7] = "res/texture/Tiles/Tiles07.png",
    [WR_TEXTURE_TILES_8] = "res/texture/Tiles/Tiles08.png",
    [WR_TEXTURE_TILES_9] = "res/texture/Tiles/Tiles09.png",
    [WR_TEXTURE_TILES_10] = "res/texture/Tiles/Tiles10.png",
    [WR_TEXTURE_TILES_11] = "res/texture/Tiles/Tiles11.png",
    [WR_TEXTURE_WOOD_1] = "res/texture/Wood/Wood01.png",
    [WR_TEXTURE_WOOD_2] = "res/texture/Wood/Wood02.png",
    [WR_TEXTURE_WOOD_3] = "res/texture/Wood/Wood03.png",
    [WR_TEXTURE_WOOD_4] = "res/texture/Wood/Wood04.png"};

typedef struct WrTexture {
    int width;
    int height;
    Color* data;
} WrTexture;

void InitTexture(WrTexture* texture, const char* path);
void TerminateTexture(WrTexture* texture);

#endif // WR_TEXTURE_H
