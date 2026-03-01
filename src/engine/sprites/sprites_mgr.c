#include "sprites_mgr.h"

// El "Cursor" que apunta al siguiente proyector (0-39)
uint8_t sprite_cursor = 0;
uint8_t vram_libre = 0; // <--- AÑADE ESTA LÍNEA AQUÍ

void sprites_reset() {
    // Escondemos los 40 proyectores moviéndolos fuera de pantalla
    for(uint8_t i = 0; i < 40; i++) {
        move_sprite(i, 0, 0); 
    }
    // Reiniciamos el cursor para el nuevo frame
    sprite_cursor = 0;
}

void draw_tile(uint8_t x, uint8_t y, uint8_t tile_index) {
    if (sprite_cursor < 40) {
        // Asignamos el dibujo al proyector actual
        set_sprite_tile(sprite_cursor, tile_index);
        // Lo posicionamos (sumamos offset de hardware: X+8, Y+16)
        move_sprite(sprite_cursor, x + 8, y + 16);
        // Avanzamos al siguiente proyector
        sprite_cursor++;
    }
}

void draw_tile_win(uint8_t x, uint8_t y, uint8_t index) {set_win_tile_xy(x, y, index);}


void vram_reset(void) {
    // Creamos un pequeño bloque de 16 bytes en 0 (un tile vacío)
    const uint8_t vacio[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    // Llenamos los 256 espacios de la VRAM con ese tile vacío
    for (uint16_t i = 0; i < 256; i++) {
        set_bkg_data(i, 1, vacio);
        set_sprite_data(i, 1, vacio);
    }
    
    // IMPORTANTE: Reiniciar tu contador de "estante"
    vram_libre = 0; 
}

void screen_clear(void) {
    uint8_t x, y;
    for(x = 0; x < 32; x++) {
        for(y = 0; y < 32; y++) {
            set_bkg_tile_xy(x, y, 0); // Ponemos el tile 0 en todas partes
        }
    }
}