#include "../engine/game_bridge.h"

void game_init(void) {
    // En tu game_init.c
    entity_manager_init(); // Limpia la lista al empezar

    room01_init();
    
    #ifdef MODO_DEBUG
        debug_init();
     #endif

    // Creas un obj0
    obj0 = entity_create(80, 72, Object0);
    //entity_create(80, 72, Object0);
    
}