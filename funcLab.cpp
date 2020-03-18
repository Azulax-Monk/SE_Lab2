#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#define MAX_OPTION_IN_SUBMENU2 5

void consoleInput(SList** ppH)
{
	SBooks newBook = { 0 };
	SList bookshelf = { 0 };
	int counter = 0, pagesNum;
	char c = 0;

	printf("\nEnter an author of a book, you want to add: ");
	getchar();
	while ((c = getchar()) != '\n')
	{
		newBook.author[counter] = c;
		counter++;
	}
	newBook.author[counter] = '\0';
	counter = 0;

	printf("\nEnter a title of a book, you want to add: ");
	while ((c = getchar()) != '\n')
	{
		newBook.title[counter] = c;
		counter++;
	}
	newBook.title[counter] = '\0';
	counter = 0;

	printf("\nEnter a date when a book was written: ");
	while ((c = getchar()) != '\n')
	{
		if (isdigit(c))
		{
			newBook.year[counter] = c;
			counter++;
		}
		else
			continue;
	}
	newBook.year[counter] = ' ';
	strcat(newBook.year, "year");  //’ќ“№ Ѕ» ѕќћ»Ћ ј Ќ≈ ¬»— ќ„»Ћј
	counter = 0;

	printf("\nEnter number of pages of a book, you want to add: ");

	while ((c = getchar()) != '\n')
	{
		newBook.pages[counter] = c;
		counter++;
	}
	newBook.pages[counter] = ' ';
	strcat(newBook.pages, "pages");
	counter = 0;

	printf("\nEnter price of a book, you want to add: ");
	scanf("%d", &newBook.price);
	add_sortElem(bookshelf, ppH, newBook);
}

void add_sortElem(SList bookshelf, SList** ppH, struct SBooks books)
{
	SList* prevEl = *ppH;
	SList* curEl = *ppH;
	SList* pTmp = (SList*)malloc(sizeof(SList));
	pTmp->mBooks = books;

	if (!*ppH)                 //якщо в списку немаЇ елемент≥в, то першим призначаЇмо pTmp
	{
		*ppH = pTmp;
		pTmp->mNext = NULL;
	}
	else                      //¬ ≥ншому випадку додаЇмо його в список ≥ сортуЇмо
	{
		for (curEl; curEl != NULL; curEl = curEl->mNext)
		{
			if (strcmp(pTmp->mBooks.title, curEl->mBooks.title) < 0)
			{
				if (curEl != *ppH)
				{
					prevEl->mNext = pTmp;
					pTmp->mNext = curEl;
				}
				else
				{
					pTmp->mNext = curEl;
					*ppH = pTmp;
				}
				break;
			}
			if (curEl != *ppH)
				prevEl = prevEl->mNext;

			if (!curEl->mNext)             //якщо елемент не Ї меншим за вже на€вн≥, то додаЇмо його в к≥нець списку
			{
				curEl->mNext = pTmp;
				pTmp->mNext = NULL;
				break;
			}
		}
	}
}

void dealloc(SList** ppHead)
{
	SList* cur = *ppHead;
	if (cur == NULL) return;
	cur = cur->mNext;
	dealloc(&cur);
	free(cur);
	*ppHead = NULL;
}

int isEmpty(SList* pFirst)
{
	return !pFirst;
}

void swap(struct SList, SList* pos1, SList* pos2)
{
	SBooks tmp;
	tmp = pos1->mBooks;
	pos1->mBooks = pos2->mBooks;
	pos2->mBooks = tmp;
}

void sel_sort(SList bookshelf, SList* phead)
{
	SList* pmax = phead;
	SList* pk = phead;
	SList* pj = phead;

	for (pk; pk != NULL; pk = pk->mNext)
	{
		for (pj; pj != NULL; pj = pj->mNext)
		{
			if (pj->mBooks.price > pmax->mBooks.price)
			{
				pmax = pj;
			}
		}
		swap(bookshelf, pk, pmax);
		pmax = pk->mNext;
		pj = pk->mNext;
	}
}

