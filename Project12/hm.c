#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARYEAR '1'
#define INTYEAR '0'

typedef struct worker {
	unsigned long ID;
	char* name;
	unsigned long salary;
	union {
		int yearI;
		char yearC[6];
	}Year;
}worker;

typedef struct WorkerList {
	worker* data;
	struct WorkerList* next;
} WorkerList;

worker* CreatWorker(char sign);
worker* _createWorker(unsigned long id, char* name, unsigned long salary, char yearHeb[6], unsigned long yearIntl, char sign);
void PrintWorker(worker* w, char sign);
WorkerList* addWorker(WorkerList* head, worker* w);
int index(WorkerList* head, long unsigned id);
int R_index(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
//WorkerList* reverse(WorkerList* head);
//void freeWorkers(WorkerList* head);

void main() {

	worker* w1 = _createWorker(4, "alex4", 20, "", 2020, INTYEAR);
	worker* w2 = _createWorker(1, "bob1", 5, "", 2020, INTYEAR);
	worker* w3 = _createWorker(3, "cid3", 15, "", 2020, INTYEAR);
	worker* w4 = _createWorker(2, "dana2", 10, "", 2020, INTYEAR);
	PrintWorker(w1, INTYEAR);
	PrintWorker(w2, INTYEAR);
	PrintWorker(w3, INTYEAR);
	PrintWorker(w4, INTYEAR);
	WorkerList* head = addWorker(NULL, w1);
	head = addWorker(head, w2);
	head = addWorker(head, w3);
	head = addWorker(head, w4);

	printf("\n%d: %s   $$$= %d\n", index(head, w1->ID), w1->name, w1->salary);
	printf("%d: %s   $$$= %d\n", index(head, w2->ID), w2->name, w2->salary);
	printf("%d: %s   $$$= %d\n", index(head, w3->ID), w3->name, w3->salary);
	printf("%d: %s   $$$= %d\n", index(head, w4->ID), w4->name, w4->salary);
	
	printf("\n%d: %s   $$$= %d\n", R_index(head, w1->ID), w1->name, w1->salary);
	printf("%d: %s   $$$= %d\n",   R_index(head, w2->ID), w2->name, w2->salary);
	printf("%d: %s   $$$= %d\n",   R_index(head, w3->ID), w3->name, w3->salary);
	printf("%d: %s   $$$= %d\n",   R_index(head, w4->ID), w4->name, w4->salary);


	update_worker(head, 20);
	printf("\n%s   $$$= %d\n", w1->name, w1->salary);
	printf("%s   $$$= %d\n",  w2->name, w2->salary);
	printf("%s   $$$= %d\n",  w3->name, w3->salary);
	printf("%s   $$$= %d\n",  w4->name, w4->salary);

	
	head = deleteWorstWorker(head);
	printf("\n%d: %s   $$$= %d\n", index(head, w1->ID), w1->name, w1->salary);
	printf("%d: %s   $$$= %d\n", index(head, w2->ID), w2->name, w2->salary);
	printf("%d: %s   $$$= %d\n", index(head, w3->ID), w3->name, w3->salary);
	printf("%d: %s   $$$= %d\n", index(head, w4->ID), w4->name, w4->salary);


	//head = reverse(head);
	//freeWorkers(head);

	//check functions 1&2
	worker* worker1 = CreatWorker(INTYEAR);
	PrintWorker(worker1, INTYEAR);

	//function 3
	head = addWorker(NULL, worker1);
	worker* worker2 = CreatWorker(INTYEAR);
	head = addWorker(head, worker2);

}

worker* CreatWorker(char sign)
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


void PrintWorker(worker* w, char sign) {

	printf("\nThe ID: %d\nThe name: %s\nThe salary: %d", w->ID, w->name, w->salary);

	if (sign == '0') {
		printf("\n The year is: %d", w->Year.yearI);
	}
	else {
		printf("\n The year is: %c", w->Year.yearC);
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

//WorkerList* reverse(WorkerList* head) { //with mistake
//	WorkerList* curr;
//	WorkerList* prev;
//	WorkerList* next;
//	prev = NULL;
//	curr = head;
//	next = NULL;
//
//	while (curr != NULL) {
//		next = curr->next;
//		curr->next = prev;
//		prev = curr;
//		curr = next;
//	}
//	head = prev;
//	return head;
//}

//void freeWorkers(WorkerList* head) {
//	for (; head->next != NULL; head = head->next) {
//		free(head->data);
//		free(head);
//	}
//}