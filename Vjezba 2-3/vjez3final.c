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


int dodajPocetak(const poz head)
{
	poz headListe=head,novi = (poz)malloc(sizeof(osoba));
	if (novi == NULL)
	{
		printf("Greska u funkciji dodajPocetak\n");
		return -1;
	}
	else
	{
		printf("\nUnesi podatke: ");
		scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);

		novi->next = headListe->next;
		headListe->next = novi;

		return 0;
	}
}
int ispis(const poz head)
{
	poz elementListe = head;
	elementListe = elementListe->next;//da ne ispisuje head(dummy) element
	while (elementListe != NULL)
	{
		printf("\n %s %s %d.", elementListe->ime, elementListe->prezime, elementListe->godinaRodenja);
		elementListe = elementListe->next;
	}

	return 0;
}

int dodajKraj(const poz head)
{
	poz elementListe=head, novi = (poz)malloc(sizeof(osoba));
	if (novi == NULL)
	{
		printf("Greska u funkciji dodajKraj\n");
		return -1;
	}
	else
	{
		printf("\nUnesi podatke: ");
		scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);

		while (elementListe->next != NULL)
		{
			elementListe = elementListe->next;
		}
		novi->next = NULL;
		elementListe->next = novi;

		return 0;
	}

}

poz pronalaziElement(const poz head)
{
	poz elementListe = head;
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);

	while (elementListe->next != NULL && strcmp(prez, elementListe->prezime) != 0)
	{
		elementListe = elementListe->next;
	}

	if (elementListe->next == NULL && strcmp(prez, elementListe->prezime) != 0)
	{
		printf("Nije pronaden el. sa tim prezimenom\n");
		return NULL;
	}
	else
	{
		printf("Pronaden je %s %s, roden %d. godine.\n", elementListe->ime, elementListe->prezime, elementListe->godinaRodenja);
		return elementListe;
	}
}

poz pronalaziPrethodniElement(const poz head)
{
	poz elementListe = head;
	char prez[MAX_NAME];
	printf("\nUnesi prezime: ");
	scanf("%s", prez);
	poz temp = NULL;

	while (elementListe->next->next != NULL && strcmp(prez, elementListe->next->prezime) != 0)
	{
		elementListe = elementListe->next;
	}

	if (elementListe->next->next == NULL && strcmp(prez, elementListe->next->prezime) != 0)
	{
		printf("Nije pronaden el. sa tim prezimenom\n");
		return NULL;
	}

	else
	{
		printf("Pronaden je %s %s, roden %d. godine ispred %s\n", elementListe->ime, elementListe->prezime, elementListe->godinaRodenja,elementListe->next->prezime);
		return elementListe;
	}
}

int brisi(const poz head)
{
	poz trash = NULL;//u nju cemo spremit adresu ovog kojeg brisemo, inace ce nam nestat ta vrijednost u  liniji 90
	poz pret = pronalaziPrethodniElement(head);
	if (pret == NULL) return -1;
	else
	{
		trash = pret->next;
		pret->next = pret->next->next;
		free(trash);

		return 0;
	}

}

int dodajIza(const poz head)
{
	poz elementListe=head,novi = (poz)malloc(sizeof(osoba));
	if (novi == NULL)
	{
		printf("Greska u funkciji dodajIza\n");
		return -1;
	}
	else
	{
		printf("\nUnesi podatke: ");
		scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
		elementListe = pronalaziElement(elementListe);
		novi->next = elementListe->next;
		elementListe->next = novi;
		return 0;
	}

}

int dodajIspred(const poz head)
{
	poz elementListe=head,novi = (poz)malloc(sizeof(osoba));
	if (novi == NULL)
	{
		printf("Greska u funkciji dodajIspred\n");
		return -1;
	}
	else
	{
		printf("\nUnesi podatke: ");
		scanf("%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
		elementListe = pronalaziPrethodniElement(elementListe);
		novi->next = elementListe->next;
		elementListe->next = novi;

		return 0;
	}


}

int dodajDatoteka(const poz head)
{
	FILE *f;
	poz elementListe = head;
	int indikatorGreske = 0;//ostat ce na nuli ako nije bilo greske, koristin ga u dijelu sa while feof jer imamo dvi moguce greske a doli je zeznuto vratit 

	f = fopen("unos.txt", "r");
	if (f == NULL)
	{
		printf("Nema datoteke s tim imenom!");
		return -1;
	}
	else
	{
		while (elementListe->next != NULL)
		{
			elementListe = elementListe->next;
		}

		while (!feof(f))
		{
			poz novi = (poz)malloc(sizeof(osoba));
			if (novi == NULL)
			{
				printf("Greska u funkciji dodajDatoteka\n");
				indikatorGreske = -2;
				break;
			}
			else
			{
				fscanf(f, "%s %s %d", novi->ime, novi->prezime, &novi->godinaRodenja);
				novi->next = NULL;
				elementListe->next = novi;
				elementListe = novi;
			}
		}
		return indikatorGreske;
	}
	fclose(f);
}
int sortiraj(const poz head)
{
	char tempIme[MAX_NAME], tempPrez[MAX_NAME];
	int tempGodina;
	poz p = head->next;
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
	return 0;
}

int ispisDatoteka(const poz head)
{
	FILE *f;
	poz elementListe = head;

	f = fopen("ispis.txt", "w");
	if (f == NULL)
	{
		printf("Ne postoji datoteka za ispis.\n");
		return -1;
	}
	else
	{
		elementListe = elementListe->next;
		while (elementListe != NULL)
		{
			fprintf(f, " %s %s %d.\n", elementListe->ime, elementListe->prezime, elementListe->godinaRodenja);
			elementListe = elementListe->next;
		}
		return 0;
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
