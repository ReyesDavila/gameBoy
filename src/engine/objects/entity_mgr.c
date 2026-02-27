#include "entity_mgr.h"

static Entity* pool;
static uint8_t max_entities;
static uint16_t entity_size;

// Estructura mínima que el motor NECESITA ver para poder renderizar
// El truco es que el motor solo mapea los primeros bytes
typedef struct {
    int16_t x, y;
    uint8_t tile_id;
    uint8_t active;
} InternalEntity;

void entity_init(Entity* storage, uint8_t max_count, uint16_t struct_size) {
    pool = storage;
    max_entities = max_count;
    entity_size = struct_size;
    
    for (uint8_t i = 0; i < max_entities; i++) {
        InternalEntity* e = (InternalEntity*)((uint8_t*)pool + (i * entity_size));
        e->active = 0;
        move_sprite(i, 0, 0);
    }
}

Entity* entity_create(int16_t x, int16_t y, uint8_t tile_id) {
    for (uint8_t i = 0; i < max_entities; i++) {
        InternalEntity* e = (InternalEntity*)((uint8_t*)pool + (i * entity_size));
        if (!e->active) {
            e->x = x; e->y = y;
            e->tile_id = tile_id;
            e->active = 1;
            set_sprite_tile(i, tile_id);
            return (Entity*)e;
        }
    }
    return 0;
}

void entity_render_all(void) {
    uint8_t i;
    typedef struct {
        int16_t x, y;
        
        uint8_t tile_id;
        uint8_t active;
        uint8_t* tile_list;
        uint8_t list_size;
    } Renderable;

    for (i = 0; i < max_entities; i++) {
        Renderable* e = (Renderable*)((uint8_t*)pool + (i * entity_size));
        
        if (e->active) {
            // MÉTODO INTELIGENTE:
            // Si tiene una lista de más de 1 tile, actualizamos el hardware.
            // Si list_size es 0 o 1, NO llamamos a set_sprite_tile (ahorro de ciclos).
            if (e->list_size > 1) {
                set_sprite_tile(i, e->tile_id);
            }

            move_sprite(i, (uint8_t)e->x + 8, (uint8_t)e->y + 16);
        } else {
            move_sprite(i, 0, 0);
        }
    }
}