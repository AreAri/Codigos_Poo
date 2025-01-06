#include <stdio.h>
int main(int argc, char const *argv[])
{
	int a, b=0, espejo=0;
	puts("Ingresa un numero de maximo 2 cifras");
	scanf("%d", &a);
	espejo=a%10;
	b=a/10;
	printf("%d%d\n", espejo,b);

	return 0;
}