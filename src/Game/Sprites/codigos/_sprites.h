#ifndef _SPRITES_H
#define _SPRITES_H

#include <gbdk/metasprites.h>
#include <stdint.h>

// --- INCLUDES DE ACTIVOS ---
#include "corazon.h"
#include "man.h"

// --- DEFINICIONES DE ID (ALFABÉTICO) ---
#define corazon 0
#define man 1

extern const metasprite_t** const lista_metasprites[];
extern const uint8_t* const lista_tile_data[];
extern const uint8_t lista_tile_count[];

#endif
