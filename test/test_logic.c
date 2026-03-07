#include <stdio.h>
#include "funciones.h"
#include <gb/gb.h>

int main() {
    printf("--- TEST DE DAÑO ---\n");
    
    int d = calcular_posicion(10, 4); 
    printf("pos ant: %d\n", 10);
    printf("pos nue: %d\n", d);

    return 0;
}