#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

int student_count = 0;

//����ѧ����Ϣ
void loadStudents()
{
    FILE* in = fopen("students.txt", "r");
    if (in == NULL) {
        // ��ʾ�û��ǵ�һ��ʹ�ø�ϵͳ
        printf("\t\t\t\t\t\n������Ҫ��ӵ�ѧ����Ϣ������");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("\t\t\t\t\tҪ��ӵĵ�%d��ѧ����Ϣ��\n", i + 1);
            addStudent();
        }
        return;
    }
    while (fscanf(in, "%s%60s%49s", students[student_count].ID, students[student_count].name, students[student_count].Class) != EOF) {
        student_count++;
    }
    fclose(in);
}

//����ѧ����Ϣ
void saveStudents()
{
    FILE* out = fopen("students.txt", "w");
    for (int i = 0; i < student_count; i++) {
        fprintf(out, "%s%60s\t%49s\n", students[i].ID, students[i].name, students[i].Class);
    }
    fclose(out);
}

// ���ѧ������
void addStudent()
{
    Student stu;
    printf("\t\t\t\t\t������ѧ����Ϣ");
    printf("\t\t\t\t\t����: ");
    scanf("%s", &stu.name);
    printf("\t\t\t\t\tѧ��: ");
    scanf("%s", &stu.ID);
    printf("\t\t\t\t\t�༶: ");
    scanf("%s", &stu.Class);

    int i = 0;
    int j = student_count - 1;
    //�ж��Ƿ������Ѵ��ڸ�ѧ��
    while (i <= j)
    {
        if (strcmp(students[i++].ID, stu.ID) == 0 || strcmp(students[j--].ID, stu.ID) == 0)
        {
            printf("\t\t\t\t\tѧ���ظ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    //ѧ��δ�ظ�����ӳɹ�
    students[student_count++] = stu;
    printf("\t\t\t\t\tѧ����ӳɹ���\n");
    system("pause");
}

// ɾ��ѧ����Ϣ����
void deleteStudent()
{
    char target[100];
    int deleted = 0;
    int i;

    printf("\t\t\t\t\t�������Ӧѧ����ѧ��: ");
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
        // �ƶ�����Ԫ�����λ����С����
        for (int j = i; j < student_count - 1; j++) {
            students[j] = students[j + 1];
        }
        student_count--;
        printf("\t\t\t\t\tѧ����Ϣ��ɾ����\n");
        system("pause");
    }

    if (!deleted) {
        printf("\t\t\t\t\tδ�ҵ�ƥ���ѧ����Ϣ����ɾ����\n");
        system("pause");
    }
}

// չʾѧ����Ϣ����
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
        printf("\t\t\t\t\tѧ��:%s ����:%s �༶:%s", students[i].ID, students[i].name, students[i].Class);
        for (int j = 0; students[i].year[j] >= 2024; j++) {
            if (j != 0)
            {
                printf("\t\t    ");
            }
            printf("\t\t\t\t\t ��������:%s ����:%s ����ʱ��:%d-%d-%d\n", students[i].bname[j], students[i].bID[j], students[i].year[j], students[i].month[j], students[i].day[j]);
        }
        printf("\n");
    }
    system("pause");
}

