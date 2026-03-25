#ifndef ENGINE_SCENES_H
#define ENGINE_SCENES_H

#include <stdint.h>

typedef struct { void (*init)(void); } Scene;
extern Scene scene_list[];
extern uint8_t scene_count; // Declaramos que existe un contador

#define CREAR_ESCENA(nombre) void nombre##_init(void);

void load_scene(uint8_t index);

#endif