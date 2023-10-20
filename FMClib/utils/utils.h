/**
 * Convierte un número entero en su representación binaria como una cadena.
 * @param numero El número entero que se va a convertir a binario.
 * @return Un puntero a una cadena que contiene la representación binaria del número.
 */
char * binario(int numero);

/**
 * Obtiene la posición de una letra en un alfabeto dado.
 *
 * @param letra La letra cuya posición se quiere determinar.
 * @param alfabeto Un puntero a una cadena que contiene el alfabeto en el que se buscará la letra.
 * @return La posición de la letra en el alfabeto (comenzando desde 0), o -1 si la letra no se encuentra en el alfabeto.
 */
int obtener_posicion(char letra, char * alfabeto);

/**
 * Devuelve el valor mínimo entre dos números enteros.
 *
 * @param a El primer número entero.
 * @param b El segundo número entero.
 * @return El valor mínimo entre 'a' y 'b'.
 */
int min(int a, int b);

/**
 * Devuelve el valor máximo entre dos números enteros.
 *
 * @param a El primer número entero.
 * @param b El segundo número entero.
 * @return El valor máximo entre 'a' y 'b'.
 */
int max(int a, int b);