// Program to perform CRUD operations on student.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytools.h"

#define ROLL_NUMBER_SIZE 15
#define NAME_SIZE 30
#define FILE_NAME "Students.dat"

void add_student();
void show_all_students();
void update_rank();
void remove_student();

typedef struct student_details
{
    char roll_number[ROLL_NUMBER_SIZE];
    char name[NAME_SIZE];
    int rank;
    char status;
} STUDENT;

int const size_of_student = sizeof(STUDENT);

void main()
{
    int choice;
    do
    {
        printf("1. Add a student\n2. Show all students\n3. Update rank\n4. Remove student\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        clear_buffer();
        switch(choice)
        {
            case 1:
                add_student();
                break;
            case 2:
                show_all_students();
                break;
            case 3:
                update_rank();
                break;
            case 4:
                remove_student();
                break;
            case 5:
                exit(0);
            default:
                printf("Enter a valid choice:\n");
        }
    } while (1);
}

void add_student()
{
    STUDENT student;
    printf("Enter student details:\n");
    printf("Roll number: ");
    fgets(student.roll_number, ROLL_NUMBER_SIZE, stdin);
    remove_new_line(student.roll_number);

    printf("Student name: ");
    fgets(student.name, NAME_SIZE, stdin);
    remove_new_line(student.name);
    
    printf("Rank: ");
    scanf("%d", &student.rank);
    clear_buffer();

    student.status = 's';

    FILE *fp_student = fopen(FILE_NAME, "a");
    fwrite(&student, size_of_student, 1, fp_student);
    fclose(fp_student);
    printf("Student added successfully!\n");
}

void show_all_students()
{
    STUDENT student;
    FILE *fp_student = fopen(FILE_NAME, "r");
    printf("All students details:\n");
    printf("\n%-15s%-20s%-11s%-5s", "Roll number", "Name", "Rank", "Status\n");
    printf("---------------------------------------------------------\n");
    while (fread(&student, size_of_student, 1, fp_student) == 1)
    {
        printf("%-15s%-20s%-11d", student.roll_number, student.name, student.rank);
        if (student.status == 's')
        {
            printf("%-10s\n", "Studying");
        }
        else
        {
            printf("%-10s\n", "Completed");
        }
    }
    fclose(fp_student);
}

void remove_student()
{
    STUDENT student;
    char roll_number[ROLL_NUMBER_SIZE];
    printf("Enter roll number of the student to remove: ");
    scanf("%s", roll_number);
    clear_buffer();
    FILE *fp_student = fopen(FILE_NAME, "r+");
    while (fread(&student, size_of_student, 1, fp_student) == 1)
    {
        if (strcmp(student.roll_number, roll_number) == 0)
        {
            student.status = 'e';
            fseek(fp_student, -size_of_student, SEEK_CUR);
            fwrite(&student, size_of_student, 1, fp_student);
            break;
        }
    }
    fclose(fp_student); 
}

void update_rank()
{
    STUDENT student;
    char roll_number[ROLL_NUMBER_SIZE];
    printf("Enter roll number of the student to update rank: ");
    scanf("%s", roll_number);
    clear_buffer();
    FILE *fp_student = fopen(FILE_NAME, "r+");
    while (fread(&student, size_of_student, 1, fp_student) == 1)
    {
        if (strcmp(student.roll_number, roll_number) == 0)
        {
            printf("Enter new rank: ");
            scanf("%d", &student.rank);
            fseek(fp_student, -size_of_student, SEEK_CUR);
            fwrite(&student, size_of_student, 1, fp_student);
            break;
        }
    }
    fclose(fp_student);
}
