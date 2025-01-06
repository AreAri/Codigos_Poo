/*Areli Arisai Meza Rendon - AreAri
    Reto:
        - Ordenar la lista (ascendente y descenente)
        - Invertir la lista
        - Eliminar duplicados
*/
#include <stdio.h>
#include <stdlib.h>

// Definiendo estructura
struct nodo
{
    // Para almacenar la informacion
    int dato;
    // Para almacenar la direccion del siguiente nodo
    struct nodo *link;
};

// Prototipos de funciones
//crear un nodo
struct nodo *crear_nodo(int datos);
//imprimir lista
void print_lista(struct nodo *head);
//agregar nodo al principio por default
void agregar(struct nodo **head, int datos);
// agregar nodo al final
void agregar_final(struct nodo **head, int datos);
//eliminar nodo segun se indique
void eliminar_posicion(struct nodo **head, int posicion);

int main(int argc, char const *argv[])
{
    struct nodo *head = NULL;
    // Agregar nodos
    agregar(&head, 3);
    agregar(&head, 2);
    agregar(&head, 1);
    agregar(&head, 0);
    printf("Si se agregara un nodo comun:");
    print_lista(head);

    // Agregar al final
    agregar_final(&head, 4);
    printf("\nSi se aplica para agregar al final:");
    print_lista(head);

    /*eliminar_posicion(&head, 3);
    printf("\nCon el nodo eliminado por posición:");
    print_lista(head);*/
    int posicion;
    printf("Introduzca la posición del nodo a eliminar: ");
    scanf("%d", &posicion);
    eliminar_posicion(&head, posicion);
    print_lista(head);
    // Liberamos memoria
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
    int contador=0;
    struct nodo *aux = head;
    for (aux=head; aux != NULL; aux=aux->link)
    {
        contador ++;
        printf("Elemento %d: %d\n",contador, aux->dato);
    }
}

void agregar(struct nodo **head, int datos)
{
    //se crea un nuevo nodo con crear_nodo
    struct nodo *nuevo = crear_nodo(datos);
    //apunto al nodo que se encuentra al inicio de la fila
    nuevo->link = *head;
    //actualiza el valor con el nuevo nodo
    *head = nuevo;
}

void agregar_final(struct nodo **head, int datos) //doble apuntador para agarrar y no perder el camino
{
    struct nodo *nuevo = crear_nodo(datos);
    //verificar lista vacia
    if (*head == NULL)
    {
        *head = nuevo;
        return;
    }
    //Recorrer la lista y encontrar el final
    struct nodo *reco = *head; //reco es el que se encarga se hacer el recorrido y encontrar el nodo final 
    while (reco->link != NULL)
    {
        reco = reco->link;
    }
    reco->link = nuevo;
    /*for (reco=*head; reco!=NULL; reco=reco->link)//HEAD lleva el * ya que es un doble apuntador
    {

    }   */ 
}

void eliminar_posicion(struct nodo **head, int posicion)
{
    //verifica si la lista esta vacia
    if (*head == NULL)
    {
        printf("La lista está vacía.\n");
        return;
    }
    //posicion permitira saber cual es el nodo que queremos sacar (el nodo en la posicion 0)
    if (posicion == 0) 
    {
        //aqui solo se elimina el nodo que este en la posicion 0
    	*head = (*head)->link;//head avanza al siguiente nodo
  		free(*head);
  		return;
	}
    //a lo que entendi
	struct nodo *ant = NULL; //ant que es anterior toma valor de NULL y nos servira para tener un registro, este esta antes de head
  	struct nodo *act = *head; //act que es actual toma el valor de head sin modificarlo y recorrer la lista sin problema (una copia de la lista)

    //empieza el recorrido sin fin?
    for (int i = 0; i < posicion && act != NULL; i++) //dependiendo de que valor tenga posicion es como se efectuara el ciclo para poder eliminar el nodo correcto
    {
  		ant = act; //el valor anterior toma el valor actual del puntero durante los recorridos
  		act = act->link; //actual avanza al sig nodo
	}

    if (act != NULL)
    {
        ant->link = act->link;
    }
    else
    {
        printf("Posición %d fuera de rango\n", posicion);
    }
    free(act);
}