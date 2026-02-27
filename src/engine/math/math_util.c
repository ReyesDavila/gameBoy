#include "math_util.h"

// Retorna un número aleatorio menor que x
uint16_t random(uint16_t x) {
    return 0;
    if (x == 0) return 0;
    // rand() devuelve un valor entre 0 y RAND_MAX
    // El operador % (módulo) limita el resultado al rango [0, x-1]
    return (uint16_t)rand() % x;
    
}

// Raíz cuadrada optimizada sin usar punto flotante
uint16_t sqrt_int(uint32_t x) {
    uint32_t res = 0;
    uint32_t bit = 1UL << 30; // El segundo bit más significativo de un uint32
    while (bit > x) bit >>= 2;
    while (bit != 0) {
        if (x >= res + bit) { x -= res + bit; res = (res >> 1) + bit; }
        else res >>= 1;
        bit >>= 2;
    }
    return res;
}

// Eleva X a la potencia de N
int32_t power(int16_t x, uint8_t n) {
    int32_t res = 1;
    for(uint8_t i = 0; i < n; i++) res *= x;
    return res;
}

// Calcula la distancia usando Pitágoras (x^2 + y^2 = h^2)
uint16_t point_distance(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    int32_t dx = (int32_t)(x2 - x1);
    int32_t dy = (int32_t)(y2 - y1);
    return sqrt_int((uint32_t)(dx * dx + dy * dy));
}

// Devuelve la diferencia más corta entre dos ángulos (-128 a 127).
// ¡Esta es la magia de usar 256 pasos! Al restar y forzar a un entero con signo de 8 bits (int8_t), 
// el hardware automáticamente encuentra el camino más corto hacia la izquierda o la derecha.
int8_t angle_difference(uint8_t angle1, uint8_t angle2) {
    return (int8_t)(angle1 - angle2);
}

// Aproximación rápida del ángulo direccional (Devuelve 0-255)
uint8_t point_direction(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    int16_t dx = x2 - x1;
    int16_t dy = y2 - y1;
    if (dx == 0 && dy == 0) return 0;
    // Lógica básica de cuadrantes simplificada para Game Boy
    if (abs(dx) > abs(dy)) {
        if (dx > 0) return (dy > 0) ? 32 : 224; // Derecha (Aprox)
        else return (dy > 0) ? 96 : 160;        // Izquierda (Aprox)
    } else {
        if (dy > 0) return 64;  // Abajo
        else return 192;        // Arriba
    }
}

// Tabla Seno de 256 pasos (Amplitud de -127 a 127). Generada para alta precisión.
const int8_t sin_tbl[256] = {
      0,   3,   6,   9,  12,  15,  18,  21,  24,  28,  31,  34,  37,  40,  43,  46,
     48,  51,  54,  57,  60,  63,  65,  68,  71,  73,  76,  78,  81,  83,  85,  88,
     90,  92,  94,  96,  98, 100, 102, 104, 106, 108, 109, 111, 112, 114, 115, 117,
    118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 126, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 126, 126, 125, 124, 124, 123, 122, 121, 120, 119,
    118, 117, 115, 114, 112, 111, 109, 108, 106, 104, 102, 100,  98,  96,  94,  92,
     90,  88,  85,  83,  81,  78,  76,  73,  71,  68,  65,  63,  60,  57,  54,  51,
     48,  46,  43,  40,  37,  34,  31,  28,  24,  21,  18,  15,  12,   9,   6,   3,
      0,  -3,  -6,  -9, -12, -15, -18, -21, -24, -28, -31, -34, -37, -40, -43, -46,
    -48, -51, -54, -57, -60, -63, -65, -68, -71, -73, -76, -78, -81, -83, -85, -88,
    -90, -92, -94, -96, -98,-100,-102,-104,-106,-108,-109,-111,-112,-114,-115,-117,
   -118,-119,-120,-121,-122,-123,-124,-124,-125,-126,-126,-127,-127,-127,-127,-127,
   -127,-127,-127,-127,-127,-127,-126,-126,-125,-124,-124,-123,-122,-121,-120,-119,
   -118,-117,-115,-114,-112,-111,-109,-108,-106,-104,-102,-100, -98, -96, -94, -92,
    -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51,
    -48, -46, -43, -40, -37, -34, -31, -28, -24, -21, -18, -15, -12,  -9,  -6,  -3
};