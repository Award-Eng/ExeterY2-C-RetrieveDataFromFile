/*
===================================
Assessment Three for PHY2027 module
Date: 19/11/2018
===================================
*/

/*
===================================================================================
This is a program designed to retrieve student data from a text file then calculate
an average and return a grade for each student as well as displaying their name and
age and dates of the test. It is designed to repeat until the user decides to stop
===================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_IN "students.txt"
#define N_STUDENTS 7
#define N_ASSIGNMENTS 5

/*
Structure containing data on the students
*/
typedef struct Student
{
    char first_name[20];
    char last_name[20];
    int age;
    int marks[N_ASSIGNMENTS];
    float final_mark;
    char grade;
} Student;

/*
Functions created for this program
*/
void read_data(Student *[]);
void final_mark(Student *[]);
int retrieve(Student *[], char [], char [], Student **);
void print_student(Student *);
char grade(float);

/*
Shows students in the database and allows you to see their individual stat's
*/
int main()
{
    Student *students[N_STUDENTS];
    read_data(students);
    final_mark(students);

    printf("Students stored in database:\n");
    for (int i = 0; i < N_STUDENTS; i++) {
        Student *student = students[i];
        printf("%s %s\n", student->first_name, student->last_name);
    }

    while (1) {
        char first_name[20], last_name[20];
        printf("Enter the name of the student: ");
        scanf("%s %s", first_name, last_name);

        Student *student;
        int found = retrieve(students, first_name, last_name, &student);
        if (found == 1) print_student(student);
        else printf("Student could not be found.\n");

        char choice[2];
        printf("Continue? (Y/N): ");
        scanf("%s", choice);
        if (strcmp(choice, "N") == 0) break;
    }
    return 0;
}
/*
Reads students data from the file and stores it in the structure
*/
void read_data(Student *students[])
{
    FILE *f = fopen(F_IN, "r");
    if (!f) {
        printf("Error - can't open file.\n");
        exit(-1);
    }

    char dates[5][20];
    fscanf(f, "%s %s %s %s %s", dates[0], dates[1], dates[2], dates[3], dates[4]);
    printf("Dates of all tests: %s\n %s\n %s\n %s\n %s\n", dates[0], dates[1], dates[2], dates[3], dates[4]);


    for (int i = 0; i < N_STUDENTS; i++) {
        Student *student = (Student*) malloc(sizeof(Student));
        fscanf(f, "%s %s %d %d %d %d %d %d",
            student->first_name,
            student->last_name,
            &(student->age),
            &(student->marks[0]),
            &(student->marks[1]),
            &(student->marks[2]),
            &(student->marks[3]),
            &(student->marks[4])
        );
        students[i] = student;
    }
    fclose(f);
}

/*
Calculates the final mark of the students
*/
void final_mark(Student *students[])
{
    for (int i = 0; i < N_STUDENTS; i++) {
        Student *student = students[i];
        int sum = 0;
        for (int j = 0; j < N_ASSIGNMENTS; j++) sum += student->marks[j];
        float final_mark = (float) sum / N_ASSIGNMENTS;
        student->final_mark = final_mark;
        student->grade = grade(final_mark);
    }
}

/*
Locates the student in the database using a name searched by the user
*/
int retrieve(Student *students[], char first_name[], char last_name[], Student **student)
{
    for (int i = 0; i < N_STUDENTS; i++) {
        if (strcmp(first_name, students[i]->first_name) == 0 &&
                strcmp(last_name, students[i]->last_name) == 0) {
            *student = students[i]; //pass value in then change in function but can't return
            return 1;
        }
    }
    return 0;
}

/*
Prints the data on the students
*/
void print_student(Student *student)
{
    printf("Name: %s %s\n", student->first_name, student->last_name);
    printf("Age: %d\n", student->age);
    printf("Final mark: %.1f\n", student->final_mark);
    printf("Grade: %c\n", student->grade);
}

/*
Calculates the final grade from the mark
*/
char grade(float final_mark)
{
    if (final_mark >= 70) return 'A';
    else if (final_mark >= 60) return 'B';
    else if (final_mark >= 50) return 'C';
    else if (final_mark >= 40) return 'D';
    else if (final_mark >= 30)return 'E';
    else return 'F';
}




/*
Test run of program
Dates of all tests: 01-01-2018
 02-02-2018
 03-03-2018
 04-04-2018
 05-05-2018
Students stored in database:
John Doe
Jane Doe
Alex Doe
Beth Doe
Bruce Wayne
Sarah Doe
Diana Prince
Enter the name of the student: Diana Prince
Name: Diana Prince
Age: 19
Final mark: 11.4
Grade: F
Continue? (Y/N): Y
Enter the name of the student: Beth Doe
Name: Beth Doe
Age: 19
Final mark: 85.6
Grade: A
Continue? (Y/N): Y
Enter the name of the student: Bob Dylan
Student could not be found.
Continue? (Y/N): N

Process returned 0 (0x0)   execution time : 37.150 s
Press any key to continue.


*/
