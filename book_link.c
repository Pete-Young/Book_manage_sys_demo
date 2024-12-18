#define _CRT_SECURE_NO_WARNINGS
#include "book_link.h"

struct BookNode* head = NULL;
struct BookNode* tail = NULL;



struct BookNode* createHead() {
	struct BookNode* headNode = (struct BookNode*)malloc(sizeof(struct BookNode));
	if (headNode == NULL) {
		printf("�ڴ����ʧ�ܣ��޷�����ͷ�ڵ㣡\n");
		return NULL;
	}
	headNode->next = NULL;
	tail = headNode;
	return headNode;
}

struct BookNode* createNode(const Book data) {
	struct BookNode* newNode = (struct BookNode*)malloc(sizeof(struct BookNode));
	if (newNode == NULL) {
		printf("�ڴ����ʧ�ܣ��޷������½ڵ㣡\n");
		return NULL;
	}
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void InsertTail(const Book data) {
	struct BookNode* newNode = createNode(data);
	tail->next = newNode;
	tail = newNode;
}