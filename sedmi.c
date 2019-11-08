#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define IZRAZ_MAX 256


typedef struct _list
{
	char *element;
	struct _list* next;
}list;

typedef list* poz;

int dodajNaStog(poz p, char c[IZRAZ_MAX]) {

	poz q = (poz)malloc(sizeof(list));

	q->element = c;

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
		printf("%c, ", elementListe->element);
		elementListe = elementListe->next;
	}

	return 0;
}



int ucitajIzDatoteke(const char *datoteka,const poz p){

	char izraz[IZRAZ_MAX], c;
	int i = 0;
	FILE *f = fopen(datoteka, "r");

	
	if(f ==NULL)
	{
		printf("Dogodila se greska prilikom otvaranja datoteke!");
		return -1;
	}


	while(!feof(f))
	{
		fscanf(f,"%s",izraz);//greska, ne moze cilo vrime na isti niz stavljat
		dodajNaStog(p,izraz);
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
