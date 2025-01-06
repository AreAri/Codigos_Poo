/*
TEORÍA
Las colas, al igual que las pilas, almacenan los datos en un orden estricto.
Las colas son estructuras tipo FIFO (first in, first out)

Una cola es una estructura que alamcena datos o elmentos y permite acceder a ellos por uno de los extremos.
un elemento se inserta a la cola por la parte final y se elimina de la cola por la parte inicial, el frente.

1	2	3	4	5
^				^
frente			final
Los elementos se eliminan en el mismo orden en el que se almacenan.

En una cola los elementos se eliminan en el mismo orden en el que se insertaron, es decir, el primer elemento que se inserto en la
estructura, sera el primero en ser eliminado.

Las 2 operaciones básicas en una cola son:
 	-Insertar elementos, se hace por el final.
 	-Eliminar elementos, se hace por el frente.

Pensando algoritmicamente 

funcion insertar (¿Lista parametros?)

insertar (inicio, final, dato)
{
	si(verifique espacio)
	{
		final -> sig;
		nuevo <- dato: // asi?
	}
		verificar que el elemento se haya insertado.
			Frente <- deja de ser nulo 
	si no 
		Desbordamiento, es decir, la cola esta llena.
}

Struct elem_cola
{
	int dato; //miembro que va almacenar el dato que deseo ingresar
	struct elem_cola *sig;
};

struct cola
{
	elemento_cola *inicio;
	elemento_cola *final;
};

crear_cola (cola *colita)
{
	//crear cola vacia
	//tanto inicio como final apuntarán a null
}

insertar_cola(*colita, dato)
{
	añadir elemento a la cola
	Agregamos un nuevo nodo, este nuevo nodo es el siguiente del final, si y solo si la cola no esta vacia.

	Si esta vacia, inicio apuntará a este nuevo nodo.
}
*/

#include <stdio.h>
#include <stdlib.h>

//crear un nodo cola
struct elemento_cola
{
    int e;
    struct elemento_cola *sig;
};

//crea la estructura de la
struct cola
{
    struct elemento_cola *inicio;
    struct elemento_cola *final;
};

int es_vacia(struct elemento_cola *frente)
{
    return frente == NULL;
}

void crear_cola(struct cola *colita)
{
    colita->inicio = NULL;
    colita->final = NULL;
}

void insertar(struct cola *colita, int e)
{
    if (colita->inicio == NULL) {
        crear_cola(colita);
    }
    struct elemento_cola *nuevo = (struct elemento_cola *)malloc(sizeof(struct elemento_cola));
    if (!nuevo)
    {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    nuevo->e = e;
    nuevo->sig = NULL;
    if (es_vacia(colita->inicio))
    {
        colita->inicio = nuevo;
    }
    else
    {
        colita->final->sig = nuevo;
    }
    colita->final = nuevo;
}

int desencolar(struct cola *colita)
{
    if (es_vacia(colita->inicio))
    {
        printf("Error: Intentando desencolar de una cola vacía.\n");
        return 0;
    }
    struct elemento_cola *aux = colita->inicio;
    int valor = aux->e;
    colita->inicio = colita->inicio->sig;
    if (colita->inicio == NULL)
    {
        colita->final = NULL;
    }
    free(aux);
    return valor;
}

void imprimir_cola(struct cola *colita)
{
    if (es_vacia(colita->inicio))
    {
        printf("La cola está vacía.\n");
        return;
    }
    printf("Elementos en la cola:\n");
    struct elemento_cola *actual = colita->inicio;
    while (actual != NULL)
    {
        printf("%d\n", actual->e);
        actual = actual->sig;
    }
}

void libertad(struct cola *colita)
{
    struct elemento_cola *aux;
    while (colita->inicio != NULL)
    {
        aux = colita->inicio;
        colita->inicio = colita->inicio->sig;
        free(aux);
    }
    colita->final = NULL;
}

int main(int argc, char const *argv[])
{
    struct cola Cola;
    crear_cola(&Cola);

    insertar(&Cola, 4);
    insertar(&Cola, 3);
    insertar(&Cola, 2);
    insertar(&Cola, 1);

    imprimir_cola(&Cola);

    printf("Elemento eliminado: %d\n", desencolar(&Cola));

    imprimir_cola(&Cola);

    libertad(&Cola);

    return 0;
}