#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include "book_link.h"
#include "book_func.h"
#include "borrow.h"
#include "student.h"

// 字体颜色
int color(int num)
{
    if (num >= 0 && num <= 15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return 0;
}

void welcomeUI() {
    color(11); // 青色
    printf("\n\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t|                                                  |\n");
    color(12); // 红色
    printf("\t\t\t\t\t|  _       _   _                                    |\n");
    color(14); // 黄色
    printf("\t\t\t\t\t| | |     (_) | |__    _ __    __ _   _ __   _   _  |\n");
    color(10); // 绿色
    printf("\t\t\t\t\t| | |     | | | '_ \\  | '__|  / _` | | '__| | | | | |\n");
    color(11); // 青色
    printf("\t\t\t\t\t| | |___  | | | |_) | | |    | (_| | | |    | |_| | |\n");
    color(13); // 紫色
    printf("\t\t\t\t\t| |_____| |_| |_.__/  |_|     \\__,_| |_|     \\__,_| |\n");
    color(9); // 蓝色
    printf("\t\t\t\t\t|                                            |___/  |\n");
    color(11); // 青色
    printf("\t\t\t\t\t|                                                  |\n");
    color(12); // 红色
    printf("\t\t\t\t\t|  __  __                                          |\n");
    color(14); // 黄色
    printf("\t\t\t\t\t| |  \\/  | __ _ _ __   __ _  __ _  ___ _ __        |\n");
    color(10); // 绿色
    printf("\t\t\t\t\t| | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|       |\n");
    color(11); // 青色
    printf("\t\t\t\t\t| | |  | | (_| | | | | (_| | (_| |  __/ |          |\n");
    color(13); // 紫色
    printf("\t\t\t\t\t| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|          |\n");
    color(9); // 蓝色
    printf("\t\t\t\t\t|                            |___/                 |\n");
    color(11); // 青色
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");

}


int mainUI() {
    welcomeUI();
        // color(7); // 白色
    color(14); // 黄色
    printf("\t\t\t\t\t|          欢迎使用图书信息管理系统！              |\n");
    color(11); // 青色
    printf("\t\t\t\t\t|               请选择以下选项：                   |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t|               1. 显示图书信息                    |\n");
    printf("\t\t\t\t\t|               2. 添加图书信息                    |\n");
    printf("\t\t\t\t\t|               3. 查询图书信息                    |\n");
    printf("\t\t\t\t\t|               4. 修改图书信息                    |\n");
    printf("\t\t\t\t\t|               5. 删除图书信息                    |\n");
    printf("\t\t\t\t\t|               6. 排序图书信息                    |\n");
    printf("\t\t\t\t\t|               7. 学生信息                        |\n");
    printf("\t\t\t\t\t|               8. 退出                            |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t| 请选择操作: ");

    int n;
    scanf("%d", &n);
    printf("\t\t\t\t\t+--------------------------------------------------+\n\n");
    return n;
}



int main() {
    head = createHead();
    int choice, subChoice;
    loadBooks(); // 程序启动时加载数据
    loadStudents();
    loadBorrow();

    while (1)
    {
        system("cls");
        choice = mainUI();

        switch (choice)
        {
        case 1: // 浏览
            displayBooks();
            break;
        case 2: // 添加
            addBook();
            break;
        case 3: // 查询
            printf("\t\t\t\t\t查询方式:\n\t\t\t\t\t1. 编号\n\t\t\t\t\t2. 书名\n\t\t\t\t\t3. 作者名\n\t\t\t\t\t4. 出版社\n\t\t\t\t\t5. 退出\n\t\t\t\t\t");
            scanf("%d", &subChoice);
            queryBooks(subChoice);
            break;
        case 4: // 修改
            modifyBook();
            break;
        case 5: // 删除
            printf("\t\t\t\t\t删除方式:\n\t\t\t\t\t1. 编号\n\t\t\t\t\t2. 书名\n\t\t\t\t\t3. 作者名\n\t\t\t\t\t4. 退出");
            scanf("%d", &subChoice);
            deleteBook(subChoice);
            break;
        case 6: // 排序
            printf("\t\t\t\t\t排序方式:\n\t\t\t\t\t1. 编号\n\t\t\t\t\t2. 出版时间\n\t\t\t\t\t");
            scanf("%d", &subChoice);
            sortBooks(subChoice);
            break;
        case 7: // 学生界面
            // subChoice = studentUI();
            studentRoutine();
            break;
        case 8: // 退出
            saveBooks(); // 保存更改
            saveStudents();
            saveBorrow();
            return 0;
        default:
            printf("\t\t\t\t\t无效的选择，请重新输入。\n");
            system("pause");
        }
    }
    system("pause");
    return 0;
}

// int main() {
//     head = createHead();
//     int choice, subChoice;
//     loadBooks(); // 程序启动时加载数据
//     loadStudents();
//     loadBorrow();

//     while (1) {
//         choice = mainUI();

//         switch (choice) {
//         case 1:
//             // 显示图书信息
//             break;
//         case 2:
//             // 添加图书信息
//             break;
//         case 3:
//             // 查询图书信息
//             break;
//         case 4:
//             // 修改图书信息
//             break;
//         case 5:
//             // 删除图书信息
//             break;
//         case 6:
//             // 排序图书信息
//             break;
//         case 7:
//             // 学生信息
//             subChoice = student1UI();
//             switch (subChoice) {
//             case 1:
//                 // 借书
//                 break;
//             case 2:
//                 // 还书
//                 break;
//             case 3:
//                 // 添加学生信息
//                 break;
//             case 4:
//                 // 删除学生信息
//                 break;
//             case 5:
//                 // 展示学生信息
//                 break;
//             case 6:
//                 // 退出
//                 return 0;
//             }
//             break;
//         case 8:
//             // 退出
//             return 0;
//         }
//     }
//     return 0;
// }