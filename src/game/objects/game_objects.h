#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "../../engine/objects/entity_mgr.h"

// EL USUARIO DEFINE SU PROPIA ESTRUCTURA (Importante: x, y, tile_id, active deben ir primero)
struct Entity {
    // --- 1. CABECERA DEL MOTOR (¡PROHIBIDO MOVER DE ORDEN!) ---
    int16_t x, y;          // Posición en píxeles
    uint8_t tile_id;       // El tile actual
    uint8_t active;        // Si está vivo o no
    uint8_t* tile_list;    // Lista de animación
    uint8_t list_size;     // Tamaño de la lista
    
    // --- 2. VARIABLES DEL USUARIO (Tus físicas personalizadas) ---
    int32_t x2, y2;        // OJO: Las subí a int32_t para evitar desbordamientos en sub-píxeles (>> 5)
    int16_t vx, vy;
    int16_t ax, ay;
    int16_t vx_max, vy_max;
    int8_t dx, dy;
    uint8_t frame_idx;
};

#define MI_CANTIDAD_ENTIDADES 20 // ¡El usuario decide el número!

extern Entity mi_pool_personalizado[MI_CANTIDAD_ENTIDADES]; // <--- FALTA ESTO
extern Entity* pelota;
extern uint8_t brillo_pelota[]; // <--- FALTA ESTO

/* --- Objetos --- */
void object_init(void);
void object_step(void);
void object_draw(void);

void pelota_init(void);
void pelota_step(void);

#endif