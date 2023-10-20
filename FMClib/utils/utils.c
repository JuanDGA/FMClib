#include "utils.h"
#include "../fmc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * binario(int x) {
    int entero = x;
    int numero_bits = 0;
    while (entero > 0) {
        numero_bits++;
        entero = entero / 2;
    }
    char * bits = calloc(numero_bits, sizeof(char));

    for (int i = 0; i < numero_bits; i++) bits[i] = '0';

    int pos = 1;
    entero = x;

    while (entero > 0) {
        int residuo = modulo(entero, 2);
        entero = entero / 2;
        char bit;
        sprintf(&bit, "%d", residuo);
        bits[numero_bits - pos] = bit;
        pos++;
    }

    return bits;
}

int obtener_posicion(char letra, char * alfabeto) {
    int tamanio_alfabeto = (int) strlen(alfabeto);

    for (int i = 0; i < tamanio_alfabeto; i++) {
        if (letra == alfabeto[i]) return i;
    }

    return -1;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}