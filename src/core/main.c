#include "./globals.h"

void main(void) {
    // 1. Inicialización del Hardware (Core)
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;

    sound_init();

    // 2. Inicialización de los Sistemas (Engine)
    debug_init();    // Enciende la "luz" para el texto
    entity_init();   // Limpia el almacén de objetos

    // 3. Inicialización del Contenido (Game)
    game_init();     // Aquí el juego crea su pelota y assets

    // 4. El Bucle Infinito (Game Loop)
    while(1) {
        //control de joypad
        joypad_update();
        
        // Lógica del juego: calcula posiciones
        game_logic();

        // El motor de entidades: dibuja todo lo que esté activo
        entity_render_all();

        // Sincronización con la pantalla de la Game Boy
        wait_vbl_done();
    }
}