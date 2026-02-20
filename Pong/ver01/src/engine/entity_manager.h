#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <gb/gb.h>
#include <stdint.h>

typedef struct {
    int16_t x, y;
    int8_t vx, vy;
    int8_t dx, dy;
    int8_t vx_max, vy_max;
    uint8_t tile_id;   // El ID del tile en la VRAM
    uint8_t active;
} Entity;

void entity_init(void);
Entity* entity_create(int16_t x, int16_t y, uint8_t tile_id);

/**
 * Recorre todas las entidades y actualiza sus sprites en el hardware
 */
void entity_render_all(void);

#endif