#include <stdio.h>
#include <stdlib.h> // Added for free()
#include "FMClib/utils/utils.h"
#include "FMClib/fmc.h"

int main() {
    int p = 89;
    int q = 101;
    int e = 7;
    int n = p * q;

    int clave_publica[]= {n, e};
    int clave_privada[]= {p, q};

    int enc = cifrar_rsa(clave_publica, 100);
    int dec = descifrar_rsa(clave_publica, clave_privada, enc);

    printf("M = 100 | M cifrado: %d = C | C descifrado: %d = M\n", enc, dec);

    char * a_cifrar = "SILAGENTENOCREEQUELASMATEMATICASSONSIMPLESESSOLOPORQUENOSEDANCUENTADELOCOMPLICADOQUEESLAVIDA";
    char * ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int clave_afin[] = {7, 19};

    char * cifrado = cifrar_afin(clave_afin, a_cifrar, ALFABETO);

    if (cifrado != NULL) { // Good practice to check before using/freeing
        printf("%s\n", cifrado);
        free(cifrado); // Free the allocated memory
        cifrado = NULL; // Optional: prevent dangling pointer use
    }

    return 0;
}
