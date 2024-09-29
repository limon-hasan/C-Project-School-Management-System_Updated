#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>   // for sleep function
#include <windows.h>

char adminUsername[] = "admin";
char adminPassword[] = "admin123";

char teacherUsername[] = "teacher";
char teacherPassword[] = "teacher123";

char studentUsername[] = "student";
char studentPassword[] = "student123";

#define MAX_TEACHERS 100
#define MAX_STUDENTS 100

struct student
{
    int roll_no;
    char name[50];
    int age;
    char class_name[10];
    char section[10];
    float due_payment;
    char grade[50];
    char attendance[50];
};

struct teacher
{
    int idno;
    char name[50];
    char assigned_class[10];
    char assigned_section[10];
    char subject[50];
    char qualification[50];
    float salary;
};

void displayMenu();
void adminMenu();
void teacherMenu();
void studentMenu();
void printStarPatternWithTitle(const char* title);
void printWelcomeMessage();
void loadingAnimation();
void clearScreen();

void clearScreen()
{
    system("cls");
}

// Function to set console text and background color
void setConsoleColor(int textColor, int backgroundColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

void displayMenu()
{
    setConsoleColor(9, 0);  // Light blue text, black background
    printf("\n\n\n\n");
    printf("\t\t\t=============================================\n");
    printf("\t\t\t|                 MAIN MENU                 |\n");
    printf("\t\t\t=============================================\n");
    printf("\t\t\t|          Please Select Your Role          |\n");
    printf("\t\t\t=============================================\n");
    printf("\t\t\t|         [1] Admin                         |\n");
    printf("\t\t\t|         [2] Teacher                       |\n");
    printf("\t\t\t|         [3] Student                       |\n");
    printf("\t\t\t|         [0] Exit                          |\n");
    printf("\t\t\t=============================================\n\n");
    printf("\t\t\t           Enter your choice: ");

//    setConsoleColor(7, 0);  // reset the color
}

void printStarPatternWithTitle(const char* title)
{
    int width = strlen(title) + 4;
    int spaces = (60 - width) / 2;

    for (int i = 1; i <= 60; i++)
    {
        printf("*");
    }
    printf("\n");

    printf("  *");
    for (int i = 1; i <= spaces - 1; i++)
    {
        printf(" ");
    }
    printf("%s", title);
    for (int i = 1; i <= spaces - 1; i++)
    {
        printf(" ");
    }
    if (width % 2 == 0)
    {
        printf("*");
    }
    else
    {
        printf(" ");
    }
    printf("\n");

    for (int i = 1; i <= 60; i++)
    {
        printf("*");
    }
    printf("\n");
}

void displayMenu();
void adminMenu();

void add_teacher_record()
{
    struct teacher t;
    FILE *fp = fopen("teachers.txt", "ab+"); // Open file in read/write mode

    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }
    // Collect teacher information
    printf("\t\t\tEnter Teacher ID: ");
    scanf("%d", &t.idno);

    // Check for duplicate ID
    struct teacher temp;
    int found = 0;
    while (fread(&temp, sizeof(struct teacher), 1, fp))
    {
        if (temp.idno == t.idno)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\t\t\tError: A teacher with ID No %d already exists!\n", t.idno);
        fclose(fp);
        return;
    }
    // If no duplicate, collect the rest of the information
    printf("\t\t\tEnter Teacher Name: ");
    scanf(" %[^\n]", t.name);
    printf("\t\t\tEnter Assigned Class: ");
    scanf(" %[^\n]", t.assigned_class);
    printf("\t\t\tEnter Assigned Section: ");
    scanf(" %[^\n]", t.assigned_section);
    printf("\t\t\tEnter Subject: ");
    scanf(" %[^\n]", t.subject);
    printf("\t\t\tEnter Qualification: ");
    scanf(" %[^\n]", t.qualification);
    printf("\t\t\tEnter Salary: ");
    scanf("%f", &t.salary);

    // Move the file pointer to the end to append the new record
    fseek(fp, 0, SEEK_END);
    fwrite(&t, sizeof(struct teacher), 1, fp);
    printf("\t\t\tTeacher record added successfully!\n");


    fclose(fp);
}

