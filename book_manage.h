#ifndef BOOK_MANAGE_H
#define BOOK_MANAGE_H

#define MAX_BOOKS 100

typedef struct {
    char barcode[20];
    char title[100];
    char author[50];
    char publisher[50];
    int publish_year;
    float price;
    int stock;
} Book;

extern Book books[MAX_BOOKS];
extern int book_count;

void loadBooks();
void saveBooks();
void addBook();
void displayBooks();
void queryBooks(int option);
void modifyBook();
void deleteBook(int option);
void sortBooks(int option);
void statistics(int option);

#endif // BOOK_MANAGE_H
