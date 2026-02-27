#include "../engine/game_bridge.h"

void game_draw(void) {
    object_draw();
    #ifdef MODO_DEBUG
        debug_begin();
        debug_watch(pelota->x);
        debug_watch(pelota->y);
    #endif

}