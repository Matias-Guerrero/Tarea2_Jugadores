# Tarea2_Jugadores
Tarea N°2 de Estructura de Datos, Ingeniería Civil Informática

Control de jugadores implementado con las TDAs mapa y pila.
======

---
**Antes de Empezar**

*   Creamos un repositorio en GitHub con el uso de comandos en git bash, el link es el siguiente: https://github.com/Matias-Guerrero/Tarea2_Jugadores
*   Utilizamos Visual Studio Code para que cada integrante del grupo clonara el repositorio en sus computadores.
*   Para ejecutar el codigo comenzamos compilando nuestros archivos .c a traves de la terminal con el siguiente comando: `gcc -g main.c list.c Map.c -o Tarea2`, con este comando se crea un archivo .exe, luego para ejecutar Tarea2.exe utilizamos el siguiente comando: `\Tarea2.exe`.
*   Para ejecutar el codigo se debe descargar solo el archivo `Tarea2.exe`.

---

En esta aplicacion implementamos las siguientes TDAs: 

* TDA Mapa:

  ````c
  typedef struct Node Node;

  struct Node {
      void * key;
      /*! Puntero al dato */
      void * data;

      /*! Puntero al siguiente nodo */
      Node * next;

      /*! Puntero al anterior nodo */
      Node * prev;
  };

  struct Map {
      /*! Puntero al incio (cabeza) de la lista */
      Node * head;

      /*! Puntero al final (cola) de la lista */
      Node * tail;

      /*! Punteor para poder recorrer la lista */
      Node * current;

      int (*is_equal)(void* key1, void* key2);
      int (*lower_than)(void* key1, void* key2);

  };
  ````

  * TDA Pila ( Lista disfrazada de pila ):

    * TDA Lista:

        ````c
        typedef struct Node Node;

        struct Node {
            const void * data;
            Node * next;
            Node * prev;
        };

        struct List {
            Node * head;
            Node * tail;
            Node * current;
        };

        typedef List List;

        Node * createNode(const void * data) {
            Node * new = (Node *)malloc(sizeof(Node));
            assert(new != NULL);
            new->data = data;
            new->prev = NULL;
            new->next = NULL;
            return new;
        };
        ````

    * Se crea un archivo stack.h para renombrar las operaciones del TDA Lista y crear las operaciones de la pila:

      ````c
      typedef List Stack;

      #define stack_create() createList()

      #define stack_push(stack, data) pushFront(stack, data)

      #define stack_pop(stack) popFront(stack)

      #define stack_top(stack) firstList(stack)

      #define stack_clean(stack) cleanList(stack)
      ````
---

Se nos pidió crear una aplicación que almacena jugadores de un videojuego, cada jugador tiene un nombre, sus puntos de habilidad, la cantidad de items que posee, una lista de items y ademas una pila de acciones realizadas por el jugador.

Para esto definimos las siguientes struct en c:

* Jugador:
````c
typedef struct{
    char nombre[MAXCHAR];
    int ptsHabilidad;
    int cantItems;
    Map* items;
    Stack* acciones;
}Jugador;
````

* Item:
````c
typedef struct{
    char nombreItem[MAXCHAR];
}Item;
````

* Accion:
````c
typedef struct{
    char nombreAccion[MAXCHAR];
    void* datoAccion;
}Accion;
````
---

Este programa comienza con la funcion main mostrando el menu de opciones de la aplicacion, para esto llamamos a la funcion menu(), este menu lo integramos dentro de un bucle do-while ya que cada vez que elijamos una opcion valida se vuelve al menu despues de completar la accion correspondinte, ademas si se ingresa una opcion erronea se mostrara un mensaje por pantalla y se volvera al menu.

Para ingresar a cierta opcion del menu, se debe ingresar valores enteros entre 1 y 10, dependiendo de lo que uno desee realizar, para esto utilizamos un switch, asi estructuramos adecuadamente todas las funciones que debemos implementar.

Funciones Implementadas:
----

