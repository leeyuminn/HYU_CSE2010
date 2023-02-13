#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 100

typedef struct BankCustomer {
	int id;
	int tArrival;
	int tService;
} Customer;

typedef Customer Element;

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val) {
	if (is_full())
		error("	 ť ��ȭ ����");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

Element dequeue()
{
	if (is_empty())
		error("	 ť ���� ����");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

Element peek()
{
	if (is_empty())
		error("	 ť ���� ����");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}

int nSimulation; //�ùķ��̼� �ð�
double probArrival; // �����ð��� �����ϴ� ��հ���
int tMaxService; // �� ���� ���� �ִ� ���񽺽ð� 
int totalWaitTime; // ��ü ���ð�
int nCustomers; // ��ü ���� ��
int nServedCustomers; //���񽺸� ���� ��ü ����

double rand0to1() { return rand() / (double)RAND_MAX; }

void insert_customers(int arrivalTime)
{
	Customer a;
	a.id = ++nCustomers;
	a.tArrival = arrivalTime;
	a.tService = (int)(tMaxService * rand0to1()) + 1;
	printf("  �� %d �湮 (���� �ð�:%d��)\n", a.id, a.tService);
	enqueue(a);
}

void read_sim_params()
{
	printf("�ùķ��̼� �� �ִ� �ð� (��:10) = ");
	scanf("%d", &nSimulation);
	printf("�����ð��� �����ϴ� �� �� (��:0.5) = ");
	scanf("%11f", &probArrival);
	printf(" �� ���� ���� �ִ� ���� �ð� (��:5) = ");
	scanf("%d", &tMaxService);
	printf("=============================================================================\n");

}

void run_simulation() {
	Customer a;
	int clock = 0;
	int serviceTime = -1;

	init_queue();
	nCustomers = totalWaitTime = nServedCustomers = 0;

	while (clock < nSimulation) {
		clock++;
		printf("����ð�=%d\n", clock);

		if (rand0to1() > probArrival)
			insert_customers(clock);

		if (serviceTime > 0) serviceTime--;
		else {
			if (is_empty()) continue;
			a = dequeue();
			nServedCustomers++;
			totalWaitTime += clock - a.tArrival;
			printf("	�� %d  ���� ���� (���ð�:%d��)\n", a.id, clock - a.tArrival);
			serviceTime = a.tService - 1;
		}
	}
}

void print_result() {
	printf("=============================================================================\n");
	printf("   ���� ���� �� ��	= %d\n", nServedCustomers);
	printf("   ��ü ��� �ð�	= %d��\n", totalWaitTime);
	printf("   ���񽺰� ��մ�ýð�	= %-5.2f\n", (double)totalWaitTime / nServedCustomers);
	printf("   ���� ��� �� ��	= %d\n", nCustomers - nServedCustomers);
}

void main() {
	srand((unsigned int)time(NULL));
	read_sim_params();
	run_simulation();
	print_result();
}