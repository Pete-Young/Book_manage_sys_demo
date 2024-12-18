#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

int student_count = 0;

//加载学生信息
void loadStudents()
{
    FILE* in = fopen("students.txt", "r");
    if (in == NULL) {
        // 表示用户是第一次使用该系统
        printf("\t\t\t\t\t\n请输入要添加的学生信息数量：");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("\t\t\t\t\t要添加的第%d个学生信息：\n", i + 1);
            addStudent();
        }
        return;
    }
    while (fscanf(in, "%s%60s%49s", students[student_count].ID, students[student_count].name, students[student_count].Class) != EOF) {
        student_count++;
    }
    fclose(in);
}

//保存学生信息
void saveStudents()
{
    FILE* out = fopen("students.txt", "w");
    for (int i = 0; i < student_count; i++) {
        fprintf(out, "%s%60s\t%49s\n", students[i].ID, students[i].name, students[i].Class);
    }
    fclose(out);
}

// 添加学生功能
void addStudent()
{
    Student stu;
    printf("\t\t\t\t\t请输入学生信息");
    printf("\t\t\t\t\t姓名: ");
    scanf("%s", &stu.name);
    printf("\t\t\t\t\t学号: ");
    scanf("%s", &stu.ID);
    printf("\t\t\t\t\t班级: ");
    scanf("%s", &stu.Class);

    int i = 0;
    int j = student_count - 1;
    //判断是否输入已存在该学号
    while (i <= j)
    {
        if (strcmp(students[i++].ID, stu.ID) == 0 || strcmp(students[j--].ID, stu.ID) == 0)
        {
            printf("\t\t\t\t\t学号重复，添加失败！\n");
            system("pause");
            return;
        }
    }
    //学号未重复则添加成功
    students[student_count++] = stu;
    printf("\t\t\t\t\t学生添加成功。\n");
    system("pause");
}

// 删除学生信息功能
void deleteStudent()
{
    char target[100];
    int deleted = 0;
    int i;

    printf("\t\t\t\t\t请输入对应学生的学号: ");
    scanf("%s", target);

    for (i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].ID, target) == 0)
        {
            deleted = 1;
            break;
        }
    }
    if (deleted)
    {
        // 移动后续元素填补空位，减小计数
        for (int j = i; j < student_count - 1; j++) {
            students[j] = students[j + 1];
        }
        student_count--;
        printf("\t\t\t\t\t学生信息已删除。\n");
        system("pause");
    }

    if (!deleted) {
        printf("\t\t\t\t\t未找到匹配的学生信息进行删除。\n");
        system("pause");
    }
}

// 展示学生信息功能
void displayStudent()
{
    for (int i = 0; i < student_count; i++) {
        int n = 0;
        for (int j = 0; j < borrow_count; j++) {
            if (strcmp(students[i].ID, borrow[j].ID) == 0) {
                strcpy(students[i].bname[n], borrow[j].bname);
                strcpy(students[i].bID[n], borrow[j].bID);
                students[i].year[n] = borrow[j].year;
                students[i].month[n] = borrow[j].month;
                students[i].day[n] = borrow[j].day;
                n++;
            }
        }
    }

    for (int i = 0; i < student_count; i++)
    {
        printf("\t\t\t\t\t学号:%s 姓名:%s 班级:%s", students[i].ID, students[i].name, students[i].Class);
        for (int j = 0; students[i].year[j] >= 2024; j++) {
            if (j != 0)
            {
                printf("\t\t    ");
            }
            printf("\t\t\t\t\t 借阅书名:%s 书编号:%s 借阅时间:%d-%d-%d\n", students[i].bname[j], students[i].bID[j], students[i].year[j], students[i].month[j], students[i].day[j]);
        }
        printf("\n");
    }
    system("pause");
}

