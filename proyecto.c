/* Areli Arisai Meza Rendón
	Realizar un codigo que utilice árboles binarios (no mas de 2 hijos por cabeza) estos deben tener:
		- Inserción *
		- Borrado 
		- Busqueda
		- Ordenamiento en:
			> Inorden *
			> Preorden *
			> Posorden *
		- Funcion de vacio (pa que no lo olvides poner) *
		- Crear raiz *
	Toma en cuenta que se debe usar recursion (esto no es opción)
	Si quieres que se imprima como árbol usa listas de listas (averigualo en el proceso)
	RETO: hacerlo grafico...
*/


#include <stdio.h>
#include <stdlib.h>

//estructura del árbol
struct arbol
{
	int dato; 
	struct arbol *izq; //lado izquierdo los menores
	struct arbol *der; //lado derecho los mayores
};

//funciones
struct arbol *crear_arbol (int num); //ya
int arbol_seco (struct arbol *raiz); //arbol vacio ya
void agregar (struct arbol **raiz, int num);//ya
void plantar (struct arbol *raiz, int nivel); //imprime el arbol ya
void podado (struct arbol **raiz, int num); //eliminar ya
void buscar (struct arbol *raiz, int num, int nivel, int padre);//ya
//ordenamiento
void inorden (struct arbol *raiz); //ya
void preorden (struct arbol *raiz); //ya
void posorden (struct arbol *raiz); //ya
void viento(struct arbol *raiz);//libera la memoria
void menu ();

int main(int argc, char const *argv[])
{
	int nivel=0;
	struct arbol *raiz = NULL;
	agregar (&raiz,17); //primero en ingresar se vuelve raiz
	agregar (&raiz,8);
	agregar (&raiz,4);
	agregar (&raiz,12);
	agregar (&raiz,25);
	agregar (&raiz,32);
	printf("~~~~ Arbol Original ~~~~\n");
	plantar(raiz,nivel);
	system ("cls || clear");


    viento(raiz);
}

void menu()
{
	printf("~~~~~~ Arbol Binarios ~~~~~~\n");
	printf("1.- Agregar\n");
	printf("2.- Eliminar\n");
	printf("3.- Ordenar\n");
	printf("4.- Buscar\n");
	printf("0.- Salir\n");
}

struct arbol *crear_arbol (int num)
{
	struct arbol *nuevo = (struct arbol*)malloc(sizeof(struct arbol));
	if (nuevo == NULL)
	{
		puts ("Error al asignar memoria");
		return 0;
	}
	nuevo->dato = num; //el nodo NUEVO toma el valor que se ingresa
	nuevo->izq = nuevo->der = NULL; // y se le crean sus punteros de izq y der para sus futuros hijos 
	return nuevo;
}

int arbol_seco (struct arbol *raiz) //verifica si hay arbol o no 
{
	return raiz == NULL;
}

void agregar(struct arbol **raiz, int num) 
{
	if (arbol_seco(*raiz)) //si no hay arbol
	{
	    *raiz = crear_arbol(num);//el numero que se ingresa se convierte en raiz
	    return; 
  	}
  	//pero si ya hay un arbol hecho
  	if (num < (*raiz)->dato) //si el numero es menor que la raiz
  	{
    	agregar(&(*raiz)->izq, num);//se agrega del lado izq
    	//porque el & es para ir directamente a la direccion del lado izq de la raiz ya si agregarlo 
  	} 
  	else if (num > (*raiz)->dato) //si es mayor se va al derecho
  	{
    	agregar(&(*raiz)->der, num); //lo mismo pero a la derecha
  	} 
  	else 
  	{
    	//si no es ninguno de los casos es porque el numero ya existe, y gemelos no se permiten 
    	return;
  	}
}

void plantar (struct arbol *raiz, int nivel)
{
	if (arbol_seco(raiz)) //si no hay arbol no se pone nada
    {
        return;
    }
    else
    {
    	plantar(raiz->der, nivel+1); //empezamos recorrido de los mayores
    	for (int i = 0; i < nivel; i++) //ciclo para empezar la impresion 
    	{
    		printf(" | ");//solo para diferenciar los niveles solo se agregan si sigue habiendo hijos a las hojas ya no 
    	} 
    	printf("%d\n", raiz->dato); //imprime nodo
    	plantar(raiz->izq, nivel+1); //recorre a los menores
	}
}

