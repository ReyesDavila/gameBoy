#ifndef SPRITES_MGR_H
#define SPRITES_MGR_H

#include <gb/gb.h>
#include <stdint.h>

/* --- FUNCIONES NATIVAS GBDK (VRAM & RENDER) --- 
   set_bkg_data(u8 start, u8 count, const u8 *data);    // Carga tiles al banco de Background/Window.
   set_sprite_data(u8 start, u8 count, const u8 *data); // Carga tiles al banco de Sprites.
   set_bkg_tile_xy(u8 x, u8 y, u8 tile_id);             // Dibuja tile en capa Background.
   set_win_tile_xy(u8 x, u8 y, u8 tile_id);             // Dibuja tile en capa Window.
*/

// Reinicia el cursor de proyectores (OAM) al inicio de cada frame.
void sprites_reset();

// Dibuja un tile usando el siguiente proyector disponible.
void draw_tile(uint8_t x, uint8_t y, uint8_t tile_index);
void draw_tile_win(uint8_t x, uint8_t y, uint8_t index);

void vram_reset(void);
void screen_clear(void);

#endif