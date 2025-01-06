#include <stdio.h>
#include <stdlib.h>

//crear un nodo cola
struct elem_cola
{
    int dato;
    struct elem_cola *sig;
};

//crea la estructura de la cola
struct cola
{
    struct elem_cola *inicio;//elimina
    struct elem_cola *final;//ingresa
}; 

int cola_vacia(struct cola *colita)
{
	//cual es correcto?
	return(colita->final==NULL);
	//return(colita->inicio==NULL);
}

struct cola *crear_cola(struct cola *colita)
{
	colita= (struct cola *) malloc (sizeof(struct cola));
	colita->inicio = colita->final = NULL;
	return(colita);
}

void insertar_cola(struct cola *colita, int datos)
{
    struct elem_cola *temp;
    temp= (struct elem_cola *) malloc (sizeof(struct elem_cola));
    temp->dato = datos;
    temp->sig=NULL;

    if (cola_vacia(colita))
    {
        colita->inicio=temp;
    }
    else
    {
        colita->final->sig= temp;
    }
    colita->final = temp;
}

void mostrar_cola(struct cola *colita, const char *mensaje) //se encarga de mostrar los datos de la cola 
{
    printf("\n%s\n", mensaje);
    struct elem_cola *temp = colita->inicio;
    while (temp != NULL)
    {
        printf("%d -> ", temp->dato); //num->num->null como imprimiria
        temp = temp->sig;
    }
    printf("NULL\n");
}

//eliminar, regrese el primer elemento de la cola y lo remueva
//desencolar = dequeue
int borrar_cola(struct cola *colita)
{
    struct elem_cola *temp;
    int dato;

    if(cola_vacia(colita))
    {
        printf("La cola está vacía.\n");
        return -1;
    }

    temp = colita->inicio;
    dato = temp->dato;
    colita->inicio = colita->inicio->sig;

    if(colita->inicio == NULL)
    {
        colita->final = NULL;
    }

    free(temp);
    return dato;
}

//funcion que regrese el primer elemento pero que no lo borre
int primer_elem(struct cola *colita)
{
    if(cola_vacia(colita))
    {
        printf("La cola está vacía.\n");
        return -1;
    }

    return colita->inicio->dato;
}

int main(int argc, char const *argv[])
{
    
    struct cola *colita = crear_cola(colita);

    insertar_cola(colita, 10);
    insertar_cola(colita, 20);
    insertar_cola(colita, 30);
    insertar_cola(colita, 40);
    mostrar_cola(colita, "Cola llena:");//muestra la cola original si eliminar elementos

    printf("Primer elemento: %d\n", primer_elem(colita));

    borrar_cola(colita);
    borrar_cola(colita);
    mostrar_cola(colita, "Cola desencolada:"); //muestra los elementos que quedan que no fueron eliminados 

    printf("Siguiente en la fila: %d\n", primer_elem(colita));

    return 0;
}