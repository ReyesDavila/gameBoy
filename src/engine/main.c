#include "game_bridge.h"

void main(void) {
    video_init();
    sound_init();
    //video_load_tiles(tilesFondo, 5);

    
    // Esperar a que el usuario pulse Start para generar una semilla aleatoria real
    waitpad(J_START); 
    initrand(DIV_REG); // DIV_REG es un registro de la GB que cambia constantemente
    

    game_init();

    while(1) {
        sprites_reset(); // 1. Limpiar proyectores del frame anterior

        // 1. ACTUALIZAR INPUT (Crucial: Primero de la fila)
        // Esto guarda el estado del frame anterior y lee el nuevo.
        joystick_update();

        // 2. LÓGICA (Aquí tus scripts usan joystick_check_button, etc.)
        game_step();

        // 3. DIBUJO MANUAL
        game_draw();

        // 5. AUDIO Y ESPERA DE V-BLANK
        audio_update();    
        wait_vbl_done();
    }

}