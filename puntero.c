#include <stdio.h>
int main(int argc, char const *argv[])
{
	/*int var = 42;
	int *dato;
	dato = &var;
	printf("Direccion de la variable: %p\n",dato);
	char *ptr;
	puts("Introduzca una dirección: ");
	scanf (" %p", &ptr);

	printf("En la direccón %p se guarda %c\n",ptr,*ptr);*/ //%muestra lo de dato %c lo convierte en base al codigo ascci solo si datos es int
	
	char var[] = "Hola, aún te duele?";
	char *dato;
	dato = var;
	//fopen = *archivo
	printf("Direccion de la variable: %p\n",dato);
	char *ptr;
	puts("Introduzca una direccion: ");
	scanf (" %p", &ptr);
	//printf("En la direccón %p se guarda %c\n",ptr,*ptr);
	for(int i=0; i<sizeof(var);i++)
	{
		printf("%c",ptr++);
	}
	
	return 0;
}