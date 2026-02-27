#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <gb/gb.h>
#include <stdint.h>

// El motor no sabe qué hay dentro, solo que existe
typedef struct Entity Entity; 

// El motor ahora pide al usuario la memoria y el tamaño
void entity_init(Entity* storage, uint8_t max_count, uint16_t struct_size);
Entity* entity_create(int16_t x, int16_t y, uint8_t tile_id);
void entity_render_all(void);

#endif