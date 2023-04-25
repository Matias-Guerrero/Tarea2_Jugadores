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
    Map* items;
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
    puts("===================================================");
    puts("                Menu Jugadores:");
    puts("===================================================");

    puts("1. Crear Jugador");
    puts("2. Mostrar Jugador");
    puts("3. Agregar Item a Jugador");
    puts("4. Eliminar Item de Jugador");
    puts("5. Agregar Puntos de Habiliad a Jugador");
    puts("6. Mostrar Jugador con Item especifico");
    puts("7. Deshacer Ultima Accion de Jugador"); // Sin implementar
    puts("8. Exportar datos de Jugadores a Archivo de Texto"); // Sin implementar
    puts("9. Cargar datos de Jugadores desde Archivo de Texto"); // Sin implementar
    puts("10. Salir");
    puts("===================================================");
}

void crearJugador(char* nombre, Map* jugadores)
{   
    // Buscamos si el jugador existe o no
    if(searchMap(jugadores, nombre) == NULL) // Si el jugador no existe
    {
        // Creamos el jugador
        Jugador* jugador = (Jugador*) malloc(sizeof(Jugador));

        // Asignamos los valores
        strcpy(jugador->nombre, nombre);
        jugador->ptsHabilidad = 0;
        jugador->cantItems = 0;
        jugador->items = createMap(is_equal_string); // Creamos el mapa de items
        jugador->acciones = stack_create(); // Creamos la pila de acciones

        // Insertamos el jugador en el mapa
        insertMap(jugadores, jugador->nombre, jugador);

        // Se muestra que el jugador fue creado exitosamente
        puts("\n========================================");
        puts("         Jugador creado exitosamente");
        puts("========================================");
    }
    else // Si el jugador ya existe
    {
        // Se muestra que el jugador ya existe
        puts("\n========================================");
        puts("         El jugador ya existe");
        puts("========================================");
    }

    sleep(2);
}

void mostrarJugador(char* nombre, Map* jugadores)
{
    // Buscamos el jugador
    Jugador* jugador = searchMap(jugadores, nombre);

    if(jugador != NULL) // Si el jugador existe
    {
        // Mostramos los datos del jugador
        puts("\n========================================");
        printf("    Nombre: %s\n", jugador->nombre);
        printf("    Puntos de Habilidad: %d\n", jugador->ptsHabilidad);
        printf("    Cantidad de Items: %d\n", jugador->cantItems);

        if(jugador->cantItems > 0) // Si el jugador tiene items
        {
            // Se crea un contador para mostrar el numero de item
            int contadorItems = 1;

            // Se obtiene el primer item de la lista
            char* item = firstMap(jugador->items);

            puts("========================================");
            puts("    Items:");
            puts("========================================");

            // Mientras el item no sea NULL
            while(item != NULL)
            {
                // Se muestra el item
                printf("    Item %d: %s\n", contadorItems, item);
                item = nextMap(jugador->items); // Se obtiene el siguiente item
                contadorItems++; // Se aumenta el contador de items
            }

            puts("========================================");
        }
        else // Si el jugador no tiene items
        {
            // Se muestra que no tiene items
            puts("========================================");
            puts("           No tiene items");
            puts("========================================");
        }
    }
    else // Si el jugador no existe
    {
        // Se muestra que el jugador no existe
        puts("\n========================================");
        puts("         El jugador no existe");
        puts("========================================");
    }

    // Se muestra un mensaje de presione una tecla para continuar
    puts("");
    system("pause");
}