void add_student_record()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    printf("\t\t\tEnter Roll Number: ");
    scanf("%d", &s.roll_no);

    struct student temp;

    // Checking for Duplicate Roll Number
    int found = 0;
    while (fread(&temp, sizeof(struct student), 1, fp))
    {
        if (temp.roll_no == s.roll_no)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\t\t\tError: A student with Roll No %d already exists!\n", s.roll_no);
        fclose(fp);
        return;
    }
    printf("\t\t\tEnter Student Name: ");
    scanf(" %[^\n]", s.name);
    printf("\t\t\tEnter Age: ");
    scanf("%d", &s.age);
    printf("\t\t\tEnter Class: ");
    scanf(" %[^\n]", s.class_name);
    printf("\t\t\tEnter Section: ");
    scanf(" %[^\n]", s.section);
    printf("\t\t\tEnter Due Payment: ");
    scanf("%f", &s.due_payment);

    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(struct student), 1, fp);
    printf("\t\t\tStudent record added successfully!\n");
    fclose(fp);
}

void edit_teacher_record()
{
    struct teacher t;
    FILE *fp = fopen("teachers.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }
    int idno;
    printf("\t\t\tEnter the Teacher ID to edit: ");
    scanf("%d", &idno);
    int found = 0;

    while (fread(&t, sizeof(struct teacher), 1, fp))
    {
        if (t.idno == idno)
        {
            found = 1;

            printf("\t\t\tEditing Teacher Record:\n");
            printf("\t\t\tEnter new Name: ");
            scanf(" %[^\n]", t.name);
            printf("\t\t\tEnter new Assigned Class: ");
            scanf(" %[^\n]", t.assigned_class);
            printf("\t\t\tEnter new Assigned Section: ");
            scanf(" %[^\n]", t.assigned_section);
            printf("\t\t\tEnter new Subject: ");
            scanf(" %[^\n]", t.subject);
            printf("\t\t\tEnter new Qualification: ");
            scanf(" %[^\n]", t.qualification);
            printf("\t\t\tEnter new Salary: ");
            scanf("%f", &t.salary);

            fseek(fp, -sizeof(struct teacher), SEEK_CUR);
            fwrite(&t, sizeof(struct teacher), 1, fp); // Update the record
            printf("\t\t\tTeacher record updated successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tTeacher ID not found!\n");
    }

    fclose(fp);
}

void edit_student_record()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+"); // Open file for reading and writing
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to edit: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;

            printf("\t\t\tEditing Student Record:\n");
            printf("\t\t\tEnter new ID No: ");
            scanf("%d", &s.roll_no);  // Assuming you have an 'idno' field in your struct
            printf("\t\t\tEnter new Name: ");
            scanf("%s", s.name);
            printf("\t\t\tEnter new Age: ");
            scanf("%d", &s.age);
            printf("\t\t\tEnter new Class: ");
            scanf("%s", s.class_name);
            printf("\t\t\tEnter new Section: ");
            scanf("%s", s.section);
            printf("\t\t\tEnter new Due Payment: ");
            scanf("%f", &s.due_payment);

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("\t\t\tStudent record updated successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void delete_teacher_record()
{
    struct teacher t;
    FILE *fp = fopen("teachers.txt", "ab+");
    FILE *temp_fp = fopen("temp_teachers.txt", "wb"); // Temporary file for non-deleted records
    if (fp == NULL || temp_fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int idno;
    printf("\t\t\tEnter the Teacher ID to delete: ");
    scanf("%d", &idno);
    int found = 0;

    while (fread(&t, sizeof(struct teacher), 1, fp))
    {
        if (t.idno == idno)
        {
            found = 1;
            printf("\t\t\tTeacher record with ID No %d deleted successfully!\n", idno);
            continue;
        }
        fwrite(&t, sizeof(struct teacher), 1, temp_fp);
    }

    if (!found)
    {
        printf("\t\t\tTeacher ID not found!\n");
    }

    fclose(fp);
    fclose(temp_fp);

    // Replace old file with the new file
    remove("teachers.txt");
    rename("temp_teachers.txt", "teachers.txt");
}

void delete_student_record()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    FILE *temp_file = fopen("temp_students.txt", "wb");
    if (fp == NULL || temp_file == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to delete: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(struct student), 1, temp_file);
    }

    fclose(fp);
    fclose(temp_file);

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
        remove("temp_students.txt");
    }
    else
    {
        remove("students.txt");
        rename("temp_students.txt", "students.txt");
        printf("\t\t\tStudent record deleted successfully!\n");
    }
}

void view_teacher_details()
{
    struct teacher t;
    FILE *fp = fopen("teachers.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }
    printf("\n\t\t\tTeacher Records:\n");
    printf("\t\t\t=================\n");
    while (fread(&t, sizeof(struct teacher), 1, fp))
    {
        printf("\t\t\tID No: %d\n", t.idno);
        printf("\t\t\tName: %s\n", t.name);
        printf("\t\t\tAssigned Class: %s\n", t.assigned_class);
        printf("\t\t\tAssigned Section: %s\n", t.assigned_section);
        printf("\t\t\tSubject: %s\n", t.subject);
        printf("\t\t\tQualification: %s\n", t.qualification);
        printf("\t\t\tSalary: %.2f\n", t.salary);
        printf("\t\t\t-----------------\n");
    }

    fclose(fp);
}

void search_teacher_records()
{
    struct teacher t;
    FILE *fp = fopen("teachers.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int idno;
    printf("\t\t\tEnter the Teacher ID to search: ");
    scanf("%d", &idno);
    int found = 0;

    while (fread(&t, sizeof(struct teacher), 1, fp))
    {
        if (t.idno == idno)
        {
            found = 1;
            printf("\n\t\t\tTeacher Record Found:\n");
            printf("\t\t\t======================\n");
            printf("\t\t\tID No: %d\n", t.idno);
            printf("\t\t\tName: %s\n", t.name);
            printf("\t\t\tAssigned Class: %s\n", t.assigned_class);
            printf("\t\t\tAssigned Section: %s\n", t.assigned_section);
            printf("\t\t\tSubject: %s\n", t.subject);
            printf("\t\t\tQualification: %s\n", t.qualification);
            printf("\t\t\tSalary: %.2f\n", t.salary);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tTeacher ID not found!\n");
    }

    fclose(fp);
}

void add_student_grade()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }
    int rollno;
    printf("\t\t\tEnter the Roll Number to add grade: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent found: %s\n", s.name);
            char new_grade[3];
            printf("\t\t\tEnter grade for %s: ", s.name);
            scanf("%s", new_grade);
            strcpy(s.grade, new_grade);


            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);

            printf("\t\t\tGrade added as %s for %s!\n", s.grade, s.name);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void add_student_attendance()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to add attendance: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent found: %s\n", s.name);
            char new_attendance[3];
            printf("\t\t\tEnter attendance (P/A): ");
            scanf("%s", new_attendance);
            strcpy(s.attendance, new_attendance);
            printf("\t\t\tAttendance recorded as %s for %s.\n", s.attendance, s.name);

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void edit_student_grade()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to edit grade: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent found: %s\n", s.name);
            char new_grade[3];
            printf("\t\t\tEnter new grade for %s: ", s.name);
            scanf("%s", new_grade);
            strcpy(s.grade, new_grade);


            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);

            printf("\t\t\tGrade updated to %s for %s!\n", s.grade, s.name);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void edit_student_attendance()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to edit attendance: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent found: %s\n", s.name);
            char new_attendance[3];
            printf("\t\t\tEnter new attendance for %s (P for Present, A for Absent): ", s.name);
            scanf("%s", new_attendance);

            strcpy(s.attendance, new_attendance);

            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(&s, sizeof(struct student), 1, fp);
            printf("\t\t\tAttendance updated to '%c' for %s!\n", s.attendance, s.name);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void view_student_details()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    printf("\n\t\t\tStudent Records:\n");
    printf("\t\t\t=================\n");
    while (fread(&s, sizeof(struct student), 1, fp))
    {
        printf("\t\t\tRoll No: %d\n", s.roll_no);
        printf("\t\t\tName: %s\n", s.name);
        printf("\t\t\tAge: %d\n", s.age);
        printf("\t\t\tClass: %s\n", s.class_name);
        printf("\t\t\tSection: %s\n", s.section);
        printf("\t\t\tDue Payment: %.2f\n", s.due_payment);
        printf("\t\t\t--------------------------\n");
    }
    fclose(fp);
}
void search_student_records()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter the Roll Number to search: ");
    scanf("%d", &rollno);
    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\n\t\t\tStudent Record Found:\n");
            printf("\t\t\t======================\n");
            printf("\t\t\tRoll No: %d\n", s.roll_no);
            printf("\t\t\tName: %s\n", s.name);
            printf("\t\t\tAge: %d\n", s.age);
            printf("\t\t\tClass: %s\n", s.class_name);
            printf("\t\t\tSection: %s\n", s.section);
            printf("\t\t\tDue Payment: %.2f\n", s.due_payment);
            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tRoll Number not found!\n");
    }

    fclose(fp);
}

