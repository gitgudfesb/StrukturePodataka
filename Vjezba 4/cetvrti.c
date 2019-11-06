#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct _polinom {
	int Koef;
	int Eks;
	struct _polinom* next;
} polinom;

typedef polinom* pok;

// UNOS I SORT ALI NE IZ DATOTEKE

int ispis(pok is)
{
	if (is->next == NULL)
	{
		printf("Nema nièega u listi za ispisati.");
		return -1;
	}
	else
	{
		while (is->next != NULL)
		{
			printf("%d %d, ", is->next->Koef, is->next->Eks);
			is = is->next;
		}
	}
	printf("\n\n");
	return 0;
}

int ZbrajaISortira(pok zbroj, int k, int e)
{

	pok q, poc = zbroj;

	while (zbroj->next != NULL && e < zbroj->next->Eks)
		zbroj = zbroj->next;
	if (zbroj->next != NULL && e == zbroj->next->Eks)
	{
		zbroj->next->Koef = zbroj->next->Koef + k;

		zbroj = poc;
	}
	else
	{
		q = (pok)malloc(sizeof(polinom));
		q->Eks = e;
		q->Koef = k;
		q->next = zbroj->next;
		zbroj->next = q;

		zbroj = poc;
	}
	return 0;
}
// IZ DATOTEKE
int UnosiSort(pok p, char* file)
{
	pok q, poc = p;
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

			if (p->next == NULL)
			{
				q = (pok)malloc(sizeof(polinom));
				q->Eks = eks;
				q->Koef = koef;
				q->next = NULL;
				p->next = q;
			}
			else
			{
				while (p->next != NULL && eks < p->next->Eks)
					p = p->next;
				// OVDI GLEDA JESU EKSPONENTI U DATOTECI MOŽDA ISTI PA IH ZBROJI I NE STVARA NOVU LISTU
				if (p->next != NULL && eks == p->next->Eks)
				{
					p->next->Koef = p->next->Koef + koef;

					p = poc;
				}
				else
				{
					q = (pok)malloc(sizeof(polinom));

					q->Eks = eks;
					q->Koef = koef;
					q->next = p->next;
					p->next = q;

					p = poc;
				}
			}
		}
	}
	return 0;
}

pok zbrojPolinoma(pok p1, pok p2, pok z)
{
	pok poc = p1, ret = z;
	p1 = p1->next;
	p2 = p2->next;
	while (p1 != NULL)
	{
		ZbrajaISortira(z, p1->Koef, p1->Eks);
		p1 = p1->next;
	}
	while (p2 != NULL)
	{
		ZbrajaISortira(z, p2->Koef, p2->Eks);
		p2 = p2->next;
	}
	return ret;
}

pok produktPolinoma(pok p1, pok p2, pok pro)
{
	p1 = p1->next;
	p2 = p2->next;
	
	pok poc = p2, ret = pro;
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			ZbrajaISortira(pro, p1->Koef * p2->Koef, p1->Eks + p2->Eks);
			p2 = p2->next;
		}
		p1 = p1->next;
		p2 = poc;
	}
	return ret;
}

int main() {

	polinom poli1, poli2, pZbroj, pProdukt;
	poli1.next = NULL;
	poli2.next = NULL;
	pZbroj.next = NULL;
	pProdukt.next = NULL;

	UnosiSort(&poli1, "polinom1.txt");
	UnosiSort(&poli2, "polinom2.txt");
	ispis(zbrojPolinoma(&poli1, &poli2, &pZbroj));
	ispis(produktPolinoma(&poli1, &poli2, &pProdukt));

	return 0;
}