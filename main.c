#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "Map.h"
#include "list.h"
#include "stack.h"

#define MAXCHAR 30

typedef struct{
    char nombre[MAXCHAR];
    int ptsHabilidad;
    int cantItems;
    List* items;
    Stack* acciones;
}Jugador;

typedef struct{
    char nombreItem[MAXCHAR];
}Item;

typedef struct{
    char nombreAccion[MAXCHAR];
    void* datoAccion;
}Accion;

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}





int main(int argc, const char * argv[]) {

    return 0;
}