// ���鹦��
void borrowBook(int option)
{

    if (option == 3)
        return;

    int found = 0;
    char input[100];
    char id[100];
    int j;
    printf("\t\t\t\t\t������ѧ��:");
    scanf("%s", &id);
    for (j = 0; j < student_count; j++)
    {
        if (strcmp(students[j].ID, id) == 0)
            break;
    }
    //�ж��Ƿ���ڸ�ѧ��
    if (j == student_count)
    {
        printf("\t\t\t\t\tѧ��������\n");
        system("pause");
        return;
    }

    struct BookNode* p = head->next;
    //����ѡ�����������Ϣ
    switch (option)
    {
    case 1: //���
        printf("\t\t\t\t\t������ͼ����: ");
        scanf("%s", input);

        while (p != NULL) {
            if (strcmp(p->data.id, input) == 0) {
                if (strcmp(p->data.status, "�ѽ�") == 0) {
                    printf("\t\t\t\t\t�����ѱ����������ʧ��\n");
                }
                //δ�����������һ��
                if (strcmp(p->data.status, "δ����") == 0)
                {
                    printf("\t\t\t\t\t���������ʱ��:");
                    scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    //�ж�����Ľ���ʱ���Ƿ���Ϲ淶
                    while (borrow[borrow_count].year <= 0 || borrow[borrow_count].month > 12 || borrow[borrow_count].month <= 0 || borrow[borrow_count].day > 31 || borrow[borrow_count].day <= 0)
                    {
                        printf("\t\t\t\t\t����ȷ����ʱ��: ");
                        scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    }
                    printf("\t\t\t\t\t���ĳɹ�\n");
                    //���״̬�ĳ��ѽ�
                    strcpy(p->data.status, "�ѽ�");
                    //��¼ѧ�������鼮
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
    case 2: //����
        printf("\t\t\t\t\t����������: ");
        scanf("%s", input);

        while (p != NULL) {
            if (strcmp(p->data.title, input) == 0) {
                if (strcmp(p->data.status, "�ѽ�") == 0) {
                    printf("\t\t\t\t\t�����ѱ����������ʧ��\n");
                }
                //δ�����������һ��
                if (strcmp(p->data.status, "δ����") == 0)
                {
                    printf("\t\t\t\t\t���������ʱ��:");
                    scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    //�ж�����Ľ���ʱ���Ƿ���Ϲ淶
                    while (borrow[borrow_count].year <= 0 || borrow[borrow_count].month > 12 || borrow[borrow_count].month <= 0 || borrow[borrow_count].day > 31 || borrow[borrow_count].day <= 0)
                    {
                        printf("\t\t\t\t\t����ȷ����ʱ��: ");
                        scanf("%d-%d-%d", &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day);
                    }
                    printf("\t\t\t\t\t���ĳɹ�\n");
                    //���״̬�ĳ��ѽ�
                    strcpy(p->data.status, "�ѽ�");
                    //��¼ѧ�������鼮
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
        printf("\t\t\t\t\t��Ч�Ľ���ѡ�\n");
        return;
    }

    if (!found)
    {
        printf("\t\t\t\t\tδ�ҵ�ƥ���ͼ����Ϣ��\n");
        system("pause");
    }
}

// �ж�������
int shijian(Student stu, int year, int month, int day, int m)
{
    // �������� tm �ṹ�壬���ڴ洢ʱ����Ϣ
    struct tm date1 = { 0 };  // �洢ѧ���ĳ�������
    struct tm date2 = { 0 };  // �洢Ŀ������

    // ��ʼ��ѧ���ĳ�������
    date1.tm_year = stu.year[m] - 1900;  // tm_year �Ǵ� 1900 �꿪ʼ��������������Ҫ��ȥ 1900
    date1.tm_mon = stu.month[m] - 1;     // tm_mon �Ǵ� 0 ��ʼ���·ݣ�0 ��ʾ 1 �£��������Ҫ��ȥ 1
    date1.tm_mday = stu.day[m];          // tm_mday ���·��е���

    // ��ʼ��Ŀ������
    date2.tm_year = year - 1900;      // ͬ����tm_year ��Ҫ��ȥ 1900
    date2.tm_mon = month - 1;         // ͬ����tm_mon ��Ҫ��ȥ 1
    date2.tm_mday = day;              // Ŀ�����ڵ���

    // ʹ�� mktime �� tm �ṹ��ת��Ϊ time_t ���͵�ʱ���
    // mktime ����ݸ��������ڼ������ 1970-01-01 ����������
    time_t time1 = mktime(&date1);    // ѧ���������ڵ�ʱ���
    time_t time2 = mktime(&date2);    // Ŀ�����ڵ�ʱ���

    // ʹ�� difftime ��������ʱ���֮��Ĳ�ֵ������Ϊ��λ��
    double diff = difftime(time2, time1);

    // ��������ת��Ϊ������
    // һ���� 24 Сʱ��ÿСʱ 60 ���ӣ�ÿ���� 60 ��
    int diffday = (int)(diff / (24 * 60 * 60));

    // ������������֮���������
    return diffday;
}

// ���鹦��
void returnBook()
{
    int year, month, day;
    int found = 0;
    char input[100];
    char id[100];
    int j;
    printf("\t\t\t\t\t������ѧ��:");
    scanf("%s", &id);
    for (j = 0; j < student_count; j++)
    {
        if (strcmp(students[j].ID, id) == 0)
            break;
    }
    //�ж��Ƿ���ڸ�ѧ��
    if (j == student_count)
    {
        printf("\t\t\t\t\tѧ��������\n");
        system("pause");
        return;
    }

    if (students[j].year[0] == 0) {
        printf("\t\t\t\t\t��ѧ����δ����\n");
        system("pause");
        return;
    }

    for (int k = 0; students[j].year[k] != 0; k++) {
        printf("\t\t\t\t\t ��������:%s ����:%s ����ʱ��:%d-%d-%d\n", students[j].bname[k], students[j].bID[k], students[j].year[k], students[j].month[k], students[j].day[k]);
    }

    printf("\t\t\t\t\t�������鼮���:");
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
            //�ж��鼮�Ƿ��Ǳ������δ��������޷�����
            if (strcmp(p->data.status, "δ����") == 0)
            {
                printf("\t\t\t\t\t����δ�����\n");
                system("pause");
                return;
            }

            printf("\t\t\t\t\t������黹ʱ��: ");
            scanf("%d-%d-%d", &year, &month, &day);
            //�ж�ʱ�������Ƿ���Ϲ淶
            while (year <= 0 || month > 12 || month <= 0 || day > 31 || day <= 0)
            {
                printf("\t\t\t\t\t����ȷ����ʱ��: ");
                scanf("%d-%d-%d", &year, &month, &day);
            }
            //������黹�����ڼ��
            int sj = shijian(students[j], year, month, day, m);
            //�жϻ��������Ƿ��ڽ�������֮�󣬲�������������
            while (sj < 0)
            {
                printf("\t\t\t\t\t����ȷ����ʱ��: ");
                scanf("%d-%d-%d", &year, &month, &day);
                //����������
                sj = shijian(students[j], year, month, day, m);
            }
            printf("\t\t\t\t\t��������:%d\n", sj);

            // ��������С��90��������ɷ���
            if (sj <= 90 && sj >= 0)
            {
                printf("\t\t\t\t\t�黹�ɹ�\n");
            }
            //������������90��Ӧ�ɷ���
            else
            {
                printf("\t\t\t\t\t����ɷ���\n");
                printf("\t\t\t\t\t�Ƿ�ɷ�:1.��   2.��\n");
                int check;
                scanf("%d", &check);
                if (check != 1 && check != 2)
                {
                    printf("\t\t\t\t\t��Чѡ��\n");
                }
                //ֻ�н��ɷ������ܼ���
                while (check != 1)
                {
                    printf("\t\t\t\t\t�Ƿ�ɷ�:1.��   2.��\n");
                    scanf("%d", &check);
                    if (check != 1 && check != 2)
                    {
                        printf("\t\t\t\t\t��Чѡ��\n");
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

            //���״̬�ĳ�δ����
            strcpy(p->data.status, "δ����");
            found = 1;
        }
        p = p->next;
    }
    system("pause");

    if (!found)
    {
        printf("\t\t\t\t\tδ�ҵ�ƥ���ͼ����Ϣ��\n");
        system("pause");
    }
}

// ѧ������

int studentUI() {
    welcomeUI();
    color(11); // ��ɫ
    printf("\n\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t|                                                  |\n");
    color(14); // ��ɫ
    printf("\t\t\t\t\t|               1. ����                            |\n");
    printf("\t\t\t\t\t|               2. ����                            |\n");
    printf("\t\t\t\t\t|               3. ���ѧ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               4. ɾ��ѧ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               5. չʾѧ����Ϣ                    |\n");
    printf("\t\t\t\t\t|               6. �˳�                            |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t+--------------------------------------------------+\n");
    printf("\t\t\t\t\t| ��ѡ�����: ");
    int n;
    scanf("%d", &n);
    printf("\t\t\t\t\t+--------------------------------------------------+\n\n");
    return n;
}

// ѧ����Ϣ����
void studentRoutine() {
    int choice, subChoice;
    while (1)
    {
        system("cls");
        choice = studentUI();

        switch (choice)
        {
        case 1: // ����
            printf("\t\t\t\t\t���ķ�ʽ: \n1. ���\n2. ����\n3. �˳�\n");
            scanf("%d", &subChoice);
            borrowBook(subChoice);
            saveStudents();
            saveBooks();
            break;
        case 2: // ����
            returnBook();
            saveStudents();
            saveBooks();
            break;
        case 3:// ���ѧ����Ϣ
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
        case 6: // �˳�
            saveStudents();
            return;
        default:
            printf("\t\t\t\t\t��Ч��ѡ�����������롣\n");
        }
    }
}