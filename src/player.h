#ifndef __WOLFENSTEIN_RAYCASTER_PLAYER_
#define __WOLFENSTEIN_RAYCASTER_PLAYER_

#include "types.h"

typedef struct Player {
    Vec2 Pos;
    float Angle;
    Vec2 Delta;
} Player;

#endif // __WOLFENSTEIN_RAYCASTER_PLAYER_