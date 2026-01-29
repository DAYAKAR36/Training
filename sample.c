// Measures execution time and memory usage.

#include <stdio.h>
#include <time.h>

void main()
{
    clock_t start_time = clock();
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < 100000; j++);
    }
    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", execution_time);
}
