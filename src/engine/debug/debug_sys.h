#ifndef DEBUG_SYS_H
#define DEBUG_SYS_H

#include <gb/gb.h>
#include <stdint.h>

// Comenta esta línea para desactivar el debug y ganar rendimiento en el juego final
#define MODO_DEBUG

#ifdef MODO_DEBUG
    void debug_init(void);
    void debug_begin(void);
    void debug_watch(int16_t value);
#else
    #define debug_init()
    #define debug_begin()
    #define debug_watch(v)
#endif

#endif