void deleteD(SList** ppH)
{
	SList* pCur1 = *ppH;
	while (1)
	{
		SList* pCur2 = pCur1;
		pCur1 = pCur1->mNext;

		if (!pCur1)
			break;
		if (pCur1->mBooks.title[0] == 'D') {
			if (!pCur1->mNext)
			{
				pCur2->mNext = NULL;
				break;
			}
			pCur2->mNext = pCur1->mNext;
			free(pCur1);
			pCur1 = pCur2;
		}
	}
	pCur1 = *ppH;
	if (pCur1->mBooks.title[0] == 'D')
		if (pCur1->mNext)
			*ppH = pCur1->mNext;
		else
			*ppH = NULL;
}

int getSize(SList* pFirst)
{
	SList* pTmp = pFirst;
	int counter = 0;
	while (pTmp)
	{
		++counter;
		pTmp = pTmp->mNext;
	}
	return counter;
}

void del_elem(SList** pHead, int listsize, int position)
{
	SList* pTmp = *pHead;
	SList* pPrevTmp = *pHead;
	int counter = 1;

	if (position == 1)            //видал€Ї 1 елемент
	{
		if (!((*pHead)->mNext))
		{
			free(*pHead);
			*pHead = NULL;
		}
		else
		{
			pTmp = pTmp->mNext;
			free(*pHead);
			*pHead = pTmp;
		}

	}
	else if (position == listsize && listsize > 1)       //видал€Ї останн≥й елемент
	{
		while (pTmp->mNext->mNext)
		{
			pPrevTmp = pPrevTmp->mNext;
		}
		pTmp = pPrevTmp->mNext;
		pPrevTmp->mNext = NULL;
		free(pTmp);
	}
	else                                    //видал€Ї елемент всередин≥
	{
		while (counter < (position - 1))
		{
			pPrevTmp = pPrevTmp->mNext;
			counter++;
		}
		pTmp = pPrevTmp->mNext;
		pPrevTmp->mNext = pTmp->mNext;
		free(pTmp);
	}
}

