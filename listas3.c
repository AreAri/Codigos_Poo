/*Sin tyoedef*/
/*Agregar_final()
	insertar un nodo al final de la lista
	eliminar();
	posicion del nodo
*/

//Librerias
#include <stdio.h>
#include <stdlib.h>

// Definiendo el registro o estructura
struct nodo
{
    // Para almacenar la informacion
    int dato;
    // Para almacenar la direccion del siguiente nodo
    struct nodo *link;
};

// Prototipos de funciones
struct nodo *crear_nodo(int datos);
void print_lista(struct nodo *head);
void agregar(struct nodo **head, int datos);
void agregar_final(struct nodo **head, int datos);
void eliminar_posicion(struct nodo **head, int posicion);

//el main
int main(int argc, char const *argv[])
{
    struct nodo *head = NULL;
    // Agregar nodos
    agregar(&head, 3);
    agregar(&head, 2);
    agregar(&head, 1);
    agregar(&head, 0);
    print_lista(head);

    // Agregar al final
    agregar_final(&head, 4);
    printf("\nDespués de agregar al final:\n");
    print_lista(head);

    // Eliminar por posición por usuario (o sin lectura)
    /*int posicion;
    printf("\nDigite la posición a eliminar del nodo: ");
    scanf("%d", &posicion);*/

    eliminar_posicion(&head, 3);
    printf("\nDespués de eliminar por posición:\n");
    print_lista(head);


    // Liberar memoria
    struct nodo *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->link;
        free(temp);
    }
    return 0;
}

struct nodo *crear_nodo(int datos)
{
    // Asignar memoria al nuevo nodo
    struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo));

    // Almacenar datos en el miembro dato del nodo
    nuevo->dato = datos;
    // Inicializar link a nulo
    nuevo->link = NULL;
    return nuevo;
}

void print_lista(struct nodo *head)
{
    puts("");
    struct nodo *aux = head;
    while (aux != NULL)
    {
        printf("Elemento: %d\n", aux->dato);
        aux = aux->link;
    }
}

void agregar(struct nodo **head, int datos)
{
    struct nodo *nuevo = crear_nodo(datos);
    nuevo->link = *head;
    *head = nuevo;
}

void agregar_final(struct nodo **head, int datos) //doble apuntador para agarrar y no perder con el que
{
    struct nodo *nuevo = crear_nodo(datos);
    //verificar lista vacia
    if (*head == NULL)
    {
        *head = nuevo;
        return;
    }
    //Recorre para ponerlo al final
    struct nodo *reco = *head; //reco es el que se encarga se hacer el recorrido y encontrar el nodo final 
    /*while (reco->link != NULL)
    {
        reco = reco->link;
    }
    reco->link = nuevo;*/
    for (reco=*head; reco!=NULL; reco=reco->link)//HEAD lleva el * ya que es un doble apuntador
    {

    }    
}

void eliminar_posicion(struct nodo **head, int posicion)
{
    //Por si no hay nada
    if (*head == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }

    //Si es la primera posicion (osea la cabeza)
    /*if (posicion == 0)
    {
        struct nodo *temp = *head;
        *head = (*head)->link;
        free(temp);
        return;
    }
    struct nodo *anterior = NULL;
    struct nodo *actual = *head;*/

    if (posicion == 0) 
    {
    	*head = (*head)->link;
  		free(*head);
  		return;
	}
	struct nodo *anterior = NULL;
  	struct nodo *actual = *head;

    //Recorre hasta encontrarlo y quitarlo
    /*int i = 0;
    while (actual != NULL && i < posicion)
    {
        anterior = actual;
        actual = actual->link;
        i++;
    }*/
    for (int i = 0; i < posicion; i++) 
    {
  		anterior = actual;
  		actual = actual->link;
	}


    //Si pone un numero que nada que ver
    /*if (actual == NULL)
    {
        printf("Posición fuera de rango.\n");
        return;
    }*/
    anterior->link = actual->link;
    free(actual);
}
