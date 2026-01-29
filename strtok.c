 // Experiment with strtok() function.

#include <stdio.h>
#include <string.h>

void main()
 {
    char str[] = "C,Java:Python";
    char *token = strtok(str, ",:");
    while (token != NULL) 
    {
        printf("%s\n", token);
        token = strtok(NULL, ",:");
    }
    printf("%s", str);
}
