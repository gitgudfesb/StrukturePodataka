#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAX 10


typedef struct _list
{
	char element[STRING_MAX];
	struct _list* next;
}list;

typedef list* poz;

int dodajNaStog(poz p, char c[STRING_MAX]) {

	poz q = (poz)malloc(sizeof(list));

	strcpy(q->element, c);

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
	elementListe = elementListe->next;
	while (elementListe != NULL)
	{
		printf("%s, ", elementListe->element);
		elementListe = elementListe->next;
	}

	return 0;
}



int ucitajIzDatoteke(const char *datoteka, const poz p) {

	char izraz[STRING_MAX], c;
	int i = 0;
	FILE *f = fopen(datoteka, "r");


	if (f == NULL)
	{
		printf("Dogodila se greska prilikom otvaranja datoteke!");
		return -1;
	}


	while (!feof(f))
	{

		izraz[0] = '\0';
		fscanf(f, "%s", izraz);//greska, ne moze cilo vrime na isti niz stavljat
		dodajNaStog(p, izraz);
	}

}



int main() {

	int a = 1;
	char *naziv = "datoteka.txt";

	list headStog;

	headStog.next = NULL;

	ucitajIzDatoteke(naziv, &headStog);

	ispis(&headStog);

	scanf("%d", &a);
	return 0;
}
