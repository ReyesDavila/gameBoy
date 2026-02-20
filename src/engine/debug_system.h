#ifndef DEBUG_SYSTEM_H
#define DEBUG_SYSTEM_H

#include <gb/gb.h>

// COMENTA esta línea para borrar TODO el debug del juego automáticamente
#define MODO_DEBUG

#ifdef MODO_DEBUG
    void debug_init(void);
    //para inicializar
    
    void debug_begin(void);
    // Para mostrar solo texto
    void debug_msg(char* label); 
    // Para mostrar texto + variable (tu función actual)
    void debug_watch(char* label, int16_t value);
#else
    #define debug_begin(void)
    #define debug_msg(label)
    #define debug_watch(label, value)
#endif

#endif