#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"       
#define MAX_OPTION_IN_MENU 8
#define MAX_OPTION_IN_SUBMENU 4


int main()
{
	FILE* fp;
	SList* phead = NULL;
	SList bookshelf = { 0 };
	int option, position, listsize;
	char strIn[10] = { 0 };

	if ((fp = fopen("Books.txt", "r+")) == NULL)
	{
		printf("File was not opened.");
		return 1;
	}

	ScanNotes(fp, &phead, bookshelf);         
	OrderList(&phead);

	if (isEmpty(phead))  return 3;
	listsize = getSize(phead);
	//
	// Μενώ
	//
	while (1)
	{
		printf("\n1) Show books.\n2) Delete a book.\n3) Delete books with the title 'D...'.\n4) Sort by price.\n5) Add a new book.\n6) Edit a note.\n7) Find a book.\n8) Exit.\n");

		do
		{
			printf("\nChoose youre option: ");
			fgets(strIn, 10, stdin);
			if (strIn[0] == '\n')
			{
				fgets(strIn, 10, stdin);
			}
			else
			{
				if (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_MENU || !atoi(strIn))
					printf("\nThere is no such option available.\n");
			}
		} while (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_MENU || !atoi(strIn));
		option = atoi(strIn);
		memset(strIn, 0, strlen(strIn));
		switch (option)
		{
		case 1:
			clearScreen();
			for (SList* i = phead; i != NULL; i = i->mNext)
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", i->position, i->mBooks.author, i->mBooks.title, i->mBooks.year, i->mBooks.pages, i->mBooks.price);
			break;
			
		case 2:
			do
			{
				printf("\nWhich one do you want to delete: ");
				fgets(strIn, 10, stdin);
				listsize = getSize(phead);
				if (atoi(strIn) <= 0 || atoi(strIn) > listsize || !atoi(strIn))
					printf("\nThere is no such position available.\n");
			} while (atoi(strIn) <= 0 || atoi(strIn) > listsize || !atoi(strIn));
			position = atoi(strIn);
			memset(strIn, 0, strlen(strIn));
			del_elem(&phead, listsize, position);
			OrderList(&phead);
			WriteNotes(fp, &phead);
			break;

		case 3:
			clearScreen();
			deleteD(&phead);
			OrderList(&phead);
			for (SList* i = phead; i != NULL; i = i->mNext)
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", i->position, i->mBooks.author, i->mBooks.title, i->mBooks.year, i->mBooks.pages, i->mBooks.price);
			break;

		case 4:
			clearScreen();
			sel_sort(bookshelf, phead);
			OrderList(&phead);
			for (SList* i = phead; i != NULL; i = i->mNext)
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", i->position, i->mBooks.author, i->mBooks.title, i->mBooks.year, i->mBooks.pages, i->mBooks.price);
			break;

		case 5:
			consoleInput(&phead);         ///////////////////////////////
			OrderList(&phead);
			break;

		case 6:
			edit_note(&phead, listsize);  /////////////////////////////////
			break;

		case 7:
			clearScreen();
			listsize = getSize(phead);
			printf("1) By title.\n2) By author.\n3) By year.\n4) By price.\n");
			do
			{
				printf("Your choice: ");
				fgets(strIn, 10, stdin);
				if (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_SUBMENU || !atoi(strIn))
					printf("\nThere is no such option available.\n");
			} while (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_SUBMENU || !atoi(strIn));
			option = atoi(strIn);
			memset(strIn, 0, strlen(strIn));
			findNote(phead, option);
			break;

		case 8:
			WriteNotes(fp, &phead);
			fclose(fp);
			dealloc(&phead);
			return 0;
		}
	}
}