- **Opcion 1:** `void crearJugador(char* nombre, Map* jugadores)`.
    
    Cuando el usuario elige la opción 1, se llama a la función llamada  `crearJugador()` que crea un nuevo jugador en un mapa de jugadores, toma dos argumentos: el nombre del jugador y un punteo a un mapa de jugadores. el código comprueba si el nombre del jugador ya existe en el mapa con la función `searchMap()` (si ya existe se mostra) , si este existiese no se registraría en el mapa de jugadores, en el caso de que no exista , se crea un nuevo jugador utilizando la función `malloc` para asignar memoria dinámicamente.

    Luego, se inicializan los campos del jugador: el nombre se copia en la estructura, `ptsHabilidad` y `cantItems` se inicializan en `0`, `items` se inicializa como una lista vacía que creamos con la funnción createList(), y `acciones` se inicializa como una pila vacía que creamos mediante la función `stack_create()`. Finalmente, el nuevo jugador se inserta en el mapa utilizando la función `insertMap()`.


    
- **Opcion 2:** `void mostrarJugador(char* nombre, Map* jugadore)`.
    
    Luego de que el usuario elija la opción 2, se llama a función `mostrarJugador()`, que toma 2 argumentos: el nombre del jugador y un puntero a un mapa de jugadores.

    Primero, la función busca utilizando la función `searchMap()` para ver si se encuentra el jugador buscado en el mapa y asignar el resultado a un puntero a `Jugador`. Si el jugador existe (Si es puntero NO es nulo), la función muestra el nombre del jugador, la cantidad de puntos de habilidad y la cantidad de ítems que tiene el jugador.

    En el caso de que la cantidad de ítems sea mayor a cero, se muestra una lista con los items del jugador. Para ello se utiliza un contador para enumerar cada item, se obtiene el primer ítem de la lista del jugador utilizando la función `firstList()`, y luego se recorre la lista utilizando la función nextList() para el resto de ítems. Cada ítem se muestra junto con su cantidad en orden (en el caso de que la cantidad de ítems sea igual a 0, se muestra un mensaje indicando que el jugador no posee ítems, o si el jugador no existe, se muestra un mensaje de error)




- **Opcion 3:** `void agregarItem(char* nombre, char* nombreItem, Map* jugadores, Jugador* jugador)`.
    
    Una vez elegida la opción 3, se llama a la función `ingresarValor()` la cual le pide al usuario que ingrese el nombre del jugador y se valida que la variable de tipo char no supere los 30 caracteres.
    Luego en la variable jugador se guarda lo que retorna la` funcion searchMap()` la cual busca si en el mapa jugadores está el nombre que ingresamos la cual es la clave que se va comparando. 
    En caso de que el jugador sea distinto de nulo llama nuevamente a la función `ingresarValor()` la cual le pide al usuario ingresar el ítem que sea agregar al jugador, después se llama a la función `agregarItem()`, en donde lo primero que hace es llamar a la función `serchMap()` el cual busca el nombre del ítem ingresado, para preguntar en el condicional if si `item` es nulo, se debe crear el item asignando memoria con malloc para así asignar el nombre ingresado del item e insertarlo en el mapa de items del jugador con la función insertMap(), luego de insertar se aumenta la cantidad de items del jugador y se muestra un mensaje indicando que el item fue creado exitosamente.
    Además se debe asignar memoria para  agregar `accion` la cual contiene la información sobre la accion `agregarItem` y se agrega a la pila de acciones del jugador con la función `stack_push()`. Y en caso que el ítem ya existe se muestra por pantalla un mensaje que indica que el ítem si existe.
    Y en el caso que el jugador sea nulo, se muestra por pantalla que el jugador no existe.




- **Opcion 4:** `void eliminarItem(char* nombre, char* nombreItem, Map* jugadores, Jugador* jugador)`.

    Una vez elegida la opción 4 se llama a la función `ingresarValor()` la cual le pide al usuario que ingrese el nombre del jugador y se valida que la variable de tipo char no supere los 30 caracteres.
    Luego en la variable jugador se guarda lo que retorna la funcion `searchMap()` la cual busca si en el mapa jugadores está el nombre que ingresamos la cual es la clave que se va comparando.
    En caso que el jugador sea distinto de nulo se ingresa al condicional if, donde se vuelve a llamar a la función `ingresarValor()` la cual le pide al usuario ingresar el ítem que sea eliminar al jugador, después se llama a la función `eliminarItem()`, en donde lo primero que hace es llamar a la función `searchMap` el cual busca el nombre del ítem ingresado. Si el item es nulo ingresa al condicional if en el cual, con la función `eraseMap()` se elimina el item y se debe disminuir la cantidad de item del jugador, una vez realizado todo esto se muestra por pantalla  que el item fue eliminado exitosamente. Además se debe asignar memoria para  agregar `accion` la cual contiene la información sobre la accion `eliminarItem` y se agrega a la pila de acciones del jugador con la función `stack_push()`. Y en caso que el ítem no existe se muestra por pantalla un mensaje que indica que el ítem no existe.




