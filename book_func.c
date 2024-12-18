#define _CRT_SECURE_NO_WARNINGS
#include "book_func.h"

int book_count = 0; // 当前图书数量


// 加载图书数据
void loadBooks() {
    FILE* in = fopen("books.txt", "r");
    if (in == NULL) {
        // 表示用户是第一次使用该系统
        welcomeUI();
        printf("\t\t\t\t\t欢迎首次使用图书借阅管理系统!\n");
        printf("请输入要存的书本的数量：");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("要添加的第%d本图书：\n", i + 1);
            addBook();
        }
        return;
    }

    Book pastBook;
    while (fscanf(in, "%s%60s%49s%49s%d%s", pastBook.id, pastBook.title,
        pastBook.author, pastBook.publisher, &pastBook.publish_year, pastBook.status) != EOF) {
        // 按行遍历并存入到链表中
        InsertTail(pastBook);
        book_count++;
    }
    fclose(in);
}

// 保存图书数据
void saveBooks() {
    FILE* out = fopen("books.txt", "w");

    struct BookNode* p = head->next;
    while (p != NULL) {
        // 按行存入链表数据
        fprintf(out, "%s%60s\t%49s\t%49s\t%d\t%s\n", p->data.id, p->data.title, p->data.author, p->data.publisher, p->data.publish_year, p->data.status);
        p = p->next;
    }

    fclose(out);
}

// 添加图书
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("\t\t\t\t\t图书库已满，无法添加更多图书。\n");
        return;
    }

    Book newBook;
    printf("\t\t\t\t\t请输入新图书信息:\n");
    printf("\t\t\t\t\t编号: ");
    scanf("%s", newBook.id);
    newBook.id[strlen(newBook.id)] = '\0';

    struct BookNode* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.id, newBook.id) == 0) {
            printf("\t\t\t\t\t图书编号重复，添加失败！\n");
            system("pause");
            return;
        }
        p = p->next;
    }

    printf("\t\t\t\t\t书名: ");
    scanf("%60s", newBook.title);
    newBook.title[strlen(newBook.title)] = '\0';
    printf("\t\t\t\t\t作者名: ");
    scanf("%49s", newBook.author);
    newBook.author[strlen(newBook.author)] = '\0';
    printf("\t\t\t\t\t出版社: ");
    scanf("%49s", newBook.publisher);
    newBook.publisher[strlen(newBook.publisher)] = '\0';
    printf("\t\t\t\t\t出版年份: ");
    scanf("%d", &newBook.publish_year);

    strcpy(newBook.status, "\t\t\t\t\t未被借");
    newBook.status[strlen(newBook.status)] = '\0';
    InsertTail(newBook);
    book_count++;
    printf("\t\t\t\t\t图书添加成功!\n");
    system("pause");
}

// 显示单本图书信息的辅助函数
void printBook(struct BookNode* p)
{
    printf("\t\t\t\t\t编号: %s, 书名: %s, 作者: %s, 出版社: %s, 出版年份: %d, 借阅状态: %s\n",
        p->data.id, p->data.title, p->data.author, p->data.publisher, p->data.publish_year, p->data.status);
}

// 浏览图书功能
void displayBooks()
{
    struct BookNode* p = head->next;

    printf("\n\t\t\t\t\t当前图书信息列表:\n");
    while (p != NULL) {
        printBook(p);
        p = p->next;
    }
    printf("\t\t\t\t\t共记录了 %d 本图书。\n", book_count);
    system("pause");
}

