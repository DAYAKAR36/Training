 // Print marks of n students.

#include <stdio.h>

void main()
{
	int number_of_students = 5, student_counter;
	int marks[number_of_students];
	printf("Enter the marks of %d students: \n", number_of_students);
	for (student_counter = 0; student_counter < number_of_students; student_counter ++)
	{
		printf("Enter marks of %d students: ", (student_counter+1));
		scanf("%d", &marks[student_counter]);
		// scanf("%d", marks + student_counter);
	}
	printf("Marks of %d students:\n", number_of_students);
	for (student_counter = 0; student_counter < number_of_students; student_counter ++)
	{
		printf("Marks of student %d: %d\n", (student_counter + 1), marks[student_counter]);
		// printf("Marks of student %d: %d\n", (student_counter + 1), *(marks + student_counter));
	}
}