// 借书功能
void borrowBook(int option)
{

    if (option == 3)
        return;

    int found = 0;
    char input[100];
    char id[100];
    int j;
    printf("\t\t\t\t\t请输入学号:");
    scanf("%s", &id);
    for (j = 0; j < student_count; j++)
    {
        if (strcmp(students[j].ID, id) == 0)
            break;
    }
    //判断是否存在该学生
    if (j == student_count)
    {
        printf("\t\t\t\t\t学生不存在\n");
        system("pause");
        return;
    }

    struct BookNode* p = head->next;
    //根据选项输入借阅信息
    switch (option)
    {
    case 1: //编号
        printf("\t\t\t\t\t请输入图书编号: ");
        scanf("%s", input);

        while (p != NULL) {
            if (strcmp(p->data.id, input) == 0) {
                if (strcmp(p->data.status, "已借") == 0) {
                    printf("\t\t\t\t\t该书已被借出，借阅失败\n");
                }
                //未被借则进入下一步
                if (strcmp(p->data.status, "未被借") == 0)
                {
                    printf("\t\t\t\t\t请输入借阅时间:");
                    scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    //判断输入的借阅时间是否符合规范
                    while (borrow[borrow_count].year <= 0 || borrow[borrow_count].month > 12 || borrow[borrow_count].month <= 0 || borrow[borrow_count].day > 31 || borrow[borrow_count].day <= 0)
                    {
                        printf("\t\t\t\t\t请正确输入时间: ");
                        scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    }
                    printf("\t\t\t\t\t借阅成功\n");
                    //书的状态改成已借
                    strcpy(p->data.status, "已借");
                    //记录学生所借书籍
                    strcpy(borrow[borrow_count].ID, id);
                    strcpy(borrow[borrow_count].bname, p->data.title);
                    strcpy(borrow[borrow_count].bID, p->data.id);
                    borrow_count++;
                }
                found = 1;
                system("pause");
                break;
            }
            p = p->next;
        }
        break;
    case 2: //书名
        printf("\t\t\t\t\t请输入书名: ");
        scanf("%s", input);

        while (p != NULL) {
            if (strcmp(p->data.title, input) == 0) {
                if (strcmp(p->data.status, "已借") == 0) {
                    printf("\t\t\t\t\t该书已被借出，借阅失败\n");
                }
                //未被借则进入下一步
                if (strcmp(p->data.status, "未被借") == 0)
                {
                    printf("\t\t\t\t\t请输入借阅时间:");
                    scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    //判断输入的借阅时间是否符合规范
                    while (borrow[borrow_count].year <= 0 || borrow[borrow_count].month > 12 || borrow[borrow_count].month <= 0 || borrow[borrow_count].day > 31 || borrow[borrow_count].day <= 0)
                    {
                        printf("\t\t\t\t\t请正确输入时间: ");
                        scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    }
                    printf("\t\t\t\t\t借阅成功\n");
                    //书的状态改成已借
                    strcpy(p->data.status, "已借");
                    //记录学生所借书籍
                    strcpy(borrow[borrow_count].ID, id);
                    strcpy(borrow[borrow_count].bname, p->data.title);
                    strcpy(borrow[borrow_count].bID, p->data.id);
                    borrow_count++;
                }
                found = 1;
                system("pause");
                break;
            }
            p = p->next;
        }
        break;
    default:
        printf("\t\t\t\t\t无效的借阅选项。\n");
        return;
    }

    if (!found)
    {
        printf("\t\t\t\t\t未找到匹配的图书信息。\n");
        system("pause");
    }
}

// 判断天数差
int shijian(Student stu, int year, int month, int day, int m)
{
    // 定义两个 tm 结构体，用于存储时间信息
    struct tm date1 = { 0 };  // 存储学生的出生日期
    struct tm date2 = { 0 };  // 存储目标日期

    // 初始化学生的出生日期
    date1.tm_year = stu.year[m] - 1900;  // tm_year 是从 1900 年开始的年份数，因此需要减去 1900
    date1.tm_mon = stu.month[m] - 1;     // tm_mon 是从 0 开始的月份（0 表示 1 月），因此需要减去 1
    date1.tm_mday = stu.day[m];          // tm_mday 是月份中的日

    // 初始化目标日期
    date2.tm_year = year - 1900;      // 同样，tm_year 需要减去 1900
    date2.tm_mon = month - 1;         // 同样，tm_mon 需要减去 1
    date2.tm_mday = day;              // 目标日期的日

    // 使用 mktime 将 tm 结构体转换为 time_t 类型的时间戳
    // mktime 会根据给定的日期计算出自 1970-01-01 以来的秒数
    time_t time1 = mktime(&date1);    // 学生出生日期的时间戳
    time_t time2 = mktime(&date2);    // 目标日期的时间戳

    // 使用 difftime 计算两个时间戳之间的差值（以秒为单位）
    double diff = difftime(time2, time1);

    // 将秒数差转换为天数差
    // 一天有 24 小时，每小时 60 分钟，每分钟 60 秒
    int diffday = (int)(diff / (24 * 60 * 60));

    // 返回两个日期之间的天数差
    return diffday;
}

