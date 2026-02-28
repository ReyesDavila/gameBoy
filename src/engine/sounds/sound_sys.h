#ifndef SONGS_H
#define SONGS_H
#include <stdint.h>
#include "hUGEDriver.h"

typedef enum { T_HUGE, T_SFX } s_type;
typedef struct { uint8_t ch, r1, r2, r3, r4, r5, dur; } SFX_d;
typedef struct { s_type type; const void *data; } Sound;

extern uint16_t sound_tick;

void sound_init(void);
void sound_play(const Sound *idx);
void sound_loop(const Sound *idx);
void sound_stop(const Sound *idx);
void sound_stop_all(void);
uint8_t sound_isplaying(const Sound *idx);
uint16_t sound_pos(const Sound *idx);
void audio_update(void);
#endif