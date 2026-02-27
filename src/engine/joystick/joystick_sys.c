#include "joystick_sys.h"

uint8_t _joy_current = 0, _joy_previous = 0;

void joystick_update(void) {_joy_previous = _joy_current;_joy_current = joypad();}
uint8_t joystick_check_button(uint8_t btn) { return (_joy_current & btn); }
uint8_t joystick_pressed_button(uint8_t btn) { return ((_joy_current & btn) && !(_joy_previous & btn)); }
uint8_t joystick_released_button(uint8_t btn) { return (!(_joy_current & btn) && (_joy_previous & btn)); }
int8_t joystick_xpos(void) {if (_joy_current & J_LEFT) return -1;if (_joy_current & J_RIGHT) return 1;return 0;}
int8_t joystick_ypos(void) {if (_joy_current & J_UP) return -1;if (_joy_current & J_DOWN) return 1;return 0;}