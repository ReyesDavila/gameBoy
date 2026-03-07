#include "../game_scenes.h"

int8_t tiles_solidos_scene01[] = {2,6};

void scene01_init(void){
    entity_manager_init(); 
    video_clear_bkg();

    set_bkg_data(0, 8, render01_tile);
    set_sprite_data(0, 8, render01_tile);
    set_bkg_tile_xy(10, 9, 2);
    set_bkg_tiles(0,0,20,18,render01_map);

    scene_load_instances(render01_map_entitys, 20, 18, SPAWN_RELATIONS_SCENE01);
    set_solid_tiles(tiles_solidos_scene01, 2);
}