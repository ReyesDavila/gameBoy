#include "./audio.h"

// El qué: NR52_REG = 0x80;
// El porqué: Enciende la unidad de sonido de la Game Boy.
// El cómo: Sin esto, cualquier sonido que enviemos será ignorado por el hardware.
void sound_init(void) {
    NR52_REG = 0x80; // Enciende el sonido
    NR51_REG = 0xFF; // Envía el sonido a ambos altavoces (estéreo)
    NR50_REG = 0x77; // Volumen máximo
}

void sound_play(UINT8 index) {
    switch(index) {
        case SND_BOUNCE:
            // Sonido de rebote usando el Canal 1 (Pulso)
            NR10_REG = 0x00; // Sin cambios de frecuencia
            NR11_REG = 0x81; // Longitud del ciclo de trabajo
            NR12_REG = 0x43; // Volumen y caída (Envolvente)
            NR13_REG = 0x73; // Frecuencia baja
            NR14_REG = 0x86; // Iniciar sonido
            break;
            
        case SND_SCORE:
            // Sonido de punto (más agudo)
            NR10_REG = 0x15;
            NR11_REG = 0x82;
            NR12_REG = 0x63;
            NR13_REG = 0x50;
            NR14_REG = 0x87;
            break;
    }
}

void sound_stop(UINT8 index) {
    // El qué: NR12_REG = 0x00;
    // El porqué: Ponemos el volumen del envolvente en 0.
    // El cómo: El canal sigue activo pero es inaudible de inmediato.
    NR12_REG = 0x00; 
    NR14_REG = 0x80; // Reiniciamos el canal en silencio
}

void sound_stop_all(void) {
    sound_stop(0);
    // Podrías añadir NR22_REG=0, NR32_REG=0, etc. para otros canales.
}