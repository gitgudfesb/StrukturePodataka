#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAX_NAME 64

typedef struct _osoba
{
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int godinaRodenja;
	struct _osoba* next;
}osoba;

typedef osoba* poz;


void dodajPocetak(poz p)
{
	poz novi = (poz)malloc( sizeof(osoba));

	printf("\nUnesi podatke: ");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);

	novi->next = p->next;
	p->next = novi;

}

void ispis(poz p)
{
	p = p->next;//da ne ispisuje head(dummy) element
	while (p!= NULL)
	{
		printf("\n %s %s %d.", p->ime, p->prezime, p->godinaRodenja);
		p = p->next;
	}
}

void dodajKraj(poz p)
{
	poz novi = (poz)malloc(sizeof(osoba));
	printf("\nUnesi podatke: ");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
	
	while (p->next!= NULL) 
	{
		p = p->next;
	}
	novi->next = NULL;
	p->next= novi;
}

poz pronalaziElement(poz p)
{
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);

	while (p->next != NULL && strcmp(prez, p->prezime)!=0)
	{
		p = p->next;
	}

	if (p->next == NULL && strcmp(prez,p->prezime)!=0) return 0;
	else return p;
}

poz pronalaziPrethodniElement(poz p)
{
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);
	poz temp=NULL;

	while (p->next != NULL && strcmp(prez, p->prezime) != 0)
	{
		temp = p;
		p = p->next;
	}

	if (p->next == NULL && strcmp(prez, p->prezime) != 0) return 0;
	else return temp;
}


void brisi(poz p) 
{
	poz trash = NULL;//u nju cemo spremit adresu ovog kojeg prisemo, inace ce nam nestat ta vrijednost u liniji 90
	poz pret = pronalaziPrethodniElement(p);
	trash = pret->next;
	pret->next = pret->next->next;
	free(trash);
}


int main()
{
	osoba head;
	int a=-1;
	head.next = NULL;

	while (a != 0)
	{
		printf("1.Unesi el. na pocetak liste\n2.Unesi el. na kraj liste\n3.Ispisi listu\n4.Izbrisi el. liste\n5.Pronadi el. s odredenim prezimenom\n");
		scanf("%d", &a);
		switch (a)
		{
			case 1: 
				dodajPocetak(&head);
				break;
			case 2:
				dodajKraj(&head);
				break;
			case 3:
				ispis(&head);
				break;
			case 4:
				brisi(&head);
				break;
			case 5:
				pronalaziElement(&head);
				break;
			default:
				break;

		}

		printf("\n\n\n");
	}

	getchar();
	return 0;
}
