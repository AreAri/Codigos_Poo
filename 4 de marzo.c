/* programa que recibe numeros enteros desde teclado y los guarde en un arreglo
los datos deben parar cuando sea 0 o llegar al final del arreglo
encuentre e imprima los valores maximo y minimo,
en lugar de int definelo como ent
*/
#include <stdio.h>
int main(int argc, char const *argv[])
{
	typedef int ent; //definiendo el tipo de dato
	ent tam, max=0, min=0, close=1;
	printf("Favor de ingresar el tamano del arreglo\n");
	scanf("%d",&tam);
	ent arr[tam]; // se pone despues para que asi no se guarde basura dentro del arreglo
	for (ent i = 0; i < tam; i++)
	{
		arr[i]=0;//se evitan errores y borra totalmente los datos anteriores
	}

	puts("Si pones 0 se detiene la captura, ten cuidado");

	for (ent i = 0; i < tam && close!=0; i++)
	{
		printf("Ingresa elemento #%d: \n",i+1);
		scanf("%d",&close);
		arr[i]=close;
	}

	for (ent i = 0; i < tam; i++)
	{
		printf("elemento: %d \n",arr[i]);
		if (arr[1]>max)
		{
			max=arr[i];
		}
		else if (arr[i]<min && min!=0)
		{
			min=arr[i];
		}
	}
	printf("Maximo: %d Minimo: %d \n",max, min);
		
	
	/*ent num = 5;
	printf("Numero es: %d\n", num );*/

	return 0;
}