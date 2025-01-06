/* los arreglos siempre seran del mismo tipo
	REGISTRO SIMPLE
	STRUCT <- palabra reservada para la creacion de registros
	fecha es el indicador del registro
*/ 
#include <stdio.h>
#define TAM 4
//definimos de la estructura 
struct fecha //los registros se puede tomar como un "nuevo tipo de dato"
{
	//mienbros del registro o estructura
	int dia;
	int mes;
	int anio;
}reg={12,10,2024}; //declaro de la estructura e inicializando (solo se inicializa si no se necesita registrarlo)

struct info
{
	int edad;
	float sueldo;
}dato; // declarando a la par de la definicion

struct info2 //struct nivel 2 con arreglos
{
	char nombre [30]; // si se ponen 29 caracteres se debe considerar el final de cadena
	char ap_pat[30];
	char ap_mat[30];
};

struct info 3 //nivel 3 estructiras con estructuras
{
	char nombres [30]; // siempre se debe consideral el final de cadena
	int calif [5]; // no se necesita conteplar el final de cadena ya que es la cantidad exacta
	struct info2 mas_info;
};

// apuntadoras a registros
struct alumnos
{
	int posicion;
	char nombre [30];
}alum;/*[TAM]={
			1, "Areli",
			2, "Alexis",
			3, "Daniel",
			4, "Eduardo"
		};
struct alumnos alum2 = {5, "Yuliana"};*/

// declarar fuera de la definicion
struct info datos2;
struct info2 nombre_c;

int main(int argc, char const *argv[])
{
	struct fecha reg2 = {10,8,2024};
	struct info2 nombres[TAM]; //arreglo de registros
	printf("%d / %d / %d \n",reg.dia, reg2.mes, reg2.anio); 

	struct alumnos  *ptr_alumnos;
	ptr_alumnos=alum; // => ptr_alumnos=&alum[0]
	// si se pone & especifica la direccion 
	struct alumnos *ptr_oyente;
	ptr_oyente=&alum2;
	puts ("ingresa tu nombre: "); //puts da salto de linea y solo muestra el texto y no funciona si necesitas imprimir un dato ingresado
	scanf("%s", nombre_c.nombre);
	puts ("El nombre capturado fue: ");
	printf("%s\n", nombre_c.nombre);

	for (int i=0; i<TAM; i++)
	{
		printf(" \n");
	}



	return 0;
}
