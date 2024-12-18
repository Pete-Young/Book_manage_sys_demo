#define _CRT_SECURE_NO_WARNINGS
#include "borrow.h"
int borrow_count = 0;

//加载借书信息
void loadBorrow()
{
    FILE* in = fopen("borrow.txt", "r");
    if (in == NULL) {
        return;
    }
    while (fscanf(in, "%s%s%s%d%d%d", borrow[borrow_count].ID, borrow[borrow_count].bname,
        borrow[borrow_count].bID, &borrow[borrow_count].year, &borrow[borrow_count].month, &borrow[borrow_count].day) != EOF) {
        borrow_count++;
    }


    fclose(in);
}

// 保存借书信息
void saveBorrow()
{
    FILE* out = fopen("borrow.txt", "w");

    for (int i = 0; i < borrow_count; i++) {
        fprintf(out, "%s\t%s\t%s\t%d\t%d\t%d\n", borrow[i].ID, borrow[i].bname,
            borrow[i].bID, borrow[i].year, borrow[i].month, borrow[i].day);
    }
    fclose(out);
}