#pragma once
#pragma once
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct SBooks {
	char author[100];
	char title[100];
	char year[50];
	char pages[50];
	int price;
}SBooks;
typedef struct SList
{
	int position;
	SBooks mBooks;
	struct SList* mNext;
}SList;
//
//Перевіряє, чи список порожній
//
int isEmpty(SList* pFirst);
//
// Дозволяє ввести нову книгу з консолі
//
void consoleInput(SList** ppH);
//
//Додає елемент у список, сортуючи його за назвою книги
//
void add_sortElem(SList bookshelf, SList** ppH, struct SBooks books);
//
// Сортує книги за ціною
//
void sel_sort(SList bookshelf, SList* phead);
//
// Видаляє книги, назва яких починається на "Д"
//
void deleteD(SList** ppH);
//
//Звільняє память
//
void dealloc(SList** ppHead);
//
//Зчитує дані про книги з текстового файлу
//
void ScanNotes(FILE* fp, SList** pHead, SList bookshelf);
//
// Видаляє вибрану книгу
//
void del_elem(SList** pHead, int listsize, int position);
//
//Записує дані про книги в текстовий файл
//
void WriteNotes(FILE* pF, SList** pHead);
//
//Повертає розмір списку
//
int getSize(SList* pFirst);
//
//Впорядковує список
//
int OrderList(SList** pHead);
//
// Дозволяє редагувати вибраний запис про книгу
//
void edit_note(SList** pHead, int listsize);
//
// Здійснює пошук за вибраним параметром
//
int findNote(SList* pHead, int option);
//
//Очищує вікно консолі
//
void clearScreen();