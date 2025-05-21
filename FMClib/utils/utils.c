#include "utils.h"
#include "../fmc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * binario(int x) {
    if (x < 0) {
        // Or handle error, or convert to unsigned representation if desired.
        // Current implementation implicitly assumes x >= 0.
        // For now, let's return NULL or an empty string for negative numbers
        // as the original function's logic doesn't support them.
        // Returning "0" for simplicity to avoid NULL issues downstream if not checked.
        // Or, more safely, an empty allocated string.
        char *empty_bits = calloc(1, sizeof(char));
        if (empty_bits) empty_bits[0] = '\0';
        return empty_bits; // Or handle error more explicitly
    }

    if (x == 0) {
        char *bits = calloc(2, sizeof(char)); // "0" + null terminator
        if (bits == NULL) return NULL; // Allocation check
        bits[0] = '0';
        bits[1] = '\0';
        return bits;
    }

    int temp_x = x;
    int numero_bits = 0;
    while (temp_x > 0) {
        numero_bits++;
        temp_x /= 2;
    }

    // numero_bits will be correct here, e.g. x=1 -> 1 bit, x=2 -> 2 bits ("10")

    char *bits = calloc(numero_bits + 1, sizeof(char)); // +1 for null terminator
    if (bits == NULL) return NULL; // Allocation check
    bits[numero_bits] = '\0'; // Null terminate

    temp_x = x;
    int index = numero_bits - 1; // Start filling from the end
    while (temp_x > 0) {
        bits[index--] = (temp_x % 2 == 1) ? '1' : '0';
        temp_x /= 2;
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