void view_grades()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter your Roll Number to view your grades: ");
    scanf("%d", &rollno);

    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent Name: %s\n", s.name);
            if (strcmp(s.grade, "") == 0)
            {
                printf("\t\t\tGrade: Not added yet\n");
            }
            else
            {
                printf("\t\t\tGrade: %s\n", s.grade);
            }

            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tNo record found for Roll Number %d\n", rollno);
    }

    fclose(fp);
}

void view_attendance()
{
    struct student s;
    FILE *fp = fopen("students.txt", "ab+");
    if (fp == NULL)
    {
        printf("\t\t\tError opening file!\n");
        return;
    }

    int rollno;
    printf("\t\t\tEnter your Roll Number to view your attendance: ");
    scanf("%d", &rollno);

    int found = 0;

    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll_no == rollno)
        {
            found = 1;
            printf("\t\t\tStudent Name: %s\n", s.name);
            printf("\t\t\tAttendance: %s\n", s.attendance); // 'P' for present, 'A' for absent

            break;
        }
    }

    if (!found)
    {
        printf("\t\t\tNo record found for Roll Number %d\n", rollno);
    }

    fclose(fp);
}

void printClass6Routine()
{
    printf("\n\nClass Routine for Class 6:\n");
    printf("Time         | Sunday       | Monday        | Tuesday     | Wednesday   | Thursday\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("9:00-9:30    | Math         | English       | Science     | Social      | Art\n");
    printf("9:30-10:00   | Math         | English       | Science     | Social      | Art\n");
    printf("10:00-10:15  | Snack Break  | Snack Break   | Snack Break | Snack Break | Snack Break\n");
    printf("10:15-10:45  | Social       | Math          | English     | Science     | Physical Education\n");
    printf("10:45-11:15  | Science      | Social        | Math        | English     | Physical Education\n");
    printf("11:15-11:30  | Break        | Break         | Break       | Break       | Break\n");
    printf("11:30-12:00  | English      | Science       | Social      | Math        | Gym\n");
    printf("12:00-12:30  | English      | Science       | Social      | Math        | Gym\n");
}

void printClass7Routine()
{
    printf("\n\nClass Routine for Class 7:\n");
    printf("Time       | Sunday               | Monday                  | Tuesday            | Wednesday         | Thursday\n");
    printf("--------------------------------------------------------------------------------------------------------------\n");
    printf("8:00-8:30  | Mathematics          | English Language        | Science            | Social Studies    | Physical Education\n");
    printf("8:30-9:00  | Mathematics          | English Language        | Science            | Social Studies    | Physical Education\n");
    printf("9:00-9:30  | Social Studies       | Mathematics             | English Language   | Science           | Art & Craft\n");
    printf("9:30-9:45  | Snack Break          | Snack Break             | Snack Break        | Snack Break       | Snack Break\n");
    printf("9:45-10:15 | Science              | Social Studies          | Mathematics        | English Language  | Physical Education\n");
    printf("10:15-10:45| English Language     | Science                 | Social Studies     | Mathematics       | Music & Dance\n");
    printf("10:45-11:00| Break                | Break                   | Break              | Break             | Break\n");
    printf("11:00-11:30| Computer Science     | Islamic Studies / Moral | Computer Science   | Islamic Studies   | Drawing\n");
    printf("11:30-12:00| Computer Science     | Islamic Studies / Moral | Computer Science   | Islamic Studies   | Drawing\n");
}

void printClass8Routine()
{
    printf("\n\nClass Routine for Class 8:\n");
    printf("Time       | Sunday             | Monday                  | Tuesday              | Wednesday            | Thursday\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("8:00-8:30  | Mathematics        | English Language        | Science              | Social Studies       | Physical Education\n");
    printf("8:30-9:00  | Mathematics        | English Language        | Science              | Social Studies       | Physical Education\n");
    printf("9:00-9:30  | Social Studies     | Mathematics             | English Language     | Science              | Art & Craft\n");
    printf("9:30-9:45  | Snack Break        | Snack Break             | Snack Break          | Snack Break          | Snack Break\n");
    printf("9:45-10:15 | Science            | Social Studies          | Mathematics          | English Language     | Physical Education\n");
    printf("10:15-10:45| English Language   | Science                 | Social Studies       | Mathematics          | Music & Dance\n");
    printf("10:45-11:00| Break              | Break                   | Break                | Break                | Break\n");
    printf("11:00-11:30| Computer Science   | Islamic Studies / Moral | Computer Science     | Islamic Studies      | Drawing\n");
    printf("11:30-12:00| Computer Science   | Islamic Studies / Moral | Computer Science     | Islamic Studies      | Drawing\n");
}


void printClass9ScienceRoutine()
{
    printf("\n\nClass Routine for Class 9 Science:\n");
    printf(" Time       |  Sunday     | Monday      | Tuesday    | Wednesday  | Thursday\n");
    printf("------------| ----------- | ------------| ---------- | ---------- | --------\n");
    printf("9:00-9:50   | Bangla      | English     | Math       | Higher Math| Chemistry\n");
    printf("9:50-10:40  | Biology     | Physics     | Religion   | Bangla     | English\n");
    printf("10:40-11:00 | Break       | Break       | Break      | Break      | Break\n");
    printf("11:00-11:50 | Math        | Higher Math | Chemistry  | Biology    | Physics\n");
    printf("11:50-12:40 | English     | Bangla      | Physics    | Religion   | Biology\n");
    printf("12:40-1:20  | Lunch Break | Lunch Break | Lunch Break| Lunch Break| Lunch Break\n");
    printf("1:20-2:10   | Chemistry   | Biology     | English    | Bangla     | Math\n");
    printf("2:10-3:00   | Physics     | Religion    | Math       | Higher Math| Chemistry\n");
}

void printClass10ScienceRoutine()
{
    printf("\n\nClass Routine for Class 10 Science:\n");
    printf(" Time       |  Sunday     | Monday      | Tuesday    | Wednesday  | Thursday\n");
    printf("------------| ----------- | ------------| ---------- | ---------- | --------\n");
    printf("9:00-9:50   | Bangla      | English     | Math       | Higher Math| Chemistry\n");
    printf("9:50-10:40  | Biology     | Physics     | Religion   | Bangla     | English\n");
    printf("10:40-11:00 | Break       | Break       | Break      | Break      | Break\n");
    printf("11:00-11:50 | Math        | Higher Math | Chemistry  | Biology    | Physics\n");
    printf("11:50-12:40 | English     | Bangla      | Physics    | Religion   | Biology\n");
    printf("12:40-1:20  | Lunch Break | Lunch Break | Lunch Break| Lunch Break| Lunch Break\n");
    printf("1:20-2:10   | Chemistry   | Biology     | English    | Bangla     | Math\n");
    printf("2:10-3:00   | Physics     | Religion    | Math       | Higher Math| Chemistry\n");
}

void printClass9CommerceRoutine()
{
    printf("\n\nClass Routine for Class 9 Commerce:\n");
    printf(" Time      |  Sunday    | Monday    | Tuesday   | Wednesday | Thursday\n");
    printf("-----------| ---------- | -------   | --------- | --------- | --------\n");
    printf("9:00-9:50  | Bangla     | English   | Math      | Accounting| Finance\n");
    printf("9:50-10:40 | Religion   | Management| English   | Bangla    | Math\n");
    printf("10:40-11:00| Break      | Break     | Break     | Break     | Break\n");
    printf("11:00-11:50| Math       | Accounting| Finance   | Religion  | Management\n");
    printf("11:50-12:40| English    | Bangla    | Management| Accounting| Religion\n");
    printf("12:40-1:20 | Lunch Break| L Break   | L Break   | L Break   | Lunch Break\n");
    printf("1:20-2:10  | Accounting | Finance   | English   | Bangla    | Math\n");
    printf("2:10-3:00  | Religion   | Management| Math      | Accounting| Finance\n");
}
void printClass10CommerceRoutine()
{
    printf("\n\nClass Routine for Class 10 Commerce:\n");
    printf(" Time      |  Sunday    | Monday    | Tuesday   | Wednesday | Thursday\n");
    printf("-----------| ---------- | -------   | --------- | --------- | --------\n");
    printf("9:00-9:50  | Bangla     | English   | Math      | Accounting| Finance\n");
    printf("9:50-10:40 | Religion   | Management| English   | Bangla    | Math\n");
    printf("10:40-11:00| Break      | Break     | Break     | Break     | Break\n");
    printf("11:00-11:50| Math       | Accounting| Finance   | Religion  | Management\n");
    printf("11:50-12:40| English    | Bangla    | Management| Accounting| Religion\n");
    printf("12:40-1:20 | Lunch Break| L Break   | L Break   | L Break   | Lunch Break\n");
    printf("1:20-2:10  | Accounting | Finance   | English   | Bangla    | Math\n");
    printf("2:10-3:00  | Religion   | Management| Math      | Accounting| Finance\n");
}

void printClass9ArtsRoutine()
{
    printf("\n\nClass Routine for Class 9 Arts:\n");
    printf("  Time     | Sunday   | Monday   | Tuesday  | Wednesday | Thursday\n");
    printf("---------- |----------|----------|----------|-----------|-----------\n");
    printf("9:00-9:50  | Bangla   | English  | Economics| Logic     | Sociology\n");
    printf("9:50-10:40 | English  | Geograp  | Sociology| Social Wk | Logic    \n");
    printf("10:40-11:00| Break    | Break    | Break    | Break     | Break    \n");
    printf("11:00-11:50| Economics| Logic    | Sociology| English   | Geography\n");
    printf("11:50-12:40| Sociology| SocialWk | Logic    | Bangla    | Economics\n");
    printf("12:40-1:20 | L Break  | L Break  | L Break  | L Break   | Lunch Break\n");
    printf("1:20-2:10  | Logic    | Bangla   | English  | Economics | Sociology\n");
    printf("2:10-3:00  | Social Wk| Sociology| Geography| English   | Bangla\n");
}

void printClass10ArtsRoutine()
{
    printf("\n\nClass Routine for Class 10 Arts:\n");
    printf("  Time     | Sunday   | Monday   | Tuesday  | Wednesday | Thursday\n");
    printf("---------- |----------|----------|----------|-----------|-----------\n");
    printf("9:00-9:50  | Bangla   | English  | Economics| Logic     | Sociology\n");
    printf("9:50-10:40 | English  | Geograp  | Sociology| Social Wk | Logic    \n");
    printf("10:40-11:00| Break    | Break    | Break    | Break     | Break    \n");
    printf("11:00-11:50| Economi  | Logic    | Sociology| English   | Geography\n");
    printf("11:50-12:40| Sociology| SocialWk | Logic    | Bangla    | Economics\n");
    printf("12:40-1:20 | L Break  | L Break  | L Break  | L Break   | Lunch Break\n");
    printf("1:20-2:10  | Logic    | Bangla   | English  | Economics | Sociology\n");
    printf("2:10-3:00  | Social Wk| Sociology| Geography| English   | Bangla\n");
}

void adminMenu()
{
    int choice;
    clearScreen();
    while (1)
    {
        printf("\n\t\t\tLogin successful! Welcome, Admin!\n\n");
        printf("\t\t\t============================================\n");
        printf("\t\t\t\t\tAdmin Menu:\n");
        printf("\t\t\t============================================\n\n");
        printf("\t\t\t1. Add Teacher Record\n");
        printf("\t\t\t2. Add Student Record\n");
        printf("\t\t\t3. Edit Teacher Record\n");
        printf("\t\t\t4. Edit Student Record\n");
        printf("\t\t\t5. Delete Teacher Record\n");
        printf("\t\t\t6. Delete Student Record\n");
        printf("\t\t\t0. Back to Main Menu\n\n");
        printf("\t\t\tSelect an option: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice)
        {
        case 1:
            clearScreen();
            printf("\n\t\t\tYou selected 'Add Teacher Record'\n");
            add_teacher_record();
            break;
        case 2:
            clearScreen();
            printf("\n\t\t\tYou selected 'Add Student Record'\n");
            add_student_record();
            break;
        case 3:
            clearScreen();
            printf("\n\t\t\tYou selected 'Edit Teacher Record'\n");
            edit_teacher_record();
            break;
        case 4:
            clearScreen();
            printf("\n\t\t\tYou selected 'Edit Student Record'\n");
            edit_student_record();
            break;
        case 5:
            clearScreen();
            printf("\n\t\t\tYou selected 'Delete Teacher Record'\n");
            delete_teacher_record();
            break;
        case 6:
            clearScreen();
            printf("\n\t\t\tYou selected 'Delete Student Record'\n");
            delete_student_record();
            break;
        case 0:
            return; // Go back to main menu
        default:
            printf("\t\t\tInvalid choice. Please try again.\n");
        }
        printf("\n\t\t\tPress any key to return to Admin Menu...");
        getch();  // Wait for user input
        clearScreen();
    }
}

void teacherMenu()
{
    int choice;
    clearScreen();
    while (1)
    {
        printf("\n\t\t\tLogin successful! Welcome, Teacher!\n\n");
        printf("\t\t\t============================================\n");
        printf("\t\t\t\t\tTeacher Menu:\n");
        printf("\t\t\t============================================\n\n");
        printf("\t\t\t1. View All Teachers Record\n");
        printf("\t\t\t2. Search a teacher Record\n");
        printf("\t\t\t3. Add Student Grade\n");
        printf("\t\t\t4. Add Student Attendance\n");
        printf("\t\t\t5. Edit Student Grade\n");
        printf("\t\t\t6. Edit Student Attendance\n");
        printf("\t\t\t0. Back to Main Menu\n\n");
        printf("\t\t\tSelect an option: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice)
        {
        case 1:
            clearScreen();
            printf("\n\t\t\tYou selected 'View All Teachers Record'\n");
            view_teacher_details();
            break;
        case 2:
            clearScreen();
            printf("\n\t\t\tYou selected 'Search a teacher Record'\n");
            search_teacher_records();
            break;
        case 3:
            clearScreen();
            printf("\n\t\t\tYou selected 'Add Student Grade'\n");
            add_student_grade();
            break;
        case 4:
            clearScreen();
            printf("\n\t\t\tYou selected 'Add Student Attendance'\n");
            add_student_attendance();
            break;
        case 5:
            clearScreen();
            printf("\n\t\t\tYou selected 'Edit Student Grade'\n");
            edit_student_grade();
            break;
        case 6:
            clearScreen();
            printf("\n\t\t\tYou selected 'Edit Student Attendance'\n");
            edit_student_attendance();
            break;
        case 0:
            return;
        default:
            printf("\n\t\t\tInvalid choice. Please try again.\n");
        }
        printf("\n\t\t\tPress any key to return to Teacher Menu...");
        getch();
        clearScreen();
    }
}

void studentMenu()
{
    int choice,sec,div;
    clearScreen();
    while (1)
    {
        printf("\n\t\t\tLogin successful! Welcome, Student!\n\n");
        printf("\t\t\t============================================\n");
        printf("\t\t\t\t\tStudent Menu:\n");
        printf("\t\t\t============================================\n\n");
        printf("\t\t\t1. View All Students Record\n");
        printf("\t\t\t2. Search a student Record\n");
        printf("\t\t\t3. View Grades\n");
        printf("\t\t\t4. View Attendance\n");
        printf("\t\t\t5. View Class Routine\n");
        printf("\t\t\t0. Back to Main Menu\n\n");
        printf("\t\t\tSelect an option: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice)
        {
        case 1:
            clearScreen();
            printf("\n\t\t\tYou selected 'View All Students Record'\n");
            view_student_details();
            break;
        case 2:
            clearScreen();
            printf("\n\t\t\tYou selected 'Search a student Record'\n");
            search_student_records();
            break;
        case 3:
            clearScreen();
            printf("\n\t\t\tYou selected 'View Grades'\n");
            view_grades();
            break;
        case 4:
            clearScreen();
            printf("\n\t\t\tYou selected 'View Attendance'\n");
            view_attendance();
            break;
        case 5:
            clearScreen();
            printf("\n\t\t\tYou selected 'View Routines'\n");
            printf("\t\t\t Showing results for 'Routine':\n");
            printf("\t\t\t==============================\n\n");
            printf("\t\t          Class 6\n");
            printf("\t\t          Class 7\n");
            printf("\t\t          Class 8\n");
            printf("\t\t          Class 9\n");
            printf("\t\t          Class 10\n\n");
            printf("\t\t    Choose a Class: (6-10)=> ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 6:
                system("cls");
                printf("\nClass 6 selected.\n\n");
                printClass6Routine();
                break;
            case 7:
                system("cls");
                printClass7Routine();
                break;
            case 8:
                system("cls");
                printClass8Routine();
                break;
            case 9:
                system("cls");
                printf("\t         1.Science\n");
                printf("\t         2.Commerce\n");
                printf("\t         3.Arts\n");

                printf("\t\tWhich section you want to see?\n         =>");
                scanf("%d",&div);

                switch(div)
                {
                case 1:
                    system("cls");
                    printClass9ScienceRoutine();
                    break;
                case 2:
                    system("cls");
                    printClass9CommerceRoutine();
                    break;
                case 3:
                    system("cls");
                    printClass9ArtsRoutine();
                }
                break;
            case 10:
                system("cls");
                printf("\t          1.Science\n");
                printf("\t          2.Commerce\n");
                printf("\t          3.Arts\n");

                printf("\t\tWhich section you want to see?\n        =>");
                scanf("%d",&sec);

                switch(sec)
                {
                case 1:
                    system("cls");
                    printClass10ScienceRoutine();
                    break;
                case 2:
                    system("cls");
                    printClass10CommerceRoutine();
                    break;
                case 3:
                    system("cls");
                    printClass10ArtsRoutine();
                }
                break;
            default:
                printf("\tInvalid option.\n");
                break;
            }
            break;
        case 0:
            return;
        default:
            printf("\tInvalid choice. Please try again.\n");
        }
        printf("\n\tPress any key to return to Student Menu...");
        getch();
        clearScreen();
    }
}


void loadingAnimation()
{
    printf("\t\tLoading");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout); // Force printing without waiting for a newline
        sleep(1);
    }
    printf("\n");
}

void printWelcomeMessage()
{
    setConsoleColor(9, 0);
    printf("\t\t\t  *****************************************\n");
    printf(" \t                  <= WELCOME TO SCHOOL MANAGEMENT SYSTEM >= \n");
    printf("\t\t\t  *****************************************\n");
    loadingAnimation();
}

int adminLogin()
{
    char username[50], password[50];
    int attempts = 0;

    while (attempts < 4)
    {
        printf("\t\t\tEnter username: ");
        scanf("%s", username);

        printf("\t\t\tEnter password: ");
        int i = 0;
        char ch;
        while (1)
        {
            ch = _getch(); // Read a character without echoing

            if (ch == 13)   // Enter key
            {
                break;
            }
            else if (ch == 8)     // Backspace key
            {
                if (i > 0)
                {
                    i--; // Move back one position
                    printf("\b \b"); // Erase the character
                }
            }
            else
            {
                password[i++] = ch; // Store the character
                printf("*"); // Display an asterisk
            }
        }
        password[i] = '\0'; // Null-terminate the password string

        // Checking for valid username and password
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
        {
            system("cls");
            printf("\nLogin successful!\n");
            return 1; // Successful login done
        }
        else
        {
            printf("\n\t\t\tInvalid credentials. Please try again.\n");
            attempts++;
        }
    }

    printf("\n\t\t\tToo many failed attempts. Returning to the main menu.\n");
    return 0;
}

int teacherLogin()
{
    char username[50], password[50];
    int attempts = 0;

    while (attempts < 4)
    {
        printf("\t\t\tEnter username: ");
        scanf("%s", username);

        printf("\t\t\tEnter password: ");
        int i = 0;
        char ch;
        while (1)
        {
            ch = _getch(); // reading a character without echoing

            if (ch == 13)   // enter key
            {
                break;
            }
            else if (ch == 8)     // backspace key
            {
                if (i > 0)
                {
                    i--; // moving back one position
                    printf("\b \b"); // erasing the character
                }
            }
            else
            {
                password[i++] = ch; // storing the character
                printf("*"); // displaying an asterisk
            }
        }
        password[i] = '\0'; // null-terminate the password string

        if ((strcmp(username, "teacher1") == 0 && strcmp(password, "teacher123") == 0) ||
                (strcmp(username, "teacher2") == 0 && strcmp(password, "teacher456") == 0) || 
                (strcmp(username, "teacher3") == 0 && strcmp(password, "teacher789") == 0))
        {
            system("cls");
            return 1; // successful login done
        }
        else
        {
            printf("\n\t\t\tInvalid credentials. Please try again.\n");
            attempts++;
        }
    }

    printf("\n\t\t\tToo many failed attempts. Returning to the main menu.\n");
    return 0;
}

int studentLogin()
{
    char username[50], password[50];
    int attempts = 0;

    while (attempts < 4)
    {
        printf("\t\t\tEnter username: ");
        scanf("%s", username);

        printf("\t\t\tEnter password: ");
        int i = 0;
        char ch;
        while (1)
        {
            ch = _getch(); // using_getch() to read a character without echoing

            if (ch == 13)   // enter key
            {
                break;
            }
            else if (ch == 8)     // backspace key
            {
                if (i > 0)   // ensure there's something to delete
                {
                    i--; // move back one position
                    printf("\b \b"); // erasing the character from the console
                }
            }
            else
            {
                password[i++] = ch; // storing the character
                printf("*"); // display an asterisk
            }
        }
        password[i] = '\0'; // null-terminate the password string

        if ((strcmp(username, "student1") == 0 && strcmp(password, "student123") == 0) ||
                (strcmp(username, "student2") == 0 && strcmp(password, "student456") == 0) ||
                (strcmp(username, "student3") == 0 && strcmp(password, "student789") == 0))
        {
            system("cls");
            return 1;
        }
        else
        {
            printf("\n\t\t\tInvalid credentials. Please try again.\n");
            attempts++;
        }
    }

    printf("\n\t\t\tToo many failed attempts. Returning to the main menu.\n");
    return 0;
}

int main()
{
    int choice;
    printWelcomeMessage();
    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clearScreen();
            printf("\t\t\tAdmin Login:\n");
            if (adminLogin())
            {
                adminMenu();
            }
            break;
        case 2:
            clearScreen();
            printf("\t\t\tTeacher Login:\n");
            if (teacherLogin())
            {
                teacherMenu();
            }
            break;
        case 3:
            clearScreen();
            printf("\t\t\tStudent Login:\n");
            if (studentLogin())
            {
                studentMenu();
            }
            break;
        case 0:
            printf("\n\t\t\tExiting the system. Goodbye!\n");
            exit(0);
        default:
            printf("\n\t\t\tInvalid choice! Please try again.\n");
        }
    }

    return 0;
}


