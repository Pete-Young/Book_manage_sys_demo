#define _CRT_SECURE_NO_WARNINGS
#include "book_func.h"

int book_count = 0; // ��ǰͼ������


// ����ͼ������
void loadBooks() {
    FILE* in = fopen("books.txt", "r");
    if (in == NULL) {
        // ��ʾ�û��ǵ�һ��ʹ�ø�ϵͳ
        welcomeUI();
        printf("\t\t\t\t\t��ӭ�״�ʹ��ͼ����Ĺ���ϵͳ!\n");
        printf("������Ҫ����鱾��������");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("Ҫ��ӵĵ�%d��ͼ�飺\n", i + 1);
            addBook();
        }
        return;
    }

    Book pastBook;
    while (fscanf(in, "%s%60s%49s%49s%d%s", pastBook.id, pastBook.title,
        pastBook.author, pastBook.publisher, &pastBook.publish_year, pastBook.status) != EOF) {
        // ���б��������뵽������
        InsertTail(pastBook);
        book_count++;
    }
    fclose(in);
}

// ����ͼ������
void saveBooks() {
    FILE* out = fopen("books.txt", "w");

    struct BookNode* p = head->next;
    while (p != NULL) {
        // ���д�����������
        fprintf(out, "%s%60s\t%49s\t%49s\t%d\t%s\n", p->data.id, p->data.title, p->data.author, p->data.publisher, p->data.publish_year, p->data.status);
        p = p->next;
    }

    fclose(out);
}

// ���ͼ��
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("\t\t\t\t\tͼ����������޷���Ӹ���ͼ�顣\n");
        return;
    }

    Book newBook;
    printf("\t\t\t\t\t��������ͼ����Ϣ:\n");
    printf("\t\t\t\t\t���: ");
    scanf("%s", newBook.id);
    newBook.id[strlen(newBook.id)] = '\0';

    struct BookNode* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.id, newBook.id) == 0) {
            printf("\t\t\t\t\tͼ�����ظ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
        p = p->next;
    }

    printf("\t\t\t\t\t����: ");
    scanf("%60s", newBook.title);
    newBook.title[strlen(newBook.title)] = '\0';
    printf("\t\t\t\t\t������: ");
    scanf("%49s", newBook.author);
    newBook.author[strlen(newBook.author)] = '\0';
    printf("\t\t\t\t\t������: ");
    scanf("%49s", newBook.publisher);
    newBook.publisher[strlen(newBook.publisher)] = '\0';
    printf("\t\t\t\t\t�������: ");
    scanf("%d", &newBook.publish_year);

    strcpy(newBook.status, "\t\t\t\t\tδ����");
    newBook.status[strlen(newBook.status)] = '\0';
    InsertTail(newBook);
    book_count++;
    printf("\t\t\t\t\tͼ����ӳɹ�!\n");
    system("pause");
}

// ��ʾ����ͼ����Ϣ�ĸ�������
void printBook(struct BookNode* p)
{
    printf("\t\t\t\t\t���: %s, ����: %s, ����: %s, ������: %s, �������: %d, ����״̬: %s\n",
        p->data.id, p->data.title, p->data.author, p->data.publisher, p->data.publish_year, p->data.status);
}

// ���ͼ�鹦��
void displayBooks()
{
    struct BookNode* p = head->next;

    printf("\n\t\t\t\t\t��ǰͼ����Ϣ�б�:\n");
    while (p != NULL) {
        printBook(p);
        p = p->next;
    }
    printf("\t\t\t\t\t����¼�� %d ��ͼ�顣\n", book_count);
    system("pause");
}

