/* si un scanf tiene en si %*c estos es un [set] -> excluye un caracter 
	* -> significa excluir
 secuencia de 100 num que calcule pares e impares y nulos
 */
#include <stdio.h>
#define tam 5
int main(int argc, char const *argv[])
{
	int num[tam], par=0, impar=0, nulo=0;
	for (int i = 0; i < tam; ++i)
	{
		printf("ingrese el dato %d: \n",i+1);
		scanf("%d",&num[i]);
		if (num[i]==0)
		{
			nulo++;
		}
		else if (num[i]&1) //bitwise operator
		{
			impar ++;
		}
		else
		{
			par ++;
		}
	}
	printf("Se tiene %d numero(s) pares\n",par );
	printf("Se tiene %d numero(s) impares\n", impar);
	printf("Se tienen %d numeros(s) nulos\n", nulo );
	return 0;
}