#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

#define MAX_NAREDBA 5
#define MAX_NAZIV 32

typedef struct _CvorStabla * stablo;
typedef struct _CvorStog * pok;

typedef struct _CvorStabla {
	char* NazivElementa;
	stablo Dijete;
	stablo Jednako;
} CvorStabla;

typedef struct _CvorStog {
	stablo pokNaStablo;
	pok next;
} CvorStoga;



int dodajDirektorij( char*  onajKojegDodajemo, stablo S)
{

		stablo noviDir = (stablo)malloc(sizeof(CvorStabla));

		noviDir->Dijete = NULL;
		noviDir->Jednako = NULL;

		stablo dijeteElementDirektorija = S->Dijete;

		noviDir->NazivElementa = (char *)malloc(strlen(onajKojegDodajemo) + 1);

		strcpy(noviDir->NazivElementa, onajKojegDodajemo);


		if (S->Dijete == NULL)
		{
			S->Dijete = noviDir;
		}
		else {
			noviDir->Jednako = dijeteElementDirektorija;
			S->Dijete = noviDir;

		}

	return 1;
}

stablo minjajDirektorij(stablo trenutniPolozaj, pok mjesto, char* premjestamoSeUOvajDir)
{
	stablo trazeniDirektorij = trenutniPolozaj->Dijete;

	while (trazeniDirektorij != NULL && strcmp(trazeniDirektorij->NazivElementa, premjestamoSeUOvajDir) != 0)
	{
		trazeniDirektorij = trazeniDirektorij->Jednako;
	}

	if (trazeniDirektorij == NULL)
	{
		printf("The system cannot find the path specified.\n");
		return trenutniPolozaj;
	}

	push(mjesto,trenutniPolozaj);

	return trazeniDirektorij;
}

int listaDirektorija(stablo s)
{
	int i = 0;
	stablo x = s->Dijete;


	printf("\n");
	while (x != NULL)
	{
		printf("\t\t%s\n", x->NazivElementa);
		x = x->Jednako;
		i++;
	}

	printf("\t\t\t\t%d DIR(s)\n", i);
	return 1;
}

pok stvoriElementStoga()
{
	pok stvoreniElement = (pok)malloc(sizeof(CvorStoga));
	stablo novoStablo = (stablo)malloc(sizeof(CvorStabla));
	novoStablo->Dijete = NULL;
	novoStablo->Jednako = NULL;
	if (stvoreniElement == NULL || novoStablo == NULL)
	{
		printf("Greska u funkciji stvoriElementStoga.\n");
		return NULL;
	}
	else
	{   
		stvoreniElement->pokNaStablo = novoStablo;
		stvoreniElement->next = NULL;
		return stvoreniElement;
	}
}

char* odrediPolozaj(pok mjesto) {
	char a[100];
	strcpy(a, "C:Strukture");

	while (mjesto->next != NULL)
	{
		strcat(a, "\\");
		strcat(a, mjesto->pokNaStablo->Dijete->NazivElementa);

		mjesto = mjesto->next;

	}

	return a;
};

int push(pok mjesto, stablo direktorij)
{
	pok dir = stvoriElementStoga();

	dir->pokNaStablo = direktorij;
	dir->next = mjesto->next;
	mjesto->next = dir;

	return 0;
}

stablo pop(pok mjesto)
{
	pok smece = mjesto->next;

	if (smece->next != NULL) {
		mjesto->next = smece->next;
	}
	return smece->pokNaStablo;
}

int odabirFunkcije( stablo direktorij, pok mjesto) {
	 
	int i = 9, el = 0;
	char naredba[MAX_NAREDBA], naziv[MAX_NAZIV],pol[100];
	char *c = (char *)malloc(100*sizeof(char));
	printf("\n\n");

	while (i != 0)
	{

		c = odrediPolozaj(mjesto);
		strcpy(pol, c);

		printf("%s>", pol);
		scanf("%s", naredba);
		if (strcmp(naredba, "dir") == 0) {

			i = listaDirektorija(direktorij);

		}
		else if (strcmp(naredba, "exit") == 0)
		{
			return 0;
		}
		else if (strcmp(naredba, "help") == 0)
		{

			printf("\ncd\t\tDisplays the name of or changes the current directory.\ncls\t\tclears the screen.\ndir\t\tDisplays a list of subdirectories in a directory.\nexit\t\tQuits the strukture program (command interpreter)\nhelp\t\tProvides Help information for Windows commands.\nmd\t\tCreates a directory.\nstart\t\tStarts a new window instance of program.\n");
			i = 1;
		}
		else if (strcmp(naredba, "start") == 0)
		{
			ShellExecute(NULL, "open", "C:\\Users\\Ivan\\source\\repos\\Project4\\Debug\\Project4.exe", NULL, NULL, SW_SHOWDEFAULT);//Da radi triba prominit sa svojim pathom
			i = 1;
		}
		else if (strcmp(naredba, "cls") == 0)
		{
			system("cls");
			i = 1;
		}
		else if (strcmp(naredba, "md") != 0 && strcmp(naredba, "cd") != 0 && strcmp(naredba, "git") != 0)
		{
			i = 11;
		}
		else {
			scanf("%s", naziv);
		}


		if (strcmp(naredba, "md") == 0)
		{
			i = dodajDirektorij(naziv, direktorij);
		}
		else if (strcmp(naredba, "cd") == 0) {

			if (strcmp(naziv, "..") == 0) {
				direktorij = pop(mjesto);
			}
			else {
				direktorij = minjajDirektorij(direktorij, mjesto, naziv);
			}
			i = 1;

		}
		else if (strcmp(naredba, "git") == 0 && strcmp(naziv, "gud") == 0) {

			ShellExecute(NULL, "open", "https://github.com/gitgudfesb/StrukturePodataka", NULL, NULL, SW_SHOWNORMAL);
			i = 1;

		}
		 if (i == 11) {
			 printf("'%s' is not recognized as an internal or external command\n\n", naredba);
		}

		 printf("\n");
	}

	
	return 0;
}

int main()
{


	stablo Korijen = (stablo)malloc(sizeof(CvorStabla));
	pok pocetnoMijesto = stvoriElementStoga();
	Korijen->Dijete = NULL;
	Korijen->Jednako = NULL;
	Korijen->NazivElementa = NULL;
	stablo trenutno = Korijen;

	pocetnoMijesto->pokNaStablo = Korijen;
	pocetnoMijesto->next = NULL;

	int i = 9;

	odabirFunkcije(trenutno, pocetnoMijesto);



	return 0;
}