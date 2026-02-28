#include "entity_mgr.h"
#include "../../game/objects/game_objects.h"
#include <string.h>

Entity* global_entities[MAX_ENTITIES];
uint8_t global_entity_count = 0;

void entity_manager_init(void) {
    global_entity_count = 0;
    memset(global_entities, 0, sizeof(global_entities));
}

Entity* _entity_create_pool(int16_t x, int16_t y, Entity* pool, uint8_t max_count, size_t struct_size, void (*i)(Entity*), void (*s)(Entity*), void (*d)(Entity*)) {
    uint8_t* ptr = (uint8_t*)pool;
    for(uint8_t idx = 0; idx < max_count; idx++) {
        Entity *e = (Entity*)(ptr + (idx * struct_size));
        if(!e->active) {
            e->active = 1;
            e->x = x; e->y = y;
            e->solid = 0; e->width = 16; e->height = 16; // Valores por defecto
            e->init = i; e->step = s; e->draw = d;
            
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

void entity_manager_draw(void) {
    for(uint8_t i = 0; i < global_entity_count; i++) 
        if(global_entities[i]->active && global_entities[i]->draw) global_entities[i]->draw(global_entities[i]);
}