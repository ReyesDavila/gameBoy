#include "../../../engine/game_bridge.h"

void Object0_init(Object0 *self){
    (void)self;

    // Al no haber x en el hijo, "self->base.x" es lo que manda
    // Si usas punteros Entity*, usa self->x (apuntará a la base)
    self->base.x = 80; 
    self->base.y = 72;
    
    // Sincronizamos la matemática de sub-píxeles
    self->x2 = self->base.x << 8;
    self->y2 = self->base.y << 8;

    self->vx = 0; self->vy = 0;
    self->vx_max = 256; self->vy_max = 256;
    self->ax = 6; self->ay = 6;
    self->fx = 2; self->fy = 2;


}