#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include"book_link.h"
#include "borrow.h"
#include "book_manage.h"

extern void welcomeUI();
typedef struct
{
    char ID[20];     // 学号
    char name[20];   // 姓名
    char Class[20];  // 班级
    char bname[100][100]; // 借书名称
    char bID[100][20];    // 借书编号
    int day[100];         // 借书时间
    int month[100];
    int year[100];
}Student;

extern int borrow_count;
#define MAX_STUDENTS 100
Student students[MAX_STUDENTS];


extern Student students[MAX_STUDENTS];


void loadStudents();
void saveStudents();
void addStudent();
void deleteStudent();
void borrowBook();
void displayStudent();
void studentRoutine();


#endif // STUDENT_H_INCLUDED