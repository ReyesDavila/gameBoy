#include "engine_scripts.h"
#include <string.h>

uint8_t tile_collision_bitset[32];

void set_solid_tiles(uint8_t* tile_ids, uint8_t count) {
    memset(tile_collision_bitset, 0, sizeof(tile_collision_bitset));
    for(uint8_t i = 0; i < count; i++) {
        uint8_t id = tile_ids[i];
        // Marcar el bit correspondiente al ID del tile
        tile_collision_bitset[id >> 3] |= (1 << (id & 7));
    }
}

// Función auxiliar rápida para leer el bitset
inline uint8_t is_tile_solid(uint8_t tile_id) {
    return tile_collision_bitset[tile_id >> 3] & (1 << (tile_id & 7));
}

bool _place_free(Entity* self, uint8_t nx, uint8_t ny) {
    // 1. COLISIÓN CON TILES (Background)
    // Revisamos los 4 puntos cardinales de la máscara de colisión
    uint8_t points_x[2] = {nx, nx + self->width - 1};
    uint8_t points_y[2] = {ny, ny + self->height - 1};
    uint8_t tile_id;

    for(uint8_t i = 0; i < 2; i++) {
        for(uint8_t j = 0; j < 2; j++) {
            // GBDK: get_bkg_tile_xy obtiene el ID del tile en coordenadas de celda (8px)
            tile_id = get_bkg_tile_xy(points_x[i] >> 3, points_y[j] >> 3);
            if(is_tile_solid(tile_id)) return false;
        }
    }

    // 2. COLISIÓN CON ENTIDADES (Solo si los tiles están libres)
    Entity *e;
    for(uint8_t i = 0; i < global_entity_count; i++) {
        e = global_entities[i];
        if(!e->active || !e->solid || e == self) continue;

        if (nx < e->x + e->width && nx + self->width > e->x &&
            ny < e->y + e->height && ny + self->height > e->y) {
            return false;
        }
    }

    return true; 
}