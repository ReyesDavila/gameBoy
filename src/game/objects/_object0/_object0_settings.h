#ifndef ENTITY_SETTINGS_H
#define ENTITY_SETTINGS_H
#include "../../engine/objects/entity_mgr.h"

typedef struct {
    Entity base;    // Obligatorio: siempre primero
    int16_t x2, y2;   // Variable propia del objeto
    int16_t vx, vy;
    int16_t vx_max, vy_max;
    int8_t dx, dy, ax, ay, fx, fy;
} Object0;

  
extern Object0 *obj0; 
#define MAX_Object0 10

extern Object0 Object0_list[MAX_Object0];

// Declaración de funciones (el motor las unirá mediante la Macro)
void Object0_init(Object0 *self);
void Object0_step(Object0 *self);
void Object0_draw(Object0 *self);


#endif