#include <stdio.h>
#include <stdlib.h>
struct nodo *crear_nodo(int datos);
//imprimir lista
void print_lista(struct nodo *head);
//agregar nodo al principio por default
void agregar(struct nodo **head, int datos);
int f (struct nodo *n1, struct nodo *n2);
struct nodo *decreciente (struct nodo **pl, int e);
/*
	if (z!=NULL) es lo mismo que if(z)
	if (z==NULL) es lo mismo que if(!z)
*/
struct nodo
{
    int *dato;
    struct nodo *link;
};
int main(int argc, char const *argv[])
{
	struct nodo *pl =NULL;

	agregar(&pl, 4);
	agregar(&pl, 20);

	print_lista(pl);
	return 0;
}

struct nodo *crear_nodo(int datos)
{
    struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo)); // Asignar memoria al nuevo nodo
    nuevo->dato = datos;// Almacenar datos en el miembro dato del nodo
    nuevo->link = NULL;
    return nuevo;
}
void print_lista(struct nodo *head)
{
    puts("");
    int num_nodo=0;
    struct nodo *aux = head;
    for (aux=head; aux != NULL; aux=aux->link)
    {
        num_nodo ++;
        printf("Elemento %d: %d\n",num_nodo, aux->dato);
    }
}
/*int f (struct nodo *n1, struct nodo *n2)
{
	if (n1==NULL && n2==NULL)
	{
		return 0
	}
	if (n1->dato > n2->dato)
	{
		return 1;
	}
}*/

int f (struct nodo *n1, struct nodo *n2)
{
	if (!(n1 && n2))
		return 0;
	return (n1->dato - n2->dato);
}

struct nodo *decreciente (struct nodo **pl, int e)
{
	struct nodo *nuevo=crear_nodo(e);
	struct nodo *ant =NULL;
	struct nodo *act=*pl;
	//es necesario
	/* nuevo->dato=e;
	nuevo->link=NULL;
	return nuevo;
	*/
	//if(*pl==NULL|| f(*pl,nuevo) >=0)
	if (!*pl || f(*pl,nuevo)>=0)
	{
		nuevo->link=*pl;
		*pl=nuevo;
		return nuevo;
	}

	while(act &&f(act,nuevo)<0)
	{
		ant=act;
		act=act->link;
	}
	nuevo->link=act;
	if (ant)//ant!=null
	{
		ant->link=nuevo;
	}
	return nuevo;
}