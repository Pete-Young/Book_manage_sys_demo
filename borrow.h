#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_BORROW 100

typedef struct {
    char ID[20];     // 学号
    char bname[100]; // 借书名称
    char bID[20];    // 借书编号
    int day;         // 借书时间
    int month;
    int year;
}Borrow;


Borrow borrow[MAX_BORROW];


extern Borrow borrow[MAX_BORROW];


void loadBorrow();
void saveBorrow();