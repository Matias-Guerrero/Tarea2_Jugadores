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

int main(int argc, const char * argv[])
{
    int opcion;
    char nombre[MAXCHAR];

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
                
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                
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
