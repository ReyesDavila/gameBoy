#include "engine_scenes.h"

void load_scene(uint8_t index) { 
    if (index < scene_count) { 
        scene_list[index].init(); 
    } 
}