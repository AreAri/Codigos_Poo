/*
    PROYECTO - EL COMPILADOR
    Areli Arisai Meza Rendón
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

enum Token_tipo 
{
    /* Enumeracion de los identificadores que se usaran */
    IDENTIFICADOR, //variables
    PALABRA_RESERVADA, //palabras reservadas que no cambian
    NUMERO, //numeros
    OPERADOR, //cualquier tipo de operados
    DELIMITADOR, //entran llaves y parentesis que tecnicamente nos dice de donde empieza y donde termina
    DESCONOCIDO, //desconocidos para mi o que no he utilizado
    SIMBOLO, //cualquier tipo de simbolos 
    LIBRERIA, //en teroria deberia estar stdio.h y similares funciona 
    ESPECIFICADOR_DE_FORMATO, //int %d, entre otros no funciona
    SECUENCIA_DE_ESCAPE, // \n no funciona 
    //estos 2 de arriba lo intente, pero no me funciono, me cerre y ya no pude ver que hacia mal
    TEXTO, //en caso de que haga texto
    TIPO //int, float etc
};

//declaramos los caracteres (los que me acorde) como no son cadena de caracteres se pone asi
const char *operadores = "+-*/=<>!%&";
const char *simbolos = ",;.""'#\\";
const char *delimitadores ="(){}[]";
//const char *formato = "%d, %s, %c, %i";

//arreglos aqui como ya aplica cadena de caracteres es necesario ponerlo como arreglo
const char *P_CLAVES[] = {
    "return", "if", "else", "while", "for", "main", "include", "printf", "puts", "const", "argc", "argv", "scanf"
};
const int num_P_CLAVES = sizeof(P_CLAVES) / sizeof(P_CLAVES[0]);

const char *types[] = {
    "int", "float", "char", "double", "void"
};
const int num_types = sizeof(types) / sizeof(types[0]);//calculamos el numero de elementos

const char *LIBRERIAs[] = {
    "stdio.h", "stdlib.h", "string.h", "stdbool.h", "ctype.h"
};
const int num_LIBRERIAs = sizeof(LIBRERIAs) / sizeof(LIBRERIAs[0]);

//berificamos si la cadena a comparar esta en los arreglos
bool es_PALABRA_RESERVADA(const char *str) 
{
    for (int i = 0; i < num_P_CLAVES; i++)
    {
        if (strcmp(str, P_CLAVES[i]) == 0) 
        {
            return true;
        }
    }
    return false;
}

bool es_tipo(const char *str) 
{
    for (int i = 0; i < num_types; i++) 
    {   
        if (strcmp(str, types[i]) == 0) 
        {
            return true;
        }
    }
    return false;
}

bool es_LIBRERIA(const char *str) 
{
    for (int i = 0; i < num_LIBRERIAs; i++) 
    {
        if (strcmp(str, LIBRERIAs[i]) == 0) 
        {
            return true;
        }
    }
    return false;
}

// Estructura para representar un token
struct Token 
{
    enum Token_tipo tipo; // Tipo del token
    char *valor; // Valor del token
    struct Token *next; // Puntero al siguiente token
    struct Token *antes; // Puntero al token antesio
};

/*struct Token* create_token(struct Tokentipo *tipo, const char *valor) 
{
    struct Token *token = (struct Token*) malloc(sizeof(struct Token));
    token->tipo = tipo;
    token->valor = (char*) malloc((strlen(valor) + 1) * sizeof(char));
    strcpy(token->valor, valor);
    token->next = NULL;
    token->antes = NULL;
    return token;
}*/


// Función para crear un nuevo token
struct Token* crear_token(enum Token_tipo tipo, const char *valor) 
{
    struct Token *token = (struct Token*) malloc(sizeof(struct Token)); // Asignar memoria para el token
    if (!token) 
    {
        printf("Error: No se pudo asignar memoria para el token\n");
        return NULL;
    }

    token->tipo = tipo; // Asignar el tipo al token
    token->valor = strdup(valor); // Copiar el valor al token
    if (!token->valor) 
    {
        printf("Error: No se pudo asignar memoria para el valor del token\n");
        free(token); // Liberar memoria del token
        return NULL;
    }

    token->next = token->antes = NULL; // Inicializar los punteros next y antes
    return token;
}

void agregar_token(struct Token **head, struct Token **fin, struct Token *nuevo_token) 
/* head inicio de la lista, fin final de la lista , nuevo token puntero al token
verificamos si esta vacia o no la lista*/
{
    if (*fin) //si si hay fin de la lista osea si h¿ya hay datos
    {
        (*fin)->next = nuevo_token; //apunta al nuevo token que se esta agregando
        nuevo_token->antes = *fin; //el fin apunta al final de la lista
        *fin = nuevo_token; //actualiza el puntero al ultimo 
    } 
    else 
    {
        *head = *fin = nuevo_token; //si esta vacia ambos apuntan al nuevo
    }
}

