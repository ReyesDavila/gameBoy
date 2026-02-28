#include "scripts_mgr.h"
#include <stddef.h>

// Función interna única para detectar choques entre dos cajas (AABB)
static bool check_aabb(Entity* a, int16_t ax, int16_t ay, Entity* b) {
    if (!b || !b->active || a == b) return false;
    return (ax < b->x + b->width && ax + a->width > b->x &&
            ay < b->y + b->height && ay + a->height > b->y);
}

// Retorna true si NO hay colisión con objetos SÓLIDOS
bool _place_free(Entity* self, int16_t nx, int16_t ny) {
    for(uint8_t i = 0; i < global_entity_count; i++) {
        if(global_entities[i]->solid && check_aabb(self, nx, ny, global_entities[i])) 
            return false;
    }
    return true;
}

// Retorna true si NO hay colisión con ABSOLUTAMENTE NADIE
bool _place_empty(Entity* self, int16_t nx, int16_t ny) {
    for(uint8_t i = 0; i < global_entity_count; i++) {
        if(check_aabb(self, nx, ny, global_entities[i])) 
            return false;
    }
    return true;
}

// Retorna true si choca con algún objeto de la lista específica
bool _place_meeting(Entity* self, int16_t nx, int16_t ny, void* pool, uint8_t max, size_t size) {
    uint8_t* ptr = (uint8_t*)pool;
    for(uint8_t i = 0; i < max; i++) {
        Entity* other = (Entity*)(ptr + (i * size));
        if(check_aabb(self, nx, ny, other)) return true;
    }
    return false;
}