// 还书功能
void returnBook()
{
    int year, month, day;
    int found = 0;
    char input[100];
    char id[100];
    int j;
    printf("\t\t\t\t\t请输入学号:");
    scanf("%s", &id);
    for (j = 0; j < student_count; j++)
    {
        if (strcmp(students[j].ID, id) == 0)
            break;
    }
    //判断是否存在该学生
    if (j == student_count)
    {
        printf("\t\t\t\t\t学生不存在\n");
        system("pause");
        return;
    }

    if (students[j].year[0] == 0) {
        printf("\t\t\t\t\t该学生并未借书\n");
        system("pause");
        return;
    }

    for (int k = 0; students[j].year[k] != 0; k++) {
        printf("\t\t\t\t\t 借阅书名:%s 书编号:%s 借阅时间:%d-%d-%d\n", students[j].bname[k], students[j].bID[k], students[j].year[k], students[j].month[k], students[j].day[k]);
    }

    printf("\t\t\t\t\t请输入书籍编号:");
    scanf("%s", input);

    int m = 0;
    for (m = 0; students[j].year[m] != 0; m++) {
        if (strcmp(students[j].bID[m], input) == 0) {
            break;
        }
    }

    struct BookNode* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.id, input) == 0) {
            //判断书籍是否是被借出，未被借出则无法还书
            if (strcmp(p->data.status, "未被借") == 0)
            {
                printf("\t\t\t\t\t该书未被借出\n");
                system("pause");
                return;
            }

            printf("\t\t\t\t\t请输入归还时间: ");
            scanf("%d-%d-%d", &year, &month, &day);
            //判断时间输入是否符合规范
            while (year <= 0 || month > 12 || month <= 0 || day > 31 || day <= 0)
            {
                printf("\t\t\t\t\t请正确输入时间: ");
                scanf("%d-%d-%d", &year, &month, &day);
            }
            //计算借书还书日期间隔
            int sj = shijian(students[j], year, month, day, m);
            //判断还书日期是否在借书日期之后，不是则重新输入
            while (sj < 0)
            {
                printf("\t\t\t\t\t请正确输入时间: ");
                scanf("%d-%d-%d", &year, &month, &day);
                //重新算天数
                sj = shijian(students[j], year, month, day, m);
            }
            printf("\t\t\t\t\t借阅天数:%d\n", sj);

            // 借阅天数小于90天无需缴纳罚款
            if (sj <= 90 && sj >= 0)
            {
                printf("\t\t\t\t\t归还成功\n");
            }
            //借阅天数大于90天应缴罚款
            else
            {
                printf("\t\t\t\t\t请缴纳罚款\n");
                printf("\t\t\t\t\t是否缴费:1.是   2.否\n");
                int check;
                scanf("%d", &check);
                if (check != 1 && check != 2)
                {
                    printf("\t\t\t\t\t无效选项\n");
                }
                //只有缴纳罚款后才能继续
                while (check != 1)
                {
                    printf("\t\t\t\t\t是否缴费:1.是   2.否\n");
                    scanf("%d", &check);
                    if (check != 1 && check != 2)
                    {
                        printf("\t\t\t\t\t无效选项\n");
                    }
                }
            }

            for (int i = 0; i < borrow_count - 1; i++) {
                if (strcmp(borrow[i].bID, input) == 0) {
                    strcpy(borrow[i].bname, borrow[i + 1].bname);
                    strcpy(borrow[i].bID, borrow[i + 1].bID);
                    borrow[i].year = borrow[i + 1].year;
                    borrow[i].month = borrow[i + 1].month;
                    borrow[i].day = borrow[i + 1].day;
                }
            }
            students[j].year[m] = 0;
            borrow_count--;

            //书的状态改成未被借
            strcpy(p->data.status, "未被借");
            found = 1;
        }
        p = p->next;
    }
    system("pause");

    if (!found)
    {
        printf("\t\t\t\t\t未找到匹配的图书信息。\n");
        system("pause");
    }
}

// 学生界面

int studentUI() {
    welcomeUI();
    color(11); // 青色
    printf("\n\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t|                                                  |\n");
    color(14); // 黄色
    printf("\t\t\t\t\t|               1. 借书                            |\n");
    printf("\t\t\t\t\t|               2. 还书                            |\n");
    printf("\t\t\t\t\t|               3. 添加学生信息                    |\n");
    printf("\t\t\t\t\t|               4. 删除学生信息                    |\n");
    printf("\t\t\t\t\t|               5. 展示学生信息                    |\n");
    printf("\t\t\t\t\t|               6. 退出                            |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t| 请选择操作: ");
    int n;
    scanf("%d", &n);
    printf("\t\t\t\t\t+--------------------------------------------------+\n\n");
    return n;
}

// 学生信息功能
void studentRoutine() {
    int choice, subChoice;
    while (1)
    {
        system("cls");
        choice = studentUI();

        switch (choice)
        {
        case 1: // 借书
            printf("\t\t\t\t\t借阅方式: \n1. 编号\n2. 书名\n3. 退出\n");
            scanf("%d", &subChoice);
            borrowBook(subChoice);
            saveStudents();
            saveBooks();
            break;
        case 2: // 还书
            returnBook();
            saveStudents();
            saveBooks();
            break;
        case 3:// 添加学生信息
            addStudent();
            saveStudents();
            break;
        case 4:
            deleteStudent();
            saveStudents();
            break;
        case 5:
            displayStudent();
            break;
        case 6: // 退出
            saveStudents();
            return;
        default:
            printf("\t\t\t\t\t无效的选择，请重新输入。\n");
        }
    }
}