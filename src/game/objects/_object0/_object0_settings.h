#ifndef ENTITY_SETTINGS_H
#define ENTITY_SETTINGS_H
#include "../../engine/objects/entity_mgr.h"

typedef struct {
    Entity base;    // Obligatorio: siempre primero
    int8_t x, y;   // Variable propia del objeto
} Object0;

extern Object0 *obj0; 
#define MAX_Object0 10

extern Object0 Object0_list[MAX_Object0];

// Declaración de funciones (el motor las unirá mediante la Macro)
void Object0_init(Object0 *self);
void Object0_step(Object0 *self);
void Object0_draw(Object0 *self);


#endif