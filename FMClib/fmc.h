/**
 * Calcula el módulo de un número dado por una base dada.
 *
 * @param numero El número del cual se calculará el módulo.
 * @param base El divisor para calcular el módulo.
 * @return El valor del número módulo base.
 */
int modulo(int numero, int base);

/**
 * Verifica si un número dado es primo.
 *
 * @param p El número que se quiere comprobar si es primo.
 * @return 1 si el número es primo, 0 en caso contrario.
 */
int es_primo(int p);

/**
 * Calcula el máximo común divisor (GCD) de dos números dados utilizando el algoritmo de euclides.
 *
 * @param a El primer número.
 * @param b El segundo número.
 * @param imprimir_pasos Un indicador para imprimir los pasos intermedios del cálculo (1 para imprimir, 0 para no imprimir).
 * @return El GCD de los dos números.
 */
int gcd(int a, int b, int imprimir_pasos);

/**
 * Calcula el inverso de un número dado en una base dada utilizando el algoritmo extendido de Euclides.
 *
 * @param numero El número para el cual se quiere encontrar el inverso.
 * @param base La base en la que se calcula el inverso.
 * @param imprimir_pasos Un indicador para imprimir los pasos intermedios del cálculo (1 para imprimir, 0 para no imprimir).
 * @return El inverso del número en la base especificada.
 */
int inverso(int numero, int base, int imprimir_pasos);

/**
 * Calcula la función Phi de Euler para un número dado.
 *
 * @param m El número para el cual se calculará la función Phi de Euler.
 * @return El valor de la función Phi de Euler para el número.
 */
long phi(long m);

/**
 * Realiza el algoritmo "square and multiply" para calcular x^y mod z.
 *
 * @param x La base.
 * @param y El exponente.
 * @param z El módulo.
 * @param imprimir_pasos Un indicador para imprimir los pasos intermedios del cálculo (1 para imprimir, 0 para no imprimir).
 * @return El resultado de x^y mod z.
 */
int square_multiply(int x, int y, int z, int imprimir_pasos);

/**
 * Cifra un mensaje usando el cifrado Afín.
 *
 * @param clave Un arreglo de dos enteros que representan la clave del cifrado Afín.
 * @param texto El mensaje que se va a cifrar.
 * @param alfabeto Un puntero a una cadena que contiene el alfabeto a utilizar.
 * @return Un puntero a una cadena que contiene el mensaje cifrado.
 */
char * cifrar_afin(int * clave, char * texto, char * alfabeto);

/**
 * Cifra un mensaje usando el cifrado RSA.
 *
 * @param clave Un arreglo de dos enteros n y e que representan la clave pública del cifrado RSA.
 * @param descifrado El mensaje que se va a cifrar.
 * @return El mensaje cifrado.
 */
int cifrar_rsa(const int * clave, int descifrado);

/**
 * Descifra un mensaje cifrado usando el cifrado Afín.
 *
 * @param clave Un arreglo de dos enteros que representan la clave del cifrado Afín.
 * @param texto El mensaje cifrado que se va a descifrar.
 * @param alfabeto Un puntero a una cadena que contiene el alfabeto a utilizar.
 * @return Un puntero a una cadena que contiene el mensaje descifrado.
 */
char * descifrar_afin(int * clave, char * texto, char * alfabeto);

/**
 * Descifra un mensaje cifrado usando el cifrado RSA.
 *
 * @param clave Un arreglo de dos enteros que representan la clave privada del cifrado RSA.
 * @param cifrado El mensaje cifrado que se va a descifrar.
 * @return El mensaje descifrado.
 */
int descifrar_rsa(const int * clave_publica, const int * clave_privada, int cifrado);