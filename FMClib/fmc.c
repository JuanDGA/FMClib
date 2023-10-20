#include "fmc.h"
#include "utils/utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modulo(int numero, int base) {
    int entero = numero / base;

    int resultado = numero - (base * entero);

    return resultado;
}

int es_primo(int p) {
    int hasta = (int) sqrtf((float) p);

    if (hasta * hasta == p) return 0;

    for (int i = 2; i < hasta; i++) {
        if (modulo(p, i) == 0) return 0;
    }

    return 1;
}

int gcd(int a, int b, int imprimir_pasos) {
    int mayor = max(a, b);
    int menor = min(a, b);

    int multiplicando = mayor / menor;
    int sumando = mayor - (multiplicando * menor);

    if (imprimir_pasos) printf("%d = %d * %d + %d\n", mayor, multiplicando, menor, sumando);

    if (sumando == 0) return menor;

    while (1) {
        mayor = menor;
        menor = sumando;

        multiplicando = mayor / menor;

        int nuevo_sumando = mayor - (multiplicando * menor);

        if (imprimir_pasos) printf("%d = %d * %d + %d\n", mayor, multiplicando, menor, nuevo_sumando);

        if (nuevo_sumando == 0) break;

        sumando = nuevo_sumando;
    }

    return sumando;
}

int inverso(int numero, int base, int imprimir_pasos) {
    // Verificamos que sea posible calcular el inverso
    if (gcd(numero, base, 0) != 1 || base <= 1) return -1;

    int mayor = max(numero, base); //RI
    int menor = min(numero, base);

    int multiplicando = mayor / menor; // QI
    int sumando = mayor - (multiplicando * menor);

    int multiplicandoAnterior = multiplicando;

    int si = 1;
    int ti = 0;
    int siAnterior = 1;
    int tiAnterior = 0;

    if (imprimir_pasos) printf("i | Ri | Qi | si | ti\n");

    int i = 0;

    while (1) {
        if (i == 1) {
            siAnterior = si;
            tiAnterior = ti;
            si = 0;
            ti = 1;
        } else if (i > 0) {
            int nuevoSi = siAnterior - (multiplicandoAnterior * si);
            int nuevoTi = tiAnterior - (multiplicandoAnterior * ti);
            siAnterior = si;
            tiAnterior = ti;
            si = nuevoSi;
            ti = nuevoTi;
        }

        if (i != 0) {
            mayor = menor;
            menor = sumando;
        }

        multiplicandoAnterior = multiplicando;
        multiplicando = mayor / menor;

        int nuevo_sumando = mayor - (multiplicando * menor);

        if (i == 0 && imprimir_pasos) printf("%d | %d | - | %d | %d\n", i, mayor, si, ti);
        else if (imprimir_pasos) printf("%d | %d | %d | %d | %d\n", i, mayor, multiplicandoAnterior, si, ti);

        i++;

        if (nuevo_sumando == 0) break;

        sumando = nuevo_sumando;
    }
    int nuevoSi = siAnterior - (multiplicandoAnterior * si);
    int nuevoTi = tiAnterior - (multiplicandoAnterior * ti);

    if (imprimir_pasos) printf("%d | %d | %d | %d | %d\n", i, menor, multiplicando, nuevoSi, nuevoTi);

    while (nuevoSi < 0) nuevoSi += base;
    while (nuevoTi < 0) nuevoTi += base;

    if (modulo(nuevoSi * numero, base) == 1) return nuevoSi;
    return nuevoTi;
}

long phi(long m) {
    int i = 2;
    int numero = m;

    long cantidad_coprimos = 1;

    while (i * i <= numero) {
        if (modulo(numero, i)) i += 1;
        else {
            numero = numero / i;
            cantidad_coprimos *= (i - 1);
        }
    }

    if (numero > 1) cantidad_coprimos *= (numero - 1);

    return cantidad_coprimos;
}

int square_multiply(int x, int y, int z, int imprimir_pasos) {
    if (imprimir_pasos) printf("Calculando %d^%d mod %d\n", x, y, z);
    if (imprimir_pasos) printf("Calculando %d en binario\n", y);
    char * bin_y = binario(y);
    int k = (int) strlen(bin_y);
    if (imprimir_pasos) printf("%d en binario es %s | K-bits = %d\n", y, bin_y, k);
    if (imprimir_pasos) printf("\nAplicando algoritmo...\n");

    int w = 1;
    for (int i = k - 1; i >= 0; i--) {
        int bin_pos = (k - i) - 1;
        if (imprimir_pasos) printf("\nAplicando Yi = %d\n", i);
        if (imprimir_pasos) printf("w = w^2 mod z | w = %d^2 mod %d\n", w, z);
        w = modulo(w * w, z);
        if (imprimir_pasos) printf("w^2 mod z = %d\n", w);
        if (bin_y[bin_pos] == '1') {
            if (imprimir_pasos) printf("Yi es 1 -> w = wx mod z -> w = %d*%d mod %d\n", w, x, z);
            w = modulo(w * x, z);
            if (imprimir_pasos) printf("wx mod z = %d\n", w);
        }
    }

    if (imprimir_pasos) printf("Resultado: %d^%d mod %d = %d\n", x, y, z, w);
    free(bin_y);
    return w;
}

char * cifrar_afin(int * clave, char * texto, char * alfabeto) {
    int tamanio_texto = (int) strlen(texto);
    char * cifrado = calloc(tamanio_texto, sizeof(char));

    for (int i = 0; i < tamanio_texto; i++) {
        char letra = texto[i];
        int posicion_letra = obtener_posicion(letra, alfabeto);

        int letra_cifrada = modulo((clave[0] * posicion_letra) + clave[1], 26);
        cifrado[i] = alfabeto[letra_cifrada];
    }

    return cifrado;
}

char * descifrar_afin(int * clave, char * texto_cifrado, char * alfabeto) {
    int tamanio_texto = (int) strlen(texto_cifrado);
    char * descifrado = calloc(tamanio_texto, sizeof(char));

    for (int i = 0; i < tamanio_texto; i++) {
        char letra_cifrada = texto_cifrado[i];
        int posicion_letra = obtener_posicion(letra_cifrada, alfabeto);

        int a_inverso = inverso(clave[0], (int) strlen(alfabeto), 0);

        int letra = modulo(a_inverso * (posicion_letra - clave[1]), (int) strlen(alfabeto));
        descifrado[i] = alfabeto[letra];
    }

    return descifrado;
}

int cifrar_rsa(const int * clave, int descifrado) {
    int n = clave[0];
    int e = clave[1];

    return square_multiply(descifrado, e, n, 0);
}

int descifrar_rsa(const int * clave_publica, const int * clave_privada, int cifrado) {
    int p = clave_privada[0];
    int q = clave_privada[1];

    int n = clave_publica[0];
    int e = clave_publica[1];

    int d = inverso(e, (p - 1) * (q - 1), 0);

    return square_multiply(cifrado, d, n, 0);
}