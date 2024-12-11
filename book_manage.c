#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include "book_manage.h" // ��Ӵ���

// ȫ�ֱ���
Book books[MAX_BOOKS];
int book_count = 0; // ��ǰͼ������

void loadBooks() { /* ����ͼ����Ϣ���ڴ� */ }
void saveBooks() { /* ����ͼ����Ϣ���ļ� */ }

void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("ͼ����������޷���Ӹ���ͼ�顣\n");
        return;
    }

    Book newBook;
    printf("��������ͼ����Ϣ:\n");
    printf("������: "); 
    scanf("%s", newBook.barcode);
    printf("����: "); 
    scanf("%99s", newBook.title); // �޸Ĵ���
    printf("������: "); 
    scanf("%49s", newBook.author); // �޸Ĵ���
    printf("������: "); 
    scanf("%49s", newBook.publisher); // �޸Ĵ���
    printf("�������: "); 
    scanf("%d", &newBook.publish_year);
    printf("�۸�: "); 
    scanf("%f", &newBook.price);
    printf("�ݲ�����: "); 
    scanf("%d", &newBook.stock);

    books[book_count++] = newBook;
    printf("ͼ����ӳɹ���\n");
}

// ��ʾ����ͼ����Ϣ�ĸ�������
void printBook(const Book* book) 
{
    printf("������: %s, ����: %s, ����: %s, ������: %s, �������: %d, �۸�: %.2f, �ݲ�����: %d\n",
        book->barcode, book->title, book->author, book->publisher,
        book->publish_year, book->price, book->stock);
}

// ���ͼ�鹦��
void displayBooks() 
{
    printf("\n��ǰͼ����Ϣ�б�:\n");
    for (int i = 0; i < book_count; i++) 
    {
        printBook(&books[i]);
    }
    printf("����¼�� %d ��ͼ�顣\n", book_count);
    system("pause");
}

void queryBooks(int option) 
{
    char input[100];
    int found = 0;

    printf("�������ѯ�ؼ���: ");
    scanf("%s", input);

    switch (option) 
    {
    case 1: // �������ѯ
        for (int i = 0; i < book_count; i++) 
        {
            if (strcmp(books[i].barcode, input) == 0) 
            {
                printBook(&books[i]);
                found = 1;
            }
        }
        system("pause");
        break;
    case 2: // ������ѯ
        for (int i = 0; i < book_count; i++) 
        {
            if (strcmp(books[i].title, input) == 0) 
            {
                printBook(&books[i]);
                found = 1;
            }
        }
        system("pause");
        break;
    case 3: // ��������ѯ
        for (int i = 0; i < book_count; i++) 
        {
            if (strcmp(books[i].author, input) == 0)
            {
                printBook(&books[i]);
                found = 1;
            }
        }
        system("pause");
        break;
    case 4: // �������ѯ
        for (int i = 0; i < book_count; i++) 
        {
            if (strcmp(books[i].publisher, input) == 0) 
            {
                printBook(&books[i]);
                found = 1;
            }
        }
        system("pause");
        break;
    default:
        printf("��Ч�Ĳ�ѯѡ�\n");
        return;
    }

    if (!found)
    {
        printf("δ�ҵ�ƥ���ͼ����Ϣ��\n");
        system("pause");
    }
}

