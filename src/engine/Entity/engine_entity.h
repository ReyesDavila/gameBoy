#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
#include <gb/gb.h>
#include <stdbool.h>

typedef struct Entity Entity;
struct Entity {
    uint8_t active;
    uint8_t solid; // <--- Nuevo campo
    uint8_t x, y;
    uint8_t width, height;// Caja de colisión
    void (*init)(Entity *self);
    void (*step)(Entity *self);
};

extern Entity* global_entities[];
extern uint8_t global_entity_count;

void entity_manager_init(void);
void entity_manager_step(void);

// Funciones internas del motor
Entity* _entity_create_pool(uint8_t x, uint8_t y, Entity* pool, uint8_t max_count, size_t struct_size, void (*i)(Entity*), void (*s)(Entity*));

// MACROS ESTILO GAMEMAKER (Requieren que la variable 'self' exista en el contexto)
#define entity_create(px, py, type) (type*)_entity_create_pool(px, py, (Entity*)type##_list, MAX_##type, sizeof(type), (void(*)(Entity*))type##_init, (void(*)(Entity*))type##_step)


//PARA DECLARAR ENTIDADES
#define DECLARE_ENTITY(NAME, MAX_INSTANCES, EXTRA_FIELDS) \
    enum { MAX_##NAME = MAX_INSTANCES }; \
    typedef struct { \
        Entity base; \
        EXTRA_FIELDS \
    } NAME; \
    extern NAME NAME##_list[MAX_##NAME]; \
    void NAME##_init(NAME *self); \
    void NAME##_step(NAME *self)

    /*
        // Capa de traducción GML -> C
        #define x (self->base.x)
        #define y (self->base.y)
        #define width (self->base.width)
        #define height (self->base.height)
    */

#endif