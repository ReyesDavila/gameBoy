#include <gb/gb.h>
#include "Game/game_api.h"
#include "Engine/engine_api.h"

void main(void) {
    // 1. Configuración de Paletas (Gris claro a negro)
    BGP_REG = 0xE4; // Background
    OBP0_REG = 0xE4; // Sprites Paleta 0
    
    // 2. Inicialización de capas
    // SHOW_BKG: Fondo, SHOW_WIN: Ventana, SHOW_SPRITES: Objetos
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;

    engine_init();

    while(1) {
        engine_step();
        
        // Espera al refresco de pantalla para evitar glitches
        wait_vbl_done();
    }
}