#include <stdio.h>

struct nodoA
{
	int dato;
	struct nodoA *izq, *der;
};

struct nodoA *crearNodo (int valor)
{
	nodoA *aux = (struct nodoA*) malloc (sizeof(nodoA));
	aux->dato= valor;
	aux->izq = aux->der = NULL;
	return aux;
};

//funcion insertar
void insertar (raiz, dato)
{
	//si el arbol esta vacio, el nodo insertado sera la raiz
	if (raiz==NULL)
	{
		raiz=crearNodo(dato);
		return raiz;
	}
	//falta
	if (aux->izq == NULL)
	{
		aux->izq= crearNodo(dato);
	}
	else //cambios
	{
		//lo mismo, pero a la derecha
	}
}

//insersion, busqueda y borrado

/*
	¿que es lo que debemos contamplar?
	Compara el elemento a insertar con la raiz, si es mayor, me voy a la derecha, si es menor, me voy a la izquierda.
	repetir lo anterior, hasta econtrar el lugar donde se debe insertar el nuevo nodo.
	
*/
void buscar(struct arbol *raiz, int num, int nivel, int padre, struct arbol *padreNodo) {
    if (arbol_seco(raiz)) {
        printf("No ha crecido el arbol\n");
        return;
    }
    if (num < raiz->dato) {
        buscar(raiz->izq, num, nivel + 1, raiz->dato, raiz);
    } else if (num > raiz->dato) {
        buscar(raiz->der, num, nivel + 1, raiz->dato, raiz);
    } else {
        printf("Encontrado: %d\n", num);
        printf("Nivel: %d\n", nivel);
        if (padre == -1) {
            printf("Es la raíz del árbol\n");
        } else {
            printf("Padre: %d\n", padre);
        }
        
        // Comprobar si tiene hermanos
        if (padreNodo != NULL) {
            if ((padreNodo->izq != NULL && padreNodo->izq->dato != num) || 
                (padreNodo->der != NULL && padreNodo->der->dato != num)) {
                printf("Tiene hermanos\n");
            } else {
                printf("No tiene hermanos\n");
            }
        } else {
            printf("No tiene hermanos\n");
        }
    }
}