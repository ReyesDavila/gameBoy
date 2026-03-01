#include "../engine/game_bridge.h"

void game_step(void) {
    entity_manager_step();
    room01_step();
}