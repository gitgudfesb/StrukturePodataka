#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define IME_MAX 64

typedef struct _elementTab* pozicija;
typedef struct _elementTab* hashListe;//moga san korisit i poziciju al nebi bilo jasno jer koriste za razl stvari
typedef struct _elementTab
{
	int mb;
	char ime[IME_MAX];
	char prezime[IME_MAX];
	pozicija next;

}Student;

typedef struct _hashTablica
{
	int brojElemenata;//njih ce bit 11
	hashListe* niz;//to je niz=pokazivac na jednu od 11 listi elemenata student,sama hashlista je pokazivac na studenta

}hashTablica;

int dajIndeksZaTablicu(char prezime[IME_MAX], int brojElemenata)
{
	int br = 0, i = 0;
	for (i = 0; i < 5; i++)
	{

		if (prezime[i] == '\0') { break; }
		if ((int)toupper(prezime[i]) >= 65 && (int)toupper(prezime[i]) <= 90) br = br + (int)toupper(prezime[i]);//pretvaran u velika slova da ne bi racunalo razlicito mala velika jer je razl acii vrijednost
		//else to nije znak pa necemo racunat vjv je krivo utipkano, ali cila provjera je zato da ako ima manje od 5 slova prezime da nebi errora bilo
	}

	br = br % brojElemenata;
	return br;
}


int usporediImena(char ime1[IME_MAX], char prezime1[IME_MAX], char ime2[IME_MAX], char prezime2[IME_MAX])
{// vraca - 1 ako je raspored ka u zagradama 1 ide ispred 2 , -1 ako obbrnuto
	ime1 = _strupr(ime1);
	prezime1 = _strupr(prezime1);
	ime2 = _strupr(ime2);
	prezime2 = _strupr(prezime2);

	if (strcmp(prezime1, prezime2) < 0) return -1; //strcmp vraca -1 ako je raspored ka u zagradama,-1 ako obbrnuto,0 ako su jednaki
	else if (strcmp(prezime1, prezime2) > 0) return 1;
	else if (strcmp(prezime1, prezime2) == 0)
	{
		if (strcmp(ime1, ime2) < 0) return -1;
		else if (strcmp(ime1, ime2) > 0) return 1;
		else return 0;//oba ista skroz
	}

}
pozicija pronadiPrethodnika(int indeks, pozicija onajkojegUnosimo, const hashTablica h)
{
	pozicija prethodni = NULL;
	pozicija gdjeunijeti = h.niz[indeks - 1];
	while (gdjeunijeti != NULL && usporediImena(gdjeunijeti->ime, gdjeunijeti->prezime, onajkojegUnosimo->ime, onajkojegUnosimo->prezime) == -1 )
	{
		prethodni = gdjeunijeti;//spremi prethodnu tako da kad izade imamo adresu prethodnog
		gdjeunijeti = gdjeunijeti->next;
	}

	return prethodni;
}

pozicija pronadiElement(int indeks, pozicija trazeni, const hashTablica h)
{
	pozicija elementListe = h.niz[indeks - 1];
	while (elementListe != NULL  && usporediImena(elementListe->ime, elementListe->prezime, trazeni->ime, trazeni->prezime) !=0 )
	{
		elementListe = elementListe->next;
	}
	if (elementListe == NULL) return NULL;
	else return elementListe;

}



int unosUTablicu(hashTablica h)
{
	int indeks;
	pozicija unos = (pozicija)malloc(sizeof(Student));
	pozicija prethodni = (pozicija)malloc(sizeof(Student));
	if (unos == NULL || prethodni==NULL)
	{
		printf("Greska pri alokaciji memorije za unos!!");
		return -1;
	}

	else
	{
		printf("Unesite ime studenta kojeg unosite:\n");
		scanf("%s", (unos->ime));
		printf("Unesite prezime studenta kojeg unosite:\n");
		scanf("%s", (unos->prezime));
		printf("Unesite maticni broj studenta kojeg unosite:\n");
		scanf("%d", &unos->mb);

		indeks = dajIndeksZaTablicu(unos->prezime, h.brojElemenata);
		if (h.niz[indeks - 1] == NULL)
		{
			h.niz[indeks - 1] = unos;
			unos->next = NULL;
			//samo unesi jer je misto na tom indeksu prazno
		}
		else
		{

			prethodni = pronadiPrethodnika(indeks, unos, h);
			if (prethodni == NULL)//trebamo ga umetnit na pocetak liste
			{
				prethodni = h.niz[indeks - 1];//prethodni korsitim ko temp, samo se umetne unos na pocetak liste
				h.niz[indeks - 1] = unos;
				h.niz[indeks - 1]->next = prethodni;
			}
			else
			{
				unos->next = prethodni->next;
				prethodni->next = unos;
			}

		}
	}
}

int ispisiMaticniBroj(const hashTablica h) {

	pozicija student = (pozicija)malloc(sizeof(Student));
	pozicija p;

	printf("Unesite ime i prezime studenta ciji maticni broj trazite: ");
	scanf("%s %s", student->ime, student->prezime);

	p = pronadiElement(dajIndeksZaTablicu(student->prezime, h.brojElemenata), student, h);

	if (p == NULL)
	{
		printf("Nije naden taj student :(!\n");
		return -1;
	}
	else
	{
		printf("Maticni broj studenta je: %d\n", p->mb);
		return 0;
	}

}

int ispisTablice(const hashTablica h) {

	int i = 0;
	hashListe t = h.niz[i];
	for (i = 0; i < h.brojElemenata; i++)
	{
		t = h.niz[i];
		printf("%d. redak tablice: ", i);
		while (t != NULL)
		{

			printf("\t%d %s %s", t->mb, t->ime, t->prezime);

			t = t->next;

		}

		printf("\n");
	}

	return 0;
}

int main()
{
	int i = 0;
	hashTablica* nova = (hashTablica*)malloc(sizeof(hashTablica));
	nova->brojElemenata = 11;
	nova->niz = (hashListe *)malloc(nova->brojElemenata * sizeof(hashListe));
	for (i = 0; i < 11; i++)
	{
		nova->niz[i] = NULL;


	}

	i = 9;
	while (i != 0) {

		printf("0 - Izlaz\n1 - Unos u tablicu\n2-Ispis iz tablice\n3 - Ispisi maticni broj\n");
		scanf("%d", &i);


		switch (i)
		{
		case 1:
			unosUTablicu(*nova);
			break;
		case 2:
			ispisTablice(*nova);
			break;
		case 3:
			ispisiMaticniBroj(*nova);
			break;
		default:
			break;
		}

	}

	return 0;
}
