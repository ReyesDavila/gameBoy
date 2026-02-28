#include "../../../engine/game_bridge.h"

void Object0_step(Object0 *self) {
    (void)self;

    int8_t jx = joystick_xpos();
    self->x += jx;









    
    #ifdef MODO_DEBUG
        debug_begin();
        debug_watch(self->x);
        debug_watch(self->y);
    #endif

}
