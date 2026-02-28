#ifndef GAME_BRIDGE_H
#define GAME_BRIDGE_H

#include <gb/gb.h>
#include <rand.h>    // <--- AÑADE ESTO para las funciones de azar
#include <stdbool.h>

// --- INCLUDES DEL MOTOR (Engine) ---
#include "video/video_sys.h"
#include "math/math_util.h"
#include "sounds/sound_sys.h"
#include "objects/entity_mgr.h"
#include "scripts/scripts_mgr.h"
#include "joystick/joystick_sys.h"
#include "debug/debug_sys.h"

// --- INCLUDES DEL JUEGO (Game) ---
#include "../game/objects/game_objects.h"
#include "../game/sounds/_sound_data.h"
#include "../game/rooms/rooms_all.h"
#include "../game/sprites/tilesFondo.h"


/* * Estas son DECLARACIONES (Notifican que la función existe)
 * El motor llamará a estas funciones, pero la lógica real
 * estará en src/game/game_init.c y src/game/game_step.c
 */

// Se ejecuta una sola vez al encender la Game Boy (Como Game Start)
void game_init(void);

// Se ejecuta 60 veces por segundo (Como el Step Event de un objeto controlador)
void game_step(void);

void game_draw(void);


#endif