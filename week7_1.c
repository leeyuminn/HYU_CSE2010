#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE	100

typedef int Element;
Element data[MAX_LIST_SIZE];
int length = 0;

void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void init_list() { length = 0; }
void clear_list() { length = 0; }
int is_empty() { return length == 0; }
int is_full() { return length == MAX_LIST_SIZE; }
int get_entry(int id) { return data[id]; }
void replace(int id, Element e) { data[id] = e; }
int size() { return length; }

void insert(int pos, int e)
{
	int i;
	if (is_full() == 0 && pos >= 0 && pos <= length) {
		for (i = length; i > pos; i--)
			data[i] = data[i - 1];
		data[pos] = e;
		length++;
	}
	else error("포화상태 오류 또는 삽입 위치 오류");
}

void delete(int pos)
{
	int i;
	if (is_empty() == 0 && 0 <= pos && pos < length) {
		for (i = pos + 1; i < length; i++)
			data[i - 1] = data[i];
		length--;
	}
	else error("공백상태 오류 또는 삭제 위치 오류");
}

int find(Element item)
{
	int i;
	for (i = 0; i < length; i++)
		if (data[i] == item) return i;
	return -1;
}

void print_list(char* msg)
{
	int i;
	printf("%s[%2d]: ", msg, length);
	for (i = 0; i < length; i++)
		printf("%2d ", data[i]);
	printf("\n");
}

void main()
{
	init_list();

	insert(0, 10);
	insert(0, 20);
	insert(1, 30);
	insert(size(), 40); //length자리에 넣기
	insert(2, 50);
	print_list("배열로 구현한 List(삽입x5)");

	replace(2, 90);
	print_list("배열로 구현한 List(교체x1)");

	delete(2);
	delete(size() - 1); //마지막 요소 삭제
	delete(0);
	print_list("배열로 구현한 List(삭제x3)");

	clear_list();
	print_list("배열로 구현한 List(정리후)");
}