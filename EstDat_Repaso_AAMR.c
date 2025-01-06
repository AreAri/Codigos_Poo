/* Areli Arisai Meza Rendon - AreAri 
Crear un programa que permita gestionar una lista de estudiantes
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
#include <stdbool.h>

// estructura para el registro de datos del estudiante
struct datos
{
	char nombre[20];
	char apellidoP[20];
	char apellidoM[20];
	char matricula[15];
	int edad;
	float promedio;
};

//funciones segun las acciones solicitadas en la actividad
void agregar(struct datos **alumnoDatos, int *numLista)
{
	 (*numLista)++; //incrementa los datos en la lista debido a que no se selecciona un limite como tal
	 *alumnoDatos = (struct datos *)realloc(*alumnoDatos, (*numLista) * sizeof(struct datos));
	 //modifica el bloque de memoria asignado para agregar a un nuevo alumno 
	 /* *alumnoDatos: puntero que obtiene los datos de la direccion de memoria de la estructura
	 	realloc permite que se modifique la memoria segun los datos que se ingrese ya que no hay un limite
	 	eso se almacena en numlista y si tamaño depende de la structura */  
	 if (*alumnoDatos == NULL) //se muestra si hubo un error en realloc
	 {
	 	printf("Error");
	 	exit(1);
	 }  
	 struct datos newStudent; //variable para almacenar a un nuevo alumno segun lo que pida la estructura
	 printf("Ingrese matricula: ");
	 scanf("%s", newStudent.matricula);
	 printf("Ingrese nombre: ");
	 scanf("%s", newStudent.nombre);
	 printf("Ingrese apellido paterno: ");
	 scanf("%s", newStudent.apellidoP);
	 printf("Ingrese apellido materno: ");
	 scanf("%s", newStudent.apellidoM);
	 printf("Ingrese edad: ");
	 scanf("%d", &newStudent.edad);
	 printf("Ingrese promedio: ");
	 scanf("%f", &newStudent.promedio);

	 (*alumnoDatos)[*numLista -1] = newStudent; //los nuevos datos a ingresar se ponen al final de la lista
}
void buscar(struct datos *alumnoDatos, int numLista)
{
	char searchStudent[15]; //variable de tipo caracater para leer la matricula
	printf("Ingrese la matricula del estudiante: ");
	scanf("%s", searchStudent);
	bool existe = false; // si no hay registro del estudiante
	printf("Sin datos...\n");
	for (int i = 0; i<numLista; ++i)
	{
			if(strcmp(alumnoDatos[i].matricula, searchStudent) == 0) // condicional para encontrar la matricula
			{ //si se cumple se muestran los datos restantes
				printf("Busqueda exitosa...\n ");
				printf("Matricula: %s\n", alumnoDatos[i].matricula);
				printf("Nombre: %s\n", alumnoDatos[i].nombre);
				printf("Apellido Paterno: %s\n", alumnoDatos[i].apellidoP);
				printf("Apellido Materno: %s\n", alumnoDatos[i].apellidoM);
				printf("Edad: %d\n", alumnoDatos[i].edad);
				printf("Promedio: %f\n", alumnoDatos[i].promedio);
				existe = true;
				break;
			}
	}
}

void mostrar(struct datos *alumnoDatos, int numLista)
{
	if (numLista == 0);
	{
		printf("Aun no hay alumnos registrados\n");
	}
	FILE *archivo;
	archivo=fopen("listaEstudiantes.txt", "w"); // se crea un archivo y "w" sirve para que el archivo se reescriba
	fprintf(archivo,"~~~ Lista de Estudiantes ~~~\n");
	printf("~~~ Lista de Estudiantes ~~~\n");
	for (int i=0; i<numLista; i++)
	{	
		/*crea un documento con los datos, si estos se eliminan o se agregan mas se actualiza
		 el documento unicamente si se vuelve a seleccional la opcion*/
		fprintf(archivo, "Matricula: %s\n", alumnoDatos[i].matricula);
		fprintf(archivo, "Nombre: %s\n", alumnoDatos[i].nombre);
		fprintf(archivo, "Apellido Paterno: %s\n", alumnoDatos[i].apellidoP);
		fprintf(archivo, "Apellido Materno: %s\n", alumnoDatos[i].apellidoM);
		fprintf(archivo, "Edad: %d\n", alumnoDatos[i].edad);
		fprintf(archivo, "Promedio: %.1f\n", alumnoDatos[i].promedio);
		fprintf(archivo,"~~~ o ~~~ o ~~~ o ~~~\n");	
		// se muestra en el cmd
		printf("Matricula: %s\n", alumnoDatos[i].matricula);
		printf("Nombre: %s\n", alumnoDatos[i].nombre);
		printf("Apellido Paterno: %s\n", alumnoDatos[i].apellidoP);
		printf("Apellido Materno: %s\n", alumnoDatos[i].apellidoM);
		printf("Edad: %d\n", alumnoDatos[i].edad);
		printf("Promedio: %.1f\n", alumnoDatos[i].promedio);
		printf("~~~ o ~~~ o ~~~ o ~~~\n");	
	}
	fclose(archivo);
}

void eliminar(struct datos *alumnoDatos, int *numLista)
{
	char DeleteStudent[15]; 
    printf("Ingrese la matricula del alumno a eliminar: ");
    scanf("%s", DeleteStudent);
    bool existe = false;
    for (int i = 0; i < *numLista; ++i)
    {
        if (strcmp(alumnoDatos[i].matricula, DeleteStudent) == 0) //con strcmp nos permite comparar los datos
        {
            existe = true;
            alumnoDatos[i] = alumnoDatos[*numLista - 1];
            alumnoDatos = (struct datos *)realloc(alumnoDatos, (*numLista - 1) * sizeof(struct datos));
            //realloc disminuye el tamaño de la memoria asignada en La lista de datos
            (*numLista)--;
            printf("Eliminacion completa... \n");
            break; 
        }
    }
    if (!existe) 
    {
        printf("Sin datos de %s\n", DeleteStudent);
    }
}
void menu()
{
	printf("\n~~~~ Menu ~~~~\n");
	printf("1.- Agregar estudiante\n");
	printf("2.- Mostrar lista\n");
	printf("3.- Buscar estudiante\n");
	printf("4.- Borrar estudiante\n");
	printf("0.- Salir\n");	
}

int main(int argc, char const *argv[])
{
	int op=0;
	struct datos *alumnoDatos = NULL; // permite inicializar la lista de datos
    int numLista = 0; 
    do{
    	menu();
    	printf("Ingrese una opcion: ");
		scanf("%d", &op);		
		switch(op)
		{
			case 1: 
				agregar(&alumnoDatos, &numLista);
				break;
			case 2: 
				mostrar(alumnoDatos, numLista);
				break;
			case 3: 
				buscar(alumnoDatos, numLista);
				break;
			case 4: 
				eliminar(alumnoDatos, &numLista);
				break;
			case 0:
				printf("Saliendo...");
				break;
			default:
				printf("Error.. intente de nuevo...\n");
		}
	}while (op!=0);
	free(alumnoDatos); 
	return 0;
}
