#include "engine_entity.h"
#include "../../game/Entity/game_entitys.h"
#include <string.h>

Entity* global_entities[MAX_ENTITIES];
uint8_t global_entity_count = 0;

void entity_manager_init(void) {
    global_entity_count = 0;
    memset(global_entities, 0, sizeof(global_entities));
}

Entity* _entity_create_pool(uint8_t x, uint8_t y, Entity* pool, uint8_t max_count, size_t struct_size, void (*i)(Entity*), void (*s)(Entity*)) {
    uint8_t* ptr = (uint8_t*)pool;
    for(uint8_t idx = 0; idx < max_count; idx++) {
        Entity *e = (Entity*)(ptr + (idx * struct_size));
        if(!e->active) {
            e->active = 1;
            e->x = x; e->y = y;
            e->solid = 0;
            e->width = 8; e->height = 8; // Valores por defecto
            e->init = i; e->step = s;
            
            if(global_entity_count < MAX_ENTITIES) {
                global_entities[global_entity_count++] = e;
            }
            if(e->init) e->init(e);
            return e;
        }
    }
    return NULL;
}


void entity_manager_step(void) {
    for(uint8_t i = 0; i < global_entity_count; i++) 
        if(global_entities[i]->active && global_entities[i]->step) global_entities[i]->step(global_entities[i]);
}

