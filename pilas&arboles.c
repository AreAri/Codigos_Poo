#include <stdio.h>
#include <stdlib.h>

struct nodo 
{
    int num;
    struct nodo *sig;
};

int es_vacia(struct nodo *p) 
{
    return p == NULL;
}

//apilamos
int push(struct nodo **p, struct nodo *elemento)
{
    elemento->sig = *p;
    *p = elemento;
    return 1;
}

int mete_p(struct nodo **p, int num)
{
    struct nodo *nuevo;
    nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    if (!nuevo)
    {
        return 0;
    }
    nuevo->num = num;
    nuevo->sig = NULL;

    return push(p, nuevo);
}

// desapilar
struct nodo* pop(struct nodo **p)
{
    if (es_vacia(*p))
    {
        return NULL;
    }

    struct nodo *aux = *p;
    *p = (*p)->sig;
    return aux;
}

void preOrder() 
{
    struct nodo *noditos = NULL;

    // la raiz = el inicio
    mete_p(&noditos, 17);

    while (!es_vacia(noditos)) 
    {
        struct nodo *hijos = pop(&noditos);//sacamos nodo... noditos es lo que sigue en la pila
        printf("%d ", hijos->num);//impriminos el nodo que sacamos de nodito pasa ser hijo
        int padres = hijos->num; //el hijo se convierte en padre
        free(hijos);//no hay hijos

        if (padres == 17) 
        {
            mete_p(&noditos, 25);
            mete_p(&noditos, 8);
        } 
        else if (padres == 8) 
        {
            mete_p(&noditos, 12);
            mete_p(&noditos, 4);
        } 
        else if (padres == 25) 
        {
            mete_p(&noditos, 32);
            mete_p(&noditos, 20);
        } 
        else if (padres == 4) 
        {
            mete_p(&noditos, 6);
            mete_p(&noditos, 1);
        } 
        else if (padres == 12) 
        {
            mete_p(&noditos, 10);
        }
    }
}

int main(int argc, char const *argv[])
{
    printf("Recorrido en preorden: ");
    preOrder();
    printf("\n");

    return 0;
}