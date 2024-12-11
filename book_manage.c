#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include "book_manage.h" // 添加此行

// 全局变量
Book books[MAX_BOOKS];
int book_count = 0; // 当前图书数量

void loadBooks() { /* 加载图书信息到内存 */ }
void saveBooks() { /* 保存图书信息到文件 */ }

void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("图书库已满，无法添加更多图书。\n");
        return;
    }

    Book newBook;
    printf("请输入新图书信息:\n");
    printf("条形码: "); 
    scanf("%s", newBook.barcode);
    printf("书名: "); 
    scanf("%99s", newBook.title); // 修改此行
    printf("作者名: "); 
    scanf("%49s", newBook.author); // 修改此行
    printf("出版社: "); 
    scanf("%49s", newBook.publisher); // 修改此行
    printf("出版年份: "); 
    scanf("%d", &newBook.publish_year);
    printf("价格: "); 
    scanf("%f", &newBook.price);
    printf("馆藏数量: "); 
    scanf("%d", &newBook.stock);

    books[book_count++] = newBook;
    printf("图书添加成功。\n");
}

// 显示单本图书信息的辅助函数
void printBook(const Book* book) 
{
    printf("条形码: %s, 书名: %s, 作者: %s, 出版社: %s, 出版年份: %d, 价格: %.2f, 馆藏数量: %d\n",
        book->barcode, book->title, book->author, book->publisher,
        book->publish_year, book->price, book->stock);
}

// 浏览图书功能
void displayBooks() 
{
    printf("\n当前图书信息列表:\n");
    for (int i = 0; i < book_count; i++) 
    {
        printBook(&books[i]);
    }
    printf("共记录了 %d 本图书。\n", book_count);
    system("pause");
}

void queryBooks(int option) 
{
    char input[100];
    int found = 0;

    printf("请输入查询关键字: ");
    scanf("%s", input);

    switch (option) 
    {
    case 1: // 条形码查询
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
    case 2: // 书名查询
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
    case 3: // 作者名查询
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
    case 4: // 出版社查询
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
        printf("无效的查询选项。\n");
        return;
    }

    if (!found)
    {
        printf("未找到匹配的图书信息。\n");
        system("pause");
    }
}

void modifyBook() {
    char targetBarcode[20];
    int index = -1;

    printf("请输入要修改的图书条形码: ");
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
        printf("找到了该图书，信息如下:\n");
        printBook(&books[index]);

        char confirm;
        printf("确认修改吗？(y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') 
        {
          
            printf("输入新的图书信息...\n");
            scanf("%s %s %s %s %d %f %d",
                books[index].barcode, books[index].title,
                books[index].author, books[index].publisher,
                &books[index].publish_year, &books[index].price,
                &books[index].stock);
            printf("图书信息修改成功。\n");
            system("pause");
        }
        else 
        {
            printf("取消修改。\n");
            system("pause");
        }
    }
    else 
    {
        printf("未找到条形码为'%s'的图书。\n", targetBarcode);
    }
}

void deleteBook(int option) 
{
    char target[100];
    int deleted = 0;

    printf("请输入要删除的信息: ");
    scanf("%s", target);

    for (int i = 0; i < book_count; i++) 
    {
        switch (option) 
        {
        case 1: // 条形码删除
            if (strcmp(books[i].barcode, target) == 0) 
            {
                deleted = 1;
                break;
            }
        case 2: // 书名删除
            if (strcmp(books[i].title, target) == 0)
            {
                deleted = 1;
                break;
            }
        case 3: // 作者名删除
            if (strcmp(books[i].author, target) == 0) 
            {
                deleted = 1;
                break;
            }
        default:
            printf("无效的删除选项。\n");
            return;
        }

        if (deleted) 
        {
            // 移动后续元素填补空位，减小计数
            for (int j = i; j < book_count - 1; j++) 
            {
                books[j] = books[j + 1];
            }
            book_count--;
            printf("图书已删除。\n");
            break;
            system("pause");
        }
    }

    if (!deleted) 
    {
        printf("未找到匹配的图书进行删除。\n");
        system("pause");
    }
}

// 辅助比较函数
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
    case 1: // 按条形码排序
        qsort(books, book_count, sizeof(Book), compareByBarcode);
        break;
    case 2: // 按馆藏数量排序
        qsort(books, book_count, sizeof(Book), compareByStock);
        break;
    case 3: // 按出版时间排序
        qsort(books, book_count, sizeof(Book), compareByYear);
        break;
    default:
        printf("无效的排序选项。\n");
        return;
    }
    printf("图书按指定方式排序完成。\n");
    displayBooks(); // 显示排序后的结果
}


void statistics(int option) 
{
    int count = 0;

    switch (option) 
    {
    case 1: // 统计馆藏数量小于某个值的图书
        printf("请输入馆藏数量阈值: ");
        scanf("%d", &count);
        for (int i = 0; i < book_count; i++) 
        {
            if (books[i].stock < count) 
            {
                printBook(&books[i]);
            }
        }
        break;
    case 2: // 统计出版日期早于某个值的图书
        printf("请输入出版年份阈值: ");
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
        printf("无效的统计选项。\n");
        return;
    }

    printf("共找到 %d 条符合条件的记录。\n", count); // 实际统计到的数量
    system("pause");
}



int main() {
    int choice, subChoice;
    loadBooks(); // 程序启动时加载数据

    while (1) 
    {
        system("cls");
        printf("\n图书信息管理系统\n");
        printf("\n***********************\n");
        printf("\n1.显示图书信息\n");  //Book_show()
        printf("\n2.添加图书信息\n");  //Book_add()
        printf("\n3.查询图书信息\n");  //Book_search()
        printf("\n4.修改图书信息\n");  //Book_modify()
        printf("\n5.删除图书信息\n");  //Book_delete()
        printf("\n6.排序图书信息\n");  //Book_sort()
        printf("\n7.统计图书信息\n");  //Book_count()
        printf("\n8.退出\n");
        printf("\n***********************\n");
        printf("\n请输入您的选择(1-8)：");
        printf("\n");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1: // 浏览
            displayBooks();
            break;
        case 2: // 添加
            addBook();
            break;
        case 3: // 查询
            printf("查询方式:\n1. 条形码\n2. 书名\n3. 作者名\n4. 出版社\n");
            scanf("%d", &subChoice);
            queryBooks(subChoice);
            break;
        case 4: // 修改
            modifyBook();
            break;
        case 5: // 删除
            printf("删除方式:\n1. 条形码\n2. 书名\n3. 作者名\n");
            scanf("%d", &subChoice);
            deleteBook(subChoice);
            break;
        case 6: // 排序
            printf("排序方式:\n1. 条形码\n2. 馆藏数量\n3. 出版时间\n");
            scanf("%d", &subChoice);
            sortBooks(subChoice);
            break;
        case 7: // 统计
            printf("统计方式:\n1. 馆藏数量小于某值\n2. 出版日期早于某年\n");
            scanf("%d", &subChoice);
            statistics(subChoice);
            break;
        case 8: // 退出
            saveBooks(); // 保存更改
            return 0;
        default:
            printf("无效的选择，请重新输入。\n");
        }

    }
    system("pause");
    return 0;
}
