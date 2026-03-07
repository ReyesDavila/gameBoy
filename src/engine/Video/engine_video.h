#ifndef ENGINE_VIDEO_H
#define ENGINE_VIDEO_H

#include <gb/gb.h>
#include <stdint.h>

/**
 * --- FUNCIONES NATIVAS DE GBDK (RESUMEN) ---
 * * 1. GESTIÓN DE VRAM (Cargar dibujos):
 * set_bkg_data(ID, cant, data)    -> Carga tiles en la memoria de fondo.
 * set_sprite_data(ID, cant, data) -> Carga tiles en la memoria de sprites.
 * * 2. BACKGROUND & WINDOW (Dibujar el mapa):
 * set_bkg_tiles(x, y, w, h, map)  -> Dibuja una matriz de tiles en el fondo.
 * set_bkg_tile_xy(x, y, tile_index);-> dibuja un tile background
 * set_win_tiles(x, y, w, h, map)  -> Dibuja una matriz en la capa de ventana.
 * move_win(x, y)                  -> Posiciona la capa Window (útil para HUD).
 * * 3. SPRITES (Dibujar objetos móviles):
 * set_sprite_tile(nb, tile_id)    -> Asigna un dibujo (tile) a un sprite de hardware.
 * move_sprite(nb, x, y)           -> Posiciona el sprite en pantalla.
 * * 4. METASPRITES (GBDK nativo):
 * move_metasprite(data, tile, nb, x, y) 
 * -> Es una función de GBDK que toma una estructura de datos (Metasprite) 
 * y mueve automáticamente varios sprites de hardware para que parezcan uno solo.
 */

// Definiciones para tu motor
void renderer_init(void);
void video_clear_bkg(void);

#endif