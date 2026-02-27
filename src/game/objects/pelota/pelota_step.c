#include "../../../engine/game_bridge.h"

void pelota_step(void) {

        // --- MOVIMIENTO X ---

    // Usamos XOR (^) para saber si solo uno está presionado (evita sumas y comparaciones)
    uint8_t control = joystick_xpos(); 

    if(control) {
        // En lugar de: 1 - 2 * joy_l
        // Usamos un simple if para asignar la dirección
        if (joystick_xpos() == -1) pelota->dx = -1; else pelota->dx = 1;
        
        // En lugar de: pelota->vx += control * pelota->dx * pelota->ax
        // Como sabemos que control es 1, sumamos o restamos la aceleración directamente
        if (pelota->dx == 1) pelota->vx += pelota->ax; else pelota->vx -= pelota->ax;
    } else {
        // Fricción manual rápida (reemplaza sign() y multiplicaciones)
        if (pelota->vx > 0) pelota->vx--;
        else if (pelota->vx < 0) pelota->vx++;
        
        if (abs(pelota->vx) < 5) pelota->vx = 0;
    }

    // Límite de velocidad (reemplaza sign() * max)
    if (pelota->vx > pelota->vx_max) pelota->vx = pelota->vx_max;
    else if (pelota->vx < -pelota->vx_max) pelota->vx = -pelota->vx_max;

    pelota->x2 += pelota->vx;
    pelota->x = (pelota->x2 >> 5);

    // --- MOVIMIENTO Y ---
    uint8_t controly = joystick_ypos();

    if(controly) {
        if (joystick_ypos()==-1) pelota->dy = -1; else pelota->dy = 1;
        
        if (pelota->dy == 1) pelota->vy += pelota->ay; else pelota->vy -= pelota->ay;
    } else {
        if (pelota->vy > 0) pelota->vy--;
        else if (pelota->vy < 0) pelota->vy++;
        
        if (abs(pelota->vy) < 5) pelota->vy = 0;
    }

    if (pelota->vy > pelota->vy_max) pelota->vy = pelota->vy_max;
    else if (pelota->vy < -pelota->vy_max) pelota->vy = -pelota->vy_max;

    pelota->y2 += pelota->vy;
    pelota->y = (pelota->y2 >> 5);


}