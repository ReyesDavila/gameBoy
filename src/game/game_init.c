#include "../core/globals.h"
#include "../assets/tiles_fondo.h"

//Definir objetos aquí.
Entity* pelota;

void game_init(void) {
    // El motor crea la entidad, el juego le da el propósito de "pelota"
    pelota = entity_create(80, 72, 2);

    #ifdef MODO_DEBUG
        debug_init();
     #endif

    // 1. Configuración de Hardware
    BGP_REG = OBP0_REG = 0xE4;  
    set_bkg_data(0, 3, FondoGraficos);
    set_sprite_data(0, 3, FondoGraficos);

    // 2. Dibujo del Escenario
    for(uint8_t x = 0; x < 20; x++) {
        for(uint8_t y = 0; y < 18; y++) {
            set_bkg_tile_xy(x, y, 1);
        }
    }

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}