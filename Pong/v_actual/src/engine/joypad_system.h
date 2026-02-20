#ifndef JOYPAD_SYSTEM_H
#define JOYPAD_SYSTEM_H

#include <gb/gb.h>
#include <stdint.h>

void joypad_update(void);      // Se llama una vez por frame en el main
uint8_t joy_pressed(uint8_t btn);  // ¿Se acaba de pulsar este frame?
uint8_t joy_check(uint8_t btn);    // ¿Está manteniéndose pulsado?
uint8_t joy_released(uint8_t btn); // ¿Se acaba de soltar?

#endif