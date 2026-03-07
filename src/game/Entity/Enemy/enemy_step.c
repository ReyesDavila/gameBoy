#include "../game_entitys.h"
#include "../gml_prose.h"

int8_t framex = 0;

void Enemy_step(Enemy *self){
    (void)self;

    framex++;
    if(framex==5)
    {
        y+=place_free(x,y+1);
        framex=0;
    }
    draw_tile_spr(x, y,5);
}