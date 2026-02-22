#ifndef AUDIO_H
#define AUDIO_H

#include <gb/gb.h>

typedef struct {
    UINT8 channel;
    UINT8 reg0, reg1, reg2, reg3, reg4;
    UINT16 duration; // Duración en frames (para saber cuándo re-activar el loop)
} SoundResource;

// Interfaz estilo Game Maker
void sound_init(void);
void sound_play(UINT8 index);
void sound_loop(UINT8 index);
void sound_stop(UINT8 index);
void sound_stop_all(void);
BOOLEAN sound_isplaying(UINT8 index);

// Interno del motor
void audio_update(void); 

#endif