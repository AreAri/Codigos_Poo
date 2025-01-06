/*Asignaciones

tipo_dato n

int dato =42;
int suma = (var1 + var2) *34 / 6 ^3;
int dato2 = 42 + otra_variable;
int a,b,c;
a=b=c=42;

¿Puede hacer esto?
char nombre[]=Arisai -> no se puede
char nombre[]="Arisai" -> si se puede
char nombre[4]="Arisai" -> desbordamiento, la cadena es muy larga

¿que sucede si?
char nombre[15];
nombre ="Arisai" -> marca error no lo permite debido a que lo toma como si fuera un apuntador 

operadores para apuntadores * y &
& <- opreador de direccion
* <- operador de indirección
 int num; <- no es apuntador
 int *num <- num se convierte apuntador a tipo entero
 num = &dato;

 dentro de c los apuntadoreas tienen 3 funciones que se consideran basicas:
 1. nos dan una amnera rapida de referenciar elementos de un arreglo.
 2. ayudan o permiten que las funciones puedan modificar los parametros de llamada.
 3. nos sirve para trabajar con estrcuturas dinamicas.

 & -> es un operador unario, nos devuelve la dirección de memoria de una variable de cualquier tipo
 * -> complemento de &, este devuelve el contenido 
 dato = &numero;
 dato2 = *dato;
imprimir dato2;


 */

#include <stdio.h>
int main(int argc, char const *argv[])
{
	int a,b,c;
	a=b=c=42;
	char nombre[]="Arisai";
	//printf("%d\n",c );
	//printf("%s\n", nombre);

	int numer0=30;
	int *dato;
	dato = &numer0;
	printf("dir nuemero: %p\n",dato );
	//int dato2 = *dato;
	int dato2 = numer0;
	printf("%d\n",dato2);// acceso indirecto

	int **ptr_1= &dato;
	printf("dir dato: %o\n",ptr_1 );

	int ***ptr_2 = &ptr_1;
	printf("dir ptr_1: %p\n",ptr_2);

	int ****ptr_3 = &ptr_2;
	printf("dir ptr_21: %p\n",ptr_3);

	int *****ptr_4 = &ptr_1;
	printf("dir ptr_3: %p\n",ptr_4)

	return 0;
}