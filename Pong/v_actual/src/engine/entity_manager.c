#include "./entity_manager.h"

#define MAX_ENTITIES 10
static Entity entity_pool[MAX_ENTITIES];

void entity_init(void) {
    uint8_t i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        entity_pool[i].active = 0;
        move_sprite(i, 0, 0); // Escondemos los sprites inicialmente
    }
}

Entity* entity_create(int16_t x, int16_t y, uint8_t tile_id) {
    uint8_t i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (!entity_pool[i].active) {
            entity_pool[i].x = x;
            entity_pool[i].y = y;
            entity_pool[i].vx = 0;
            entity_pool[i].vy = 0;
            entity_pool[i].vx_max = 10;
            entity_pool[i].vy_max = 10;
            entity_pool[i].dx = 1;
            entity_pool[i].dy = 1;
            entity_pool[i].tile_id = tile_id;
            entity_pool[i].active = 1;
            
            // Asignamos el tile al sprite correspondiente al índice i
            set_sprite_tile(i, tile_id);
            return &entity_pool[i];
        }
    }
    return 0;
}

void entity_render_all(void) {
    uint8_t i;
    for (i = 0; i < MAX_ENTITIES; i++) {
        if (entity_pool[i].active) {
            // Dibujamos la entidad en su posición x, y
            move_sprite(i, (uint8_t)entity_pool[i].x, (uint8_t)entity_pool[i].y);
        } else {
            // Si no está activa, la mandamos fuera de la pantalla
            move_sprite(i, 0, 0);
        }
    }
}