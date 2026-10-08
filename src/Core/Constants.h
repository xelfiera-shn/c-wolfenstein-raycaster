#ifndef WR_CONSTANTS_H
#define WR_CONSTANTS_H

#include "Utils/Math.h"

#define WR_SCREEN_DEFAULT_WIDTH 1200
#define WR_SCREEN_DEFAULT_HEIGHT 800

#define WR_INNER_WIDTH 960
#define WR_INNER_HEIGHT 600

#define WR_PLAYER_FOV (WR_PI / 3.f) // PI/3 (60 degrees)
#define WR_PLAYER_COLLISION_RADIUS 0.2f
#define WR_PLAYER_MOVE_SPEED 3.f     // 3 cell per second
#define WR_PLAYER_TURN_SPEED (WR_PI) // Half lap per second (180 degrees)

#define WR_FOG_DISTANCE 8.f
#define WR_FOG_MIN_BRIGHTNESS_FACTOR 0.1f
#define WR_VERTICAL_HIT_BRIGHTNESS_FACTOR 0.7f

#endif // WR_CONSTANTS_H
