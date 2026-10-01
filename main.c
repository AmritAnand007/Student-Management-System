#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    int id;
    char name[50];
    float marks;
};
void addStudent() {
    struct Student s;
    FILE *file = fopen("students.txt", "a");
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fprintf(file, "%d|%s|%.2f\n", s.id, s.name, s.marks);
    fclose(file);
    printf("\nStudent added successfully!\n");
}
void displayStudents()
{
    struct Student s;
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) 
    {
        printf("No student records found!\n");
        return;
    }
    printf("\n========== STUDENT RECORDS ==========\n");
    while (fscanf(file, "%d|%49[^|]|%f\n",
                  &s.id, s.name, &s.marks) == 3) {
        printf("ID     : %d\n", s.id);
        printf("Name   : %s\n", s.name);
        printf("Marks  : %.2f\n", s.marks);
        printf("-------------------------------------\n");
    }
    fclose(file);
}
void searchStudent() 
{
    struct Student s;
    int id;
    int found = 0;
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) 
{
        printf("No student records found!\n");
        return;
    }
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);
    while (fscanf(file, "%d|%49[^|]|%f\n",
                  &s.id, s.name, &s.marks) == 3) {
        if (s.id == id) {
            printf("\nStudent Found!\n");
            printf("ID     : %d\n", s.id);
            printf("Name   : %s\n", s.name);
            printf("Marks  : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nStudent not found!\n");
    }
    fclose(file);
}
void deleteStudent()
{
    struct Student s;
    int id;
    int found = 0;
    FILE *file = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);
    while (fscanf(file, "%d|%49[^|]|%f\n",
                  &s.id, s.name, &s.marks) == 3)
                  {
        if (s.id == id)
        {
            found = 1;
            continue;
        }
        fprintf(temp, "%d|%s|%.2f\n",
                s.id, s.name, s.marks);
    }
    fclose(file);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found!\n");
}
int main()
{
    int choice;
    while (1) 
    {
        printf("\n=====================================\n");
        printf("     STUDENT RECORD MANAGEMENT\n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("\nThank you for using the program!\n");
                return 0;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}