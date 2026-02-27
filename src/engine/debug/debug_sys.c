#include "debug_sys.h"
#include "../../game/sprites/fuenteNumerica/fuenteNumerica.h"

#ifdef MODO_DEBUG

// --- CONFIGURACIÓN DINÁMICA ---
#define WIN_X_BASE 7       // Borde izquierdo
#define WIN_Y_BOTTOM 144   // Altura total de la pantalla (oculta)
#define TILE_NUM_START 200 
#define TILE_BLANCO 210

static uint8_t current_row;
static uint8_t win_y_pos;

void debug_init(void) {
    // Cargamos los tiles una sola vez
    set_bkg_data(TILE_NUM_START, 12, fuenteNumerica);
    
    // Inicialmente la Window está fuera de la pantalla (en el fondo)
    win_y_pos = WIN_Y_BOTTOM;
    move_win(WIN_X_BASE, win_y_pos);
    SHOW_WIN;
}

void debug_begin(void) {
    // Al empezar el frame, reseteamos la fila y la posición Y
    current_row = 0;
    win_y_pos = WIN_Y_BOTTOM;
    move_win(WIN_X_BASE, win_y_pos);
}

void debug_watch(int16_t value) {
    uint8_t buf[8]; 
    uint8_t tmp[5]; 
    int8_t p = 0;
    uint8_t i = 0;
    
    int16_t v = (value < 0) ? -value : value;

    // Conversión de número a tiles
    if (v == 0) {
        tmp[p++] = TILE_NUM_START; 
    } else {
        while (v > 0 && p < 5) {
            tmp[p++] = (v % 10) + TILE_NUM_START;
            v /= 10;
        }
    }

    // Signo negativo (tile 211)
    if (value < 0) buf[i++] = 211;
    
    while (p > 0) buf[i++] = tmp[--p];
    
    // Limpieza con tile blanco
    buf[i++] = TILE_BLANCO;

    // --- EL TRUCO DEL ASCENSOR ---
    // 1. Dibujamos en la Window en la fila actual
    set_win_tiles(0, current_row++, i, 1, buf);

    // 2. Subimos la posición física de la Window 8 píxeles
    if (win_y_pos > 8) {
        win_y_pos -= 8;
        move_win(WIN_X_BASE, win_y_pos);
    }
}
#endif