#include "../engine/audio.h"
#include "audio_defines.h"

const SoundResource game_sounds[] = {
    // Canal 1: Salto (Pulso con Sweep)
    {1, 0x15, 0x81, 0x43, 0x73, 0x86, 20},
    // Canal 4: Explosión (Ruido)
    {4, 0x00, 0x01, 0xF3, 0x73, 0x80, 45},
    // Canal 2: Melodía BGM (Pulso limpio)
    {2, 0x00, 0x82, 0x63, 0x50, 0x87, 120}
};

const UINT8 game_sounds_count = 3;