#include "../engine_api.h"

uint8_t sprite_cursor = 0;
uint8_t vram_libre = 0; // <--- AÑADE ESTA LÍNEA AQUÍ

void sprites_reset(void) {
    // Escondemos los 40 proyectores moviéndolos fuera de pantalla
    for(uint8_t i = 0; i < 40; i++) {
        move_sprite(i, 0, 200); 
    }
    // Reiniciamos el cursor para el nuevo frame
    sprite_cursor = 0;
}

void draw_tile_spr(uint8_t x, uint8_t y, uint8_t tile_index) {
    if (sprite_cursor < 40) {
        // Asignamos el dibujo al proyector actual
        set_sprite_tile(sprite_cursor, tile_index);
        // Lo posicionamos (sumamos offset de hardware: X+8, Y+16)
        move_sprite(sprite_cursor, x + 8, y + 16);
        // Avanzamos al siguiente proyector
        sprite_cursor++;
    }
}
