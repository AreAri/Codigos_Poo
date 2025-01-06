#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aun no lo voltea

struct nodo
{
	char *e;
	struct nodo *sig;
};

int es_vacia(struct nodo *p)
{
	return p==NULL;
}

int push(struct nodo **p, struct nodo *elemento)
{
	elemento->sig= *p;
	*p=elemento;
	return 1;
}

int mete_p(struct nodo **p, char *e)
{
	struct nodo *nuevo;
	nuevo=(struct nodo *)malloc(sizeof(struct nodo));
	if (!nuevo)
	{
		return 0;
	}
	nuevo->e= e;
	nuevo->sig= NULL;

	return push(p,nuevo);
}

struct nodo *pop(struct nodo **p)
{
	if (es_vacia(*p))
	{
		//puts("Estas intentando hacer pop en una pila vacia");
		return NULL;
	}

	struct nodo *aux=*p;
	*p=(*p)->sig;
	return aux;
}

void imprimir_rec(struct nodo **p)
{
	if (es_vacia(*p))
	{
		puts("");
		//puts("\nNo hay elementos, pila vacia T-T");
		return;
	}

	struct nodo *aux = pop(p);
	printf("%c",*aux->e);
	imprimir_rec(p);
	
	push(p,aux);
	printf("%c",*aux->e);
}

void separar(struct nodo **p,char *e)
{
	int t = strlen(e);
	for (int i = 0; i < t; ++i)
	{
		mete_p(p,&e[i]);

	}
}


int main(int argc, char const *argv[])
{
	struct nodo *p = NULL;
	//mete_p(&p,"hipopotamo");
	separar(&p,"hipopotamo");
	imprimir_rec(&p);
	return 0;
}