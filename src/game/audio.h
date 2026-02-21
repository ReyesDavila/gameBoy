#ifndef AUDIO_H
#define AUDIO_H

#include <gb/gb.h>

// Definimos índices para nuestros sonidos (como en Game Maker)
#define SND_BOUNCE 0
#define SND_SCORE  1
#define SND_START  2

void sound_init(void); // Nueva: Para encender el chip de sonido
void sound_play(UINT8 index);
void sound_loop(UINT8 index); // Nota: En GB esto requiere manejo de interrupciones, haremos una versión simple.
void sound_stop(UINT8 index);
void sound_stop_all(void);
BOOLEAN sound_isplaying(UINT8 index);

#endif