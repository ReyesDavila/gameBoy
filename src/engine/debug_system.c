#include <gb/gb.h>
#include "../core/globals.h"

#ifdef MODO_DEBUG
#include <stdio.h> // Solo para el truco inicial

void debug_init(void) {
    printf(" "); 
}

static uint8_t row;

// Función interna auxiliar (privada) para procesar el texto
static uint8_t draw_label(uint8_t* buffer, char* label) {
    uint8_t i = 0;
    while (label[i] != '\0' && i < 15) {
        buffer[i] = (uint8_t)label[i] - 32; // Mapeo ASCII a Tiles
        i++;
    }
    return i; // Devuelve cuántos caracteres escribió
}

void debug_msg(char* label) {
    uint8_t buffer[20];
    uint8_t len = draw_label(buffer, label);
    
    // Limpieza de restos al final
    buffer[len++] = 0; 
    buffer[len++] = 0;
    
    set_bkg_tiles(0, row++, len, 1, buffer);
}

void debug_watch(char* label, int16_t value) {
    uint8_t buffer[20];
    uint8_t i = draw_label(buffer, label);
    
    // Añadir separador
    buffer[i++] = 26; // ":"
    buffer[i++] = 0;  // Espacio
    
    // --- Lógica de conversión de número ---
    int16_t v = (value < 0) ? -value : value;
    uint8_t temp_num[6];
    int8_t p = 0;
    if (v == 0) temp_num[p++] = 16;
    else {
        while (v > 0) {
            temp_num[p++] = (v % 10) + 16;
            v /= 10;
        }
        if (value < 0) temp_num[p++] = 13;
    }
    while (p > 0) buffer[i++] = temp_num[--p];
    // ---------------------------------------

    buffer[i++] = 0;
    buffer[i++] = 0;
    set_bkg_tiles(0, row++, i, 1, buffer);
}

void debug_begin(void) {
    row = 0;
}
#endif