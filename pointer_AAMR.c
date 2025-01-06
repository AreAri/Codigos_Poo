/* 
	APUNTADORES
	- operador de direccion: &
	- operador de indirección: *
	- permiten acceso indirecto
	- aritmétics de apuntadores:
		- incremento
		- decremento
		- asignación
		- dirección
		- indirección
		- diferencia
		- comparación
		*/
#include <stdio.h>
int main(int argc, char const *argv[])
{
	// declaro e inicializo una variable de tipo entero
	int viariable = 9;

	//declaro un apuntador a tipo entero
	int *ptr_var; //identificador de la constante a utilizar

	//inicializar el apuntador no debe llevar el *
	ptr_var = &viariable;
	// declara e inicializar int *ptr_var= &viariable (lo mismo pero ahorras lineas)

	printf("Acceso directo a var: %d\n", viariable);
	printf("Acceso indireci a var con ptr: %d\n", *ptr_var); //con asterisco valor sin asterico direccion de memoria
	printf("Direccion a var: %d\n", &viariable);
	printf("Direccion a var con ptr: %d\n", ptr_var);
	return 0;
}