#ifndef VIDEO_SYSTEM_H
#define VIDEO_SYSTEM_H

#include <gb/gb.h>
#include <stdint.h>

/**
 * Inicializa el hardware de video, paletas y activa capas.
 */
void video_init(void);

/**
 * Carga datos de tiles en la memoria VRAM.
 * @param data Puntero a los bytes de los tiles.
 * @param count Cantidad de tiles a cargar.
 */
void video_load_tiles(const uint8_t *data, uint8_t count);

#endif