void free_tokens(struct Token *head) //liberamos memoria de los tokens con esta funcion
{
    struct Token *actual = head; //primer elemento de la lista 
    while (actual) //recorrido para poder liberar memoria de los tokens
    {
        struct Token *next = actual->next; //evitamos que se pierda  cada vez que libere
        free(actual->valor); //liberamos el token
        free(actual);//liberamos el que se encuentra actualmente
        actual = next;//avanzamos al sig token
    }
}

//las pilas
/* al principio no sabia como usarla, tanto asi que crei que la usaba y resulto que no, en fin lo que use fue su auxiliar ya que no supe usar la pila asi
    normal, lo que hace es que se crea la pila se almacenan los datos, se pasan a la uxiliar y de la auxiliar a la cola para que asi se imprima en el orden
    y no el orden reverso como cuando usaba la pila normal */
struct nodo_pila //definimos el nodo de la pila
{
    struct Token *token; //tomamos al token
    struct nodo_pila *next; //nos movemos
};

struct pila 
{
    struct nodo_pila *inicio; //apunta al primero de la pila, no al primero en entra si no al primero de hasta arriba
};

struct pila *crear_pila() //creamos la pila
{
    struct pila *pilita = (struct pila*) malloc(sizeof(struct pila));//asignamos si respectiva memoria
    if (pilita == NULL) 
    {
        printf("Error: No se pudo asignar memoria\n"); //esta cosa siempre se me olvida
        return NULL;
    }
    pilita->inicio = NULL; //empezamo con nada
    return pilita;
}

void push(struct pila *pilita, struct Token *token) 
{
    struct nodo_pila *nodo = (struct nodo_pila*) malloc(sizeof(struct nodo_pila));
    if (nodo == NULL) 
    {
        printf("Error: No se pudo asignar memoria\n"); 
        return;
    }
    nodo->token = token; //agregamos al token a la pila
    nodo->next = pilita->inicio; //apuntamos al inicio de la pila
    pilita->inicio = nodo;//actualizamos
}

struct Token* pop(struct pila *pilita) 
{
    if (pilita->inicio == NULL) //verificamos si esta vacia
    {
        return NULL;
    }
    struct nodo_pila *inicio = pilita->inicio; //iniciooral 
    struct Token *token = inicio->token;
    pilita->inicio = inicio->next; //iniciooral apunta al siguiente 
    free(inicio); //liberamos
    return token;
}

void free_pila(struct pila *pilita) //ahora liberamos a la pila
{
    while (pilita->inicio != NULL) 
    {
        struct nodo_pila *inicio = pilita->inicio;
        pilita->inicio = inicio->next;
        free(inicio);
    }
    free(pilita);
}

//ahora las colas
struct nodo_cola 
{
    struct Token *token;
    struct nodo_cola *next;
};

struct cola 
{
    struct nodo_cola *defrente;//inicio de la cola
    struct nodo_cola *rear;//ultimo
};

struct cola* crear_cola() //creamos la cola
{
    struct cola *colita = (struct cola*) malloc(sizeof(struct cola));
    if (colita == NULL) 
    {
        printf("Error: No se pudo asignar memoria para la cola\n");
        return NULL;
    }
    colita->defrente = colita->rear = NULL; //inicio y final estan en la nada
    return colita;
}

void encolar(struct cola *colita, struct Token *token) //agregamos nodos
{
    struct nodo_cola *nodo = (struct nodo_cola*) malloc(sizeof(struct nodo_cola));
    if (nodo == NULL) 
    {
        printf("Error: No se pudo asignar memoria para el nodo \n");
        return;
    }
    nodo->token = token;
    nodo->next = NULL;//el que se mueve esta en null
    if (colita->rear == NULL) //si esta vacia
    {
        colita->defrente = colita->rear = nodo; //ambos miran al nuevo
        return;
    }
    colita->rear->next = nodo; //si no esta se va agregando al siguiente
    colita->rear = nodo; //este esta con los nuevos
}

struct Token* desencolar(struct cola *colita) //quitamos
{
    if (colita->defrente == NULL) //por si esta vacia
    {
        return NULL;
    }
    struct nodo_cola *defrente = colita->defrente; //defrente es el iniciooral 
    struct Token *token = defrente->token;
    colita->defrente = defrente->next; //avanza
    if (colita->defrente == NULL) //si es vacia
    {
        colita->rear = NULL; //el final debe ser nulo
    }
    free(defrente); //liberamos el iniciooral
    return token;
}

