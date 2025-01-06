// Empezamos con la pesadilla, hacer una lista doblemente ligada donde se inserte al principio, al final y entre ellos
//imagina que es una historieta o libro en linea el pag_anterior y pag_sig son los cambios de pagina que uno hace y lo que insertar son nuevas paginas

#include <stdio.h>
#include <stdlib.h>

struct libro
{
	int pag;
	struct libro *pag_anterior;
	struct libro *pag_sig;
};

//crea el nodo (crear libro)
struct libro *crear_libro (int pag);
//la funcion de vacio esa no puede faltar
int vacio(struct libro *portada);
//insertar al inicio
void insertar_I (struct libro **portada, int pag); //el **portada realmente seria el **head dando a entender que es la cabeza de la lista
//insertar al final
void insertar_F (struct libro **portada, int pag);
//insertar entre paginas
void insertar_E(struct libro **portada, int pag_anterior, int pag_nueva, int pag_siguiente);
//imprime el libro
void imprime (struct libro *portada);
//libera espacio
void liberar(struct libro **portada);
//elimina una pagina
void eliminar(struct libro **portada, int pag);


int main(int argc, char const *argv[])
{
	struct libro *portada = NULL;
	puts("Nuevo libro");
	insertar_I(&portada, 2);
	insertar_F(&portada, 3);
	insertar_I(&portada, 1);
	insertar_F(&portada, 4);
	insertar_F(&portada, 0);
	
	imprime(portada);

	puts("\nEliminando paginas");
	eliminar(&portada, 2);
	imprime(portada);

	puts("\nInserta entre pag ");
	insertar_E(&portada, 1, 2, 4);
	insertar_E(&portada, 3, 5 , 4);
	insertar_E(&portada, 5, 6, 0);
	imprime(portada);
	liberar(&portada);
	return 0;
}

//creas el libro
struct libro *crear_libro (int pag)
{
	struct libro *nuevo = (struct libro *)malloc(sizeof(struct libro));
	if (nuevo == NULL) 
	{
    	printf("Error: No hay memoria disponible para crear un nuevo libro.\n");
    	return NULL;
  	}
	nuevo->pag = pag;
	nuevo->pag_anterior = NULL;
	nuevo->pag_sig = NULL;
	return nuevo;
}

int vacio(struct libro *portada)
{
	return portada == NULL;
}

//inserta al principio (por si se te olvido agregar algo de inicio)
void insertar_I (struct libro **portada, int pag)
{
	struct libro *nuevo = crear_libro(pag);
	if (vacio(*portada))
	{
		nuevo ->pag_sig = NULL;
		*portada = nuevo;
		return;
	}
	else
	{
		//aun me confundo
		nuevo -> pag_sig = *portada; 
		(*portada)-> pag_anterior = nuevo;
		*portada = nuevo;
	}
}

//agregar al final (nuevos capitulos)
void insertar_F (struct libro **portada, int pag)
{
	struct libro *nuevo = crear_libro(pag);
	if (vacio(*portada))
	{
		*portada = nuevo;
		return;
	}
	else
	{
		struct libro *lector = *portada;
		while(lector -> pag_sig != NULL)
		{
			lector = lector->pag_sig;
		}
		lector->pag_sig = nuevo;
		nuevo -> pag_anterior = lector;
	}
}

//imprimir
void imprime (struct libro *portada)
{
	struct libro *lector = portada;
	while (lector != NULL)
	{
		printf("%d -> ", lector->pag );
		lector = lector->pag_sig;
	}
	printf("fin del libro\n");
}

void liberar(struct libro **portada) 
{
    struct libro *lector = *portada;
    while (lector!= NULL) 
    {
        libro *temp = lector;
        lector = lector->pag_sig;
        free(temp);
    }
    *portada = NULL;
}

void eliminar(struct libro **portada, int pag) //falta recursivo T_T
{
    struct libro *lector = *portada;
    if (vacio(*portada))
    {
        printf("no existe el libro\n");
        return;
    }
    while (lector != NULL) 
    {
        if (lector->pag == pag) 
        {
            if (lector->pag_anterior != NULL) //ver si la pagina tiene una anterior a ella
            {
                lector->pag_anterior->pag_sig = lector->pag_sig; //dibujalo porque te confundes 
            } 
            else 
            {
                *portada = lector->pag_sig; //si no continua leyendo
            }
            if (lector->pag_sig != NULL) //si la pagina tiene tiene una siguente de ella
            {
                lector->pag_sig->pag_anterior = lector->pag_anterior; //lo mismo que arriba
            }
            free(lector); //eliminamos pagina
            return;
        }
        lector = lector->pag_sig; //sigue leyendo
    }
}

//entre las paginas realmente se inserta en orden asi que debes cambiarlo
void insertar_E(struct libro **portada, int pag_anterior, int pag_nueva, int pag_siguiente) 
{
  struct libro *nuevo = crear_libro(pag_nueva);

  // Buscamos las paginas que selecciona el usuario (anterior y siguiente)
  struct libro *anterior = *portada;
  while (anterior != NULL && anterior->pag != pag_anterior) 
  {
    anterior = anterior->pag_sig;
  }

  struct libro *siguiente = anterior->pag_sig;

  // ok no funciona busca como arreglarlo 
  // if (anterior == NULL || siguiente == NULL) 
  // {
  //   printf("esas paginas no existen\n");
  //   return;
  // }

  // Insertar el nuevo nodo entre los nodos encontrados dibujalo tambien
  anterior->pag_sig = nuevo;
  nuevo->pag_anterior = anterior;
  nuevo->pag_sig = siguiente;
  siguiente->pag_anterior = nuevo;

  // Actualizar el puntero portada si se inserta al principio no esto no funciona no lo descomentes te quita el primer dato
  // if (anterior == *portada) 
  // {
  //   *portada = nuevo;
  // }
}

//buscar intenta ese para insertar por orden 
