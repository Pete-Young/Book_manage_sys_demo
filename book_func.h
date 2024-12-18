#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include"book_link.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<Windows.h>  


#define MAX_BOOKS 100

extern int book_count;


void loadBooks();
void saveBooks();
void addBook();
void printBook();
void displayBooks();
void queryBooks(int option);
void modifyBook();
void deleteBook(int option);
void sortById();
void sortByYear();
void sortBooks(int option);
// int color(int num);
// extern int welcomeUI();