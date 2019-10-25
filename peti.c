#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct _list{
	int n;
	struct _list* next;
} list;

typedef list* pok;


int UnosiSort(pok p, char* file)
{
	pok q, poc = p;
	int n;
	FILE* f = fopen(file, "r");
	if (f == NULL) 
	{ 
		printf("Greška kod otvaranja filea");
		return -1;
	}
	else
	{
		while (!(feof(f)))
		{
			fscanf(f, "%d", &n);

			if (p->next == NULL)
			{
				q = (pok)malloc(sizeof(list));
				q->n = n;
				q->next = NULL;
				p->next = q;
			}
			else
			{
				while (p->next != NULL && n > p->next->n)
					p = p->next;

				if (p->next != NULL && n == p->next->n)
					p = poc;

				else
				{
					q = (pok)malloc(sizeof(list));

					q->n = n;
					q->next = p->next;
					p->next = q;

					p = poc;
				}
			}
		}
	}

	return 0;
}

int unijaListi(pok prva, pok druga)
{
	pok u,q;
	u = (pok)malloc(sizeof(list));
	u->next = NULL;

	while (prva->next != NULL)
	{
		q = (pok)malloc(sizeof(list));
		q->n = prva->n;
		u->next = q;
		q->next = NULL;

		prva = prva->next;
		u = u->next;
	}

	while (druga->next != NULL)
	{
		while (u->next != NULL && druga->next->n > u->next->n)//trazimo misto u koje pase element druge liste(izmedu veceg i manjeg iz prve)
		{
			u = u->next;
		}
		if (u->next != NULL && druga->next == u->next->n)
		{
			druga = druga->next;
		}
		else
		{
			q = (pok)malloc(sizeof(list));
			q->n = druga->next->n;
			q->next = u->next;
			u->next = q;
		}

	}
}


int main()
{

}