- **Opcion 5:** `void agregarPuntosHabilidad(char* nombre, int ptsHabilidad, Map* jugadores, Jugador* jugador)`.

    Antes de entrar a la función, pide al usuario que ingrese al jugador a seleccionar para el proceso y verifica que exista. Si existe entra en la función, caso contrario se muestra por pantalla que el jugador no existe.

    Esta elección lleva al llamado de `agregarPuntosHabilidad`, esta función al iniciar toma el parámetro `ptsHabilidad` y suma la cantidad a la variable de `jugador->ptsHabilidad`, actualizando la cantidad de puntos del jugador inmediatamente. Posterior a esta acción, se muestra un mensaje de éxito y se guarda la acción a través de la pila acción del jugador de la siguiente manera: se crea una nueva variable tipo `acción` la cual reservaremos memoria y luego le copiaremos un string identificativo `agregarPuntosHabilidad` a la variable `accion->nombreAccion`, la cual servirá posteriormente para identificar la acción realizada. Luego de esto se guarda el dato `ptsHabilidad` dentro de `accion->datoAccion` y finaliza realizando un `stack Push` a la pila `jugador->acciones`.



- **Opcion 6:** `void mostrarJugadoresItem(har* nombreItem, Map* jugadores)`.

    Se selecciona la opción y le pide al usuario el ítem a ingresar para ingresarlo al parametro `nombreItem` de `mostrarJugadoresItem` y llama a esta misma función. 

    La operación comienza obteniendo el primer jugador del mapa de jugadores que se inicializa con un contador de jugadores para mostrar a los jugadores numerados y un bool para verificar si hay jugadores con items. Luego empieza a recorrer el mapa de jugadores y guarda una variable ítem que busca el parámetro `nombreItem` en el mapa de items de jugadores, en caso de que no lo encuentra, pasa al siguiente elemento del mapa. En el caso de que si hubo un jugador con un item, el bool `hayJugadores `pasa a True y se imprime un mensaje para mostrar que si hay items y empieza a listar todos los jugadores con el objeto solicitado en la función. En caso de que haya recorrido todo el mapa sin encontrar se imprime un mensaje de que no se han encontrado jugadores.


- **Opcion 7:** `void deshacerAccion(char *nombreJugador, Map *jugadores)`.

    Antes de entrar a la función, pide al usuario que ingrese al jugador a seleccionar para el proceso y verifica que exista. Si existe entra en la función, caso contrario se muestra por pantalla que el jugador no existe.

    Esta función deshace la última acción de la pila de acciones de un jugador. para lograr esto, buscamos el jugador `nombreJugador` que se paso como parametro en el mapa y se obtiene la última acción del `jugador->acciones` con un `stack_top`.  Ahora vienen los 4 casos posibles:
    
    1. Si la acción es nula retorna un mensaje y termina la función. 

    2. Si la última acción tiene `nombreAccion` igual a `agregarItem`, se elimina la acción de la pila y se elimina el item de la acción dicha del jugador, luego se reduce `jugador->cantItems` una unidad y muestra un mensaje de éxito.

    3. Si la última acción es `eliminarItem` se elimina la acción de la pila y se vuelve a insertar el ítem en el jugador y añadir 1 unidad a `cantItems` y muestra un mensaje.

    4. Si la última acción es `agregarPuntosHabilidad` se elimina la acción de la pila y se resta a `jugador->ptsHabilidad` los puntos guardados en `jultima_accion->datoAccion`, luego finaliza con un mensaje de éxito.

  Cuando termina la operación principal, se le solicita al usuario que presione una tecla para continuar.


