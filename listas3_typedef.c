/*con typedef*/
#include <stdio.h>
#include <stdlib.h>
// prototipos de función no se utilizan
//definiendo el registro para las nodos de la lista
typedef struct nodo
{
	//para alamacenar la info
	int dato;
	//para almacenar la información del sig nodo
	struct nodo *link;
}apodo;

//crear un nuevo nodo
apodo *crear_nodo(int datos)
{
	//asignar memoria al nuevo nodo
	apodo *nuevo =(apodo *)malloc(sizeof(apodo));
	//falta verificar que tengamos memoria
	//alamcenar datos en el miembro dato del nodo
	nuevo->dato=datos;
	//inicializar link a nulo
	nuevo->link=NULL;
	//regrese el apuntador al nuevo nodo
	return nuevo;
}

//imprimir lista
void print_lista(apodo *head)
{
	/*para recorrer la lista de principio a fin usaremos aux para avanzar hasta que el siguiente nodo sea igual a NULO*/
	puts(" ");
	apodo *aux=head;
	while(aux !=NULL)
	{
		printf("Elemento: %d\n", aux->dato);
		aux=aux->link;
	}
	//para recorrer la lista
	/*for (aux=head; aux != NULL; aux=aux->link)
	{
		printf("Elemento: %d\n", aux->dato);
	}*/
}

//agregar
void agregar(apodo **head, int datos)
{
	/* La funcion agregar lleva un doble apuntador, porque?
		porque necesita modificar el valor de head dentro de la función.
		Necesitamos el doble apuntador para actualizar el head, la razon es que head ya es un apuntador a un nodo, entonces para cambiae el valor
		al que head apunta, se necesita un apuntador head.
		el primer * nos permite acceder al valor al que apunta head
		el segundo * nos permite modificar el valor al que apunta head

		antes de agregar
		head-> nodo1;

		despues de agregar
		heat ->nuevo_nodo->nodo1;
	*/
	//crar un nuevo nodo, usando la funcion crear_nodo
	apodo *nuevo=crear_nodo(datos);
	//apuntando al head actual, es decir al nodo que se encuentra actualmente al inicio de la fila
	nuevo->link=*head;
	//actualizar el valor del head que apunte al nuevo nodo
	*head =nuevo;
}

int main(int argc, char const *argv[])
{
	//declarar elapuntador inicial
	apodo *head=NULL;
	//agregar nodo
	agregar(&head,2);
	agregar(&head,1);
	return 0;
}