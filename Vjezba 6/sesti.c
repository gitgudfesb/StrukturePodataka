#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


typedef struct _list* poz;

typedef struct _list
{
	int element;
	poz next;
}list;


int pushStog( poz p) {

	int broj = ((rand() % 91) + 10);
	poz q = (poz)malloc(sizeof(list));

	q->element = broj;

	q->next = p->next;

	p->next = q;

	return 0;
}

int pushRed(poz p) {

	int broj = ((rand() % 91) + 10);
	poz q = (poz)malloc(sizeof(list));

	q->element = broj;

	while (p->next != NULL) {
		p = p->next;
	}

	q->next = p->next;

	p->next = q;


	return 0;
}

int pop(poz p) {

	poz trash = p->next;

	if (trash == NULL) {
		printf("Lista je vec prazna !!!");
		return -1;
	}

	p->next = trash->next;

	free(trash);


	return 0;
}

int ispis(const poz p)
{
	poz elementListe = p;
	elementListe = elementListe->next;//da ne ispisuje head(dummy) element
	while (elementListe != NULL)
	{
		printf("%d, ", elementListe->element);
		elementListe = elementListe->next;
	}

	return 0;
}


int main() {

	int a = 1;

	list headStog, headRed;

	headStog.next = NULL;
	headRed.next = NULL;

	while (a != 0)
	{
		printf("1.Dodaj nasumicni element u stog\n2.Dodaj nasumicni element u red\n3.Izbrisi elemen stoga\n4.Izbrisi element reda\n5.Ispisi\n6.Izadi\n");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			pushStog(&headStog);
			break;
		case 2:
			pushRed(&headRed);
			break;
		case 3:
			pop(&headStog);
			break;
		case 4:
			pop(&headRed);
			break;
		case 5:
			printf("Stog: \n");
			ispis(&headStog);
			printf("\nRed: \n");
			ispis(&headRed);
			break;
		case 6:
			a = 0;
			break;
		default:
			break;

		}

		printf("\n\n\n");
	}

	return 0;
}
