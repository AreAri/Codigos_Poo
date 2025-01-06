/* Areli Arisai Meza Rendon - AreAri
	1.- Realizar un programa para leer caracteres desde el teclado y almacenarlos en un archivo, hasta que el usuario teclee el caracter "#".
	El nombre del archivo debe ser ingresado desde línea de comandos y el nombre del programa deber ser EDD_Iniciales_1.c.
*/
#include <stdio.h>
int main(int argc, char const *argv[])
{
	char carac, name[50];
	FILE *archivo;
	printf("Ingrese el nombre del archivo, recuerda agregar .txt al final\n");
	printf("Ejemplo: archivo.txt\n");
	scanf("%s",name);
	printf("Ingrese los caracteres que desea guardar en el archivo\n");
	printf("Si pones '#' finaliza el ingreso\n");
	archivo=fopen(name,"w"); //w es para escritura fopen abre el archivo
	do
	{
		scanf("%c",&carac);// se leen los caracteres que ingresa el usuario 
		if (carac != '#') 
		{
      		fprintf(archivo, "%c", carac);// imprime los caracteres dentro del archivo
    	}
	}while(carac!='#');
	fclose(archivo);//fclose cierra archivo
	printf("Ingreso de datos finalizado\n");
	return 0;
}