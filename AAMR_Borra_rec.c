#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo
{
	float e;
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

int mete_p(struct nodo **p, float e)
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

/*void imprimir_p(struct nodo **p)
{
	if (es_vacia(*p))
	{
		puts("No hay elementos, pila vacia T-T");
	}

	//para ir sacando datos con pop
	struct nodo *aux = pop(p);
	struct nodo *paux= NULL; 

	puts("\nLIFO (casa propia)");
	while(aux !=NULL)//corre a los elementos
	{
		printf("%.2f\n",aux->e );
		push (&paux, aux);
		aux= pop(p);
	}
	aux=pop(&paux);

	puts("\nConstruir de nuevo la pila (casa ajena)");
	while(aux !=NULL) //el otro while que los regresa a su casa
	{
		printf("%.2f\n",aux->e );
		paux= pop(&aux);
		push(p,paux);
	}
}*/

void imprimir_rec(struct nodo **p)
{
	if (es_vacia(*p))
	{
		puts("No hay elementos, pila vacia T-T");
		return;
	}

	struct nodo *aux = pop(p);
	printf("%.2f\n",aux->e);
	imprimir_rec(p);
	
	push(p,aux);
	printf("%.2f\n",aux->e);
}


//no es optima para una pila, porque no usara ni push ni pop
//aqui la tratamos como una lista, pila insultada
/*void borrar_p(struct nodo **p)
{
	struct nodo *nuevo;
	if (es_vacia(*p))
	{
		return;
	}
	nuevo =*p;
	*p=nuevo->sig;
	free(nuevo);
}*/

void borrar_p(struct nodo **p, float dato) 
{
	struct nodo *aux = NULL;
    struct nodo *nuevo;
    bool eureka=false;

    if (es_vacia(*p)) 
    {
        puts("pila está vacía.");
        return;
    }

    // Buscamos el dato en la pila original para elimiarlo
    while (*p != NULL) 
    {
        nuevo = pop(p); //pop para agarrar el dato
        if (nuevo->e == dato) //se comparan
        {
            free(nuevo); // Liberamos la memoria del nodo que contiene el dato
            eureka=true;
        } 
        else 
        {
            push(&aux, nuevo); // los que no coinciden se pasan a la pila auxiliar
        }
    }

    // devolvemos elementos de la pila auxiliar a la pila original
    while (aux != NULL) //hasta que quede vacia
    {
        nuevo = pop(&aux); //tomamos el dato
        push(p, nuevo); //lo regresamos a su lugar de origen 
    }

     if (!eureka) // Si el dato no se encontró en la pila
    {
        printf("El elemento %.2f no existe en la pila.\n", dato);
    }

}

void borrar_p_recursivo(struct nodo **p, float dato, bool eureka = false)
{
    struct nodo *aux = NULL;
    struct nodo *nuevo;
   
    if (es_vacia(*p))
    {
        puts("pila está vacía.");
        return;
    }

    nuevo = pop(p); //pop para agarrar el dato
    if (nuevo->e == dato) //se comparan
    {
        free(nuevo); // Liberamos la memoria del nodo que contiene el dato
        eureka = true;
    }
    else
    {
        push(&aux, nuevo); // los que no coinciden se pasan a la pila auxiliar
        borrar_p_recursivo(p, dato); // Llamada recursiva para seguir buscando el dato
    }

    // devolvemos elementos de la pila auxiliar a la pila original
    while (aux != NULL) //hasta que quede vacia
    {
        nuevo = pop(&aux); //tomamos el dato
        push(p, nuevo); //lo regresamos a su lugar de origen
    }

   
}

int main(int argc, char const *argv[])
{
	struct nodo *p = NULL;
	mete_p(&p,3.4);
	mete_p(&p,5.5);
	mete_p(&p,6.6);
	mete_p(&p,9.03);
	//mete_p(&p, 13.5);
	//mete_p(&p,1.5);
	puts("Pila original");
//	imprimir_p(&p);

	puts("\n~~~~Pila borrada~~~~");

	//borrar_p(&p, 5.5);
	borrar_p_recursivo(&p,6.6);
	//imprimir_p(&p);

	puts("Imprimiendo con recursion");
	imprimir_rec(&p);
	return 0;
}