void agregarItem(char* nombre, char* nombreItem, Map* jugadores, Jugador* jugador)
{
    // Aqui agregamos el item a la lista de items
    Item* item = (Item*) malloc(sizeof(Item));
    strcpy(item->nombreItem, nombreItem);

    insertMap(jugador->items, item->nombreItem, item);

    // Aqui aumentamos la cantidad de items
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
    // Aqui eliminamos el item de la lista de items
    // Primero buscamos el item
    Item* item = searchMap(jugador->items, nombreItem);

    if(item != NULL) // Si el item existe
    {
        // Se elimina el item
        eraseMap(jugador->items, nombreItem);

        jugador->cantItems--; // Se disminuye la cantidad de items del jugador

        // Se muestra que el item fue eliminado exitosamente
        puts("\n========================================");
        puts("         Item eliminado exitosamente");
        puts("========================================");

        // Aqui agregamos la accion a la pila de acciones
        Accion* accion = (Accion*) malloc(sizeof(Accion));
        strcpy(accion->nombreAccion, "eliminarItem");
        accion->datoAccion = item;

        stack_push(jugador->acciones, accion); // Se agrega la accion a la pila de acciones

        // Se muestra un mensaje de presione una tecla para continuar
        puts("");
        system("pause");
        return;
    }

    puts("\n========================================");
    puts("         El item no existe");
    puts("========================================");

    puts("");
    system("pause");
}

void agregarPuntosHabilidad(char* nombre, int ptsHabilidad, Map* jugadores, Jugador* jugador)
{
    // Se agregan los puntos de habilidad
    jugador->ptsHabilidad += ptsHabilidad;

    // Se muestra que los puntos de habilidad fueron agregados exitosamente
    puts("\n========================================");
    puts("Puntos de habilidad agregados exitosamente");
    puts("========================================");

    // Aqui agregamos la accion a la pila de acciones
    Accion* accion = (Accion*) malloc(sizeof(Accion));
    strcpy(accion->nombreAccion, "agregarPuntosHabilidad");
    accion->datoAccion = (void *) ptsHabilidad;

    // Se agrega la accion a la pila de acciones
    stack_push(jugador->acciones, accion);

    // Se muestra un mensaje de presione una tecla para continuar
    puts("");
    system("pause");
}

void mostrarJugadoresItem(char* nombreItem, Map* jugadores)
{
    // Se obtiene el primer jugador del mapa
    Jugador* jugador = firstMap(jugadores);
    int contadorJugadores = 0; // Se crea un contador de jugadores
    bool hayJugadores = false; // Se crea una variable para saber si hay jugadores con el item

    // Mientras el jugador no sea NULL
    while(jugador != NULL)
    {   
        Item* item = searchMap(jugador->items, nombreItem); // Se busca el item

        if(item != NULL) // Si el item existe
        {   
            // Si no hay jugadores con el item
            if(!hayJugadores)
            {   
                // Se muestra el titulo de jugadores con el item
                puts("\n========================================");
                puts("        Jugadores con el item:");
                puts("========================================");
            }

            // Se muestra el nombre del jugador
            printf("    - %s\n", jugador->nombre);
            contadorJugadores++; // Se aumenta el contador de jugadores
            hayJugadores = true; // Se cambia la variable a true
        }

        // Se obtiene el siguiente jugador
        jugador = nextMap(jugadores);
    }

    if(contadorJugadores == 0) // Si no hay jugadores con el item
    {
        puts("\n========================================");
        puts("     No hay jugadores con ese item");
        puts("========================================");
    }
    else // Si hay jugadores con el item
    {
        puts("========================================");
        printf(" Total de jugadores con el item: %d\n", contadorJugadores);
        puts("========================================");
    }

    // Se muestra un mensaje de presione una tecla para continuar
    puts("");
    system("pause");
}

void deshacerAccion(char *nombreJugador, Map *jugadores)
{   
    Jugador* jugador = searchMap(jugadores, nombreJugador);
    
    Accion* ultima_accion = stack_top(jugador->acciones);

    if(ultima_accion == NULL)
    {
        puts("\n========================================");
        printf("%s no tiene ninguna accion a eliminar\n", jugador->nombre);
        puts("========================================");
        
        puts("");
        system("pause");
        return;
    }

    if(strcmp(ultima_accion->nombreAccion, "agregarItem") == 0)
    {
        stack_pop(jugador->acciones);
        eraseMap(jugador->items, ((Item*) ultima_accion->datoAccion)->nombreItem);
        jugador->cantItems--;

        puts("\n========================================");
        puts("     Accion agregarItem deshecha");
        puts("========================================");
    }
    
    if(strcmp(ultima_accion->nombreAccion, "eliminarItem") == 0)
    {
        stack_pop(jugador->acciones);
        insertMap(jugador->items, ((Item*) ultima_accion->datoAccion)->nombreItem, ultima_accion->datoAccion);
        jugador->cantItems++;
        
        puts("\n========================================");
        puts("     Accion eliminarItem deshecha");
        puts("========================================");
    }

    if(strcmp(ultima_accion->nombreAccion, "agregarPuntosHabilidad") == 0)
    {
        stack_pop(jugador->acciones);
        jugador->ptsHabilidad -= (int) ultima_accion->datoAccion;
      
        puts("\n========================================");
        puts("  Accion agregarPuntoHabilidad deshecha");
        puts("========================================");
    }

    puts("");
    system("pause");
}

