#include "../game_entitys.h"
#include "../gml_prose.h"

void Entity01_step(Entity01 *self){
    (void)self;

    y+=1;
    
    draw_tile_spr(x, y,3);
}