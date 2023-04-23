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

void ingresarValor(char* cadena, char* texto)
{
    puts("========================================");
    printf("%s:\n", texto);
    puts("========================================");
    scanf("%30[^\n]", cadena);
    while(getchar() != '\n');
}

void mostrarMenu()
{
    puts("========================================");
    puts("             Menu Jugadores:");
    puts("========================================");

    puts("1. Crear Jugador");
    puts("2. Mostrar Jugador");
    puts("3. Agregar Item a Jugador");
    puts("4. Eliminar Item de Jugador");
    puts("5. Agregar Puntos de Habiliad a Jugador");
    puts("6. Mostrar Jugador con Item especifico");
    puts("7. Deshacer Ultima Accion de Jugador");
    puts("8. Exportar datos de Jugador a Archivo de Texto"); // Sin implementar
    puts("9. Cargar datos de Jugador desde Archivo de Texto");
    puts("10. Salir");
    puts("========================================");
}

void crearJugador(char* nombre, Map* jugadores)
{
    if(searchMap(jugadores, nombre) == NULL)
    {
        Jugador* jugador = (Jugador*) malloc(sizeof(Jugador));

        strcpy(jugador->nombre, nombre);
        jugador->ptsHabilidad = 0;
        jugador->cantItems = 0;
        jugador->items = createList();
        jugador->acciones = stack_create();

        insertMap(jugadores, jugador->nombre, jugador);
        puts("\n========================================");
        puts("         Jugador creado exitosamente");
        puts("========================================");
    }
    else
    {
        puts("\n========================================");
        puts("         El jugador ya existe");
        puts("========================================");
    }

    sleep(2);
}

void mostrarJugador(char* nombre, Map* jugadores)
{
    Jugador* jugador = searchMap(jugadores, nombre);

    if(jugador != NULL)
    {
        puts("\n========================================");
        printf("    Nombre: %s\n", jugador->nombre);
        printf("    Puntos de Habilidad: %d\n", jugador->ptsHabilidad);
        printf("    Cantidad de Items: %d\n", jugador->cantItems);

        if(jugador->cantItems > 0)
        {
            int contadorItems = 1;
            char* item = firstList(jugador->items);

            puts("========================================");
            puts("    Items:");
            puts("========================================");

            while(item != NULL)
            {
                printf("    Item %d: %s\n", contadorItems, item);
                item = nextList(jugador->items);
                contadorItems++;
            }

            puts("========================================");
        }
        else
        {
            puts("========================================");
            puts("           No tiene items");
            puts("========================================");
        }
    }
    else
    {
        puts("\n========================================");
        puts("         El jugador no existe");
        puts("========================================");
    }

    puts("");
    system("pause");
}

void agregarItem(char* nombre, char* nombreItem, Map* jugadores, Jugador* jugador)
{
    Item* item = (Item*) malloc(sizeof(Item));
    strcpy(item->nombreItem, nombreItem);

    pushBack(jugador->items, item);

    jugador->cantItems++;

    puts("\n========================================");
    puts("         Item agregado exitosamente");
    puts("========================================");

    // Aqui agregamos la accion a la pila de acciones
    Accion* accion = (Accion*) malloc(sizeof(Accion));
    strcpy(accion->nombreAccion, "agregarItem");
    accion->datoAccion = item;

    stack_push(jugador->acciones, accion);

    puts("");
    system("pause");
}

void eliminarItem(char* nombre, char* nombreItem, Map* jugadores, Jugador* jugador)
{
    Item* item = firstList(jugador->items);

    while(item != NULL)
    {
        if(strcmp(item->nombreItem, nombreItem) == 0)
        {
            popCurrent(jugador->items);

            jugador->cantItems--;

            puts("\n========================================");
            puts("         Item eliminado exitosamente");
            puts("========================================");

            // Aqui agregamos la accion a la pila de acciones
            Accion* accion = (Accion*) malloc(sizeof(Accion));
            strcpy(accion->nombreAccion, "eliminarItem");
            accion->datoAccion = item;

            stack_push(jugador->acciones, accion);

            puts("");
            system("pause");
            return;
        }

        item = nextList(jugador->items);
    }

    puts("\n========================================");
    puts("         El item no existe");
    puts("========================================");

    puts("");
    system("pause");
}

