#include <gb/gb.h>
#include <stdio.h>

void main(void) {
    printf("Hola Desde cero!\n");
    printf("Presiona Start");
    
    while(1) {
        wait_vbl_done();
    }
}