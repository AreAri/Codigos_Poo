#include <stdio.h>
int multi(int a, int b)
{
	if (b==0) //caso base
	{
		return 0;
	}else
	return multi(a,b-1)+a; //recursion
}

int suma(int a)
{
	if (a==1)
	{
		return 0;
	}else
	return a+suma(a-1);
}

int main(int argc, char const *argv[])
{
	int a, b,n ;
	printf("Ingresa el primer valor: ");
	scanf("%d",&a);
	printf("Ingresa el 2do valor\n");
	scanf("%d",&b);
	printf("el resultado es: %d\n",multi );
	return 0;
}

