#include "_sprites.h"

// 1. Punteros a Metasprites
const metasprite_t** const lista_metasprites[] = {
    corazon_metasprites,
    man_metasprites,
};

// 2. Punteros a Datos de Tiles
const uint8_t* const lista_tile_data[] = {
    corazon_tiles,
    man_tiles,
};

// 3. Conteo de Tiles
const uint8_t lista_tile_count[] = {
    corazon_TILE_COUNT,
    man_TILE_COUNT,
};
