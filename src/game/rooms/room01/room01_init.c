#include "../../../engine/game_bridge.h"

void room01_init(void){

    // 2. Dibujo del Escenario
    uint8_t x, y; // <-- Decláralas aquí afuera
    for(x = 0; x < 20; x++) {
        for(y = 0; y < 18; y++) {
            set_bkg_tile_xy(x, y, 1);
        }
    }

    // Equivalente a un "Create Event" en Game Maker
    sound_loop(&snd_coin); 
}