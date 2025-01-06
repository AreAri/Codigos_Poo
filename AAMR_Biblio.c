// actividad 19 de febrero 2024
// Areli Arisai Meza Rendón - AreAri
#include <stdio.h>
#include <stdlib.h>
#define max 2 //constante ya definida y no de modifica en ninguna parte del programa 

struct datos
{
	char name[50];
	char ap[50];
	char am[50];
	char rfc[15];
	int edad;
	float sueldo;
};//reg[30]; //struct datos reg[3]; -- es lo mismo pero en el otro de declara y define al mismo tiempo

struct libros
{
	char titulo[50];
	struct datos autor;
	char isbn[50];//codigo especial del libro
	float costo;
};//reg2 = {"lord of thge rings", "J.R.R.", "Tolkien", "Tolkien", "TJTR123HV", 60, 100000.00, "123HBLK", 500}; //declarando la estructura y capturando datos
// "J.R.R.", "Tolkien", "Tolkien", "TJTR123HV", 60, 100000.00 es parte de la estructura datos

struct biblioteca
{
	char nombre[50];
	struct libros info_libros;
	int cantidad;	
};
void registros(struct biblioteca bio[max]);
void imprimir(struct biblioteca bio[max]);

int main(int argc, char const *argv[])
{
	struct biblioteca bio[max];
	registros(bio);
	imprimir(bio);
	return 0;
}

void registros(struct biblioteca bio[max])
{
	printf("Datos de de 3 bibliotecas\n");
	for (int i=0; i<max; i++)
	{
		printf("Nombre de biblioteca: ");
		scanf(" %[^\n]",bio[i].nombre);
		 /*%[^\n] es un formato de caprura que permite que se contemplen los espacios sin saltarse a otros campos, se le pone espacio al 
		 final en caso de que no se necesite el espacio
		 [] dentro se pone un set de instrucciones */
		printf("Titulo: ");
		scanf(" %[^\n]",&bio[i].info_libros.titulo);
		printf("Autor: ");
		scanf(" %[^\n]",&bio[i].info_libros.autor.name);
		printf("Apellido paterno: ");
		scanf(" %[^\n]",&bio[i].info_libros.autor.ap);
		printf("Apellido materno: ");
		scanf(" %[^\n]",&bio[i].info_libros.autor.am);
		printf("isbn: ");
		scanf(" %s",&bio[i].info_libros.isbn);
		printf("costo: $");
		scanf(" %f",&bio[i].info_libros.costo);
		printf("Cantidad de libros: ");
		scanf(" %d",&bio[i].cantidad);
	}
}

void imprimir (struct biblioteca bio[max])
{
	puts("Datos registrados\n");
	for (int i = 0; i < max; i++)
	{
	    printf("Biblioteca: %s\n", bio[i].nombre);
	    printf("Libro:\n");
	    printf("Titulo: %s\n", bio[i].info_libros.titulo);
	    printf("Autor: %s %s %s\n", bio[i].info_libros.autor.name, bio[i].info_libros.autor.ap, bio[i].info_libros.autor.am);
	    printf("ISBN: %s\n", bio[i].info_libros.isbn);
	    printf("Costo: %0.2f\n", bio[i].info_libros.costo);
	    printf("Cantidad de libros: %d\n", bio[i].cantidad);
	}
}
/* matematicas	| programacion
	f 			| registros						| nombre
	(x)			| (struct biblioteca bio[max])	| lista de parametros - argumentos
	f(3)		| registros(bio) 				| llamar la funcion con el dato especifico 
*/