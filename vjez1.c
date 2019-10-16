#define _CRT_SECURE_NO_WARNINGS
#define MAX_IME 50
#define MAX_REDAK 150
#include <stdio.h>
#include <stdlib.h>

typedef struct _student
{
	char ime[MAX_IME];
	char prezime[MAX_IME];
	int brBodovi;

} studenti;

int kolikoRedaka(char *);
studenti* unos(int, char *);
int ispis(studenti *, int);
int maks(studenti *, int);

int main() {

	int brRed = 0, max = 0;
	brRed = kolikoRedaka("studenti.txt");
	//rewind("studenti.txt");
	ispis(unos(brRed, "studenti.txt"), brRed);

	getchar();

	return 0;
}

int kolikoRedaka(char* f)
{
	int brojRedaka = 0;
	char c[MAX_REDAK];
	FILE* fl = fopen(f, "r");

	while (!feof(fl)) 
	{
		fgets(c, MAX_REDAK, fl);
		if (strlen(c) > 1)
		{
			brojRedaka++;
		}
		strcpy(c, "");

	}
	fclose(fl);

	return brojRedaka;
}

studenti* unos(int i, char* f)
{
	int j = 0, t = 0;
	studenti* st = (studenti*)malloc(i * sizeof(studenti));
	FILE* fl = fopen(f, "r");

	for (j = 0; j < i; j++) {
		fscanf(fl, "%d %s %s", &st[j].brBodovi, st[j].ime, st[j].prezime);
	}
	fclose(fl);
	return st;
}
int ispis(studenti* st, int i)
{
	int j = 0;
	int maxValue = maks(st, i);
	for (j = 0; j < i; j++)
		printf("%d %s %s %.2f\n", st[j].brBodovi, st[j].ime, st[j].prezime, (float)st[j].brBodovi / maxValue * 100);

	return 0;
}

int maks(studenti * stu, int re)
{
	int max = 0, i = 0;

	for (i = 0; i < re; i++)
		if (stu[i].brBodovi > max)
			max = stu[i].brBodovi;

	return max;
}
