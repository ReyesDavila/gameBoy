#include "../engine/game_bridge.h"

void game_step(void) {
    object_step();
    pelota_step();
}