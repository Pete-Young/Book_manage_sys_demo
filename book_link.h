#pragma once

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern struct BookNode* tail;
extern struct BookNode* head;

typedef struct {
    char id[20];        // 编号
    char title[100];    // 书名
    char author[50];    // 作者 
    char publisher[50]; // 出版社 
    int publish_year;   // 出版年份 
    char status[30];    // 借阅状态
} Book;


struct BookNode {
    Book data;
    struct BookNode* next;
};

struct BookNode* createHead();
struct BookNode* createNode(const Book data);
void InsertTail(const Book data);