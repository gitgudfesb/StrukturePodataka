#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAX 10


typedef struct _list
{
	int element;
	struct _list* next;
}list;

typedef list* poz;

int dodajNaStog(poz p, int a) {

	poz q = (poz)malloc(sizeof(list));

	q ->element = a;

	q->next = p->next;

	p->next = q;

	return 0;
}


int pop(poz p) {

	poz trash = p->next;
	int vraca;

	if (trash == NULL) 
	{	
		printf("Lista je vec prazna !!!");
		return NULL;
	}


	p->next = trash->next;

	vraca = trash->element;
	free(trash);


	return vraca;
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



int postfiksRacun(const char *datoteka, const poz p) 
{

	char izraz[STRING_MAX], c;
	int i = 0, a = 0,b = 0, br = 0,rezultat=0;
	FILE *f = fopen(datoteka, "r");


	if (f == NULL)
	{
		printf("Dogodila se greska prilikom otvaranja datoteke!");
		return -1;
	}


	while (!feof(f))
	{

		izraz[0] = '\0';
		fscanf(f, "%s", izraz);

		while(izraz[i] != '\0')
		{
			if(isdigit(izraz[i])==0) br++;
			i++;
		}	
		i = 0;

		if(br == 0 ) dodajNaStog(p, atoi(izraz));
	else
	{
		a=pop(p);
		b=pop(p);
		switch (izraz[0]) 
				{
					case '*':
						printf("%d",a * b);
						break;
					case '+':

						printf("%d",a + b);
						break;
					case '/':

						printf("%d",a / b);
						break;
					case '-':

						printf("%d",a - b);
						break;
					default:
						printf("OsAn UjUtRo Je, ZaSra Si");
						break;
				}
		

	}
		
	}

	//Triba dodat na stog rezultat
	//Radi samo za jednu op

}



int main() 
{

	int a = 1;
	char *naziv = "datoteka.txt";

	list headStog;

	headStog.next = NULL;

	postfiksRacun(naziv, &headStog);

	ispis(&headStog);

	scanf("%d", &a);
	return 0;
}
