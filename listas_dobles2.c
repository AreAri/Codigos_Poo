#include <stdio.h>
#include <stdlib.h>

struct nodo_ld {
    int dato;
    struct nodo_ld *atras;
    struct nodo_ld *delante;
};

typedef struct nodo_ld nodo_ld;

nodo_ld *crear_nodo(int dato) {
    nodo_ld *nuevo_nodo = (nodo_ld *)malloc(sizeof(nodo_ld));
    nuevo_nodo->dato = dato;
    nuevo_nodo->atras = NULL;
    nuevo_nodo->delante = NULL;
    return nuevo_nodo;
}

void insertar_inicio(nodo_ld **head, int datos) {
    nodo_ld *nuevo_nodo = crear_nodo(datos);
    nuevo_nodo->atras = NULL; // El nuevo nodo será el primero, por lo que su 'atras' es NULL

    // Si la lista está vacía, simplemente asigna el nuevo nodo como 'head'
    if (*head == NULL) {
        nuevo_nodo->delante = NULL; // El 'delante' también es NULL porque no hay nodos después
        *head = nuevo_nodo;
    } else {
        // Si la lista no está vacía, inserta el nuevo nodo al inicio
        nuevo_nodo->delante = *head; // El 'delante' del nuevo nodo apunta al antiguo 'head'
        (*head)->atras = nuevo_nodo; // El 'atras' del antiguo 'head' apunta al nuevo nodo
        *head = nuevo_nodo; // Actualiza el 'head' para que apunte al nuevo nodo
    }
}
void insertar_final(nodo_ld **head, int dato) {
    nodo_ld *nuevo_nodo = crear_nodo(dato);
    if (*head == NULL) {
        *head = nuevo_nodo;
    } else {
        nodo_ld *aux = *head;
        while (aux->delante != NULL) {
            aux = aux->delante;
        }
        aux->delante = nuevo_nodo;
        nuevo_nodo->atras = aux;
    }
}

void eliminar_nodo(nodo_ld **head, int dato) {
    nodo_ld *aux = *head;
    while (aux != NULL) {
        if (aux->dato == dato) {
            if (aux->atras != NULL) {
                aux->atras->delante = aux->delante;
            } else {
                *head = aux->delante;
            }
            if (aux->delante != NULL) {
                aux->delante->atras = aux->atras;
            }
            free(aux);
            return;
        }
        aux = aux->delante;
    }
}

void imprimir_lista(nodo_ld *head) {
    nodo_ld *aux = head;
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->delante;
    }
    printf("\n");
}
void liberar_memoria(nodo_ld *head) {
    nodo_ld *actual = head;
    nodo_ld *siguiente;

    while (actual != NULL) {
        siguiente = actual->delante;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    nodo_ld *head = NULL;

    insertar_inicio(&head, 5);
    insertar_final(&head, 10);
    insertar_inicio(&head, 3);
    insertar_final(&head, 15);

    imprimir_lista(head);

    eliminar_nodo(&head, 10);

    imprimir_lista(head);

    return 0;
}