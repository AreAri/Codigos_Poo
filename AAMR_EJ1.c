/* Areli Arisai Meza Rendon - AreAri
	RETO:
		Al codigo de listas se le deben agregar:
			- Invertir la lista
			- Ordenarla de forma ascendente y descendente
			- Eliminar los nodos repetidos
*/
#include <stdio.h>
#include <stdlib.h>

struct nodo
{
    int dato;
    struct nodo *link;
};

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
void ordenar (struct nodo **head, int ord);
//eliminar dobles
//void eliminar_parejas(struct nodo **head);
//eliminar dobles con recursion
int eliminar_parejas(struct nodo **head);
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
    if (nuevo == NULL) 
    {
		printf("Error al asignar memoria para el nuevo nodo\n");    	
		return NULL;
  	}
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
    struct nodo *ant = NULL; //ant que es anterior toma valor de NULL y nos servira para tener un registro, este esta antes de head
  	struct nodo *act = *head; //act que es actual toma el valor de head sin modificarlo y recorrer la lista sin problema (una copia de la lista)

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
    /*
    A lo que entendi mi lista es: 0 - 4 - 5 - 1
    al empezar          2do recorrido   3er recorrido     4to recorrido     ultimo
    head= 0 = actual    anterior = 0    anterior = 4      anterior = 5      anterior =1       
    anterior = null     actual = 4      actual = 5        actual = 1        actual = null =anterio
    sig = 4             sig = 5         sig = 1           sig = null
    */
  }
  *head = anterior;
}
//ordenar
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

//eliminar duplicados
/*void eliminar_parejas(struct nodo **head) 
{
    if (*head == NULL || (*head)->link == NULL) 
    {
        return;
    }
    struct nodo *actual = *head;
    struct nodo *anterior = NULL;
    struct nodo *repetido;
    while (actual != NULL) 
    {
        repetido = actual;
        while (repetido->link != NULL) 
        {
            if (actual->dato == repetido->link->dato) 
            {
                struct nodo *temp = repetido->link;
                repetido->link = repetido->link->link;
                free(temp);
            } 
            else 
            {
                repetido = repetido->link;
            }
        }
        anterior = actual;
        actual = actual->link;
	}
}*/
//eliminar dobles con recursion
int eliminar_parejas(struct nodo **head) 
{
    if (*head == NULL || (*head)->link == NULL) 
    {
        return 0;
    }
    struct nodo *actual = *head;
    struct nodo *temp = NULL;
    int repetido = actual->dato;
    while (actual ->link) 
    {
    	if (actual->link->dato==repetido)
    	{
    		temp = actual->link;
            actual->link = temp->link;
            free(temp);
    	}
    	 else
        {
            actual = actual->link;
        }
    }
    if (!(*head)->link)
    {
        return 1;
    }

    return eliminar_parejas(&(*head)->link);   
}

/*
	El codigo me genero muchos problemas, aveces funcionaba, aveces no (y eso que no le movia a nada mas), me marcaba warning....
	solo espero que si funcione esta vez como me funciona a mi 
*/