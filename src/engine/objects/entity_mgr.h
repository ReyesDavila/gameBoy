#ifndef ENTITY_MGR_H
#define ENTITY_MGR_H
#include <gb/gb.h>
#include <stdbool.h>

typedef struct Entity Entity;
struct Entity {
    uint8_t active;
    uint8_t solid;        // 1 = Sólido, 0 = Traspasable
    int16_t x, y;
    uint8_t width, height;// Caja de colisión
    void (*init)(Entity *self);
    void (*step)(Entity *self);
    void (*draw)(Entity *self);
};

extern Entity* global_entities[];
extern uint8_t global_entity_count;

void entity_manager_init(void);
void entity_manager_step(void);
void entity_manager_draw(void);

// Funciones internas del motor
Entity* _entity_create_pool(int16_t x, int16_t y, Entity* pool, uint8_t max_count, size_t struct_size, void (*i)(Entity*), void (*s)(Entity*), void (*d)(Entity*));

// MACROS ESTILO GAMEMAKER (Requieren que la variable 'self' exista en el contexto)
#define entity_create(px, py, type) (type*)_entity_create_pool(px, py, (Entity*)type##_list, MAX_##type, sizeof(type), (void(*)(Entity*))type##_init, (void(*)(Entity*))type##_step, (void(*)(Entity*))type##_draw)

#endif