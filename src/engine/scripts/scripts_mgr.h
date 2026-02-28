#ifndef SCRIPTS_MGR_H
#define SCRIPTS_MGR_H

#include <gb/gb.h>
#include <stdbool.h>
#include "../objects/entity_mgr.h"

// Macros directas para el usuario
#define place_free(nx, ny) _place_free((Entity*)self, nx, ny)
#define place_empty(nx, ny) _place_empty((Entity*)self, nx, ny)
#define place_meeting(nx, ny, type) _place_meeting((Entity*)self, nx, ny, (void*)type##_list, MAX_##type, sizeof(type))

// Prototipos
bool _place_free(Entity* self, int16_t nx, int16_t ny);
bool _place_empty(Entity* self, int16_t nx, int16_t ny);
bool _place_meeting(Entity* self, int16_t nx, int16_t ny, void* pool, uint8_t max, size_t size);

#endif