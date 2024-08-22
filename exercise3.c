#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    #define n 10

    #pragma omp parallel sections
    {
        // Factorial
        #pragma omp section
        {
            int result = 1;

            for (int i = 1; i<= n; i++) {
                result *= i;
            }

            printf("El resultado del factorial de %d es: %d\n", n, result);
        }
        
        // Fibonacci
        #pragma omp section
        {
            int fibo1 = 0; 
            int fibo2 = 1;
            int newFibo;

            for(int i = 2; i <= n; i++) {
                newFibo = fibo1 + fibo2;
                fibo1 = fibo2;
                fibo2 = newFibo;
            }

            printf("El resultado del fibonacci de %d es: %d\n", n, newFibo);
        }

        // Elemento más grande en un array
        #pragma omp section
        {
            int myArray[n];
            int greaterNum = 0;
            srand(time(NULL));

            for (int i = 0; i <= n; i++) {
                myArray[i] = rand() % 11;
            }

            printf("El array de tamano %d es: ", n);
            for (int i = 0; i <= n; i++) {
                if(myArray[i] > greaterNum) {
                    greaterNum = myArray[i];
                }
                printf("[%d] ", myArray[i]);
            }
            
            printf(" y su numero mas grande es: %d\n", greaterNum);
        }
    }
    return 0;
}
