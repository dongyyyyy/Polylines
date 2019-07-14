#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct pointNode{
	int x;
	int y;
	struct pointNode* prev;
	struct pointNode* next;
}pointNode;

typedef struct pointList{
	int size;
	pointNode* front;
	pointNode* back;
}pointList;

void initList(pointList* l); // ����Ʈ �ʱ�ȭ
void ListAdd(pointList* l, int x, int y);// ����Ʈ �߰�
int ListRemove(pointList* l,int x , int y); // ����Ʈ ����
void ListPrint(pointList* l);
void ListToArray1(pointList* l, Point* ary);
void ListToArray2(pointList* l, Point **ary);