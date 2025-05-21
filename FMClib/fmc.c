#include "fmc.h"
#include "utils/utils.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modulo(int numero, int base) {
    if (base == 0) {
        // Or handle error appropriately, e.g., return a specific value or print an error.
        // For now, let's assume base will not be zero based on typical usage in crypto.
        // Consider adding proper error handling if base can be zero.
        return 0; 
    }
    if (base < 0) {
      // Modulo with negative base is not standard in this context, make base positive.
      base = -base;
    }
    int resultado = numero % base;
    if (resultado < 0) {
        resultado += base;
    }
    return resultado;
}

int es_primo(int p) {
    if (p <= 1) { // Numbers less than or equal to 1 are not prime
        return 0;
    }
    if (p <= 3) { // 2 and 3 are prime
        return 1;
    }
    // Eliminate multiples of 2 and 3
    if (modulo(p, 2) == 0 || modulo(p, 3) == 0) {
        return 0;
    }

    // Check divisors from 5 onwards, using a step of 6
    // (i.e., 5, 7, 11, 13, 17, 19, ...)
    // All primes greater than 3 can be written in the form 6k ± 1
    int hasta = (int)sqrt((double)p);
    for (int i = 5; i <= hasta; i = i + 6) {
        if (modulo(p, i) == 0 || modulo(p, i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

int gcd(int num_a, int num_b, int imprimir_pasos) {
    int a = num_a; 
    int b = num_b;

    // Handle cases with zero. gcd(x,0) = |x|. gcd(0,0) is often undefined, can return 0 or error.
    if (a == 0 && b == 0) return 0; // Or handle as an error

    // Take absolute values.
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    // gcd(x,0) = |x|
    if (a == 0) return b; // b is already abs(b)
    if (b == 0) return a; // a is already abs(a)

    int mayor = max(a, b);
    int menor = min(a, b);
    int remainder;

    // Loop for Euclidean algorithm
    while (menor != 0) {
        remainder = modulo(mayor, menor);
        if (imprimir_pasos) {
            printf("%d = %d * %d + %d\n", mayor, mayor / menor, menor, remainder);
        }
        mayor = menor;
        menor = remainder;
    }
    // When menor (which was the remainder) is 0, mayor (which was the divisor) is the GCD.
    return mayor;
}

int inverso(int numero_orig, int base, int imprimir_pasos) {
    if (base <= 1) {
        return -1;
    }

    if (gcd(numero_orig, base, 0) != 1) {
        return -1; 
    }

    int a = modulo(numero_orig, base);
    
    if (a == 0 && base == 1) { // gcd(0,1)=1, inv(0) mod 1 is 0.
        return 0;
    }
    // If a=0 and base > 1, gcd would not be 1.

    // EEA state: a*s + base*t = gcd(a,base)
    // Iteration i:
    // r_i = r_{i-2} - q_i * r_{i-1}
    // s_i = s_{i-2} - q_i * s_{i-1} (coefficients for 'a')
    // t_i = t_{i-2} - q_i * t_{i-1} (coefficients for 'base')

    // Initial values (i=0 and i=1 implicitly)
    int r_im2 = a;    // r_0 = a
    int s_im2 = 1;    // s_0 = 1 (coefficient of 'a' in a = 1*a + 0*base)
    int t_im2 = 0;    // t_0 = 0 (coefficient of 'base' in a = 1*a + 0*base)

    int r_im1 = base; // r_1 = base
    int s_im1 = 0;    // s_1 = 0 (coefficient of 'a' in base = 0*a + 1*base)
    int t_im1 = 1;    // t_1 = 1 (coefficient of 'base' in base = 0*a + 1*base)
    
    int iter = 0;

    if (imprimir_pasos) {
        printf("i | Ri | Qi | si | ti\n");
        // Line for a = (numero % base) which is r_im2 (R0)
        printf("%d | %d | - | %d | %d\n", iter, r_im2, s_im2, t_im2); 
    }

    // Loop continues as long as current remainder (r_im1 initially) is not 0.
    while (r_im1 != 0) {
        iter++;
        // q_i is r_{i-2} / r_{i-1}
        int q_i = r_im2 / r_im1; 

        if (imprimir_pasos) {
            // This line is for r_im1 (current R_i)
            // s_im1 and t_im1 are its Bezout coefficients for a and base
            printf("%d | %d | %d | %d | %d\n", iter, r_im1, q_i, s_im1, t_im1);
        }

        // Calculate r_i, s_i, t_i
        int r_i = modulo(r_im2, r_im1); // r_im2 - q_i * r_im1;
        int s_i = s_im2 - q_i * s_im1;
        int t_i = t_im2 - q_i * t_im1;

        // Update states for next iteration: i-2 becomes i-1, i-1 becomes i
        r_im2 = r_im1;
        s_im2 = s_im1;
        t_im2 = t_im1;

        r_im1 = r_i;
        s_im1 = s_i;
        t_im1 = t_i;
    }

    // After loop, r_im2 holds gcd(a, base), which must be 1 (due to gcd check).
    // s_im2 is the coefficient for 'a' (numero % base).
    // t_im2 is the coefficient for 'base'.
    // So, a * s_im2 + base * t_im2 = gcd(a,base) = 1.
    // The inverse of 'a' ( = numero % base) mod 'base' is s_im2.
    
    int inverse_val = s_im2;
    return modulo(inverse_val, base); // Ensure positive result in [0, base-1]
}

long phi(long m) {
    if (m <= 0) {
        // Phi is usually defined for positive integers. phi(1)=1.
        // Consider returning 0 or an error indicator for m <= 0.
        // Or based on typical cryptographic use, assume m >= 1.
        // Let's return 0 for m <= 0 as a convention.
        return 0;
    }
    if (m == 1) {
        return 1;
    }

    long result = m;
    long p; // Iterator for prime factors

    // Check for divisibility by 2
    if (m % 2 == 0) {
        result = result / 2; // Same as result = result - result / 2;
        while (m % 2 == 0) {
            m = m / 2;
        }
    }

    // Check for odd factors from 3 up to sqrt(m)
    // Note: p * p can overflow if m is large enough, sqrt((double)m) is safer.
    // However, p * p <= m avoids floating point and is common.
    // Given m is long, p will also be long. p*p could exceed LONG_MAX if p > sqrt(LONG_MAX).
    // Max long is 2^63-1. sqrt(2^63-1) is approx 3*10^9. p*p is fine.
    for (p = 3; p * p <= m; p = p + 2) { // Iterate over odd numbers
        if (m % p == 0) {
            result = result / p * (p - 1); // result = result - result / p;
            while (m % p == 0) {
                m = m / p;
            }
        }
    }

    // If m is still greater than 1, then m is a prime factor itself
    if (m > 1) {
        result = result / m * (m - 1); // result = result - result / m;
    }

    return result;
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
    int len_alfabeto = (int) strlen(alfabeto);

    if (len_alfabeto == 0) {
        // Cannot proceed with an empty alphabet, return NULL or handle error.
        // Returning an empty allocated string for safety.
        char *empty_cifrado = calloc(1, sizeof(char));
        if (empty_cifrado) empty_cifrado[0] = '\0';
        return empty_cifrado;
    }

    char * cifrado = calloc(tamanio_texto + 1, sizeof(char));
    if (cifrado == NULL) {
        return NULL; // Allocation failed
    }

    for (int i = 0; i < tamanio_texto; i++) {
        char letra = texto[i];
        int posicion_letra = obtener_posicion(letra, alfabeto);

        if (posicion_letra == -1) {
            // Character not in alphabet. Keep it as is, or replace with a placeholder.
            // Current behavior based on original code: it would proceed with -1.
            // Let's keep the character as is if not found in the alphabet.
            cifrado[i] = letra; 
        } else {
            int letra_cifrada_pos = modulo((clave[0] * posicion_letra) + clave[1], len_alfabeto);
            // Ensure modulo result is not negative if modulo can return negative for negative inputs
            // Our fixed modulo should handle this: result is always in [0, base-1]
            cifrado[i] = alfabeto[letra_cifrada_pos];
        }
    }
    cifrado[tamanio_texto] = '\0'; // Explicitly null-terminate, good practice even with calloc.

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