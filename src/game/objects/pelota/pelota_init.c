#include "../../../engine/game_bridge.h"

void pelota_init(void){
    
    pelota = (Entity*)entity_create(0, 0, 4);
    if(pelota) {
        pelota->x = 80;
        pelota->y = 72;
        pelota->vx = 0;
        pelota->vy = 0;
        pelota->vx_max = 64;
        pelota->vy_max =64;
        pelota->dx=0;
        pelota->dy=0;
        pelota->ax=1;
        pelota->ay=1;
  
        pelota->tile_id = 2;
        //pelota->tile_list = brillo_pelota; // Al ser NULL/0, el motor no gasta ciclos en set_sprite_tile
        pelota->list_size = 0;
    }
}