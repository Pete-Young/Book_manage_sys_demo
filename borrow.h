#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_BORROW 100

typedef struct {
    char ID[20];     // ѧ��
    char bname[100]; // ��������
    char bID[20];    // ������
    int day;         // ����ʱ��
    int month;
    int year;
}Borrow;


Borrow borrow[MAX_BORROW];


extern Borrow borrow[MAX_BORROW];


void loadBorrow();
void saveBorrow();