void free_cola(struct cola *colita)  //liberamos a la cola
{
    while (colita->defrente != NULL) 
    {
        struct nodo_cola *defrente = colita->defrente;
        colita->defrente = defrente->next;
        free(defrente);
    }
    free(colita);
}

//el dolor de cabeza, el analisis lexico
struct Token* clasificacion_tokens(char **dato_entrada) //esto analiza y defienbe ya con la clasificacion del token y tiene un puntero doble para modificar
{
    char buffer[256]; //alamcenar los token
    int len = 0; //longitud del token

    while (isspace(**dato_entrada)) 
    {
        //omitimos los espacios en blanco (como la linea 301 es un espacio en blanco, los y tabulaciones espacios tambien cuentan)
        (*dato_entrada)++;
    }

    if (**dato_entrada == '\0') //si llega al final de la cadena significa que ya no hay mas tokens
    {
        return NULL;
    }

   if (isalpha(**dato_entrada) || **dato_entrada == '_') //verifica si el primero es una letra (isalpha)
   {
        while (isalnum(**dato_entrada) || **dato_entrada == '_') //isalnum verifica si es alfa numerico
        {
            buffer[len++] = *(*dato_entrada)++; //mientra que no sea alfanumerico el buffer va aumentando
        }
        buffer[len] = '\0';

        //CONTINUA PARA SEGUIR CLASIFICANDO ojito este es para validar lo de biblioteca o si no todo se pone por separado
        while (**dato_entrada == '.') 
        {
            buffer[len++] = *(*dato_entrada)++;
            while (isalnum(**dato_entrada) || **dato_entrada == '_') 
            {
                buffer[len++] = *(*dato_entrada)++;
            }
        }
        buffer[len] = '\0';
        //se compara con las contantes anteriores y poder clasificarlas
        if (es_PALABRA_RESERVADA(buffer)) 
        {
            struct Token *token = crear_token(PALABRA_RESERVADA, buffer); //crean los token que corresponden
            return token;
        } 
        else if (es_tipo(buffer)) 
        {
            struct Token *token = crear_token(TIPO, buffer);
            return token;
        } 
        else if (es_LIBRERIA(buffer)) 
        {
            struct Token *token = crear_token(LIBRERIA, buffer); 
            return token;
        }
        else 
        {
            struct Token *token = crear_token(IDENTIFICADOR, buffer);
            return token;
        }
    }
    else if (isdigit(**dato_entrada)) //si el primero es digito
    {
        while (isdigit(**dato_entrada)) 
        {
            buffer[len++] = *(*dato_entrada)++; //almacena todos los digitos
        }
        buffer[len] = '\0';
        struct Token *token = crear_token(NUMERO, buffer);  // y crea el token de numero
        return token;
    } 
    else if (strchr(operadores, **dato_entrada)) //srtchr busca el primer caracter
    { // Operadores
        buffer[len++] = *(*dato_entrada)++; //si lo encuentra lo agrega al buffer y se incrementa
        buffer[len] = '\0'; //despues lo pone al final de la cadena
        struct Token *token = crear_token(OPERADOR, buffer); // y crea el token que corresponde
        return token;
    } 
    else if (strchr(simbolos, **dato_entrada)) 
    { // Simbolos , ; .
        buffer[len++] = *(*dato_entrada)++;
        buffer[len] = '\0';
        struct Token *token = crear_token(SIMBOLO, buffer); // SIMBOLO
        return token;
    } 
    else if (strchr(delimitadores, **dato_entrada)) 
    {
        buffer[len++] = *(*dato_entrada)++;
        buffer[len] = '\0';
        struct Token *token = crear_token(DELIMITADOR, buffer); // DELIMITADOR
        return token;
    } 
    else if (**dato_entrada == '"') //si el primer caracter es la comilla
    {
        buffer[len++] = *(*dato_entrada)++;
        while (**dato_entrada && **dato_entrada != '"') //copia los caracteres dentro de las ""
        {
            if (**dato_entrada == '\\' && (*(*dato_entrada + 1) == 'n' || *(*dato_entrada + 1) == 't' || *(*dato_entrada + 1) == 'r')) 
            { //si encuentra una secuencia de escape igual la imprime pero no pude separarlo como tal del texto
                buffer[len++] = *(*dato_entrada)++;
                buffer[len++] = *(*dato_entrada)++;
            } else {
                buffer[len++] = *(*dato_entrada)++;
            }
        }
        if (**dato_entrada == '"') 
        {
            buffer[len++] = *(*dato_entrada)++;
        }
        buffer[len] = '\0';
        struct Token *token = crear_token(TEXTO, buffer); // crea el token
        return token;
    } 
    else 
    {
        (*dato_entrada)++;
        struct Token *token = crear_token(DESCONOCIDO, ""); 
        return token;
    }
}

