#include "./audio.h"

extern const SoundResource game_sounds[];
extern const UINT8 game_sounds_count;

static UINT16 counters[10]; 
static BOOLEAN looping[10];
static BOOLEAN playing[10];

void sound_init(void) {
    NR52_REG = 0x80; // Master On
    NR51_REG = 0xFF; // Todo a ambos altavoces
    NR50_REG = 0x77; // Volumen máximo
}

void sound_play(UINT8 index) {
    if (index >= game_sounds_count) return;
    const SoundResource* s = &game_sounds[index];
    
    looping[index] = FALSE;
    playing[index] = TRUE;
    counters[index] = s->duration;
    
    // Switch de canales: Cada uno tiene sus propios registros
    switch(s->channel) {
        case 1:
            NR10_REG = s->reg0; NR11_REG = s->reg1; NR12_REG = s->reg2;
            NR13_REG = s->reg3; NR14_REG = s->reg4;
            break;
        case 2:
            NR21_REG = s->reg1; NR22_REG = s->reg2;
            NR23_REG = s->reg3; NR24_REG = s->reg4;
            break;
        case 3:
            NR30_REG = s->reg0; NR31_REG = s->reg1; NR32_REG = s->reg2;
            NR33_REG = s->reg3; NR34_REG = s->reg4;
            break;
        case 4:
            NR41_REG = s->reg1; NR42_REG = s->reg2;
            NR43_REG = s->reg3; NR44_REG = s->reg4;
            break;
    }
}

void sound_loop(UINT8 index) {
    sound_play(index);
    looping[index] = TRUE;
}

void sound_stop(UINT8 index) {
    if (index >= game_sounds_count) return;
    const SoundResource* s = &game_sounds[index];
    
    playing[index] = FALSE;
    looping[index] = FALSE;

    // Silenciamos el canal específico poniendo su volumen (Envelope) en 0
    switch(s->channel) {
        case 1: NR12_REG = 0; break;
        case 2: NR22_REG = 0; break;
        case 3: NR32_REG = 0; break; // En canal 3 es el nivel de salida
        case 4: NR42_REG = 0; break;
    }
}

void sound_stop_all(void) {
    for(UINT8 i = 0; i < game_sounds_count; i++) {
        sound_stop(i);
    }
}

BOOLEAN sound_isplaying(UINT8 index) {
    return (index < game_sounds_count) ? playing[index] : FALSE;
}

void audio_update(void) {
    for(UINT8 i = 0; i < game_sounds_count; i++) {
        if(playing[i]) {
            if(counters[i] > 0) {
                counters[i]--;
            } else {
                if(looping[i]) sound_play(i);
                else playing[i] = FALSE;
            }
        }
    }
}