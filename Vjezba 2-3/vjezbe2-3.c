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
	poz novi = (poz)malloc(sizeof(osoba));

	printf("\nUnesi podatke: ");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);

	novi->next = p->next;
	p->next = novi;

}

void ispis(poz p)
{
	p = p->next;//da ne ispisuje head(dummy) element
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

	while (p->next != NULL)
	{
		p = p->next;
	}
	novi->next = NULL;
	p->next = novi;
}

poz pronalaziElement(poz p)
{
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);

	while (p->next != NULL && strcmp(prez, p->prezime) != 0)
	{
		p = p->next;
	}

	if (p->next == NULL && strcmp(prez, p->prezime) != 0) return 0;
	else return p;
}

poz pronalaziPrethodniElement(poz p)
{
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);
	poz temp = NULL;

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

void dodajIza(poz p)
{
	poz novi = (poz)malloc(sizeof(osoba));
	printf("\nUnesi podatke: ");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
	p = pronalaziElement(p);
	novi->next = p->next;
	p->next = novi;

}

void dodajIspred(poz p)
{
	poz novi = (poz)malloc(sizeof(osoba));
	printf("\nUnesi podatke: ");
	scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
	p = pronalaziPrethodniElement(p);
	novi->next = p->next;
	p->next = novi;

}

void dodajDatoteka(poz p)
{
	FILE *f;
	f = fopen("unos.txt", "r");
	if (f == NULL) printf("Nema datoteke s tim imenom!");
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}

		while (!feof(f))
		{
			poz novi = (poz)malloc(sizeof(osoba));
			fscanf(f, "%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
			novi->next = NULL;
			p->next = novi;
			p = novi;

		}

	}
	fclose(f);
}
void sortiraj(poz p)
{
	char tempIme[MAX_NAME], tempPrez[MAX_NAME];
	int i, j, tempGodina;
	p = p->next;
	poz temp;

	for (p; p != NULL; p = p->next)
	{
		for (temp = p->next; temp != NULL; temp = temp->next)
		{

			if (strcmp(p->prezime, temp->prezime) != -1)
			{
				tempGodina = p->godinaRodenja;
				strcpy(tempIme, p->ime);
				strcpy(tempPrez, p->prezime);

				p->godinaRodenja = temp->godinaRodenja;
				strcpy(p->ime, temp->prezime);
				strcpy(p->prezime, temp->prezime);

				temp->godinaRodenja = tempGodina;
				strcpy(temp->ime, tempIme);
				strcpy(temp->prezime, tempPrez);


			}
		}
	}
}

void ispisDatoteka(poz p)
{
	FILE *f;
	f = fopen("ispis.txt", "w");
	if (f == NULL) printf("Ne postoji datoteka za ispis.");
	else
	{
		p = p->next;
		while (p != NULL)
		{
			fprintf(f, " %s %s %d.\n", p->ime, p->prezime, p->godinaRodenja);
			p = p->next;
		}
	}
	fclose(f);
}

int main()
{
	osoba head;
	int a = -1;
	head.next = NULL;

	while (a != 0)
	{
		printf("1.Unesi el. na pocetak liste\n2.Unesi el. na kraj liste\n3.Ispisi listu\n4.Izbrisi el. liste\n5.Pronadi el. s odredenim prezimenom\n6.Dodaj el. iz datoteke\n7.Ispisi el. u datoteku\n 8.Unesi el. ispred trazenog el.\n9.Unesi el. iza trazenog el.\n10. Sortiraj\n");
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
		case 6:
			dodajDatoteka(&head);
			break;
		case 7:
			ispisDatoteka(&head);
			break;
		case 8:
			dodajIspred(&head);
			break;
		case 9:
			dodajIza(&head);
			break;
		case 10:
			sortiraj(&head);
			break;
		default:
			break;

		}

		printf("\n\n\n");
	}

	getchar();
	return 0;
}

