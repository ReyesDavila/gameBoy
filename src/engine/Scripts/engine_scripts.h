#ifndef ENGINE_SCRIPTS_H
#define ENGINE_SCRIPTS_H

#include "../Entity/engine_entity.h"

// 256 tiles / 8 bits por byte = 32 bytes para representar todos los IDs posibles
extern uint8_t tile_collision_bitset[32];

#define place_free(nx, ny) _place_free((Entity*)self, nx, ny)

// Configura qué tiles son sólidos pasando un array y su tamaño
void set_solid_tiles(uint8_t* tile_ids, uint8_t count);

bool _place_free(Entity* self, uint8_t nx, uint8_t ny);

#endif