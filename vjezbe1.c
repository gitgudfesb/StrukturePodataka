#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>



struct studenti
{
	char ime[15];
	char prezime[15];
	int brBodovi;

};

int main() {

	int i = 1, j = 0, t=0;
	char c;
	 struct studenti *s;


	FILE *f;
	f = fopen("Text.txt", "r");

	while ((c = fgetc(f)) != EOF) {

		if (c == '\n')
			i++;

	}
	
	s = (struct studenti *)malloc(i * sizeof(struct studenti));

	rewind(f);

	for (j = 0; j < i; j++) {
		fscanf(f, "%d %s %s", &s[j].brBodovi,s[j].ime, s[j].prezime);
		if (s[j].brBodovi > t) {
			t = s[j].brBodovi;
		}
	
	}

	for (j = 0; j < i; j++) {
		printf("%d %s %s %.2f \n", s[j].brBodovi, s[j].ime, s[j].prezime, ((float)s[j].brBodovi/t )* 100 );
		

	}


	getchar();
	return 0;
}
