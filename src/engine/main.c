#include "engine_api.h"
#include "../game/game_api.h"

void main(void){
    renderer_init();
    game_init();

    while(1)
    {
        sprites_reset();
        game_step();
        wait_vbl_done();
    }
}