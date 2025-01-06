// clase oyente con el doc marin 
#include <stdio.h>

struct datos
{
	char nombre[100];
	int edad;
	float peso;
};

void registro (struct datos *per)
{	
	/*per->edad=50 
	per->peso=68.9
	per->nombre=...*/
	scanf("%d",%per->edad);
	scanf("%f",&per->peso);
	scanf("%s",per->nombre);
	//void * recibo y despues combierto y recombierto
	//funcion suma que reciba 2 parametros que sean enteros, flotantes, string se deben convertir para poder hacer el resultado y regresar los resultados
	// que detecte que dato se le esta ingresando 
}


int main(int argc, char const *argv[])
{
	struct datos *per;
	registro();
	return 0;
}