// ��ѯͼ�鹦��
void queryBooks(int option) {

    if (option == 5)
        return;

    char input[100];
    bool found = false;

    printf("\t\t\t\t\t�������ѯ�ؼ���: ");
    scanf("%s", input);
    input[strlen(input)] = '\0';

    struct BookNode* p = head->next;
    switch (option) {
    case 1: // ��Ų�ѯ
        while (p != NULL) {
            if (strcmp(p->data.id, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 2: // ������ѯ
        while (p != NULL) {
            if (strcmp(p->data.title, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 3: // ��������ѯ
        while (p != NULL) {
            if (strcmp(p->data.author, input) == 0) {
                printBook(p);
                found = true;
            }
            p = p->next;
        }
        system("pause");
        break;
    case 4: // �������ѯ
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
        printf("\t\t\t\t\t��Ч�Ĳ�ѯѡ�\n");
        return;
    }

    if (!found) {
        printf("\t\t\t\t\tδ�ҵ�ƥ���ͼ����Ϣ��\n");
        system("pause");
    }
}

// �޸�ͼ�鹦��
void modifyBook() {
    char targetId[20];
    int index = -1;

    printf("\t\t\t\t\t������Ҫ�޸ĵ�ͼ����: ");
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
        printf("\t\t\t\t\t�ҵ��˸�ͼ�飬��Ϣ����:\n");
        printBook(q);

        char confirm;
        printf("\t\t\t\t\tȷ���޸���(y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {

            printf("\t\t\t\t\t�����µ�ͼ����Ϣ...\n");
            printf("\t\t\t\t\t���: ");
            scanf("%s", q->data.id);

            printf("\t\t\t\t\t����: ");
            scanf("%60s", q->data.title);
            printf("\t\t\t\t\t������: ");
            scanf("%49s", q->data.author);
            printf("\t\t\t\t\t������: ");
            scanf("%49s", q->data.publisher);
            printf("\t\t\t\t\t�������: ");
            scanf("%d", &q->data.publish_year);
            printf("\t\t\t\t\tͼ����Ϣ�޸ĳɹ���\n");
            system("pause");
        }
        else {
            printf("\t\t\t\t\tȡ���޸ġ�\n");
            system("pause");
        }
    }
    else {
        printf("\t\t\t\t\tδ�ҵ����Ϊ'%s'��ͼ�顣\n", targetId);
    }
}

// ɾ��ͼ�鹦��
void deleteBook(int option) {

    if (option == 4)
        return;

    char target[100];
    int deleted = 0;
    printf("\t\t\t\t\t������Ҫɾ������Ϣ: ");
    scanf("%s", target);

    struct BookNode* p = head->next;
    struct BookNode* q = head;
    switch (option) {
    case 1: // ���ɾ��
        while (p != NULL) {
            if (strcmp(p->data.id, target) == 0) {
                deleted = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        break;
    case 2: // ����ɾ��
        while (p != NULL) {
            if (strcmp(p->data.title, target) == 0) {
                deleted = 1;
                break;
            }
            q = p;
            p = p->next;
        }
        break;
    case 3: // ������ɾ��
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
        printf("\t\t\t\t\t��Ч��ɾ��ѡ�\n");
        system("pause");
        return;
    }

    if (deleted) {
        struct BookNode* temp = p;
        q->next = p->next;
        free(temp);
        book_count--;
        printf("\t\t\t\t\tͼ����ɾ����\n");
        system("pause");
        return;
    }

    if (!deleted) {
        printf("\t\t\t\t\tδ�ҵ�ƥ���ͼ�����ɾ����\n");
        system("pause");
    }
}

// ����ͼ��������ĸ�������
void sortById() {
    // ð������ͼ���Ű��մ�С�����������
    for (int i = 0; i < book_count; i++) {
        // ��������ָ�룬����q �� t���������ݵıȽϣ�m��ʼ��ָ��q��ǰһ���ڵ�
        struct BookNode* m = head;
        struct BookNode* q = head->next;
        struct BookNode* t = q->next;
        for (int j = 0; j < book_count - i - 1; j++) {
            if (strcmp(q->data.id, t->data.id) > 0) {
                /*
                    ���q�ı�ű�t������m����һ���ڵ�ָ��t
                    q����һ���ڵ�ָ��t����һ���ڵ㣬����t����һ���ڵ�ָ��p
                    ����ʱ��λ����������t�ܵ���q��ǰ�棬m ��Ϊ�� t ��ǰһ���ڵ�
                    ��� ��Ҫ m = t; t = q->next;������֤ t �� q �ĺ�һλ��m ��qǰ��
                */
                m->next = t;
                q->next = t->next;
                t->next = q;
                m = t;
                t = q->next;
            }
            else {
                // ���û�з����仯������3��ָ�붼���ڸ��Ե���һ���ڵ�
                m = m->next;
                q = q->next;
                t = t->next;
            }
        }
    }
}

// ���ݳ����������ĸ�������
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

// ͼ��������
void sortBooks(int option)
{
    switch (option)
    {
    case 1: // ���������
        sortById();
        break;
    case 2: // ������ʱ������
        sortByYear();
        break;
    default:
        printf("\t\t\t\t\t��Ч������ѡ�\n");
        return;
    }
    printf("\t\t\t\t\tͼ�鰴ָ����ʽ������ɡ�\n");
    displayBooks(); // ��ʾ�����Ľ��
}

