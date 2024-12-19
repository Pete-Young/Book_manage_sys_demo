#pragma once

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern struct BookNode* tail;
extern struct BookNode* head;

typedef struct {
    char id[20];        // ���
    char title[100];    // ����
    char author[50];    // ���� 
    char publisher[50]; // ������ 
    int publish_year;   // ������� 
    char status[30];    // ����״̬
} Book;


struct BookNode {
    Book data;
    struct BookNode* next;
};

struct BookNode* createHead();
struct BookNode* createNode(const Book data);
void InsertTail(const Book data);