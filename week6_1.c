#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
} Node;
Node* top = NULL;

void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

int is_empty() { return top == NULL; }
void init_stack() { top = NULL; }

Element peek()
{
	if (is_empty())
		error("	 ���� ���� ����");
	return top->data;
}

void destroy_stack()
{
	while (is_empty() == 0)
		pop();
}

int size()
{
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link) count++;
	return count;
}

void push(Element e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;

	p->link = top;
	top = p;
}

Element pop()
{
	Node* p;
	Element e;
	if (is_empty())
		error("���� ���� ����");
	p = top;
	top = p->link;
	e = p->data;
	free(p);
	return e;
}

void print_stack(char* msg)
{
	Node* p;
	printf("%s[%2d]= ", msg, size());
	for (p = top; p != NULL; p = p->link)
		printf("%2d ", p->data);
	printf("\n");
}

void main()
{
	int i;

	init_stack();
	for (i = 1; i < 10; i++)
		push(i);
	print_stack("����Ƚ��� push 9ȸ");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	print_stack("����Ƚ��� pop 3ȸ");
	destroy_stack();
	print_stack("����Ƚ��� destroy ");
}