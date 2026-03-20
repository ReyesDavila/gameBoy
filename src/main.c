#include <gb/gb.h>
#include "Game/game_api.h"
#include "Engine/engine_api.h"

void main(void) {
    DISPLAY_ON;
    // --- AÑADE ESTO ---
    OBP0_REG = 0xE4;  // Paleta estándar para objetos (Sprites)
    BGP_REG = 0xE4;   // Paleta estándar para el fondo (Background)
    // ------------------
    
    SHOW_BKG;
    SPRITES_8x8;
    SHOW_SPRITES;
    SHOW_WIN;
    
    // Carga los 2 tiles del corazón en el índice 0 de la VRAM
    sprites_reset();            // Limpiamos la gestión
    load_sprite_to_vram(0);     // Carga Corazón en slot 0
    load_sprite_to_vram(1);     // Carga Man en slot 2 (si el corazón ocupa 2)

    game_init();
    while(1) {
        sprites_prepare_frame(); // 1. Resetea el índice OAM a 0

        draw_sprite(corazon, 0, 32, 32); 
        draw_sprite(man, 0, 80, 72);

        hide_sprites_range(current_oam, 40);

        game_step();
        wait_vbl_done();
    }
}