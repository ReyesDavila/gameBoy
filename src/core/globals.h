#ifndef GLOBALS_H
#define GLOBALS_H

#include <gb/gb.h>

// --- ENGINE (Herramientas de bajo nivel) ---
#include "../engine/debug_system.h"
#include "../engine/joypad_system.h"
#include "../game/entity_manager.h"

// Matemáticas rápidas para Game Boy (sin librerías pesadas)
#define abs(n) ((n) < 0 ? -(n) : (n))
#define sign(n) ((n > 0) - (n < 0))

// --- GAME (Lógica de alto nivel) ---
// Aquí declaras las funciones que MAIN (Core) llamará, 
// pero que el desarrollador del JUEGO escribirá.
void game_init(void);
void game_logic(void);

#endif