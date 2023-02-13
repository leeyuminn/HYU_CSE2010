#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct student_t {
	int id;
	char name[32];
	char dept[32];
} Student;

typedef Student Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE - 1; }
int size() { return top + 1; }

Student get_student(int id, char* name, char* dept)
{
	Student s;
	s.id = id;
	strcpy(s.name, name);
	strcpy(s.dept, dept);
	return s;
}

void push(Element e) {
	if (is_full())
		error("스택 포화 에러");
	data[++top] = e;
}

Element pop() {
	if (is_empty())
		error("스택 공백 에러");
	return data[top--];
}

Element peek() {
	if(is_empty())
		error("스택 공백 에러");
	return data[top];
}

void print_stack(char msg[]) {
	int i;
	printf("%s[%2d]= ", msg, size());

	for (i = 0; i < size(); i++)
		printf("\n\t%-15d %-10s %-20s", data[i].id, data[i].name, data[i].dept);
	printf("\n");
}

void main() {
	int i;

	init_stack();
	push(get_student(2015130007, "홍길동", "컴퓨터공학과"));
	push(get_student(2015130007, "이순신", "기계공학과"));
	push(get_student(2015130007, "김연아", "체육과"));
	push(get_student(2015130007, "황희", "법학과"));
	print_stack("친구 4명 삽입 후");
	pop();
	print_stack("친구 1명 삭제 후");


	/*for (i = 1; i < 10; i++)
		push(i);
	print_stack("스택 push 9회");

	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());

	print_stack("스택 pop 3회");*/
}