void inorden (struct arbol *raiz) //de mayor a menor
{
	if (arbol_seco(raiz)) 
    {
        return;
    }
    inorden(raiz->izq); //recorrido del lado izquierdo
    printf("%d ", raiz->dato); //va imprimiendo
    inorden(raiz->der); //recorre del lado derecho tambien
}

void preorden (struct arbol *raiz)
{
	if (arbol_seco(raiz)) 
    {
        return;
    }
    printf("%d ", raiz->dato); //empieza la raiz
    preorden(raiz->izq); //inicia recorrido a la izquierda
    preorden(raiz->der); //recorrido a la derecha
}

void posorden (struct arbol *raiz)
{
	if (arbol_seco(raiz)) 
    {
        return;
    }
    posorden(raiz->izq); //inicia recorrido a la izquierda
    posorden(raiz->der); //recorrido a la derecha
    printf("%d ", raiz->dato); //imprime
}

void podado (struct arbol **raiz, int num)
{
    if (arbol_seco(*raiz)) //sin arbol
    {
        return;
    }
    
    if (num < (*raiz)->dato) // Si el número es menor
    {
        podado(&(*raiz)->izq, num); // Va a la izquierda y elimina
    }
    else if (num > (*raiz)->dato) // Si es mayor
    {
        podado(&(*raiz)->der, num); // Va a la derecha y elimina
    }
    else 
    {
        // Nodo encontrado
        struct arbol *temp = *raiz;
        if ((*raiz)->izq == NULL && (*raiz)->der == NULL) // Hojas
        {
            *raiz = NULL;
            free(temp);
        }
        else if ((*raiz)->izq == NULL) // Solo hijo derecho
        {
            *raiz = (*raiz)->der;
            free(temp);
        }
        else if ((*raiz)->der == NULL) // Solo hijo izquierdo
        {
            *raiz = (*raiz)->izq;
            free(temp);
        }
        else // Dos hijos 
        {
            struct arbol *mayor = (*raiz)->der;
            while (mayor->izq != NULL)
            {
                mayor = mayor->izq;
            }
            (*raiz)->dato = mayor->dato;
            podado(&(*raiz)->der, mayor->dato);
            /*
            	Teniendo en cuenta el orden de los nodos por inorden, si se elimina un nodo que ademas de hijos tenga nietos sube el mayor, ojo
            	el mayor segun inorden 
            	es decir si elimino el nodo raiz 17 en vez de que suba su hijo mayor 25 subira el nieto 20 debido al inorden sigue siendo el mayor pero 
            	el mayor mas cercano
            */
        }
    }
}

void buscar (struct arbol *raiz, int num, int nivel, int padre)
{
    if (arbol_seco(raiz)) 
    {
        printf("No ha nacido un nodo con ese valor\n"); //si el nodo no existe en el arbol 
        return;
    }
    if (num < raiz->dato) //si es menor que la raiz
    {
        buscar(raiz->izq, num, nivel + 1, raiz->dato);//hace el recorrido del lado izq, berifica el numero, toma su nivel, el nodo del arbol
    } 
    else if (num > raiz->dato) //si es mayor
    {
        buscar(raiz->der, num, nivel + 1, raiz->dato);//va a la derecha, numero a buscar, nivel, el dato de la raiz
    } 
    else //si es igual al actual
    {
        printf("Encontrado: %d\n", num); //numero que se encontro
        printf("Nivel: %d\n", nivel);//su nivel
        if (padre == -1) //como la raiz esta en 0 se verifica que no tenga un padre
        {
            printf("Es la raíz del árbol\n");
        }
         else 
        {
            printf("Padre: %d\n", padre);//imprimimos el padre el pequeño hijo 
        }
    }
}

void viento(struct arbol *raiz) //es bueno liberar 
{
    if (arbol_seco(raiz))
    {
        return;
    }

    viento(raiz->izq);
    viento(raiz->der);
    free(raiz);
}