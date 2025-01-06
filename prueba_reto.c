#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

//la estructuta
struct nodo
{
    // Para almacenar la informacion
    int dato;
    // Para almacenar la direccion del siguiente nodo
    struct nodo *link;
};

//Prototipoc ya completos
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
//prototipos del reto
//invertir la lista
void invertir(struct nodo **head);
// ordenar
//void ordenar(struct nodo **head, bool fin);
void ordenar (struct nodo **head, int ord);
//eliminar dobles
void eliminar_parejas(struct nodo **head);
//menu
void menu ();

int main(int argc, char const *argv[])
{
	int op = 0, an=0, anf=0, pos, ord=0;
	struct nodo *head =  NULL;
	do
	{
		system ("cls || clear");
		print_lista(head);
		menu();
		printf("Ingrese una opcion: ");
		scanf("%d",&op);
		//extenso menu de opciones
		switch(op)
		{
			case 1:
				system ("cls || clear");
				printf("Agregar nodos\n");
				printf("Ingrese el valor del nodo: ");
				scanf("%d",&an);
				agregar(&head,an);
				break;
			case 2:
				system ("cls || clear");
				printf("Agregar nodos al final de lista\n");
				printf("Ingrese el valor del nodo: ");
				scanf("%d",&anf);
				agregar_final(&head,anf);
				break;
			case 3:
				printf("\nIngrese la posicion del nodo a eliminar: ");
				scanf("%d",&pos);
				eliminar_posicion(&head, pos);
				break;
			case 4:
				printf("\nInvertiendo Lista....\n");
				invertir(&head);
				break;
			case 5: 
				system ("cls || clear");
				printf("Ordenar lista\n");
				printf("Como deseas ordenar la lista?\n");
				printf("1.- Ascendente\n");
				printf("2.- Descendente\n");
				printf("Ingrese su opcion: ");
				scanf("%d",&ord);
				if(ord==1)
				{
					ordenar(&head, ord);
					//ordenar(&head, true);
				}
				else if (ord==2)
				{
					ordenar(&head,ord);
				}
				else if (ord!=1 || ord!=2)
				{
					printf("Opcion equivocada\n");
				}
				break;
			case 6:
				printf("\nEliminando duplicados.....\n");
				eliminar_parejas(&head);
				break;
			case 0:
				printf("Sayonara....\n");
				break;
			default:
				printf("Opcion incorrecta, verifica tus opciones\n");
				break;
		}

	}while(op!=0);

	//no olvidemos liberar memoria
	struct nodo *temporal;
    while (head != NULL)
    {
        temporal = head;
        head = head->link;
        free(temporal);
    }

	return 0;
}

void menu ()
{
	printf("~~~~~~ MENU ~~~~~~\n");
	printf("1.- Agregar nodos\n");
	printf("2.- Agregar nodos al final\n");
	printf("3.- Eliminar por posicion\n");
	printf("4.- Invertir listas\n");
	printf("5.- Ordenar lista\n");
	printf("6.- Eliminar duplicados\n");
	printf("0.- Salir\n");
}

//creamos nuestro nodo
struct nodo *crear_nodo(int datos)
{
    struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo)); // Asignar memoria al nuevo nodo
    nuevo->dato = datos;// Almacenar datos en el miembro dato del nodo
    nuevo->link = NULL;
    return nuevo;
}

//imprimimos lista
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

//agregar nodos
void agregar(struct nodo **head, int datos)
{
    struct nodo *nuevo = crear_nodo(datos); //se crea un nuevo nodo con crear_nodo
    nuevo->link = *head; //apunto al nodo que se encuentra al inicio de la fila
    *head = nuevo; //actualiza el valor con el nuevo nodo
}

//agregar nodos pero al final
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
}

//eliminar por pocicion
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

//invertir hecerlo recursivo
void invertir(struct nodo **head) 
{
  struct nodo *anterior = NULL;//el nodo antes
  struct nodo *actual = *head; //donde esta posicionado actualemente
  struct nodo *sig; //para el nodo que sigue
  while (actual != NULL) //si actual no es nulo debera hacer el recorrido ya que si hay datos en lista
  {
    sig = actual->link;
    actual->link = anterior;
    anterior = actual;
    actual = sig;
  }
  *head = anterior;
}

void ordenar(struct nodo **head, int ord)
{ //este si los ordena de una.. hacerlo a papel si funciono 
	struct nodo *actual = *head;
	struct nodo *despues;
	int temp;
	if (*head == NULL || (*head)->link == NULL) //verificar si la lista no esta vacia o si solo tiene 1 nodo
   	{
    	return;
  	}
	while (actual!=NULL) //actual al ser nulo significa que ya no hay datos
	{
		despues = actual->link;//despues toma siempre el valor del siguiente de actual
		while (despues!=NULL)//en base a lo de arriba este debe llegar primero al null
		{
			if (ord==1 && actual->dato > despues->dato)//si el dato de actual es mayor que el dato de despues
			{ 
				temp= despues ->dato; //temp toma el dato de despues para no perderlo
				despues->dato=actual->dato; //despues cambia con el dato de actual
				actual->dato = temp;//actual se convierte en el dato de despues que se guardo en temporal
			}
			else if (ord== 2 && actual->dato < despues->dato)
			{
				temp= despues ->dato;
				despues->dato=actual->dato;
				actual->dato = temp;
			}
			despues=despues->link;//termina el if y despues debe avanzar al siguiente
		}
		actual=actual->link;//actual tambien avanza
	}
}

//eliminar dobles
/*void eliminar_parejas(struct nodo **head) //	a lo que entendi... no elimina si los dobles estan alejados
{
  	if (*head == NULL || (*head)->link == NULL) //lista vacia o con un solo nodo
  	{
    	return; 
  	}
  	struct nodo *actual = *head;
  	struct nodo *anterior = NULL;
	while (actual != NULL) 
	{
    	struct nodo *sig = actual->link;
    	if (sig != NULL && actual->dato == sig->dato) //ver si no esta al final
    	{
    		// Elimina nodo duplicado 
      		if (anterior == NULL) 
      		{
        		*head = sig->link;
      		} 
      		else 
      		{
        		anterior->link = sig->link;
      		}
      		free(actual->link);
    	} 
    	else 
    	{
      		anterior = actual;//avanza si no hay nodos iguales
    	}
    	actual = sig;
  	}
}*/
//se intento.... 
void eliminar_parejas(struct nodo **head) 
{ /*en esta parte en si no elimina por completo el dato, solo elimina los duplicados y se queda con 1, sin embargo ya elimina 
	a pesar de estar lejanos, aunque creo que eso debia hacer
	no se explicarlo con palabras asi que procedere a enviarle una imagen*/
	if (*head == NULL || (*head)->link == NULL) 
	{
	    return;
	}
	struct nodo *actual = *head;
	struct nodo *anterior = NULL;
	struct nodo *repetido;
	while (actual != NULL) 
	{
		repetido = actual->link; 
	    while (repetido != NULL) 
	    {
	      	if (actual->dato == repetido->dato) 
	      	{
				if (repetido == actual->link) 
				{
				    actual->link = repetido->link;
				} 
				else 
				{
					anterior->link = repetido->link;
				}
				free(repetido);
				repetido = actual->link;
			}
	    }
	    actual = actual->link;
	}
}
