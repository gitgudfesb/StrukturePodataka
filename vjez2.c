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


poz dodajPocetak(poz p)
{
	int i = 0, n = 0;

	printf("Koliko osoba zelite upisati na pocetak: ");
	scanf("%d", &n);
	poz novi = (poz)malloc(n * sizeof(osoba));

	for (i = 0; i < n; i++)
	{
		printf("\nUnesi ime osobe: ");
		scanf("%s", (novi + i)->ime);
		printf("\nUnesi prezime osobe: ");
		scanf("%s", (novi + i)->prezime);
		printf("\nUnesi godinu rodenja osobe: ");
		scanf("%d", &(novi + i)->godinaRodenja);

		(novi + i)->next = p->next;
		p->next = (novi + i);

	}
	return p->next;
}

void ispis(poz p)
{
	while (p != NULL)
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
	poz temp;

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
	poz pret = pronalaziPrethodniElement(p);
	pret->next = pret->next->next;//checkaj
	free(pret->next);

}


int main()
{
	osoba dummy;
	int a;

	dummy.next = NULL;

	dummy.next = dodajPocetak(&dummy);

	ispis(dummy.next);

	printf("%s", pronalaziElement(&dummy)->ime);

	scanf("%d", &a);

	return 0;
}
