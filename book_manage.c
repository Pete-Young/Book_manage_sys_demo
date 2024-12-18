#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include "book_link.h"
#include "book_func.h"
#include "borrow.h"
#include "student.h"

// ������ɫ
int color(int num)
{
    if (num >= 0 && num <= 15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return 0;
}

void welcomeUI() {
    color(11); // ��ɫ
    printf("\n\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t|                                                  |\n");
    color(12); // ��ɫ
    printf("\t\t\t\t\t|  _       _   _                                    |\n");
    color(14); // ��ɫ
    printf("\t\t\t\t\t| | |     (_) | |__    _ __    __ _   _ __   _   _  |\n");
    color(10); // ��ɫ
    printf("\t\t\t\t\t| | |     | | | '_ \\  | '__|  / _` | | '__| | | | | |\n");
    color(11); // ��ɫ
    printf("\t\t\t\t\t| | |___  | | | |_) | | |    | (_| | | |    | |_| | |\n");
    color(13); // ��ɫ
    printf("\t\t\t\t\t| |_____| |_| |_.__/  |_|     \\__,_| |_|     \\__,_| |\n");
    color(9); // ��ɫ
    printf("\t\t\t\t\t|                                            |___/  |\n");
    color(11); // ��ɫ
    printf("\t\t\t\t\t|                                                  |\n");
    color(12); // ��ɫ
    printf("\t\t\t\t\t|  __  __                                          |\n");
    color(14); // ��ɫ
    printf("\t\t\t\t\t| |  \\/  | __ _ _ __   __ _  __ _  ___ _ __        |\n");
    color(10); // ��ɫ
    printf("\t\t\t\t\t| | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|       |\n");
    color(11); // ��ɫ
    printf("\t\t\t\t\t| | |  | | (_| | | | | (_| | (_| |  __/ |          |\n");
    color(13); // ��ɫ
    printf("\t\t\t\t\t| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|          |\n");
    color(9); // ��ɫ
    printf("\t\t\t\t\t|                            |___/                 |\n");
    color(11); // ��ɫ
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");

}


int mainUI() {
    welcomeUI();
        // color(7); // ��ɫ
    color(14); // ��ɫ
    printf("\t\t\t\t\t|          ��ӭʹ��ͼ����Ϣ����ϵͳ��              |\n");
    color(11); // ��ɫ
    printf("\t\t\t\t\t|               ��ѡ������ѡ�                   |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t|               1. ��ʾͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               2. ���ͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               3. ��ѯͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               4. �޸�ͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               5. ɾ��ͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               6. ����ͼ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               7. ѧ����Ϣ                        |\n");
    printf("\t\t\t\t\t|               8. �˳�                            |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t| ��ѡ�����: ");

    int n;
    scanf("%d", &n);
    printf("\t\t\t\t\t+--------------------------------------------------+\n\n");
    return n;
}



int main() {
    head = createHead();
    int choice, subChoice;
    loadBooks(); // ��������ʱ��������
    loadStudents();
    loadBorrow();

    while (1)
    {
        system("cls");
        choice = mainUI();

        switch (choice)
        {
        case 1: // ���
            displayBooks();
            break;
        case 2: // ���
            addBook();
            break;
        case 3: // ��ѯ
            printf("\t\t\t\t\t��ѯ��ʽ:\n\t\t\t\t\t1. ���\n\t\t\t\t\t2. ����\n\t\t\t\t\t3. ������\n\t\t\t\t\t4. ������\n\t\t\t\t\t5. �˳�\n\t\t\t\t\t");
            scanf("%d", &subChoice);
            queryBooks(subChoice);
            break;
        case 4: // �޸�
            modifyBook();
            break;
        case 5: // ɾ��
            printf("\t\t\t\t\tɾ����ʽ:\n\t\t\t\t\t1. ���\n\t\t\t\t\t2. ����\n\t\t\t\t\t3. ������\n\t\t\t\t\t4. �˳�");
            scanf("%d", &subChoice);
            deleteBook(subChoice);
            break;
        case 6: // ����
            printf("\t\t\t\t\t����ʽ:\n\t\t\t\t\t1. ���\n\t\t\t\t\t2. ����ʱ��\n\t\t\t\t\t");
            scanf("%d", &subChoice);
            sortBooks(subChoice);
            break;
        case 7: // ѧ������
            // subChoice = studentUI();
            studentRoutine();
            break;
        case 8: // �˳�
            saveBooks(); // �������
            saveStudents();
            saveBorrow();
            return 0;
        default:
            printf("\t\t\t\t\t��Ч��ѡ�����������롣\n");
            system("pause");
        }
    }
    system("pause");
    return 0;
}

// int main() {
//     head = createHead();
//     int choice, subChoice;
//     loadBooks(); // ��������ʱ��������
//     loadStudents();
//     loadBorrow();

//     while (1) {
//         choice = mainUI();

//         switch (choice) {
//         case 1:
//             // ��ʾͼ����Ϣ
//             break;
//         case 2:
//             // ���ͼ����Ϣ
//             break;
//         case 3:
//             // ��ѯͼ����Ϣ
//             break;
//         case 4:
//             // �޸�ͼ����Ϣ
//             break;
//         case 5:
//             // ɾ��ͼ����Ϣ
//             break;
//         case 6:
//             // ����ͼ����Ϣ
//             break;
//         case 7:
//             // ѧ����Ϣ
//             subChoice = student1UI();
//             switch (subChoice) {
//             case 1:
//                 // ����
//                 break;
//             case 2:
//                 // ����
//                 break;
//             case 3:
//                 // ���ѧ����Ϣ
//                 break;
//             case 4:
//                 // ɾ��ѧ����Ϣ
//                 break;
//             case 5:
//                 // չʾѧ����Ϣ
//                 break;
//             case 6:
//                 // �˳�
//                 return 0;
//             }
//             break;
//         case 8:
//             // �˳�
//             return 0;
//         }
//     }
//     return 0;
// }