#include "video_sys.h"

void video_init(void) {
    // Configuración de Paletas (Estándar: Negro, Gris D., Gris C., Blanco)
    BGP_REG = OBP0_REG = 0xE4;

    // Inicialización de Capas
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;
}

void video_load_tiles(const uint8_t *data, uint8_t count) {
    // Cargamos los mismos tiles para Background y Sprites (opcional, pero común)
    set_bkg_data(0, count, data);
    set_sprite_data(0, count, data);
}