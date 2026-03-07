#include "../game_entitys.h"
#include "../gml_prose.h"

void Entity02_step(Entity02 *self){
    (void)self;

    x+=place_free(x+1,y);
    
    draw_tile_spr(x, y,4);
}