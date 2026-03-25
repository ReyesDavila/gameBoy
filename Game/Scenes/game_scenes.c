#include "game_scenes.h"

// Definición real del arreglo
Scene scene_list[] = { 
    { scene00_init }
};

// Definición del contador basada en el tamaño real aquí
uint8_t scene_count = sizeof(scene_list) / sizeof(Scene);