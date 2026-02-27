#include "../engine/game_bridge.h"

void game_init(void) {
    entity_init(mi_pool_personalizado, MI_CANTIDAD_ENTIDADES, sizeof(Entity));
    #ifdef MODO_DEBUG
        debug_init();
     #endif

    object_init();
    pelota_init();
    room01_init();
}