void imprimir_token(FILE *crear_archivo, struct Token *token) //imprimo dentro de lo que es el archivo
{
    const char *tipo_str; //se encarga de buscar al token correcto e imprimirlo

    switch (token->tipo) //esto es mediante dependientos del tipo del token
    {
        case IDENTIFICADOR:
            tipo_str = "IDENTIFICADOR:";
            break;
        case PALABRA_RESERVADA:
            tipo_str = "PALABRA_RESERVADA:";
            break;
        case NUMERO:
            tipo_str = "NUMERO:";
            break;
        case OPERADOR:
            tipo_str = "OPERADOR:";
            break;
        case DELIMITADOR:
            tipo_str = "DELIMITADOR:";
            break;
        case DESCONOCIDO:
            tipo_str = "DESCONOCIDO:";
            break;
        case SIMBOLO:
            tipo_str = "SIMBOLO:";
            break;
        case LIBRERIA:
            tipo_str = "LIBRERIA:";
            break;
        case ESPECIFICADOR_DE_FORMATO:
            tipo_str = "ESPECIFICADOR_DE_FORMATO:";
            break;
        case SECUENCIA_DE_ESCAPE:
            tipo_str = "SECUENCIA_DE_ESCAPE:";
            break;
        case TEXTO:
            tipo_str = "TEXTO:"
            ;
            break;
        case TIPO:
            tipo_str = "TIPO:";
            break;
        default:
            tipo_str = "DESCONOCIDO:";
            break;
    }
    fprintf(crear_archivo, "%s %s\n", tipo_str, token->valor); //se imprime en este formato y haciendo un salto de linea cada vez que termina de identificarlo
}


char* apertura() 
{
    char archivo[256];
    FILE *file; // Puntero al archivo
    char *contenido;
    long file_size;

    puts("Ingresa el nombre de tu archivo con el formato debido");
    puts("Ejemplo: \nArchivo.c");
    scanf("%255s", archivo);

    // Abrir el archivo solo para leer
    file = fopen(archivo, "r");

    if (!file) 
    { // Si no se encuentra, manda mensaje de que no se pudo abrir
        puts("No se pudo abrir el archivo");
        return NULL;
    }

    //Obtener el tamaño del archivo SI LO QUITO REPITE LAS ULTIMAS LINEAS
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Allocar memoria para el contenido del archivo CREAS CON ESTO EL ARCHIVO NO LO QUITES
    contenido = (char *) malloc(sizeof(char) * (file_size + 1));

    // Leer el archivo completo
    fread(contenido, 1, file_size, file);
    contenido[file_size] = '\0'; // Agregar el caracter nulo al final

    fclose(file); // Cerrar el archivo

    return contenido;
}

int main() 
{
    char *dato_entrada = apertura();
    if (dato_entrada == NULL) 
    {
        return 1;
    }

    struct Token *head = NULL, *fin = NULL;

    while (*dato_entrada) 
    {
        struct Token *token = clasificacion_tokens(&dato_entrada);
        if (token == NULL) 
        {
            break;
        }
        agregar_token(&head, &fin, token);
    }

    // Crear pilas y cola
    struct pila *pilita = crear_pila(); //yo creia que si la usaba pero nunca vi un push ni un pop
    struct cola *colita = crear_cola();
    struct pila *pila_aux = crear_pila(); 

    // Transferir tokens de la lista a la pila ... aqui ya confirmo que la uso ya veo los push y pop
    struct Token *actual = head;
    while (actual) 
    {
        push(pilita, actual);
        actual = actual->next;
    }

    // de la pila original para a la copia para asi invertir los datos a como ingreso
     while (pilita->inicio) 
    {
        struct Token *token = pop(pilita);
        push(pila_aux, token);
    }

     // teniendo el orden correcto pasamos a la cola
    while (pila_aux->inicio) 
    {
        struct Token *token = pop(pila_aux);
        encolar(colita, token);
    }

    // Crear el archivo de salida
    FILE *crear_archivo = fopen("archivo_tokens.txt", "w");
    if (crear_archivo == NULL) 
    {
        perror("No se pudo abrir el archivo de salida");/*perror fue curioso, vi que lo usaban en tiktok cuando se quieren crear archivos y es para 
            imprimir un error pero con una descripcion de esta*/
        return 1;
    }

    // la cola se encarga de poner los tokens clasificados al archivo
    while (colita->defrente) 
    {
        struct Token *token = desencolar(colita);
        imprimir_token(crear_archivo, token);
    }

    fclose(crear_archivo); // Cerrar el archivo de salida

    free_tokens(head);
    free_pila(pilita); // Pila liberada
    free_cola(colita);
    free(dato_entrada); // Liberar la memoria del contenido del archivo
    return 0;
}