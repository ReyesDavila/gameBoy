#include "../../engine/sounds/sound_sys.h"
#include "_sound_data.h"

extern const hUGESong_t sample_song;
static const SFX_d sfx_db[] = {
    {2, 0x00, 0x81, 0x42, 0x73, 0x86, 10}, // Moneda (C2)
    {1, 0x00, 0x81, 0x51, 0x5E, 0x86, 8},  // Disparo (C1)
    {4, 0x00, 0x3B, 0x64, 0x73, 0x80, 30}, // Explosion (C4)
    {1, 0x15, 0x81, 0x43, 0x73, 0x86, 15}, // Salto (C1)
    {1, 0x00, 0x82, 0x91, 0xFF, 0x87, 20}, // Error (C1 Grave)
    {2, 0x00, 0x42, 0x73, 0x20, 0x85, 40}, // Inicio (C2)
    {2, 0x00, 0x81, 0xF3, 0x73, 0x86, 25}, // Estrella (C2 Agudo)
    {1, 0x22, 0x81, 0x43, 0x73, 0x86, 30}, // Energia (C1 Sweep up)
    {4, 0x00, 0x01, 0x52, 0x11, 0x80, 15}, // Puerta (C4 Ruido bajo)
    {2, 0x00, 0x01, 0xF1, 0x73, 0x86, 50}  // Portal (C2 Modulado)
};

const Sound snd_sample_song = { T_HUGE, &sample_song};
const Sound snd_coin = { T_SFX, &sfx_db[0] };
const Sound snd_shoot = { T_SFX, &sfx_db[1] };
const Sound snd_explode = { T_SFX, &sfx_db[2] };
const Sound snd_jump = { T_SFX, &sfx_db[3] };
const Sound snd_error = { T_SFX, &sfx_db[4] };
const Sound snd_start = { T_SFX, &sfx_db[5] };
const Sound snd_star = { T_SFX, &sfx_db[6] };
const Sound snd_powerup = { T_SFX, &sfx_db[7] };
const Sound snd_door = { T_SFX, &sfx_db[8] };
const Sound snd_portal = { T_SFX, &sfx_db[9] };