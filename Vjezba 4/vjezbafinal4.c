#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _polinom* pok;

typedef struct _polinom {
	int Koef;
	int Eks;
	pok next;
} polinom;

pok stvoriElementListe(void);
int ispis(const pok);
int ZbrajaISortira(const pok, const int , const int );
int UnosiSort(const pok , const char*);
pok zbrojPolinoma(const pok, const pok, const pok);
pok produktPolinoma(const pok , const pok, const pok);

pok stvoriElementListe()
{
	pok stvoreniElement = (pok)malloc(sizeof(polinom));
	if (stvoreniElement == NULL)
	{
		printf("Greska u funkciji stvoriElement.\n");
		return NULL;
	}
	else
	{
		stvoreniElement->next = NULL;//PAZIII OVO INICIJALIZIRA NA NULL
		return stvoreniElement;
	}
}

int ispis(const pok head)
{
	pok p = head;
	if (p->next == NULL)
	{
		printf("Nema ničega u listi za ispisati.");
		return -1;
	}
	else
	{
		while (p->next != NULL)
		{
			printf("%d %d, ", p->next->Koef, p->next->Eks);
			p = p->next;
		}

		return 0;
	}
	printf("\n\n");
}

int ZbrajaISortira(const pok zbroj, const int k, const int e)
{

	pok q;
	pok p = zbroj;

	while (p->next != NULL && e < p->next->Eks)
		p = p->next;
	if (p->next != NULL && e == p->next->Eks)
	{
		p->next->Koef = p->next->Koef + k;

		p = zbroj;
	}
	else
	{
		q = stvoriElementListe();
		q->Eks = e;
		q->Koef = k;
		q->next = p->next;
		p->next = q;

		p = zbroj;
	}
	return 0;
}
// IZ DATOTEKE
int UnosiSort(const pok p, const char* file)
{
	pok q;
	pok poc = p;
	int eks, koef;
	FILE* f = fopen(file, "r");
	if (f == NULL) {
		printf("Greška kod otvaranja filea");
		return -1;
	}
	else
	{
		while (!(feof(f))) {

			fscanf(f, "%d %d", &koef, &eks);

			if (poc->next == NULL)
			{
				q = stvoriElementListe();
				q->Eks = eks;
				q->Koef = koef;
				q->next = NULL;
				poc->next = q;
			}
			else
			{
				while (poc->next != NULL && eks < poc->next->Eks)
					poc = poc->next;
				// OVDI GLEDA JESU EKSPONENTI U DATOTECI MOŽDA ISTI PA IH ZBROJI I NE STVARA NOVU LISTU
				if (poc->next != NULL && eks == poc->next->Eks)
				{
					poc->next->Koef = poc->next->Koef + koef;

					poc = p;
				}
				else
				{
					q = stvoriElementListe();

					q->Eks = eks;
					q->Koef = koef;
					q->next = poc->next;
					poc->next = q;

					poc = p;
				}
			}
		}
	}
	return 0;
}

pok zbrojPolinoma(const pok p1, const pok p2, const pok zbroj)
{
	pok pol1 = p1;
	pok pol2 = p2;
	pol1 = pol1->next;
	pol2 = pol2->next;
	while (pol1 != NULL)
	{
		ZbrajaISortira(zbroj, pol1->Koef, pol1->Eks);
		pol1 = pol1->next;
	}
	while (pol2 != NULL)
	{
		ZbrajaISortira(zbroj, pol2->Koef, pol2->Eks);
		pol2 = pol2->next;
	}
	return zbroj;
}

pok produktPolinoma(const pok p1, const pok p2, const pok produktPol)
{
	pok pol1 = p1;
	pok pol2 = p2;
	pol1 = pol1->next;
	pol2 = pol2->next;

	while (pol1 != NULL)
	{
		while (pol2 != NULL)
		{
			ZbrajaISortira(produktPol, pol1->Koef * pol2->Koef, pol1->Eks + pol2->Eks);
			pol2 = pol2->next;
		}
		pol1 = pol1->next;
		pol2 = p2->next;
	}
	return produktPol;
}

int main() {

	polinom poli1, poli2, pZbroj, pProdukt;
	poli1.next = NULL;
	poli2.next = NULL;
	pZbroj.next = NULL;
	pProdukt.next = NULL;

	UnosiSort(&poli1, "polinom1.txt");
	UnosiSort(&poli2, "polinom2.txt");
	printf("Zbroj: \n");
	ispis(zbrojPolinoma(&poli1, &poli2, &pZbroj));
	printf("\nProdukt: \n");
	ispis(produktPolinoma(&poli1, &poli2, &pProdukt));

	return 0;
}
