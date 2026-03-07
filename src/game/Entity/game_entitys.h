#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../game_api.h"

// El programador define el límite aquí
#define MAX_ENTITIES 40

DECLARE_ENTITY(Entity01, 5, 
    uint8_t hp;         // Variable 1
    int8_t patrol_dir;  // Variable 2
    uint16_t score_val; // Variable 3 (ocupa 2 bytes)
);

DECLARE_ENTITY(Entity02, 5, 
    uint8_t hp;         // Variable 1
    int8_t patrol_dir;  // Variable 2
    uint16_t score_val; // Variable 3 (ocupa 2 bytes)
);

DECLARE_ENTITY(Enemy, 5, 
    uint8_t hp;         // Variable 1
    int8_t patrol_dir;  // Variable 2
    uint16_t score_val; // Variable 3 (ocupa 2 bytes)
);

#endif