#include <omp.h>
#include <stdio.h>

int main() {
    #define N 1000000
    int sum = 0;
    double startTime, endTime;

    // Se inicia el cronómetro.
    startTime = omp_get_wtime();

    // Calcular de manera paralela la suma.
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) { // Números naturales no incluyen el 0 e incluyen el último número.
        sum+=i;
    }

    endTime = omp_get_wtime();

    printf("La suma es: %d\nEjecutado en un tiempo de: %f\n", sum, endTime - startTime);

    return 0;
}
