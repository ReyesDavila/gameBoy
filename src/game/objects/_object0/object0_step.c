#include "../../../engine/game_bridge.h"

void Object0_step(Object0 *self) {
    (void)self;

    // --- MOVIMIENTO X ---
    int8_t jx = joystick_xpos();
    if(jx) {
        if (jx == -1) self->dx = -1; else self->dx = 1;
        if (self->dx == 1) self->vx += self->ax; else self->vx -= self->ax;
    } else {
        if (self->vx > 0) self->vx -= self->fx;
        else if (self->vx < 0) self->vx++;
        if (abs(self->vx) < 5) self->vx = 0;
    }
    if (self->vx > self->vx_max) self->vx = self->vx_max;
    else if (self->vx < -self->vx_max) self->vx = -self->vx_max;
    self->x2 += self->vx;
    self->base.x = (self->x2 >> 8);

    // --- MOVIMIENTO Y ---
    int8_t jy = joystick_ypos();
    if(jy) {
        if (jy == -1) self->dy = -1; else self->dy = 1;
        if (self->dy == 1) self->vy += self->ay; else self->vy -= self->ay;
    } else {
        if (self->vy > 0) self->vy -= self->fy;
        else if (self->vy < 0) self->vy++;
        if (abs(self->vy) < 5) self->vy = 0;
    }
    if (self->vy > self->vy_max) self->vy = self->vy_max;
    else if (self->vy < -self->vy_max) self->vy = -self->vy_max;
    self->y2 += self->vy;
    self->base.y = (self->y2 >> 8);


    draw_tile(self->base.x, self->base.y, 2);

    #ifdef MODO_DEBUG
        debug_begin();
        debug_watch(self->base.x);
        debug_watch(self->base.y);
    #endif

}
