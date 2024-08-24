/*
 * Archivo: Ejercicio_5A.c
 * Descripción: Este programa cuenta cuántas veces aparece un valor específico 
 * ('key') en un arreglo de números aleatorios.
 * 
 * Funcionalidad:
 * - Genera un arreglo de tamaño N con valores aleatorios.
 * - Inserta manualmente el valor 'key' en tres posiciones específicas del arreglo.
 * - Cuenta cuántas veces aparece 'key' en el arreglo usando una función llamada count_key().
 * - Imprime el número de apariciones de 'key' en el arreglo.
 * 
 * Referencia:
 * Chandra, . R. et al. Parallel Programming in OpenMP
 *
 * Fecha modificación: 08-24-2024
 * 
 * NOTA: MODIFICADO PARA QUE SE HAGA DE MANERA PARALELA USANDO OMP. SE USA UN PARALLEL FOR PARA DIVIDIR
 * EL TRABAJO ENTRE MÚLTIPLES HILOS Y SE USA LA CLÁSULA reduction PARA ACUMULAR EL NÚMERO DE OCURRENCIAS
 * DE 'key'.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072

long count_key(long Nlen, long *a, long key) {
    long count = 0;

    #pragma omp parallel for reduction(+:count) 
    for (int i = 0; i < Nlen; i++) {
        if (a[i] == key) count++;
    }

    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;

    for (long i = 0; i < N; i++) a[i] = rand() % N;

    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    nkey = count_key(N, a, key); // cuenta key secuencialmente

    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey);

    return 0;
}
