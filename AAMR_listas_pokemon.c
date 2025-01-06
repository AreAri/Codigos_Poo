/* Areli Arisai Meza Rendon - AreAri
	Listas con pokemon
	1.- Abra - Kadabra - Alakazam - Mega-Alakazam
	2.- Charmander - Charmeleon - Charizard - Mega-Charizard
	3.- Bulbasaur - Ivysaur - Venusaur - Mega-Venusaur
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void eliminar_posicion(struct nodo **head, int posicion);
int comparar(char *cad1, char *cad2);
void ordenar (struct nodo **head, int ord);

int main(int argc, char const *argv[])
{
	int op = 0, pos=0, elec=0, po=0;
	char pokemon[50];
	//definir las 3 listas
	struct nodo *psiquico =  NULL; // abra- Kadabra - Alakazam - Mega-Alakazam
	struct nodo *fuego = NULL; // Charmander - Charmeleon - Charizard - Mega-Charizard
	struct nodo *planta = NULL; // Bulbasaur - Ivysaur - Venusaur - Mega-Venusaur
	do 
	{
		system ("cls || clear");
		printf("Pokemones tipo psiquico:");
		print_lista(psiquico);
		printf("\nPokemones tipo fuego:");
		print_lista(fuego);
		printf("\nPokemones tipo planta:");
		print_lista(planta);
		menu();
		printf("Ingrese una opcion: ");
		scanf("%d", &op);
		switch(op)
		{
			case 1://agregar
				system ("cls || clear");
				printf("Que tipo de pokemon desea agregar\n");
				listas();
				scanf("%d", &po);
				switch(po)
				{
					case 1:
						printf("Ingrese el nombre del pokemon tipo psiquico: ");
						scanf("%s",pokemon);
						agregar(&psiquico,pokemon);
						break;
					case 2:
						printf("Ingrese el nombre del pokemon tipo fuego: ");
						scanf("%s",pokemon);
						agregar(&fuego,pokemon);
						break;
					case 3:
						printf("Ingrese el nombre del pokemon tipo planta: ");
						scanf("%s",pokemon);
						agregar(&planta,pokemon);
						break;
				}
				break;
			case 2://eliminar
				system ("cls || clear");
				printf("De que lista desea eliminar: ");
				listas();
				scanf("%d", &po);
				switch(po)
				{
					case 1:
						printf("Ingrese el nombre del pokemon tipo psiquico: ");
						scanf("%s",pokemon);
						agregar(&psiquico,pokemon);
						break;
					case 2:
						printf("Ingrese el nombre del pokemon tipo fuego: ");
						scanf("%s",pokemon);
						agregar(&fuego,pokemon);
						break;
					case 3:
						printf("Ingrese el nombre del pokemon tipo planta: ");
						scanf("%s",pokemon);
						agregar(&planta,pokemon);
						break;
				}
				break;
		}
	}while(op!=0);
	
	return 0;
}

void menu()
{
	printf("~~~~~~ MENU ~~~~~~\n");
	printf("1.- Agregar\n");
	printf("2.- Eliminar\n");
	printf("3.- Ordenar lista alfabeticamente\n");
	printf("4.- Cocatenar\n");
	printf("5.- Buscar\n");
	printf("0.- Salir\n");
}

void listas()
{
	printf("1.- Pokemon tipo psiquico\n");
	printf("2.- Pokemon tipo fuego\n");
	printf("3.- Pokemon tipo planta\n");
}

struct nodo *crear_nodo(char *datos)
{
	struct nodo *nuevo = (struct nodo *)malloc(sizeof(struct nodo));
	if (nuevo == NULL) 
	{
        printf("Error al asignar memoria para el nuevo nodo\n");
        exit(1); // O maneja el error apropiadamente
    }
 
    nuevo->dato = datos;
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
        printf("Elemento %d: %s\n", num_nodo, aux->dato);
    }
}

//agregar
void agregar(struct nodo **head, char *datos)//strcmp strcpy
{
    struct nodo *nuevo = crear_nodo(datos); 
    nuevo->link = *head; 
    *head = nuevo; 
}

