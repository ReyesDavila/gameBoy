#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#define pi 314

// Macros de Game Maker (Alta velocidad)
#define abs(x) ((x)<0 ? -(x) : (x)) // Valor absoluto
#define sign(x) ((x)>0 ? 1 : ((x)<0 ? -1 : 0)) // Signo del número
#define sqr(x) ((int16_t)(x)*(x)) // Cuadrado en 16 bits (Cuidado: máx x=255)
#define min(x,y) ((x)<(y) ? (x) : (y)) // Mínimo de dos valores
#define max(x,y) ((x)>(y) ? (x) : (y)) // Máximo de dos valores
#define mean(x,y) (((x)+(y)) >> 1) // Promedio de dos valores
#define degtorad(x) ((int16_t)(((int16_t)(x) * 9) >> 9)) // Aproximación rápida (x * 0.0175)
#define radtodeg(x) ((int16_t)(((int16_t)(x) * 183) >> 5)) // Aproximación rápida (x * 5.72)

// Funciones de Ángulo y Distancia
extern const int8_t sin_tbl[256]; // Tabla de seno escalada a 128
#define lengthdir_x(len, ang) ((int16_t)(((int16_t)(len) * sin_tbl[(uint8_t)((ang)+64)]) >> 7)) // X del vector 16 bits
#define lengthdir_y(len, ang) ((int16_t)(((int16_t)(len) * sin_tbl[(uint8_t)(ang)]) >> 7)) // Y del vector 16 bits
#define dsin(a) (sin_tbl[(uint8_t)(a)]) // Seno rápido (0-255)
#define dcos(a) (sin_tbl[(uint8_t)((a)+64)]) // Coseno rápido (0-255)

uint16_t random(uint16_t x); // Genera número aleatorio entre 0 y x-1
uint16_t sqrt_int(uint16_t x); // Raíz cuadrada para números enteros
uint16_t point_distance(int16_t x1, int16_t y1, int16_t x2, int16_t y2); // Distancia euclidiana entre puntos
uint8_t point_direction(int16_t x1, int16_t y1, int16_t x2, int16_t y2); // Ángulo entre dos puntos (0-255)
int8_t angle_difference(uint8_t a, uint8_t b); // Diferencia más corta entre dos ángulos

#endif