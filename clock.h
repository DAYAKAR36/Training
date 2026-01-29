 // Header file to  get the execution time   													
																								
#ifndef GET_EXECUTION_TIME_H																	
#define GET_EXECUTION_TIME_H

#include <stdio.h>																				
#include <time.h>

#define GET_EXECUTION_TIME(function_name)														\
do 																								\
{																								\
	clock_t start_time = clock();																\
	function_name();																			\
	clock_t end_time = clock();																	\
	printf("Execution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);	\
}while (0)

#endif