#include "../core/globals.h"

void game_logic(void) {


    //movimiento x
    uint8_t control = 0;
    control = !!(joy_check(J_LEFT)+joy_check(J_RIGHT)==1);
    if(control){pelota->dx = 1-2*joy_check(J_LEFT);}
    pelota->vx +=control*pelota->dx*pelota->ax;
    if(!control){pelota->vx-=sign(pelota->vx);}
    if(!control & abs(pelota->vx)<5){pelota->vx=0;}
    if(abs(pelota->vx)>pelota->vx_max){pelota->vx = sign(pelota->vx)*pelota->vx_max;}
    pelota->x2 += pelota->vx;
    pelota->x = (pelota->x2 >> 5);

    //movimiento y
    uint8_t controly = 0;
    controly = !!(joy_check(J_UP)+joy_check(J_DOWN)==1);
    if(controly){pelota->dy = 1-2*joy_check(J_UP);}
    pelota->vy +=controly*pelota->dy*pelota->ay;
    if(!controly){pelota->vy-=sign(pelota->vy);}
    if(!controly & abs(pelota->vy)<5){pelota->vy=0;}
    if(abs(pelota->vy)>pelota->vy_max){pelota->vy = sign(pelota->vy)*pelota->vy_max;}
    pelota->y2 += pelota->vy;
    pelota->y = (pelota->y2 >> 5);

    #ifdef MODO_DEBUG
        debug_begin();
        debug_watch("control", control);
        debug_watch("x",pelota->vx);
        debug_watch("y",pelota->y);
    #endif
}