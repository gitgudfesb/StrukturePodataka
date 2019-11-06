#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME 256
#include<stdio.h>
#include<stdlib.h>

typedef struct _list {
	int broj;
	struct _list* next;
} list;

typedef list* pozicija;

pozicija stvoriElementListe()
{
	pozicija stvoreniElement = (pozicija)malloc(sizeof(list));
	if (stvoreniElement == NULL)
	{
		printf("Greska u funkciji stvoriElement.\n");
	}
	else
	{
		stvoreniElement->next = NULL;//PAZIII OVO INICIJALIZIRA NA NULL
		return stvoreniElement;
	}
}

int unosIzaElementa(const pozicija izaKojeg, const pozicija onajKojeg)
{
	if (onajKojeg == NULL || izaKojeg == NULL)
	{
		printf("Greska u funkciji unosIzaElementa.\n");
		return -1;
	}
	else
	{
		onajKojeg->next = izaKojeg->next;
		izaKojeg->next = onajKojeg;
		return 0;
	}


}

int unosiSortirajuci(const pozicija head, const char* imeFilea)
{
	pozicija ucitanIzFilea, elementListe = head;
	int n;
	FILE* f = fopen(imeFilea, "r");
	if (f == NULL)
	{
		printf("Greska kod otvaranja filea u funkciji unosiSortirajuci.\n");
		return -1;
	}
	else
	{
		while (!(feof(f)))
		{
			fscanf(f, "%d", &n);

			if (elementListe->next == NULL)//ako je lista prazna 
			{
				ucitanIzFilea = stvoriElementListe();
				ucitanIzFilea->broj = n;
				unosIzaElementa(elementListe, ucitanIzFilea);

				elementListe = head;
			}
			else
			{
				while (elementListe->next != NULL && n > elementListe->next->broj)
					elementListe = elementListe->next;

				if (elementListe->next != NULL && n == elementListe->next->broj)
					elementListe = head;

				else
				{
					ucitanIzFilea = stvoriElementListe();
					ucitanIzFilea->broj = n;
					unosIzaElementa(elementListe, ucitanIzFilea);

					elementListe = head;
				}
			}
		}
		return 0;
	}


}

pozicija napraviUnijuListi(const pozicija headPrve, const pozicija headDruge)
{
	pozicija unijaListi, prvaLista = headPrve, drugaLista = headDruge, elementZaDodavanje, drzacHeadaUnije;
	unijaListi = (pozicija)malloc(sizeof(list));
	drzacHeadaUnije = unijaListi;//drzi head jer kasnije kad kopiramo prvu u nju,micemo se kroz listu
	unijaListi->next = NULL;
	prvaLista = prvaLista->next;//stavlja na prvi element, a ne na head jer head ne kopiramo

	while (prvaLista != NULL)//kopira prvu listu u uniju krece sa prvog el, zavrsava na zadnjem
	{
		elementZaDodavanje = stvoriElementListe();
		elementZaDodavanje->broj = prvaLista->broj;
		unijaListi->next = elementZaDodavanje;
		elementZaDodavanje->next = NULL;

		unijaListi = unijaListi->next;
		prvaLista = prvaLista->next;
	}

	unijaListi = drzacHeadaUnije;

	drugaLista = drugaLista->next;

	while (drugaLista != NULL)
	{
		while (unijaListi->next != NULL && drugaLista->broj > unijaListi->next->broj)//trazimo misto u koje pase element druge liste(izmedu veceg i manjeg iz prve)
		{
			unijaListi = unijaListi->next;
		}
		if (unijaListi->next != NULL && drugaLista->broj == unijaListi->next->broj)
		{
			drugaLista = drugaLista->next;//ne upisuje istog dva put u uniju(moze se lako prominit da ga doda samo se stavi manje ili jednako ode i doda kod iz else-a)
		}
		else
		{
			elementZaDodavanje = stvoriElementListe();
			elementZaDodavanje->broj = drugaLista->broj;
			elementZaDodavanje->next = unijaListi->next;
			unijaListi->next = elementZaDodavanje;

			drugaLista = drugaLista->next;
		}

	}

	return drzacHeadaUnije;
}

pozicija presjekListi(const pozicija headPrve, const pozicija headDruge)
{
	pozicija headPresjeka, presjek, prvaLista = headPrve, drugaLista = headDruge, element;
	presjek = stvoriElementListe();
	headPresjeka = presjek;
	prvaLista = prvaLista->next;
	drugaLista = drugaLista->next; // SAMO IH POMIÈE SA HEADA
	presjek->next = NULL;

	while (prvaLista != NULL)
	{
		while (drugaLista != NULL)
		{
			if (prvaLista->broj == drugaLista->broj)
			{
				element = stvoriElementListe();
				element->next = presjek->next;
				presjek->next = element;
				element->broj = prvaLista->broj;
				presjek = presjek->next;
			}
			drugaLista = drugaLista->next;
		}
		prvaLista = prvaLista->next;
		drugaLista = headDruge->next;
	}

	return headPresjeka;
}

int ispisListe(const pozicija head)
{
	pozicija elementListe = head;
	elementListe = elementListe->next;

	if (head == NULL)
	{
		printf("Greska pri ispisu.\n");
		return -1;
	}
	else
	{
		printf("\n");
		while (elementListe != NULL)
		{
			printf("%d ", elementListe->broj);
			elementListe = elementListe->next;
		}
		return 0;
	}


}

int main()
{
	pozicija headPrveListe = stvoriElementListe();
	pozicija headDrugeListe = stvoriElementListe();
	pozicija unija = stvoriElementListe();
	pozicija presjek = stvoriElementListe();
	char imeDatoteke[MAX_NAME];

	printf("Unesite ime datoteke iz koje zelite ucitati prvu listu:");
	scanf("%s", imeDatoteke);
	unosiSortirajuci(headPrveListe, imeDatoteke);


	printf("Unesite ime datoteke iz koje zelite ucitati drugu listu:");
	scanf("%s", imeDatoteke);
	unosiSortirajuci(headDrugeListe, imeDatoteke);

	unija = napraviUnijuListi(headPrveListe, headDrugeListe);
	presjek = presjekListi(headPrveListe, headDrugeListe);
	ispisListe(headPrveListe);
	ispisListe(headDrugeListe);
	ispisListe(unija);
	ispisListe(presjek);

	scanf("%s", imeDatoteke);
	return 0;
}