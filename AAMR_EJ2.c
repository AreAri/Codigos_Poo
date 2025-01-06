/* Areli Arisai Meza Rendon - AreAri
	Listas con pokemon
	1.- Abra - Kadabra - Alakazam - Mega-Alakazam
	2.- Charmander - Charmeleon - Charizard - Mega-Charizard
	3.- Bulbasaur - Ivysaur - Venusaur - Mega-Venusaur
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct nodo
{
    char *dato;
    struct nodo *link;
};

struct nodo *crear_nodo(char *datos);
void menu();
void listas();
void print_lista(struct nodo *head);
void agregar(struct nodo **head, char *datos);
void agregar_por_tipo(struct nodo **lista, char *tipo);
void eliminar(struct nodo **lista, int posicion);
void ordenar (struct nodo **head);
struct nodo *concatena(struct nodo *ps, struct nodo *fire, struct nodo *plant);
void buscar(struct nodo *head, char *busca);
void liberar_memoria(struct nodo *lista);

int main(int argc, char const *argv[])
{
    int op = 0, po = 0, pos=0;
    char pokemon[50];
    //definir las 3 listas
    struct nodo *psiquico = NULL; // abra- Kadabra - Alakazam - Mega-Alakazam
    struct nodo *fuego = NULL;     // Charmander - Charmeleon - Charizard - Mega-Charizard
    struct nodo *planta = NULL;    // Bulbasaur - Ivysaur - Venusaur - Mega-Venusaur
    struct nodo *conca = NULL; //todas
    do
    {
        //system("cls || clear");
        printf("\nPokemones tipo psiquico:");
        print_lista(psiquico);
        printf("\nPokemones tipo fuego:");
        print_lista(fuego);
        printf("\nPokemones tipo planta:");
        print_lista(planta);
        printf("\nLista concatenada:");
        print_lista(conca);
        menu();
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1: //agregar
            system("cls || clear");
            printf("Que tipo de pokemon desea agregar\n");
            listas();
            scanf("%d", &po);
            switch (po)
            {
            case 1:
                agregar_por_tipo(&psiquico, "psiquico");
                break;
            case 2:
                agregar_por_tipo(&fuego, "fuego");
                break;
            case 3:
                agregar_por_tipo(&planta, "planta");
                break;
            }
            break;
        case 2: //eliminar
        	system("cls || clear");
            printf("De que lista desea eliminar\n");
            listas();
            scanf("%d", &po);
            switch (po) 
            {
		    	case 1:
		    		print_lista(psiquico);
		    		printf("\nIngrese la posicion a eliminar: ");
					scanf("%d",&pos);
		      		eliminar(&psiquico, pos);
		      		break;
		    	case 2:
		    		print_lista(fuego);
		    		printf("\nIngrese la posicion del nodo a eliminar: ");
					scanf("%d",&pos);
		      		eliminar(&fuego, pos);
		      		break;
		    	case 3:
		    		print_lista(planta);
		    		printf("\nIngrese la posicion del nodo a eliminar: ");
					scanf("%d",&pos);
		      		eliminar(&planta, pos);
		     	 	break;
		    }
		    break;
		case 3: //ordenar
			ordenar(&psiquico);
			ordenar(&fuego);
			ordenar(&planta);
			ordenar(&conca);
			break;
		case 4: //concatenar
    		conca = concatena(psiquico, fuego, planta);
            break;
        case 5: //buscar
        	system("cls || clear");
        	printf("Cual es el pokemon que deseas buscar?: ");
        	scanf("%s", pokemon);
        	buscar(conca, pokemon);
        	break;
		case 0:
        	printf("Suerte maestro pokemon...\n");
        	break;
        default:
			printf("Opcion incorrecta, verifica tus opciones\n");
			break;
        }
    } while (op != 0);

    liberar_memoria(psiquico);
    liberar_memoria(fuego);
    liberar_memoria(planta);
    liberar_memoria(conca);

    return 0;
}

void menu()
{
    printf("\n~~~~~~ MENU ~~~~~~\n");
    printf("1.- Agregar\n");
    printf("2.- Eliminar\n");
    printf("3.- Ordenar lista alfabeticamente\n");
    printf("4.- Cocatenar\n");
    printf("5.- Buscar\n");
    printf("0.- Salir\n");
}

void listas()
{ /* solamente lo use para poder utilizarla en otras funciones y no saturar el main*/
    printf("1.- Pokemon tipo psiquico\n");
    printf("2.- Pokemon tipo fuego\n");
    printf("3.- Pokemon tipo planta\n");
}

struct nodo *crear_nodo(char *datos)
{
    struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    if (!nuevo)
    {
        printf("Error al asignar memoria para el nuevo nodo\n");
        return NULL; 
    }
    nuevo->dato = strdup(datos);//strdup duplica l acadena de caracteres, la use ya que me si yo agregaba un nuevo
    // dato en una lista diferente se agregaba en ambas listas y buscando fue la unica solucion ante mi problema 
    nuevo->link = NULL;
    return nuevo;
}

