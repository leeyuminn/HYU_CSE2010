#include <stdio.h>
#include <stdlib.h>

void insert(int array[], int size, int loc, int value) { //loc의 자리에 value를
	int i;
	for (i = size - 2; i >= loc; i--) //size-2는 현재 들어있는 원소의 개수
		array[i + 1] = array[i];
	array[loc] = value;
}

void delete(int array[], int size, int loc) {
	int i;
	for (i = loc; i < (size - 1); i++)
		array[i] = array[i + 1];
	array[size - 1] = 0;
}

void print_value(int array[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
}

int main() {
	int two[20];

	int i, j;
	two[0] = 0;
	for (i = 1; i < 20; i++) {
		int sum = 1;
		for (j = 0; j < i; j++) {
			sum *= 2;
		}
		two[i] = sum;
	}
	print_value(two, 20);
	printf("\n");
	printf("삽입후 \n");
	insert(two, 20, 3, 100);
	print_value(two, 20);
	printf("\n");
	printf("삭제후 \n");
	delete(two, 20, 3);
	print_value(two, 20);
	printf("\n");
	return 0;

	/*(1)two[0] = 1;
	for (int i = 1; i < 20; i++) {
		two[i] = two[i - 1] * 2;
	}
	for (int j = 0; j < 20; j++) {
		printf("%d ", two[j]);
	}*/
}