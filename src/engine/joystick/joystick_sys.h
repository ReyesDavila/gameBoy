#ifndef JOYSTICK_SYS_H
#define JOYSTICK_SYS_H

#include <gb/gb.h>
#include <stdint.h>

// Botones nativos de GBDK (Máscaras de bits):
// J_START  : Botón Start
// J_SELECT : Botón Select
// J_A      : Botón A
// J_B      : Botón B
// J_UP     : Cruceta Arriba
// J_DOWN   : Cruceta Abajo
// J_LEFT   : Cruceta Izquierda
// J_RIGHT  : Cruceta Derecha

extern uint8_t _joy_current, _joy_previous;

void joystick_update(void);
uint8_t joystick_check_button(uint8_t btn);
uint8_t joystick_pressed_button(uint8_t btn);
uint8_t joystick_released_button(uint8_t btn);
int8_t joystick_xpos(void);
int8_t joystick_ypos(void);

#endif