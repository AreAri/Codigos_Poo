/* Areli Arisai Meza Rendon - AreAri
	2-. (EDD_YBD_2) Realizar un programa para leer cualquier archivo de texto, y su contenido sea impreso en pantalla.
   	El nombre del archivo debe ser ingresado desde linea de comandos. Se puede seguir el sig formato:
   		FOLDER ./a.out archivo.txt
   	donde, "archivo.txt" es el nombre del archivo a leer.*/
#include <stdio.h>
int main() 
{
  	FILE *archivo;
	char carac, name[50];
	printf("Ingrese el nombre del archivo, recuerda agregar .txt al final \n");
	printf("Ejemplo: archivo.txt\n");
	scanf("%s",name);
	archivo = fopen(name, "r");// r nos permite poder ingresar al archivo unicamente en forma de lectura
	if (archivo == NULL) 
	{
		printf("Error al abrir el archivo.\n");
	    return 1;
	}
	do 
	{
		carac = fgetc(archivo);// fgetc nos permite poder leer los caracteres dentro del archivo
	    if (carac != EOF) //eof significa fin del archivo, si no es el final se imprime
	    {
	    	printf("%c", carac);
	    }
	} while (carac != EOF);//se repite hasta que llegue al final del archivo
	fclose(archivo);
	return 0;
}