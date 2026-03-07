#include <gb/gb.h>
#include "engine_video.h"


void renderer_init(void) {
    DISPLAY_OFF;
    SPRITES_8x8;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void video_clear_bkg(void) {
    // Llena el mapa de 32x32 con el tile 0 (que debe ser transparente o vacío)
    fill_bkg_rect(0, 0, 32, 32, 0);
}
