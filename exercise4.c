
/* La variable A se comparte entre los hilos así que está sujeta a condiciones de carrera, mientras que
B es privada así que, de manera independiente, cada hilo trabajará con su propia copia. A sufre inconsistencias
pero B no, solo que sus valores finales no se acumularán ni compartirán entre los hilos */

#include <omp.h>
#include <stdio.h>

int main() {
    int A = 0;
    int B = 0;
    #define N 10

    // shared.
    #pragma omp parallel for shared(A)
    for (int i = 0; i <= N; i++){
        A += i;
        printf("Hilo %d: A = %d\n", omp_get_thread_num(), A);
    }

    printf("\nEl resultado de la suma es: %d\n", A);

    // private.
    #pragma omp parallel for private(B)
    for (int i = 0; i < N; i++) {
        B = i;
        B += 2;
        printf("Hilo %d: B = %d\n", omp_get_thread_num(), B);
    }

    printf("El valor de B es: %d\n", B); // no se pueden ver las modificaciones porque son privadas.

    // ambos.
    #pragma omp parallel for shared(A) private(B)
    for (int i = 0; i <= N; i++) {
        A += i;
        B = i;
        B += 2;
        printf("Hilo %d: A = %d, B = %d\n", omp_get_thread_num(), A, B);
    }

    printf("A = %d\n", A);
    return 0;
}
