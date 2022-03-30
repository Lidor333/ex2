#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARYEAR 0
#define INTYEAR 1

typedef struct worker {
	unsigned long ID;
	char* name;
	unsigned long salary;
	union Year {
		int yearI;
		char yearC[6];
	}Year;
}worker;

typedef struct WorkerList {
	worker* data;
	struct WorkerList* next;
} WorkerList;

//Functions
worker* CreatWorker(int sign);
//worker* _createWorker(unsigned long id, char* name, unsigned long salary, char yearHeb[6], unsigned long yearIntl, char sign);
void PrintWorker(worker* w, int sign);
WorkerList* addWorker(WorkerList* head, worker* w);
int index(WorkerList* head, long unsigned id);
int R_index(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);
void PrintAllWorkers(WorkerList* head);

void main() {
	
	worker* w1 = CreatWorker(1);
	worker* w2 = CreatWorker(1);
	/*worker* w3 = CreatWorker(0);
	worker* w4 = CreatWorker(1);*/
	
	printf("the worker list is:\n");
	WorkerList* head = addWorker(NULL, w1);
	/*PrintWorker(w1, INTYEAR);
	PrintWorker(w2, INTYEAR);
	PrintWorker(w3, INTYEAR);
	PrintWorker(w4, INTYEAR);*/
	head = addWorker(head, w2);
	/*head = addWorker(head, w3);
	head = addWorker(head, w4);*/
	PrintAllWorkers(head);
	printf("****************\n");

	printf("the list sorted in ascending order:\n");
	PrintAllWorkers(head);
	printf("****************\n");

	printf("The list after the pay raise:\n");
	update_worker(head, 20);
	PrintAllWorkers(head);
	printf("****************\n");
	
	printf("List in reverse order:\n");
	head = reverse(head);
	PrintAllWorkers(head);
	printf("****************");
	
	printf("Updated List:\n");
	head = deleteWorstWorker(head);
	PrintAllWorkers(head);
	printf("****************");
	

	////check functions 1&2
	//worker* worker1 = CreatWorker(INTYEAR);
	//PrintWorker(worker1, INTYEAR);

	////function 3
	//head = addWorker(NULL, worker1);
	//worker* worker2 = CreatWorker(INTYEAR);
	//head = addWorker(head, worker2);
	freeWorkers(head);

}

worker* CreatWorker(int sign)
{
	worker* w = (worker*)malloc(sizeof(worker));
	if (w) {
		printf("\nenter your id:\n");
		scanf_s("%d", &w->ID);
		fseek(stdin, 0, SEEK_END);
		char newname[50];

		printf("enter name:\n");
		fgets(newname, 50, stdin);
		int len = strlen(newname);
		w->name = (char*)malloc(sizeof(char) * len);
		if ((w->name) != NULL) {
			strcpy(w->name, newname);
		}
		printf("enter salary:\n");
		scanf_s("%d", &w->salary);
		fseek(stdin, 0, SEEK_END);
		printf("enter a year:\n");
		switch (sign)
		{
		case CHARYEAR:
			gets(w->Year.yearC);
			break;
		case INTYEAR:
			scanf_s("%d", &(w->Year.yearI));
			break;
		default:
			break;
		}
	}
	return w;
}

worker* _createWorker(unsigned long id, char* name, unsigned long salary, char yearHeb[6], unsigned long yearIntl, char sign)
{
	worker* w = (worker*)malloc(sizeof(worker));
	if (w == NULL) exit(0);
	w->ID = id;
	w->salary = salary;
	int len = strlen(name);
	w->name = (char*)malloc(sizeof(char) * len);
	if ((w->name) != NULL) {
		strcpy(w->name, name);
	}
	switch (sign)
	{
	case CHARYEAR:
		//w->Year.yearC = yearHeb;
		break;
	case INTYEAR:
		w->Year.yearI = yearIntl;
		break;
	default:
		break;
	}

	return w;
}


void PrintWorker(worker* w, int sign) {

	printf("The ID: %d\nThe name: %s\nThe salary: %d\n", w->ID, w->name, w->salary);

	if (sign == 0) {
		printf("The year is: %s\n", w->Year.yearC);
	}
	else {
		printf("The year is: %d\n", w->Year.yearI);
	}
	printf("\n");
}

void PrintAllWorkers(WorkerList* head)
{
	while (head)
	{
		PrintWorker(head->data, 1);
		head = head->next;
	}
}

WorkerList* addWorker(WorkerList* head, worker* w) {
	WorkerList* curr;
	WorkerList* prev;
	WorkerList* toAdd = (WorkerList*)malloc(sizeof(WorkerList));
	if (toAdd == NULL) exit(0);
	toAdd->data = w;
	toAdd->next = NULL;

	//if is empty list
	if (head == NULL) {
		head = toAdd;
	}

	//we check the head before:
	else if (toAdd->data->salary < head->data->salary) {
		toAdd->next = head;
		head = toAdd;
	}

	//if is not smaller than the head so in supose to be in the middle of the list
	else {
		curr = head->next;
		prev = head;
		while (curr != NULL) {
			if (toAdd->data->salary < curr->data->salary) {
				prev->next = toAdd;
				toAdd->next = curr;
				return head;
			}
			prev = curr;
			curr = curr->next;
		}
		//if to add is the bigger in the list we push him to the enf of the list
		prev->next = toAdd;
	}
	return head;
}

int index(WorkerList* head, long unsigned id) { //found index of worker
	int i = 1;
	while (head != NULL) {
		if (head->data->ID == id) {
			return i;
		}
		else {
			i++;
			head = head->next;
		}
	}
	return -1;
}

int R_index(WorkerList* head, long unsigned id) { //found worker by id by rexorciv
	if (head->data->ID == id) return 1;
	if (head->next == NULL) return -1;
	int res = R_index(head->next, id);
	return res == -1 ? -1 : res + 1;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* p = head, *prev = NULL;
	if (head->next == NULL)
		return NULL;
	for (; p->next != NULL; p = p->next)
		prev = p;
	free(p);
	prev->next = NULL;
	return head;
}

void update_worker(WorkerList* head, float percent) {
	for (; head != NULL; head = head->next) {
		head->data->salary *= (100.0 + percent)/100.0;
	}
}

WorkerList* reverse(WorkerList* head) { //with mistake
	WorkerList* curr;
	WorkerList* prev;
	WorkerList* next;
	prev = NULL;
	curr = head;
	next = NULL;

	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return head;
}

void freeWorkers(WorkerList* head) {
	for (; head->next != NULL; head = head->next) {
		free(head->data);
		free(head);
	}
}

