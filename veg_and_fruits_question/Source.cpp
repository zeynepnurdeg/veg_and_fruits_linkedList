#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList_Struct.h"

void displayList(node_t* hp) {
	if (hp != NULL) {
		printf("%3d    %-10s   %.2f\n", hp->data.id, hp->data.name, hp->data.price);
		displayList(hp->next);
	}
}

int menu() {
	printf("\n\tMENU\n");
	printf("---------------\n");
	printf("1. Add Record\n");
	printf("2. Update Record\n");
	printf("3. EXIT\n");

	int choice = 0;
	do {
		printf("\nEnter your choice: ");
		scanf(" %d", &choice);
		while (getchar() != '\n');
	} while (choice < 1 || choice > 3);

	return (choice);
}

node_t* searchInfo(node_t* p, int id) {
	while (p != NULL && p->data.id != id)
		p = p->next;
	return (p);
}

int addToEnd(node_t* hp, LType info) {
	node_t* tp = hp;
	node_t* addr = searchInfo(tp, info.id);

	if (addr != NULL)
		return 0;
	else
	{
		printf("Enter name: ");
		scanf(" %s", info.name);
		printf("Enter price: ");
		scanf("%lf", &info.price);

		addr = hp;
		while (addr->next != NULL)
			addr = addr->next;
		addAfter(addr, info);
	}
	return 1;
}

node_t* createList(FILE* inp) {
	node_t* headp = NULL;
	node_t* tp;
	LType temp;

	while (fscanf(inp, "%d %s %lf", &temp.id, temp.name, &temp.price) != EOF)
	{
		if (headp == NULL)
			headp = addBeginning(headp, temp);
		else {
			tp = headp;
			while (tp->next != NULL)
				tp = tp->next;
			addAfter(tp, temp);
		}
	}

	return (headp);
}

void updateList(node_t* headp, int id) {
	LType updateItem;
	int n;
	node_t* addr = headp;
	addr = searchInfo(addr, id);


	if (addr != NULL) {
		printf("%3d    %-10s   %.2f\n", addr->data.id, addr->data.name, addr->data.price);

		do {
			printf("\nUpdate (1. ID, 2. Name, and 3. Price): ");
			scanf("%d", &n);
		} while (n < 1 || n > 3);

		switch (n)
		{
		case 1:
			printf("Enter the new id: ");
			scanf("%d", &updateItem.id);
			addr->data.id = updateItem.id;
			break;
		case 2:
			printf("Enter the new name: ");
			scanf(" %s", updateItem.name);
			strcpy(addr->data.name, updateItem.name);
			break;
		case 3:
			printf("Enter the new price: ");
			scanf("%lf", &updateItem.price);
			addr->data.price = updateItem.price;
			break;
		}
	}
	else
		printf("Item DOESN'T exist!!!\n");
}

void writeList(node_t* headp) {
	char fileName[25] = "vegAndFruits.bin";
	LType temp;

	FILE* out;
	out = fopen(fileName, "wb");

	while (headp != NULL) {
		temp = headp->data;
		fwrite(&temp, sizeof(LType), 1, out);
		headp = headp->next;
	}

	printf("Writing linked list to binary file called <%s>\n", fileName);
	printf("Goodbye\n");
}

int main(void)
{
	char openFile[25];
	FILE* inp;

	do {
		printf("Enter a file name: ");
		scanf(" %s", openFile);
		inp = fopen(openFile, "r");
	} while (inp == NULL);

	int choice;

	node_t* headp;
	headp = createList(inp);

	LType temp = headp->data;

	do {
		printf("\nID     Name         Price\n");
		printf("------------------------------\n");
		displayList(headp);

		choice = menu();
		int check;
		switch (choice)
		{
		case 1:
			do {
				printf("\nEnter vegetable Id : ");
				scanf("%d", &temp.id);
				check = addToEnd(headp, temp);
				if (check == 0)
					printf("This item exists\n");
			} while (check == 0);
			break;
		case 2:
			printf("Enter vegetable id: ");
			scanf(" %d", &temp.id);
			updateList(headp, temp.id);
			break;
		case 3:
			writeList(headp);
			break;
		}
		printf("\n");
	} while (choice != 3);
	return 0;
}