void WriteNotes(FILE* pF, SList** pHead)                                         //шось не записуЇ норм, проблема з ед≥тами
{
	SList* pTmp = (*pHead);

	fseek(pF, 0, SEEK_SET);
	fprintf(pF, "\n");
	while (pTmp->mNext)
	{
		fprintf(pF, "%s,%s,%s,%s,%d\n", pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
		pTmp = pTmp->mNext;
	}
	fprintf(pF, "%s,%s,%s,%s,%d.", pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
}

int OrderList(SList** pHead)
{
	if (!(*pHead))
		return 1;
	SList* pTmp = (*pHead);
	int counter = 1;

	while (pTmp->mNext)
	{
		pTmp->position = counter;
		counter++;
		pTmp = pTmp->mNext;
	}
	pTmp->position = counter;
	return 0;
}

void ScanNotes(FILE* fp, SList** pHead, SList bookshelf)
{
	int i = 0;
	char sym_c;
	SBooks SBElem;

	do
	{
		getc(fp);
		while ((sym_c = getc(fp)) != ',')
		{
			SBElem.author[i] = sym_c;
			i++;
		}
		SBElem.author[i] = '\0';
		i = 0;

		while ((sym_c = getc(fp)) != ',')
		{
			SBElem.title[i] = sym_c;
			i++;
		}
		SBElem.title[i] = sym_c = '\0';
		i = 0;

		while ((sym_c = getc(fp)) != ',')
		{
			SBElem.year[i] = sym_c;
			i++;
		}
		SBElem.year[i] = '\0';
		i = 0;

		while ((sym_c = getc(fp)) != ',')
		{
			SBElem.pages[i] = sym_c;
			i++;
		}
		SBElem.pages[i] = '\0';
		i = 0;

		fscanf(fp, "%d", &SBElem.price);
		add_sortElem(bookshelf, pHead, SBElem);
		sym_c = getc(fp);
		fseek(fp, -1, 1);
	} while (sym_c != '.');
}

void edit_note(SList** pHead, int listsize)
{
	SList* pTmp = (*pHead);
	int notenum = 0, option = 0, i = 0;
	char newTitle[50];
	char newAuthor[20];
	char newYear[10];
	char newPages[10];
	char strIn[10];

	do
	{
		printf("\nWhich task(from 1 to %d) do you want to edit: ", listsize);
		fgets(strIn, 10, stdin);
		if (atoi(strIn) <= 0 || atoi(strIn) > listsize || !atoi(strIn))
			printf("\nThere is no such position available.\n");
	} while (atoi(strIn) <= 0 || atoi(strIn) > listsize || !atoi(strIn));
	notenum = atoi(strIn);
	memset(strIn, 0, strlen(strIn));

	for (int i = 1; i < notenum; i++)
		pTmp = pTmp->mNext;

	printf("\n1)Name of the book;\n2)Author;\n3)Year;\n4)Pages number;\n5)Price.\n");
	do
	{
		printf("\nWhich part do you want ot change: ");
		fgets(strIn, 10, stdin);
		if (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_SUBMENU2 || !atoi(strIn))
			printf("nThere is no such option available.\n");
	} while (atoi(strIn) <= 0 || atoi(strIn) > MAX_OPTION_IN_SUBMENU2 || !atoi(strIn));
	option = atoi(strIn);
	memset(strIn, 0, strlen(strIn));

	switch (option)
	{
	case 1:
		printf("\nEnter your edited title: ");
		getchar();
		fgets(newTitle, 50, stdin);
		for (i; i < (strlen(newTitle) - 1); i++)
			pTmp->mBooks.title[i] = newTitle[i];
		pTmp->mBooks.title[i] = '\0';
		i = 0;
		break;

	case 2:
		printf("\nEnter your edited author's name: ");
		getchar();
		fgets(newAuthor, 20, stdin);
		for (i; i < (strlen(newAuthor) - 1); i++)
			pTmp->mBooks.author[i] = newAuthor[i];
		pTmp->mBooks.author[i] = '\0';
		i = 0;
		break;

	case 3:
		printf("\nEnter your edited year: ");
		getchar();
		fgets(newYear, 10, stdin);
		for (i; i < (strlen(newYear) - 1); i++)
			pTmp->mBooks.year[i] = newYear[i];									       // ’ќ“№ Ѕ» Ќ”Ћ№ —»ћ¬ќЋ Ѕ”¬
		i = 0;
		break;

	case 4:
		printf("\nEnter your edited pages number: ");
		memset(pTmp->mBooks.pages, 0, sizeof(pTmp->mBooks.pages));
		getchar();
		fgets(newPages, 10, stdin);
		for (i; i < (strlen(newPages) - 1); i++)
			pTmp->mBooks.pages[i] = newPages[i];
		pTmp->mBooks.pages[i] = ' ';
		strcat(pTmp->mBooks.pages, "pages");
		i = 0;
		break;

	case 5:
		printf("\nEnter your edited price: ");
		scanf("%d", &pTmp->mBooks.price);
	}
}

int findNote(SList* pHead, int option)
{
	char wordSearch[50];
	char sPrice[10];
	SList* pTmp = pHead;

	if (!pTmp)
	{
		printf("\nList is empty.");
		return 1;
	}

	printf("Enter word/year/price for a search: ");
	scanf("%s", &wordSearch);

	printf("\nResult:\n\n");

	while (pTmp->mNext)
	{
		switch (option)
		{
		case 1:
			if (strstr(pTmp->mBooks.title, wordSearch))
			{
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", pTmp->position, pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
			}
			break;
		case 2:
			if (strstr(pTmp->mBooks.author, wordSearch))
			{
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", pTmp->position, pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
			}
			break;
		case 3:
			if (strstr(pTmp->mBooks.year, wordSearch))
			{
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", pTmp->position, pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
			}
			break;
		case 4:
			if (strstr(_itoa(pTmp->mBooks.price, sPrice, 10), wordSearch))
			{
				printf(" %-3d || %-18s || %-27s || %6s || %-10s || %-4d grn. ||\n", pTmp->position, pTmp->mBooks.author, pTmp->mBooks.title, pTmp->mBooks.year, pTmp->mBooks.pages, pTmp->mBooks.price);
			}
			break;
		}
		pTmp = pTmp->mNext;
	}


}

void clearScreen()
{
	system("@cls||clear");
}