void modifyBook() {
    char targetBarcode[20];
    int index = -1;

    printf("������Ҫ�޸ĵ�ͼ��������: ");
    scanf("%s", targetBarcode);

    for (int i = 0; i < book_count; i++) 
    {
        if (strcmp(books[i].barcode, targetBarcode) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        printf("�ҵ��˸�ͼ�飬��Ϣ����:\n");
        printBook(&books[index]);

        char confirm;
        printf("ȷ���޸���(y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') 
        {
          
            printf("�����µ�ͼ����Ϣ...\n");
            scanf("%s %s %s %s %d %f %d",
                books[index].barcode, books[index].title,
                books[index].author, books[index].publisher,
                &books[index].publish_year, &books[index].price,
                &books[index].stock);
            printf("ͼ����Ϣ�޸ĳɹ���\n");
            system("pause");
        }
        else 
        {
            printf("ȡ���޸ġ�\n");
            system("pause");
        }
    }
    else 
    {
        printf("δ�ҵ�������Ϊ'%s'��ͼ�顣\n", targetBarcode);
    }
}

void deleteBook(int option) 
{
    char target[100];
    int deleted = 0;

    printf("������Ҫɾ������Ϣ: ");
    scanf("%s", target);

    for (int i = 0; i < book_count; i++) 
    {
        switch (option) 
        {
        case 1: // ������ɾ��
            if (strcmp(books[i].barcode, target) == 0) 
            {
                deleted = 1;
                break;
            }
        case 2: // ����ɾ��
            if (strcmp(books[i].title, target) == 0)
            {
                deleted = 1;
                break;
            }
        case 3: // ������ɾ��
            if (strcmp(books[i].author, target) == 0) 
            {
                deleted = 1;
                break;
            }
        default:
            printf("��Ч��ɾ��ѡ�\n");
            return;
        }

        if (deleted) 
        {
            // �ƶ�����Ԫ�����λ����С����
            for (int j = i; j < book_count - 1; j++) 
            {
                books[j] = books[j + 1];
            }
            book_count--;
            printf("ͼ����ɾ����\n");
            break;
            system("pause");
        }
    }

    if (!deleted) 
    {
        printf("δ�ҵ�ƥ���ͼ�����ɾ����\n");
        system("pause");
    }
}

// �����ȽϺ���
int compareByBarcode(const void* a, const void* b)
{
    return strcmp(((Book*)a)->barcode, ((Book*)b)->barcode);
}

int compareByStock(const void* a, const void* b) 
{
    return ((Book*)a)->stock - ((Book*)b)->stock;
}

int compareByYear(const void* a, const void* b) 
{
    return ((Book*)a)->publish_year - ((Book*)b)->publish_year;
}

void sortBooks(int option) 
{

    switch (option) 
    {
    case 1: // ������������
        qsort(books, book_count, sizeof(Book), compareByBarcode);
        break;
    case 2: // ���ݲ���������
        qsort(books, book_count, sizeof(Book), compareByStock);
        break;
    case 3: // ������ʱ������
        qsort(books, book_count, sizeof(Book), compareByYear);
        break;
    default:
        printf("��Ч������ѡ�\n");
        return;
    }
    printf("ͼ�鰴ָ����ʽ������ɡ�\n");
    displayBooks(); // ��ʾ�����Ľ��
}


void statistics(int option) 
{
    int count = 0;

    switch (option) 
    {
    case 1: // ͳ�ƹݲ�����С��ĳ��ֵ��ͼ��
        printf("������ݲ�������ֵ: ");
        scanf("%d", &count);
        for (int i = 0; i < book_count; i++) 
        {
            if (books[i].stock < count) 
            {
                printBook(&books[i]);
            }
        }
        break;
    case 2: // ͳ�Ƴ�����������ĳ��ֵ��ͼ��
        printf("��������������ֵ: ");
        scanf("%d", &count);
        for (int i = 0; i < book_count; i++) 
        {
            if (books[i].publish_year < count) 
            {
                printBook(&books[i]);
            }
        }
        break;
    default:
        printf("��Ч��ͳ��ѡ�\n");
        return;
    }

    printf("���ҵ� %d �����������ļ�¼��\n", count); // ʵ��ͳ�Ƶ�������
    system("pause");
}



int main() {
    int choice, subChoice;
    loadBooks(); // ��������ʱ��������

    while (1) 
    {
        system("cls");
        printf("\nͼ����Ϣ����ϵͳ\n");
        printf("\n***********************\n");
        printf("\n1.��ʾͼ����Ϣ\n");  //Book_show()
        printf("\n2.���ͼ����Ϣ\n");  //Book_add()
        printf("\n3.��ѯͼ����Ϣ\n");  //Book_search()
        printf("\n4.�޸�ͼ����Ϣ\n");  //Book_modify()
        printf("\n5.ɾ��ͼ����Ϣ\n");  //Book_delete()
        printf("\n6.����ͼ����Ϣ\n");  //Book_sort()
        printf("\n7.ͳ��ͼ����Ϣ\n");  //Book_count()
        printf("\n8.�˳�\n");
        printf("\n***********************\n");
        printf("\n����������ѡ��(1-8)��");
        printf("\n");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1: // ���
            displayBooks();
            break;
        case 2: // ���
            addBook();
            break;
        case 3: // ��ѯ
            printf("��ѯ��ʽ:\n1. ������\n2. ����\n3. ������\n4. ������\n");
            scanf("%d", &subChoice);
            queryBooks(subChoice);
            break;
        case 4: // �޸�
            modifyBook();
            break;
        case 5: // ɾ��
            printf("ɾ����ʽ:\n1. ������\n2. ����\n3. ������\n");
            scanf("%d", &subChoice);
            deleteBook(subChoice);
            break;
        case 6: // ����
            printf("����ʽ:\n1. ������\n2. �ݲ�����\n3. ����ʱ��\n");
            scanf("%d", &subChoice);
            sortBooks(subChoice);
            break;
        case 7: // ͳ��
            printf("ͳ�Ʒ�ʽ:\n1. �ݲ�����С��ĳֵ\n2. ������������ĳ��\n");
            scanf("%d", &subChoice);
            statistics(subChoice);
            break;
        case 8: // �˳�
            saveBooks(); // �������
            return 0;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }

    }
    system("pause");
    return 0;
}
