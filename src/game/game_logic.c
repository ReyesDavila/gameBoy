#include "../core/globals.h"
#include "./game_objects.h"



void game_logic(void) {

    uint8_t control = 0;
    control = !!(joy_check(J_LEFT)+joy_check(J_RIGHT)==1);
    if(control){pelota->dx = 1-2*joy_check(J_LEFT);}
    pelota->vx +=control*pelota->dx;
    if(!control){pelota->vx-=sign(pelota->vx);}
    if(!control & abs(pelota->vx)<5){pelota->vx=0;}
    if(abs(pelota->vx)>pelota->vx_max){pelota->vx = sign(pelota->vx)*pelota->vx_max;}
    pelota->x+=pelota->vx;

    #ifdef MODO_DEBUG
        debug_begin();
        debug_watch("control", control);
        debug_watch("x",pelota->dx);
        debug_watch("y",pelota->y);
    #endif
}