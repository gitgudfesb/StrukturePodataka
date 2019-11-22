#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAX 10

typedef struct _CvorStabla * stablo;
typedef struct _CvorStog * pok;

typedef struct _CvorStabla {
	int el;
	stablo lijevo;
	stablo desno;
} CvorStabla;

typedef struct _CvorStog {
	stablo pokNaStablo;
	pok next;
} CvorStoga;

stablo stvoriElementStabla();
pok stvoriElementStoga();
int CitanjePostfiksa(const char *, const pok);
pok dodajNaStog(const pok, const int);
stablo skiniSaStoga(const pok);
int ispisUDatoteku(const char *, const stablo);

int ispisUDatoteku(const char * dat, const stablo p)
{
	FILE *f = fopen(dat, "a");

	if (f == NULL)
	{
		printf("Ne valja nešto u ispisUDatoteku!");
		return -1;
	}
	else
	{
		if (p->lijevo != NULL)
		{
			fprintf(f, "(");

			fclose(f);
			ispisUDatoteku(dat, p->lijevo);
			f = fopen(dat, "a");

			switch (p->el)
			{
			case 42:
				fprintf(f, " * ");
				break;
			case 43:
				fprintf(f, " + ");
				break;
			case 45:
				fprintf(f, " - ");
				break;
			default:
				fprintf(f, "pazi pazi");
				break;
			}
			fclose(f);
			ispisUDatoteku(dat, p->desno);
			f = fopen(dat, "a");

			fprintf(f, ")");
		}
		else
		{
			fprintf(f, "%d", p->el);
		}
	}
	fclose(f);
	return 0;
}

int CitanjePostfiksa(const char *datoteka, const pok p)
{
	char izraz[STRING_MAX];
	int i = 0, br = 0;
	pok q = NULL;
	stablo a = NULL;
	stablo b = NULL;
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

		while (izraz[i] != '\0')
		{
			if (isdigit(izraz[i]) == 0) br++;
			i++;
		}
		i = 0;

		if (br == 0) q = dodajNaStog(p, atoi(izraz));
		else
		{
			a = skiniSaStoga(p);
			b = skiniSaStoga(p);
			q = dodajNaStog(p, izraz[0]);
			q->pokNaStablo->desno = a;
			q->pokNaStablo->lijevo = b;
		}
		br = 0;
		//ovo samo ispisuje jel uèita sve lipo
		printf("%d, ", q->pokNaStablo->el);
	}
	return 0;
}

pok stvoriElementStoga()
{
	pok stvoreniElement = (pok)malloc(sizeof(CvorStoga));
	if (stvoreniElement == NULL)
	{
		printf("Greska u funkciji stvoriElementStoga.\n");
		return NULL;
	}
	else
	{
		stvoreniElement->pokNaStablo = stvoriElementStabla();
		stvoreniElement->next = NULL;
		return stvoreniElement;
	}
}

stablo stvoriElementStabla()
{
	stablo List = (stablo)malloc(sizeof(CvorStabla));
	if (List == NULL)
	{
		printf("Greska u funkciji stvoriElementStabla.\n");
		return NULL;
	}
	else
	{
		List->desno = NULL;
		List->lijevo = NULL;
		return List;
	}
}

pok dodajNaStog(const pok head, const int a)
{

	pok h = head, q = NULL;
	while (h->next != NULL)
		h = h->next;

	q = stvoriElementStoga();
	q->next = NULL;
	q->pokNaStablo->el = a;
	h->next = q;

	return q;

}

stablo skiniSaStoga(const pok p) {

	pok h = p, pret = NULL;
	stablo vraca = NULL;

	while (h->next != NULL)
	{
		pret = h;
		h = h->next;
	}

	pok trash = h;

	if (trash == NULL)
	{
		printf("Lista je vec prazna.");
		return NULL;
	}

	if (pret == NULL)
	{
		printf("Ne valja vam postfiks unos.");
		return NULL;
	}
	else
		pret->next = NULL;

	vraca = trash->pokNaStablo;
	free(trash);


	return vraca;
}

int main()
{

	int a = 1;
	char *naziv = "datoteka.txt";

	CvorStoga headStog;
	pok p;
	p = &headStog;

	headStog.next = NULL;

	CitanjePostfiksa(naziv, p);
	ispisUDatoteku(naziv, p->next->pokNaStablo);

	scanf("%d", &a);
	return 0;
}