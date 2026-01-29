 // Experiment with storing records into 2 dimensioanl array.

#include <stdio.h>
#include <string.h>

void main()
{
    char Record[] = "ABOO1234\0      Servana\0       22000\0        ";
    char field_values[3][15];
    memcpy(field_values, Record, sizeof(field_values));
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", field_values[i]);
    }
}
