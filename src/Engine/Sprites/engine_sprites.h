#ifndef ENGINE_SPRITES_H
#define ENGINE_SPRITES_H

#include <gbdk/metasprites.h>
#include <stdint.h>

// Definimos el máximo aquí
#define MAX_SPRITES 40

// PROTOTIPOS: Ahora con sus tipos de retorno y argumentos correctos
void sprites_reset(void);
void load_sprite_to_vram(uint8_t id);
void draw_sprite(uint8_t id, uint8_t frame, uint8_t x, uint8_t y);
extern uint8_t current_oam;
void sprites_prepare_frame(void);

// EXTERN: Le dice al motor que estas variables están en otro archivo (.c)
extern uint8_t lista_vram_offsets[MAX_SPRITES];
extern uint8_t vram_pointer;

#endif