//imprimir
void print_lista(struct nodo *head)
{
    puts("");
    int num_nodo = 0;
    struct nodo *aux = head;
    for (aux = head; aux != NULL; aux = aux->link)
    {
        num_nodo++;
        printf("Elemento %d: %s\n", num_nodo, aux->dato);
    }
}

//agregar
void agregar(struct nodo **head, char *datos) //strcmp strcpy
{
    struct nodo *nuevo = crear_nodo(datos);
    nuevo->link = *head;
    *head = nuevo;
}

//agrega a la lista correspondiente
void agregar_por_tipo(struct nodo **lista, char *tipo)
{/* este 2do agregar es mas que nada porque me comenatron que se veia muy saturado el main con tantas opciones, por lo que se me ocurrio hacer esta función
*/
    char npokemon[50];
    printf("Ingrese el nombre del Pokemon tipo %s: ", tipo);
    scanf("%s", npokemon);
    agregar(lista, npokemon);
}

//eliminar
void eliminar(struct nodo **lista, int posicion) 
{ /*guiandome de un video tutorial, fue mi intento de  usar recursividad en eliminar*/
  	if (*lista == NULL) 
  	{ 
  		printf("La lista esta vacia.\n");
    	return; //si la lista esta vacia retorna 
  	}

  	if (posicion == 0) // si el nodo se encontraba en la primera posicion se asigna el nodo siguiente y liberamos la memoria
  	{
    	struct nodo *aux = *lista;
    	*lista = (*lista)->link;
    	free(aux);
    	return;
  	}
  	 else
    {
        printf("Posicion %d fuera de rango\n", posicion);
    }

  	eliminar(&(*lista)->link, posicion - 1);
  /* la recursividad, en si si no es el primer nodo este se retorna asi mismo donde la lista es donde empieza y la posicion del nodo a eliminar
  este avanzara */
}

void ordenar(struct nodo **head)
{ /* este parte fue la que se me complico mas, en si mi idea era reutilizar lo de la actividad anterior y utilizar la funcion comparar, sin embargo al hacer eso
si lo ordenaba pero eliminaba datos, por lo que con un poco de ayuda llegamos a esta solucion.
Lo intente con recursion, pero no logre que se resperara un ciclo, si lo ordenaba pero cada vez que seleccionaba la opcion 
No logre que diferenciara las mayusculas de las minusculas.
*/
    if (*head == NULL || (*head)->link == NULL) 
    {
        return;
    }
    bool ord;
    do {
        ord = false;
        struct nodo *actual = *head;
        struct nodo *anterior = NULL;
        struct nodo *siguiente;

        while (actual->link != NULL) 
        {
            siguiente = actual->link;
            if (strcmp(actual->dato, siguiente->dato) > 0) 
            {
               if (!anterior) 
               {
                    *head = siguiente;
                } 
                else 
                {
                    anterior->link = siguiente;
                }
                actual->link = siguiente->link;
                siguiente->link = actual;
                ord = true; 
            }
            anterior = actual;
            actual = siguiente;
        }
    } while (ord); 
}

//concatenar
struct nodo *concatena(struct nodo *ps, struct nodo *fire, struct nodo *plant)
{ /* temp recorre las listas, cada for corresponde a una de las listas donde temp se iguala a la cabeza de cada una de ellas,
para que se pueda concatener temp debe ser diferente de null y posterior a eso avanzar al siguiente dato al que apunta 
no pude que se agregara de forma automatica si se agregan a las listas individuales y por lo que tampoco pude agregar con un orden
lo intente pero me marcaba errores en los char y por mas que investigue no llegue a la solucion como tal*/
    struct nodo *concatenada = NULL;
    struct nodo *temp = NULL;

    for (temp = ps; temp != NULL; temp = temp->link)
    {
        agregar(&concatenada, temp->dato);
    }
    for (temp = fire; temp != NULL; temp = temp->link)
    {
        agregar(&concatenada, temp->dato);
    }
    for (temp = plant; temp != NULL; temp = temp->link)
    {
        agregar(&concatenada, temp->dato);
    }

    return concatenada;
}

void buscar(struct nodo *head, char *busca)
{
  struct nodo *actual = head;

  while (actual != NULL)
  {
    if (strcmp(actual->dato, busca) == 0)
    {
      printf("Pokemon registrado en la pokedex\n");
      printf("Nombre: %s\n", actual->dato);
      printf("Direccion: %p\n", actual->link);
      return;
    }
    actual = actual->link;
  }

  printf("El pokemon aun no se registra en la pokedex\n");
}

void liberar_memoria(struct nodo *lista) 
{
    struct nodo *aux;
    while (lista) 
    {
        aux = lista;
        lista = lista->link;
        free(aux);
    }
}

//strcasecmp para mayusculas