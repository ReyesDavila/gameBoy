#include <gb/gb.h>
#include <stddef.h>
#include "sound_sys.h"

uint16_t sound_tick = 0;
static const Sound *c_bgm = NULL;
static const Sound *c_sfx = NULL;
static uint8_t s_t = 0;

void sound_init(void) {NR52_REG = 0x80; NR51_REG = 0xFF;NR50_REG = 0x77;}
void sound_play(const Sound *idx){ if(idx->type==T_HUGE){ c_bgm=idx; hUGE_init((const hUGESong_t *)idx->data); sound_tick=0; } else { c_sfx=idx; const SFX_d *d=(const SFX_d *)idx->data; s_t=d->dur; if(d->ch==1){ NR10_REG=d->r1; NR11_REG=d->r2; NR12_REG=d->r3; NR13_REG=d->r4; NR14_REG=d->r5; } else if(d->ch==2){ NR21_REG=d->r2; NR22_REG=d->r3; NR23_REG=d->r4; NR24_REG=d->r5; } else if(d->ch==4){ NR41_REG=d->r2; NR42_REG=d->r3; NR43_REG=d->r4; NR44_REG=d->r5; } } }
void sound_loop(const Sound *idx){ sound_play(idx); }
void sound_stop(const Sound *idx){ if(idx==c_bgm){ c_bgm=NULL; sound_tick=0; NR12_REG=NR22_REG=NR32_REG=NR42_REG=0; } else if(idx==c_sfx){ c_sfx=NULL; s_t=0; } }
void sound_stop_all(void){ c_bgm=NULL; c_sfx=NULL; s_t=0; sound_tick=0; NR12_REG=NR22_REG=NR32_REG=NR42_REG=0; }
uint8_t sound_isplaying(const Sound *idx){ return (idx==c_bgm || (idx==c_sfx && s_t>0)); }
uint16_t sound_pos(const Sound *idx){ if(idx->type==T_HUGE && idx==c_bgm) return (uint16_t)sound_tick; if(idx->type==T_SFX && idx==c_sfx) return s_t; return 0; }
void audio_update(void){ if(s_t>0) s_t--; if(c_bgm!=NULL){ hUGE_dosound(); sound_tick++; } }