void agregarPuntosHabilidad(char* nombre, int ptsHabilidad, Map* jugadores, Jugador* jugador)
{
    jugador->ptsHabilidad += ptsHabilidad;

    puts("\n========================================");
    puts("Puntos de habilidad agregados exitosamente");
    puts("========================================");

    // Aqui agregamos la accion a la pila de acciones
    Accion* accion = (Accion*) malloc(sizeof(Accion));
    strcpy(accion->nombreAccion, "agregarPuntosHabilidad");
    accion->datoAccion = (void *) ptsHabilidad;

    stack_push(jugador->acciones, accion);

    puts("");
    system("pause");
}

int main(int argc, const char * argv[])
{
    int opcion;
    char nombre[MAXCHAR];
    char nombreItem[MAXCHAR];
    Jugador* jugador;

    /*  Aqui Creamos el mapa para guardar jugadores*/
    Map* jugadores = createMap(is_equal_string);
    
    system("cls");
    puts("========================================");
    puts("               Trabajo 2");
    puts("     Desarrollado por Grupo ERROR 404");
    puts("========================================");
    sleep(2);

    do{
        system("cls");
        mostrarMenu();
        puts("");
        printf("Eliga una opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');
        
        switch (opcion)
        {
            case 1:
                system("cls");

                ingresarValor(nombre, "    Ingrese el nombre del jugador");

                crearJugador(nombre, jugadores);

                break;
            case 2:
                system("cls");

                ingresarValor(nombre, "    Ingrese el nombre del jugador");

                mostrarJugador(nombre, jugadores);
                break;
            case 3:
                system("cls");

                ingresarValor(nombre, "    Ingrese el nombre del jugador");

                jugador = searchMap(jugadores, nombre);

                if(jugador != NULL)
                {
                    ingresarValor(nombreItem, "    Ingrese el nombre del item");

                    puts("");
                    agregarItem(nombre, nombreItem, jugadores, jugador);
                }
                else
                {
                    puts("\n========================================");
                    puts("         El jugador no existe");
                    puts("========================================");

                    puts("");
                    system("pause");
                }

                break;
            case 4:
                system("cls");

                ingresarValor(nombre, "    Ingrese el nombre del jugador");

                jugador = searchMap(jugadores, nombre); 

                if(jugador != NULL)
                {
                    puts("");
                    ingresarValor(nombreItem, "    Ingrese el nombre del item");

                    eliminarItem(nombre, nombreItem, jugadores, jugador);
                }
                else
                {
                    puts("\n========================================");
                    puts("         El jugador no existe");
                    puts("========================================");

                    puts("");
                    system("pause");
                }

                break;
            case 5:
                system("cls");

                ingresarValor(nombre, "    Ingrese el nombre del jugador");
                
                jugador = searchMap(jugadores, nombre);

                if(jugador != NULL)
                {
                    int ptsHabilidad;
                    char cadenaPts[MAXCHAR];

                    puts("");
                    ingresarValor(cadenaPts, "Ingrese los puntos de habilidad a agregar");
                    ptsHabilidad = atoi(cadenaPts);

                    agregarPuntosHabilidad(nombre, ptsHabilidad, jugadores, jugador);
                }
                else
                {
                    puts("\n========================================");
                    puts("         El jugador no existe");
                    puts("========================================");

                    puts("");
                    system("pause");
                }
                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:

                break;
            case 10:
                system("cls");
                printf("Saliendo...\n");
                sleep(2);
                system("cls");
                break;
            default:
                printf("\nOpcion no valida. Intente nuevamente.\n\n");
                system("pause");
        }
   } while (opcion != 10);

    return EXIT_SUCCESS;
    
}
