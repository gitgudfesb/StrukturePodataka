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

void ZbrajaISortira(pok zbroj, int k, int e)
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

}
// IZ DATOTEKE
void UnosiSort(pok p, char* file)
{
	pok q, poc = p;
	int eks, koef;
	FILE* f = fopen(file, "r");
	if (f == NULL) printf("Greška kod otvaranja filea");
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
				if ( p->next!=NULL && eks == p->next->Eks)
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
}

void zbrojPolinoma(pok p1, pok p2, pok z)
{
	pok poc = p1;
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

	//ISPISUJE ZBROJENE POLINOME
	while (z->next != NULL)
	{
		printf("%d %d, ", z->next->Koef, z->next->Eks);
		z = z->next;
	}
	printf("\n\n");
}

void produktPolinoma(pok p1, pok p2, pok pro)
{
	p1 = p1->next;
	p2 = p2->next;
	pok poc = p2;
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
	//ISPIS POMNOŽENIH POLINOMA
	while (pro->next != NULL)
	{
		printf("%d %d, ", pro->next->Koef, pro->next->Eks);
		pro = pro->next;
	}
}

int main() {

	polinom poli1, poli2, pZbroj, pProdukt;
	poli1.next = NULL;
	poli2.next = NULL;
	pZbroj.next = NULL;
	pProdukt.next = NULL;

	UnosiSort(&poli1, "polinom1.txt");
	UnosiSort(&poli2, "polinom2.txt");
	zbrojPolinoma(&poli1, &poli2, &pZbroj);
	produktPolinoma(&poli1, &poli2, &pProdukt);

	return 0;
}