// 查询图书功能
void queryBooks(int option) {

    if (option == 5)
        return;

    char input[100];
    bool found = false;

    printf("\t\t\t\t\t请输入查询关键字: ");
    scanf("%s", input);
    input[strlen(input)] = '\0';

    struct BookNode* p = head->next;
    switch (option) {
    case 1: // 编号查询
        while (p != NULL) {
            if (strcmp(p->data.id, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 2: // 书名查询
        while (p != NULL) {
            if (strcmp(p->data.title, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 3: // 作者名查询
        while (p != NULL) {
            if (strcmp(p->data.author, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 4: // 出版社查询
        while (p != NULL) {
            if (strcmp(p->data.publisher, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    default:
        printf("\t\t\t\t\t无效的查询选项。\n");
        return;
    }

    if (!found) {
        printf("\t\t\t\t\t未找到匹配的图书信息。\n");
        system("pause");
    }
}

// 修改图书功能
void modifyBook() {
    char targetId[20];
    int index = -1;

    printf("\t\t\t\t\t请输入要修改的图书编号: ");
    scanf("%s", targetId);
    targetId[strlen(targetId)] = '\0';

    struct BookNode* p = head->next;
    struct BookNode* q = NULL;
    while (p != NULL) {
        if (strcmp(p->data.id, targetId) == 0) {
            q = p;
            break;
        }
        p = p->next;
    }

    if (q != NULL) {
        printf("\t\t\t\t\t找到了该图书，信息如下:\n");
        printBook(q);

        char confirm;
        printf("\t\t\t\t\t确认修改吗？(y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {

            printf("\t\t\t\t\t输入新的图书信息...\n");
            printf("\t\t\t\t\t编号: ");
            scanf("%s", q->data.id);

            printf("\t\t\t\t\t书名: ");
            scanf("%60s", q->data.title);
            printf("\t\t\t\t\t作者名: ");
            scanf("%49s", q->data.author);
            printf("\t\t\t\t\t出版社: ");
            scanf("%49s", q->data.publisher);
            printf("\t\t\t\t\t出版年份: ");
            scanf("%d", &q->data.publish_year);
            printf("\t\t\t\t\t图书信息修改成功。\n");
            system("pause");
        }
        else {
            printf("\t\t\t\t\t取消修改。\n");
            system("pause");
        }
    }
    else {
        printf("\t\t\t\t\t未找到编号为'%s'的图书。\n", targetId);
    }
}

// 删除图书功能
void deleteBook(int option) {

    if (option == 4)
        return;

    char target[100];
    int deleted = 0;
    printf("\t\t\t\t\t请输入要删除的信息: ");
    scanf("%s", target);

    struct BookNode* p = head->next;
    struct BookNode* q = head;
    switch (option) {
    case 1: // 编号删除
        while (p != NULL) {
            if (strcmp(p->data.id, target) == 0) {
                deleted = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        break;
    case 2: // 书名删除
        while (p != NULL) {
            if (strcmp(p->data.title, target) == 0) {
                deleted = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        break;
    case 3: // 作者名删除
        while (p != NULL) {
            if (strcmp(p->data.author, target) == 0) {
                deleted = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        break;
    default:
        printf("\t\t\t\t\t无效的删除选项。\n");
        system("pause");
        return;
    }

    if (deleted) {
        struct BookNode* temp = p;
        q->next = p->next;
        free(temp);
        book_count--;
        printf("\t\t\t\t\t图书已删除。\n");
        system("pause");
        return;
    }

    if (!deleted) {
        printf("\t\t\t\t\t未找到匹配的图书进行删除。\n");
        system("pause");
    }
}

// 根据图书编号排序的辅助函数
void sortById() {
    // 冒泡排序将图书编号按照从小到大进行排序
    for (int i = 0; i < book_count; i++) {
        // 定义三个指针，其中q 和 t是用于数据的比较，m则始终指向q的前一个节点
        struct BookNode* m = head;
        struct BookNode* q = head->next;
        struct BookNode* t = q->next;
        for (int j = 0; j < book_count - i - 1; j++) {
            if (strcmp(q->data.id, t->data.id) > 0) {
                /*
                    如果q的编号比t大，则让m的下一个节点指向t
                    q的下一个节点指向t的下一个节点，再让t的下一个节点指向p
                    但此时从位置上来看，t跑到了q的前面，m 成为了 t 的前一个节点
                    因此 需要 m = t; t = q->next;继续保证 t 的 q 的后一位，m 在q前面
                */
                m->next = t;
                q->next = t->next;
                t->next = q;
                m = t;
                t = q->next;
            }
            else {
                // 如果没有发生变化，则让3个指针都等于各自的下一个节点
                m = m->next;
                q = q->next;
                t = t->next;
            }
        }
    }
}

// 根据出版年份排序的辅助函数
void sortByYear() {
    for (int i = 0; i < book_count; i++) {
        struct BookNode* m = head;
        struct BookNode* q = head->next;
        struct BookNode* t = q->next;
        for (int j = 0; j < book_count - i - 1; j++) {
            if (q->data.publish_year > t->data.publish_year) {
                m->next = t;
                q->next = t->next;
                t->next = q;
                m = t;
                t = q->next;
            }
            else {
                m = m->next;
                q = q->next;
                t = t->next;
            }
        }
    }
}

// 图书排序功能
void sortBooks(int option)
{
    switch (option)
    {
    case 1: // 按编号排序
        sortById();
        break;
    case 2: // 按出版时间排序
        sortByYear();
        break;
    default:
        printf("\t\t\t\t\t无效的排序选项。\n");
        return;
    }
    printf("\t\t\t\t\t图书按指定方式排序完成。\n");
    displayBooks(); // 显示排序后的结果
}

