#include "joypad_system.h"

static uint8_t joy_now;
static uint8_t joy_prev;

void joypad_update(void) {
    joy_prev = joy_now;
    joy_now = joypad();
}

uint8_t joy_check(uint8_t btn) {
    // El !! convierte cualquier número distinto de cero en 1
    return !!(joy_now & btn); 
}

uint8_t joy_pressed(uint8_t btn) {
    return !!((joy_now & btn) && !(joy_prev & btn));
}

uint8_t joy_released(uint8_t btn) {
    return !!(!(joy_now & btn) && (joy_prev & btn));
}