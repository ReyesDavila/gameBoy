#ifndef _SCENE01_SETTINGS_H
#define _SCENE01_SETTINGS_H

#include "../game_scenes.h"

// Definimos los IDs de los tiles que representan objetos
#define TILE_PLAYER    3
#define TILE_ENEMY     4
#define TILE_ENEMY2    5

//#define TILE_AUTO      30

// Esta macro permite al usuario mapear el ID con el TYPE de la estructura
// Es minimalista: si el tile coincide, ejecuta el entity_create
#define SPAWN_RELATIONS_SCENE01(tile, x, y) \
    if (tile == TILE_PLAYER) entity_create(x, y, Entity01); \
    if (tile == TILE_ENEMY) entity_create(x, y, Entity02); \
    if (tile == TILE_ENEMY2) entity_create(x, y, Enemy); \

void scene01_init(void);

extern int8_t tiles_solidos_scene01[];

#endif