- **Opcion 8:** `void guardarJugadores(char* nombreArchivo, Map* jugadores)`.

    Al seleccionar la opción 8 se llama a la función `guardarJugadores()`lo primero que hace es crear el archivo y verificar si se ha creado correctamente, en caso que no se haya creado de manera correcta el archivo se  muestra por pantalla un mensaje indicando que no se creó de manera correcta el archivo, en el caso contrario entra al condicional else en donde la primera línea del archivo son los nombres de las columnas.

    Luego se obtiene el primer jugador del mapa y se va recorrer el mapa de jugadores mientras sea distinto de nulo, y se va a escribir el nombre, los puntos de habilidad y la cantidad de ítems, después de obtiene el primer ítem del jugador de la lista de ítems para así recorrer la lista de ítems mientras sea distinto de nulo, y se va a escribir el nombre del item y por último se escribir un salto de línea.

    Una vez que se terminó de recorrer el mapa se muestra por pantalla un mensaje indicando que los jugadores se guardaron exitosamente y se cierra el archivo. Y para finalizar con la función se muestra un mensaje de presionar una tecla para continuar con la ejecución del programa.



- **Opcion 9:** `void cargarJugadores(char* nombreArchivo, Map* jugadores)`.
  
    Al seleccionar la opción 9 se llama a la función `cargarJugadores()`, en donde lo primero que hace es abrir el archivo en modo lectura y verificar si se abrió correctamente. En el caso que el archivo no exista, se muestra por pantalla un mensaje indicando que el archivo no existe. En caso contrario se lee la primera línea del archivo la cual contiene los nombres de las columnas que son: Nombre, Puntos de habilidad, #items, Item 1, Item 2, Item 3, Item 4, Item 5, Item 6, Item 7, Item 8.

    Después se crea un arreglo de caracteres para guardar la línea leída del archivo, luego se lee la primera línea del archivo, la cual responde a los nombres de las columnas, para así ir leyendo línea por línea y esperando cada campo mediante la función `strtok`, en donde se recibir como primer parámetro la línea que se va a separar y como segundo parámetro el carácter que delimitador que en este caso es la coma.

    Luego si el jugador no existe en el  mapa de jugadores se entra al condicional if, donde se van a obtener los puntos de habilidad y la cantidad de ítems del jugador, después se crea el jugador donde se le asignan la memoria y se copian los datos. Luego con un for se recorre la cantidad de items del jugador, se obtiene el nombre del item y se crea el ítem, y se utiliza la función para quitar las tildes del nombre de item y luego copiar el nombre del item con la función strcpy, luego se inserta el item en el mapa de items del jugador y finalmente se inserta el jugador en el mapa de jugadores, después se muestra por pantalla un mensaje indicando que los jugadores se han cargado. Por último se cierra el archivo y para finalizar con la función se muestra un mensaje de presionar una tecla para continuar con la ejecución del programa.



- **Opcion 10:** 

    Si se selecciona la opción 10, esto hará que se muestre un mensaje por pantalla que indica que se está saliendo del programa, lo cual cierre la terminal y dará término a la ejecución del programa de control de pacientes.

---

**Coevaluacion Personal**

| Nombres | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
|--------|--------------|----------------|--------------|--------------------|------------------|-------|
| Ulysses B. | 20 | 20 | 20 | 15 | 20 | 95 |
| Matías G. | 20 | 20 | 20 | 20 | 20 | 100 |
| Fabiana P. | 20 | 20 | 20 | 20 | 20 | 100 |
| Matías R. | 15 | 20 | 20 | 20 | 20 | 95 |

**Coevaluacion Grupal**

| Evaluación grupal | Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
|------------------|--------------|----------------|--------------|--------------------|------------------|-------|
| ERROR 404 | 20 | 20 | 15 | 20 | 15 | 90 |

# NOTA IMPORTANTE
Dentro de los primeros 5 commits, se encuentran 4 cuales están a nombre de un usuario `"Your Name"` (el otro commit está a nombre de nuestra compañera Fabiana Piña ya que utilizó el programa GitHub Desktop y se pudo identificar el commit sin iniciar sesión) debido a que  iniciamos sesión previamente en git bash. Por tanto aclararemos los nombres de cada integrante en estas actualizaciones:

17 de abril: 

*   Commit Título `"Creacion Repositorio Tarea 2."` subido por Matías
Guerrero

21 de abril: 
*   Commit Título `"Agregamos funcion mostrarMenu() y en el main agregamos la estructura …"` subido por Matías-Guerrero

22 de abril: 
*   Commit Título `"Agregamos la funcion ingresar valor y la funcion crear jugador, y en …"` subido por Mathi-sus
*   Commit Título `"se hizo la funcion mostrar jugador y se implemento dentro del menu."` subido por Odysseus-Horn
