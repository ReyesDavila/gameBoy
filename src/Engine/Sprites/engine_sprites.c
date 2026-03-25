#include "engine_sprites.h"
#include "../../Game/Sprites/game_sprites.h" 


uint8_t current_oam = 0; // Variable global para rastrear OAM

// 4. Memoria dinámica: Aquí guardaremos el slot asignado en tiempo de ejecución
uint8_t lista_vram_offsets[MAX_SPRITES]; 
uint8_t vram_pointer = 0; // Rastreador de la siguiente posición libre

// Llama a esto AL INICIO de cada frame
void sprites_prepare_frame(void) {
    current_oam = 0; 
}

void draw_sprite(uint8_t id, uint8_t frame, uint8_t x, uint8_t y) {
    // Usamos move_metasprite normal (5 argumentos) que es más directo
    current_oam = move_metasprite(
        lista_metasprites[id][frame], 
        lista_vram_offsets[id], 
        current_oam,  
        x + 8,        // Coordenada X real 
        y + 16        // Coordenada Y real
    );
}


// Resetea la "estantería" de la VRAM
void sprites_reset(void) {
    vram_pointer = 0;
    for(uint8_t i = 0; i < MAX_SPRITES; i++) {
        lista_vram_offsets[i] = 0;
    }
}

// Carga un sprite específico y anota su posición
void load_sprite_to_vram(uint8_t id) {
    // Guardamos dónde empieza este sprite
    lista_vram_offsets[id] = vram_pointer;
    
    // Subimos los tiles a la Game Boy en la posición actual
    set_sprite_data(vram_pointer, lista_tile_count[id], lista_tile_data[id]);
    
    // Movemos el puntero para el siguiente sprite
    vram_pointer += lista_tile_count[id];
}