void guardarJugadores(char* nombreArchivo, Map* jugadores)
{
    FILE* archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL)
    {
        puts("\n========================================");
        puts("   El archivo no se creo correctamente");
        puts("========================================");
    }
    else
    {
        // Columnas de archivo a escribir:
        // Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8
        fprintf(archivo, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");

        Jugador* jugador = firstMap(jugadores);

        while(jugador != NULL)
        {
            fprintf(archivo, "%s,%d,%d", jugador->nombre, jugador->ptsHabilidad, jugador->cantItems);

            Item* item = firstMap(jugador->items);

            while(item != NULL)
            {
                fprintf(archivo, ",%s", item->nombreItem);
                item = nextMap(jugador->items);
            }

            fprintf(archivo, "\n");
            jugador = nextMap(jugadores);
        }

        puts("\n========================================");
        puts("     Jugadores guardados exitosamente");
        puts("========================================");
    }

    fclose(archivo);

    puts("");
    system("pause");
}

void cargarJugadores(char* nombreArchivo, Map* jugadores)
{
    FILE* archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL)
    {
        puts("\n========================================");
        puts("     El archivo no existe");
        puts("========================================");
    }
    else
    {
        // Columnas de archivo a leer:
        // Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8

        char linea[100*MAXCHAR];

        fgets(linea, 100*MAXCHAR, archivo);

        while(fgets(linea, 100*MAXCHAR, archivo))
        {
            char* nombre = strtok(linea, ",");

            if(searchMap(jugadores, nombre) == NULL)
            {
                char* ptsHabilidad = strtok(NULL, ",");
                char* cantItems = strtok(NULL, ",");

                Jugador* jugador = (Jugador*) malloc(sizeof(Jugador));
                strcpy(jugador->nombre, nombre);
                jugador->ptsHabilidad = atoi(ptsHabilidad);
                jugador->cantItems = atoi(cantItems);
                jugador->items = createMap(is_equal_string);
                jugador->acciones = stack_create();

                for(int i = 0; i < jugador->cantItems; i++)
                {
                    char* nombreItem = strtok(NULL, ",\n");

                    Item* item = (Item*) malloc(sizeof(Item));
                    
                    strcpy(item->nombreItem, nombreItem);

                    insertMap(jugador->items, item->nombreItem, item);
                }

                insertMap(jugadores, jugador->nombre, jugador);
            }
        }

        puts("\n========================================");
        puts("         Jugadores cargados");
        puts("========================================");
    }

    fclose(archivo);

    puts("");
    system("pause");
}

int main(int argc, const char * argv[])
{
    int opcion;
    char nombre[MAXCHAR];
    char nombreItem[MAXCHAR];
    char nombreArchivo[MAXCHAR];
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
                system("cls");
                
                ingresarValor(nombreItem, "    Ingrese el nombre del item");

                mostrarJugadoresItem(nombreItem, jugadores);

                break;
            case 7:
                system("cls");
                
                ingresarValor(nombre, "    Ingrese el nombre del jugador");

                if(searchMap(jugadores, nombre) != NULL)
                {
                    deshacerAccion(nombre, jugadores);
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
            case 8:
                system("cls");

                ingresarValor(nombreArchivo, "    Ingrese el nombre del archivo");

                guardarJugadores(nombreArchivo, jugadores);

                break;
            case 9:
                system("cls");

                ingresarValor(nombreArchivo, "    Ingrese el nombre del archivo");

                cargarJugadores(nombreArchivo, jugadores); 

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
