/* Crear un programa que permita gestionar una lista de estudiantes
	Registro:
		- Nombre
		- Edad
		- Matricula
		- Promedio
	Acciones:
		- Agregar estudiante
		- Mostrar toda la lista
		- Buscar un estudiante
		- Eliminar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Registro de datos
struct datos
{
	char name[20];
	char paterno [20];
	char materno [20];
	int edad;
	char matricula[11];
	float prom;
};

//funciones
void menu () //menu de las acciones 
{
	printf ("~~~~ MENU ~~~~\n");
	printf ("1.- Agregar estudiante\n ");
	printf ("2.- Mostrar lista\n");
	printf ("3.- Buscar estudiante\n");
	printf ("4.- Eliminar\n");
	printf ("5.- Salir\n");
}

void agregar (struct datos **alumno, int *num_lista)
{
	(*num_lista)++;//nos permitira agregar mas campos a la lista ya que no se define la cantidad como tal
	*alumno = (struct datos *)realloc(*alumno, (*num_lista) * sizeof(struct datos));
	/* realloc dimenciona y este varia segun la cantidad de alumnos se ingresen el cual se define con *num_lista
		*alumno es nuestro puntero para el 1er elemento	*/
	if (*alumno == NULL) 
	{
        printf("Error\n");
        exit(1);
    }
	printf("Ingrese matricula: ");
	scanf("%s", (*alumno)[*num_lista - 1].matricula);
	printf("Ingrese apellido paterno: ");
	scanf("%s", (*alumno)[*num_lista - 1].paterno);
	printf("Ingrese apellido materno: ");
	scanf("%s", (*alumno)[*num_lista - 1].materno);
	printf("Ingrese nombre: ");
	scanf("%s", (*alumno)[*num_lista - 1].name);
	printf("Ingrese edad: ");
	scanf("%d", &(*alumno)[*num_lista - 1].edad);
	printf("Ingrese promedio: ");
	scanf("%f", &(*alumno)[*num_lista - 1].prom);
	// *alumno vamos a la posicion donde se encuentra *num_lista - 1 
};

void mostrar (struct datos *alumno, int num_lista)
{
	if (num_lista == 0);
	{
		printf("Aun no hay alumnos registrados\n");
	}

	FILE *archivo;
	archivo=fopen("registro_alumnos.txt", "w"); //"w" para que el archivo se reescriba
	for (int i=0; i< num_lista; ++i)
	{
		printf("Matricula: %s\n", alumno[i].matricula);
		printf("Apellido paterno: %s\n", alumno[i].paterno);
	    printf("Apellido materno: %s\n", alumno[i].materno);
		printf("Nombre: %s\n", alumno[i].name);
	    printf("Edad: %d\n", alumno[i].edad);
	    printf("Promedio: %.2f\n", alumno[i].prom);
	}
	fclose(archivo);
}

void buscar (struct datos *alumno, int num_lista)
{
	int op;
	char b[11];
	printf ("Ingrese matricula del alumno: ");
	scanf ("%s", b);
	for (int i = 0; i < num_lista; ++i) 
	{
        if (strcmp(alumno[i].matricula, b) == 0)
        {
            printf("\n Busqueda exitosa \n");
            printf("Matrícula: %s\n", alumno[i].matricula);
            printf("Nombre: %s\n", alumno[i].name);
            printf("Apellido paterno: %s\n", alumno[i].paterno);
            printf("Apellido materno: %s\n", alumno[i].materno);
            printf("Edad: %d\n", alumno[i].edad);
            printf("Promedio: %.2f\n", alumno[i].prom);
            return;
        }
    }
    printf ("%s no encontrado en el sistema");	
}

void eliminar (struct datos *alumno, int *num_lista)
{
	char d[11];
	int encontrado = 0; 
	printf("Ingrese matricula del alumno para eliminar: ");
	scanf("%s", d);
	for (int i = 0; i < *num_lista; ++i) 
	{
        if (strcmp(alumno[i].matricula, d) == 0)
        {
        	encontrado = 1;
            alumno[i] = alumno[*num_lista - 1];
            alumno = (struct datos *)realloc(alumno, (*num_lista - 1) * sizeof(struct datos));
            //realloc disminuye el tamaño de la memoria asignada en La lista de alumnos
            (*num_lista)--;
            printf("Estudiante eliminado... \n");
            break; 
        }
    }
    if (!encontrado) {
        printf("%s no encontrado en el sistema.\n", d);
    }
}

int main(int argc, char const *argv[])
{
	struct datos *alumno = NULL;
	int num_lista = 0;
	int opcion;

	do
	{
		menu();
		printf ("Ingrese una opccion: ");
		scanf ("%d",&opcion);

		switch (opcion)
		{
			case 1:
				agregar (&alumno, &num_lista);
				break;
			case 2:
				mostrar (alumno, num_lista);
				break;
			case 3:
				buscar(alumno, num_lista);
				break;
			case 4:
				eliminar(alumno, num_lista);
				break;
			case 5: 
				printf("\n Saliendo... \n");
				break;
			default: 
				printf ("\n Opcion no valida, intenta de nuevo...\n");
		}

	}while (opcion!=0);
	return 0;
}