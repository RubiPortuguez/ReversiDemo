#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 200

/* Función que solicita al usuario una elección sobre cómo proceder en el juego.
@return:
- 1 si el usuario elige guardar el progreso.
- 0 si el usuario decide continuar el juego sin guardar.*/
int seleccion(void) {
    // Variable para almacenar la elección del usuario
    int ev;

    // Mostrar las opciones al usuario
    printf("¿Qué deseas hacer?\n");
    printf("INGRESA 1 PARA GUARDAR TU PROGRESO.\n");
    printf("INGRESA 0 PARA CONTINUAR.\n");
    // Leer la elección del usuario
    scanf("%d", &ev);
    system("clear");

    return ev;
}

/*Función que solicita al usuario un nombre para el archivo donde se guardará la partida.
 @param:
 - nombre_archivo[]: Cadena donde se almacenará el nombre del archivo ingresado por el usuario.*/
void solicitar_nombre_archivo (char nombre_archivo[])
{
  // Solicitar al usuario el nombre del archivo
  printf("Ingresa el nombre del archivo donde deseas guardar la partida: \n");
  // Leer el nombre del archivo ingresado por el usuario
  scanf("%s", nombre_archivo);
}

/*Función para guardar el estado actual del juego en un archivo.
 @param:
 - archivo: Nombre del archivo donde se guardará la partida.
 - tablero[8][8]: Arreglo que representa el estado actual del tablero.
 - jugador1[]: Nombre del jugador 1.
 - jugador2[]: Nombre del jugador 2.
 - jugador_actual: Número del jugador que tiene el turno actual (1 o 2).
 - fichas_j1: Número de fichas del jugador 1.
 - fichas_j2: Número de fichas del jugador 2.
 - modo: Modo de juego actual (por ejemplo, jugador vs jugador o jugador vs CPU).*/
void guardar_partida(char *archivo, int tablero[8][8], char jugador1[], char jugador2[], int jugador_actual, int fichas_j1, int fichas_j2, int modo)
{
  FILE *file = fopen(archivo, "w"); // Abrir archivo en modo escritura

  int i;

  int j;

  // Validar que el archivo se abrió correctamente
  if (file == NULL) {
      printf("Error al guardar la partida.\n");
      return;
    }
  
  // Escribir los datos de la partida en el archivo
  fprintf(file, "Modo de Juego: %d\n", modo);
  fprintf(file, "Jugador 1: %s\n", jugador1);
  fprintf(file, "Jugador 2: %s\n", jugador2);
  fprintf(file, "Turno del Jugador: %d\n", jugador_actual);
  fprintf(file, "Fichas Jugador 1: %d\n", fichas_j1);
  fprintf(file, "Fichas Jugador 2: %d\n", fichas_j2);
  fprintf(file, "Tablero:\n");

  // Guardar el estado del tablero
  for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++) {
	      fprintf(file, "%d ", tablero[i][j]);
      }
      fprintf(file, "\n");
  }
  fclose(file);
  printf("Partida guardada correctamente en el archivo %s.\n", archivo);
}

int cargar_partida(char *filename, int tablero[8][8], char j1[], char j2[], int *jugador, int *modo) {
    int i, j;
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s.\n", filename);
        return 0; // Indica que la carga falló
    }

    // Leer el modo de juego
    fscanf(archivo, "Modo de Juego: %d\n", modo);

    // Leer los nombres de los jugadores
    fscanf(archivo, "Jugador 1: %[^\n]\n", j1);
    fscanf(archivo, "Jugador 2: %[^\n]\n", j2);

    // Leer el turno del jugador
    fscanf(archivo, "Turno del Jugador: %d\n", jugador);

    // Ignorar las líneas de las fichas
    fscanf(archivo, "Fichas Jugador 1: %*d\n");
    fscanf(archivo, "Fichas Jugador 2: %*d\n");

    // Leer el tablero
    fscanf(archivo, "Tablero:\n");
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            fscanf(archivo, "%d", &tablero[i][j]);
        }
    }

    fclose(archivo);
    return 1; // Indica que la carga fue exitosa
}

/*Función que implementa el modo de juego "Jugador vs CPU"*/
void PCvsJUG() {
    // Declaración de variables
    int tablero[8][8]; // Tablero de juego
    int movimientos[8][8]; // Arreglo para almacenar movimientos válidos
    int f, c; // Coordenadas para los movimientos
    int ran, jugador; // Determinar quién comienza y gestionar turnos
    int fichas_j1 = 0, fichas_cpu = 0; // Contadores de fichas para jugador y CPU
    int x, y, k, j; // Índices para recorrer el tablero
    int max_fichas, mejor_fila, mejor_columna; // Para seleccionar el mejor movimiento del CPU
    int movimientos_disponibles; // Indica si hay movimientos válidos disponibles
    char j1[MAX]; // Nombre del jugador
    int guardar;
    char nombre_archivo[MAX]; // Almacena el nombre del archivo para guardar la partida
    char cpu[MAX] = "CPU"; // Nombre fijo para la CPU
    char palabra[MAX] = "CARGANDO..."; // Mensaje de carga
    int i, suma = 0; // Variables auxiliares para efectos visuales

    // Mensaje de bienvenida
    printf("BIENVENIDO A REVERSI :)\n");
    printf("HAS SELECCIONADO EL MODO 1 ---> PLAYER VS CPU\n");
    system("sleep 3");
    system("clear");

    // Pedir el nombre del jugador
    printf("Ingresa tu nombre, Jugador 1:\n");
    scanf("%[^\n]", j1);
    getchar(); // Limpiar entrada
    system("clear");

    // Mostrar mensaje de carga
    for (i = 0; palabra[i] != '\0'; i++) {
        system("sleep 0.1");
        printf("%c \n", palabra[i]);
        system("sleep 0.1");
        suma++;
    }
    printf("\n");

    if (i == suma) {
        system("clear");
        llenar_tablero(tablero); // Inicializa el tablero con las fichas iniciales
    }

    // Determinar aleatoriamente quién comienza
        ran = random_jugador();
            if (ran <= 5) 
            {
             jugador = 1;
            } 
             else 
            {
             jugador = 2;
            }

    // Ciclo principal del juego
    while (1) {
        // Contar las fichas de ambos jugadores
        fichas_j1 = 0;
        fichas_cpu = 0;
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 1) {
                    fichas_j1++;
                } else if (tablero[x][y] == 2) {
                    fichas_cpu++;
                }
            }
        }

        // Mostrar el tablero y las fichas de cada jugador
        imp_contenido_tablero(tablero);
        printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, cpu, fichas_cpu);

        // Determinar el jugador actual
        if (jugador == 1) {
            printf("Turno del Jugador 1 'O' %s:\n", j1);
        } else {
            printf("Turno del Jugador 2 'X' %s:\n", cpu);
            system("sleep 2");
            printf("CPU calculando tiro...\n");
            system("sleep 2");
        }

        // Calcular movimientos válidos para el jugador actual
        movimientos_validos(tablero, jugador, movimientos);

        // Verificar si hay movimientos disponibles
        movimientos_disponibles = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if (movimientos[k][j] > 0) {
                    movimientos_disponibles = 1;
                }
            }
        }

        if (movimientos_disponibles == 0) {
            // Si no hay movimientos válidos, pasar turno
            printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);
            if (jugador == 1) {
                jugador = 2;
            } else {
                jugador = 1;
            }
        } else {
            if (jugador == 1) {
                // Pedir al jugador sus coordenadas
                recibir_verificar_coordenada(&f, &c, tablero);
                while (movimientos[f][c] == 0) {
                    printf("Movimiento inválido. Intenta de nuevo.\n");
                    recibir_verificar_coordenada(&f, &c, tablero);
                }
            } else {
                // Lógica de la CPU: Seleccionar el mejor movimiento
                max_fichas = 0;
                mejor_fila = -1;
                mejor_columna = -1;
                for (k = 0; k < 8; k++) {
                    for (j = 0; j < 8; j++) {
                        if (movimientos[k][j] > max_fichas) {
                            max_fichas = movimientos[k][j];
                            mejor_fila = k;
                            mejor_columna = j;
                        }
                    }
                }
                f = mejor_fila;
                c = mejor_columna;
                printf("El CPU seleccionó la fila %d y columna %d.\n", f, c);
            }

            // Realizar el movimiento en el tablero
            tablero[f][c] = jugador;
            analizar(f, c, tablero, jugador);

            // Preguntar si el jugador desea guardar la partida
            guardar = seleccion();
            if (guardar == 1) {
                solicitar_nombre_archivo(nombre_archivo); // Solicitar nombre del archivo
                guardar_partida(nombre_archivo, tablero, j1, cpu, jugador, fichas_j1, fichas_cpu, 1); // Guardar el estado actual.
            }

            // Cambiar turno al otro jugador
               if (jugador == 1) 
                {
                    jugador = 2;
                } 
                else 
                {
                    jugador = 1;
                }
        }

        // Verificar si el juego ha terminado
        if (fichas_j1 + fichas_cpu == 64 || movimientos_disponibles == 0) {
            if (fichas_j1 > fichas_cpu) {
                printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            } else if (fichas_cpu > fichas_j1) {
                printf("¡Victoria para %s con %d fichas!\n", cpu, fichas_cpu);
            } else {
                printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
            return;
        }
    }
}

/*Función que implementa el modo de juego "Jugador vs Jugador"*/
void JUGvsJUG() {
    // Declaración de variables principales
    int tablero[8][8]; // Tablero de juego
    int movimientos[8][8]; // Matriz para almacenar movimientos válidos
    int f, c, ran; // Coordenadas para los movimientos y variable aleatoria para decidir quién comienza
    int jugador; // Indica el jugador actual
    int guardar; // Variable para manejar si el usuario desea guardar la partida
    int fichas_j1 = 0; // Contador de fichas del Jugador 1
    int fichas_j2 = 0; // Contador de fichas del Jugador 2
    int x, y, k, j; // Índices auxiliares para recorrer el tablero
    int movimientos_disponibles; // Indica si hay movimientos válidos disponibles
    char nombre_archivo[MAX]; // Almacena el nombre del archivo para guardar la partida
    char j1[MAX], j2[MAX]; // Nombres de los jugadores
    char palabra[MAX] = "CARGANDO..."; // Mensaje de carga para efecto visual
    int i, suma = 0; // Variables auxiliares para el efecto de carga

    // Bienvenida al modo "Jugador vs Jugador"
    printf("BIENVENIDO A REVERSI :) \n");
    printf("HAS SELECCIONADO EL MODO 2 ---> PLAYER VS PLAYER \n");
    system("sleep 3");
    system("clear");

    // Solicitar los nombres de los jugadores
    nombres(j1, j2);
    system("clear");
    printf("\n");

    // Mostrar mensaje de carga 
    for (i = 0; palabra[i] != '\0'; i++) {
        system("sleep 0.1");
        printf("%c \n", palabra[i]);
        system("sleep 0.1");
        suma++;
    }
    printf("\n");

    // Verificar si el efecto de carga terminó y preparar el tablero
    if (i == suma) {
        system("clear");
        llenar_tablero(tablero); // Inicializa el tablero con las fichas iniciales
    }

    // Decidir aleatoriamente quién comienza
    ran = random_jugador();
    if (ran <= 5) {
        jugador = 1; // Jugador 1 comienza
    } else {
        jugador = 2; // Jugador 2 comienza
    }

    // Ciclo principal del juego
    while (1) {
        // Reiniciar contadores de fichas para ambos jugadores
        fichas_j1 = 0;
        fichas_j2 = 0;

        // Calcular las fichas actuales de los jugadores
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 1) {
                    fichas_j1++;
                } else if (tablero[x][y] == 2) {
                    fichas_j2++;
                }
            }
        }

        // Mostrar el tablero y el estado de las fichas
        imp_contenido_tablero(tablero);
        printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, j2, fichas_j2);

        // Indicar el turno actual
        if (jugador == 1) {
            printf("Turno del Jugador 1 'O' %s: \n", j1);
        } else {
            printf("Turno del Jugador 2 'X' %s: \n", j2);
        }

        // Calcular movimientos válidos para el jugador actual
        movimientos_validos(tablero, jugador, movimientos);

        // Verificar si hay movimientos disponibles
        movimientos_disponibles = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if (movimientos[k][j] > 0) {
                    movimientos_disponibles = 1;
                }
            }
        }

        if (movimientos_disponibles == 0) {
            // Si no hay movimientos válidos, se pierde el turno
            printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);
            jugador = (jugador == 1) ? 2 : 1; // Cambiar turno al otro jugador
        } else {
            // Si hay movimientos válidos
            if (jugador == 1 || jugador == 2) {
                recibir_verificar_coordenada(&f, &c, tablero); // Solicitar coordenadas
                while (movimientos[f][c] == 0) {
                    printf("Movimiento inválido. Intenta de nuevo.\n");
                    recibir_verificar_coordenada(&f, &c, tablero);
                }
            }

            // Realizar el movimiento en el tablero
            tablero[f][c] = jugador;
            analizar(f, c, tablero, jugador);

            // Preguntar si el jugador desea guardar la partida
            guardar = seleccion();
            if (guardar == 1) {
                solicitar_nombre_archivo(nombre_archivo); // Solicitar nombre del archivo
                guardar_partida(nombre_archivo, tablero, j1, j2, jugador, fichas_j1, fichas_j2, 2); // Guardar el estado actual.
            }

            // Cambiar turno al otro jugador
               if (jugador == 1) 
                {
                    jugador = 2;
                } 
                else 
                {
                    jugador = 1;
                }
        }

        // Verificar si el juego ha terminado
        if (fichas_j1 + fichas_j2 == 64 || movimientos_disponibles == 0) {
            if (fichas_j1 > fichas_j2) {
                printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            } else if (fichas_j2 > fichas_j1) {
                printf("¡Victoria para %s con %d fichas!\n", j2, fichas_j2);
            } else {
                printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
            return; 
        }
    }
}

/*Función que implementa el modo "Jugador vs Jugador", con la funcionalidad de guardar el historial de la partida en un archivo.
 @param:
 - fname: Nombre del archivo donde se almacenará el historial de la partida.*/
void fJUGvsJUG(char fname[]) {
    int tablero[8][8]; // Arreglo que representa el tablero de juego
    char nfile[MAX]; // Nombre del archivo donde se guardará el historial
    int movimientos[8][8]; // Arreglo que almacena los movimientos válidos

    FILE *historial; // Archivo donde se almacenará el historial de la partida

    int f, c, ran; // Coordenadas de fila y columna, y variable para el turno inicial
    int jugador; // Jugador actual
    int fichas_j1 = 0, fichas_j2 = 0; // Contadores de fichas de cada jugador
    int x, y, k, j; // Índices para recorrer el tablero y movimientos
    int movimientos_disponibles; // Indica si hay movimientos válidos disponibles
    char j1[MAX], j2[MAX]; // Nombres de los jugadores
    char palabra[MAX] = "CARGANDO..."; // Mensaje de carga
    int i, suma = 0; // Variables auxiliares para la animación de carga
    int turno = 1; // Contador de turnos

    // Guardar el nombre del archivo donde se almacenará el historial de la partida
    sscanf(fname, "%s", nfile);

    // Crear el archivo y escribir el encabezado del historial
    historial = fopen(nfile, "ap");
    fprintf(historial, "HISTORIAL DE PARTIDA: \n");
    fprintf(historial, "\n");
    fclose(historial);

    // Mostrar mensaje de bienvenida
    printf("BIENVENIDO A REVERSI :) \n");
    printf("HAS SELECCIONADO EL MODO 2 ---> PLAYER VS PLAYER \n");
    printf("RECUERDA QUE TU HISTORIAL DE JUEGO COMENZARÁ A SER GUARDADO \n");
    system("sleep 3");
    system("clear");

    // Solicitar los nombres de los jugadores
    nombres(j1, j2);

    // Guardar los nombres de los jugadores en el archivo del historial
    historial = fopen(nfile, "w");
    fprintf(historial, "NOMBRE DE JUGADOR 1: %s \n", j1);
    fprintf(historial, "NOMBRE DE JUGADOR 2: %s \n", j2);
    fclose(historial);

    system("clear");

    // Mostrar el mensaje de carga
    printf("\n");
    for (i = 0; palabra[i] != '\0'; i++) {
        system("sleep 0.1");
        printf("%c \n", palabra[i]);
        system("sleep 0.1");
        suma++;
    }
    printf("\n");

    // Inicializar el tablero con las fichas iniciales
    if (i == suma) {
        system("clear");
        llenar_tablero(tablero);
    }

    // Decidir aleatoriamente quién comienza
    ran = random_jugador();
    if (ran <= 5) {
        jugador = 1; // Jugador 1 comienza
    } else {
        jugador = 2; // Jugador 2 comienza
    }

    // Ciclo principal del juego
    while (1) {
        // Calcular las fichas de ambos jugadores
        fichas_j1 = 0;
        fichas_j2 = 0;
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 1) {
                    fichas_j1++;
                } else if (tablero[x][y] == 2) {
                    fichas_j2++;
                }
            }
        }

        // Mostrar el tablero y las fichas de cada jugador
        imp_contenido_tablero(tablero);
        printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, j2, fichas_j2);

        // Guardar el estado actual del tablero en el archivo de historial
        historial = fopen(nfile, "ap");
        fprintf(historial, "TURNO: %d \n", turno);
        fprintf(historial, "Fichas - %s: %d | %s: %d\n", j1, fichas_j1, j2, fichas_j2);
        fprintf(historial, "  0 1 2 3 4 5 6 7\n");
        for (x = 0; x < 8; x++) {
            fprintf(historial, "%d ", x);
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 0) {
                    fprintf(historial, ". ");
                } else if (tablero[x][y] == 1) {
                    fprintf(historial, "O ");
                } else if (tablero[x][y] == 2) {
                    fprintf(historial, "X ");
                }
            }
            fprintf(historial, "\n");
        }
        fprintf(historial, "\n");
        fclose(historial);

        // Indicar quién está jugando
        if (jugador == 1) {
            printf("Turno del Jugador 1 'O' %s: \n", j1);
        } else {
            printf("Turno del Jugador 2 'X' %s: \n", j2);
        }

        // Calcular movimientos válidos
        movimientos_validos(tablero, jugador, movimientos);

        // Verificar si hay movimientos disponibles
        movimientos_disponibles = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if (movimientos[k][j] > 0) {
                    movimientos_disponibles = 1;
                }
            }
        }

        if (movimientos_disponibles == 0) {
            printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);

            // Cambiar turno
            if (jugador == 1) {
                jugador = 2;
            } else {
                jugador = 1;
            }
        } else {
            // Recibir y validar coordenada del jugador
            recibir_verificar_coordenada(&f, &c, tablero);
            while (movimientos[f][c] == 0) {
                printf("Movimiento inválido. Intenta de nuevo.\n");
                recibir_verificar_coordenada(&f, &c, tablero);
            }

            // Realizar el movimiento
            tablero[f][c] = jugador;
            analizar(f, c, tablero, jugador);

            // Cambiar turno
            if (jugador == 1) {
                jugador = 2;
            } else {
                jugador = 1;
            }
        }

        // Incrementar el contador de turnos
        turno++;

        // Verificar si el juego ha terminado
        if (fichas_j1 + fichas_j2 == 64 || movimientos_disponibles == 0) {
            historial = fopen(nfile, "ap");
            if (fichas_j1 > fichas_j2) {
                printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
                fprintf(historial, "¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            } else if (fichas_j2 > fichas_j1) {
                printf("¡Victoria para %s con %d fichas!\n", j2, fichas_j2);
                fprintf(historial, "¡Victoria para %s con %d fichas!\n", j2, fichas_j2);
            } else {
                printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
                fprintf(historial, "¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
            fclose(historial);
            return;
        }
    }
}

/*Función que implementa el modo "PC vs Jugador", con la funcionalidad de guardar el historial de la partida en un archivo.
 @param:
 - fname: Nombre del archivo donde se almacenará el historial de la partida.*/
void fPCvsJUG (char fname[])
{
int tablero[8][8]; // Arreglo que representa el tablero de juego
int movimientos[8][8]; // Arreglo para almacenar los movimientos válidos
int f, c, ran; // Coordenadas de fila y columna, y variable para determinar el turno inicial
int jugador; // Jugador actual (1 para el jugador, 2 para la CPU)
int fichas_j1 = 0; // Contador de fichas del Jugador
int fichas_cpu = 0; // Contador de fichas de la CPU
FILE *historial; // Archivo donde se almacenará el historial de la partida
char nfile[MAX]; // Nombre del archivo del historial
int x, y, k, j; // Índices para recorrer el tablero y los movimientos válidos
int max_fichas; // Máximo número de fichas que puede capturar la CPU en un movimiento
int mejor_fila, mejor_columna; // Coordenadas del mejor movimiento de la CPU
int movimientos_disponibles; // Bandera para verificar si hay movimientos válidos disponibles
char j1[MAX]; // Nombre del jugador
char cpu[MAX] = "CPU"; // Nombre fijo de la CPU
char palabra[MAX] = "CARGANDO..."; // Mensaje de carga visual
int i, suma = 0; // Variables para la animación de carga
int turno = 1; // Contador de turnos

  // Guardar el nombre del archivo donde se almacenará el historial de la partida
  sscanf(fname, "%s", nfile);

  // Crear el archivo y escribir el encabezado del historial
  historial = fopen(nfile, "ap");
  fprintf(historial, "HISTORIAL DE PARTIDA: \n");
  fprintf(historial, "\n");
  fclose(historial);

  // Bienvenida
  printf("BIENVENIDO A REVERSI :) \n");
  printf("HAS SELECCIONADO EL MODO 1 ---> PLAYER VS CPU \n");
  printf("RECUERDA QUE TU HISTORIAL DE JUEGO COMENZARÁ A SER GUARDADO \n");
  system("sleep 3");
  system("clear");

  // Pedir el nombre del jugador
  printf("Ingresa tu nombre, Jugador 1: \n");
  scanf("%[^\n]", j1);
  getchar();
  system("clear");

  printf("\n");

  // Guardar los nombres de los jugadores en el archivo del historial
  historial = fopen(nfile, "w");
  fprintf(historial, "NOMBRE DE JUGADOR 1: %s \n", j1);
  fprintf(historial, "NOMBRE DE JUGADOR 2: CPU \n");
    fclose(historial);

    system("clear");

  printf("\n");

    
  // Mostrar mensaje de carga
  for (i = 0; palabra[i] != '\0'; i++) {
    system("sleep 0.1");
    printf("%c \n", palabra[i]);
    system("sleep 0.1");
    suma++;
  }
  printf("\n");

  if (i == suma)
    {
      system("clear");
      llenar_tablero(tablero); // Inicializa el tablero con las fichas iniciales
    }

  // Decidir aleatoriamente quién comienza
  ran = random_jugador();
  if (ran <= 5)
    {
      jugador = 1; // Jugador comienza
    }
  else
    {
      jugador = 2; // CPU comienza
    }

  // Ciclo principal del juego
  while (1)
    {  
      fichas_j1 = 0;
      fichas_cpu = 0;

      // Calcular las fichas de ambos jugadores
      for (x = 0; x < 8; x++)
	{
	  for (y = 0; y < 8; y++)
	    {
	      if (tablero[x][y] == 1)
		{
		  fichas_j1++;
                }
	      else if (tablero[x][y] == 2)
		{
		  fichas_cpu++;
                }
            }
        }

      // Mostrar el tablero y las fichas actuales de cada jugador
      imp_contenido_tablero(tablero); 
      printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, cpu, fichas_cpu);


      // Guardamos el estado inicial del tablero en el archivo de historial

      historial = fopen(nfile, "ap");
      fprintf(historial, "TURNO: %d \n", turno);
      fprintf(historial, "Fichas - %s: %d | %s: %d\n", j1, fichas_j1, cpu, fichas_cpu);

      fprintf(historial, "  0 1 2 3 4 5 6 7\n");
       for (x = 0; x < 8; x++)
	{
	  fprintf(historial, "%d", x);
	  for (y = 0; y < 8; y++) 
	    {

	      if (tablero[x][y] == 0)
		{
		  fprintf(historial, ". ");
		}
	      else if (tablero[x][y] == 1)
		{
		  fprintf(historial, "O ");
		}
	      else if (tablero[x][y] == 2)
		{
		  fprintf(historial, "X ");
		}
	    }
	   fprintf(historial, "\n");
	}

        fprintf(historial, "\n");
	fclose(historial);

      

      // Determinar el jugador actual
      if (jugador == 1)
	{
	  printf("Turno del Jugador 1 'O' %s: \n", j1);
        }
      else
	{
	  printf("Turno del Jugador 2 'X' %s: \n", cpu);
	  system("sleep 2"); // Simular tiempo de cálculo del CPU
	  printf("CPU calculando tiro... \n");
	  system("sleep 2");
        }

      movimientos_validos(tablero, jugador, movimientos);

      // Verificar si hay movimientos disponibles
      movimientos_disponibles = 0;
      for (k = 0; k < 8; k++)
	{
	  for (j = 0; j < 8; j++)
	    {
	      if (movimientos[k][j] > 0)
		{
		  movimientos_disponibles = 1;
                }
            }
        }

      if (movimientos_disponibles == 0)
	{
	  printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);

	  // Cambiar turno
	  if (jugador == 1)
	    {
	      jugador = 2;
            }
	  else
	    {
	      jugador = 1;
            }
        }
      else
	{
	  if (jugador == 1)
	    {
	      // Recibir y validar coordenada del jugador
	      recibir_verificar_coordenada(&f, &c, tablero);
	      while (movimientos[f][c] == 0)
		{
		  printf("Movimiento inválido. Intenta de nuevo.\n");
		  recibir_verificar_coordenada(&f, &c, tablero);
                }
            }
	  else
	    {
	      // Lógica para el CPU: buscar el mejor movimiento
	      max_fichas = 0;
	      mejor_fila = -1;
	      mejor_columna = -1;

	      for (k = 0; k < 8; k++)
		{
		  for (j = 0; j < 8; j++)
		    {
		      if (movimientos[k][j] > max_fichas)
			{
			  max_fichas = movimientos[k][j];
			  mejor_fila = k;
			  mejor_columna = j;
                        }
                    }
                }

	      // Asignar las coordenadas seleccionadas por el CPU
	      f = mejor_fila;
	      c = mejor_columna;
	      printf("El CPU seleccionó la fila %d y columna %d.\n", f, c);
            }

	  // Realizar movimiento
	  tablero[f][c] = jugador;
	  analizar(f, c, tablero, jugador);

	  // Cambiar turno
	  if (jugador == 1)
	    {
	      jugador = 2;
            }
	  else
	    {
	      jugador = 1;
            }
        }

      turno ++;

      // Verificar si el juego ha terminado
      if (fichas_j1 + fichas_cpu == 64 || movimientos_disponibles == 0)
	{
	  historial = fopen(nfile, "ap");
	  if (fichas_j1 > fichas_cpu)
	    {
	      printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
	      fprintf(historial, "¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            }
	  else if (fichas_cpu > fichas_j1)
	    {
	      printf("¡Victoria para %s con %d fichas!\n", cpu, fichas_cpu);
	      fprintf(historial, "¡Victoria para %s con %d fichas!\n", cpu, fichas_cpu);
            }
	  else
	    {
	      printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
	      fprintf(historial, "¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
	  fclose(historial);
	  return;
        }
    } 
}

/*Función que permite continuar una partida previamente guardada del modo "Jugador vs Jugador".
 @Param:
 - archivo_guardado: Ruta del archivo donde se encuentra la partida guardada.*/
void continuarJUGvsJUG(char *archivo_guardado) {
    // Variables principales
    int tablero[8][8]; // Arreglo que representa el estado del tablero
    char j1[MAX], j2[MAX]; // Nombres de los jugadores
    int jugador, modo; // Jugador actual (1 o 2) y modo de juego
    int fichas_j1 = 0, fichas_j2 = 0; // Contadores de fichas de cada jugador
    int movimientos[8][8]; // Arreglo que almacena los movimientos válidos
    int movimientos_disponibles, f, c, x, y, k, j; // Variables para coordenadas y contadores

    // Cargar la partida guardada desde el archivo
    if (!cargar_partida(archivo_guardado, tablero, j1, j2, &jugador, &modo)) {
        printf("No se pudo cargar la partida desde %s.\n", archivo_guardado);
        return;
    }

    printf("Partida cargada exitosamente. Continuando...\n");

    // Ciclo principal del juego
    while (1) {
        // Reiniciar contadores de fichas de los jugadores
        fichas_j1 = 0;
        fichas_j2 = 0;
        // Contar las fichas actuales en el tablero
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 1) fichas_j1++;
                else if (tablero[x][y] == 2) fichas_j2++;
            }
        }

        // Mostrar el estado actual del tablero y las fichas de cada jugador
        imp_contenido_tablero(tablero);
        printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, j2, fichas_j2);

        // Mostrar el turno del jugador actual
        printf("Turno del Jugador %d (%s):\n", jugador, jugador == 1 ? j1 : j2);

        // Calcular los movimientos válidos para el jugador  actual
        movimientos_validos(tablero, jugador, movimientos);

        // Verificar si hay movimientos válidos disponibles
        movimientos_disponibles = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if (movimientos[k][j] > 0) movimientos_disponibles = 1;
            }
        }

        if (movimientos_disponibles == 0) {
            // Si no hay movimientos válidos, el jugador pierde su turno
            printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);
            jugador = (jugador == 1) ? 2 : 1; // Cambiar al siguiente jugador
        } else {
            // Pedir coordenadas y realizar el movimiento
            recibir_verificar_coordenada(&f, &c, tablero);
            while (movimientos[f][c] == 0) {
                printf("Movimiento inválido. Intenta de nuevo.\n");
                recibir_verificar_coordenada(&f, &c, tablero);
            }

            // Actualizar el tablero con el movimiento del jugador
            tablero[f][c] = jugador;
            analizar(f, c, tablero, jugador);

            // Preguntar si el jugador desea guardar la partida
            printf("¿Deseas guardar el progreso? (1: Sí, 0: No): ");
            int guardar;
            scanf("%d", &guardar);
            if (guardar == 1) {
                guardar_partida(archivo_guardado, tablero, j1, j2, jugador, fichas_j1, fichas_j2, modo);
            }

            jugador = (jugador == 1) ? 2 : 1; // Cambiar turno al siguiente jugador
        }

        // Verificar si el juego ha terminado 
        if (fichas_j1 + fichas_j2 == 64 || movimientos_disponibles == 0) {
            if (fichas_j1 > fichas_j2) {
                printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            } else if (fichas_j2 > fichas_j1) {
                printf("¡Victoria para %s con %d fichas!\n", j2, fichas_j2);
            } else {
                printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
            break;
        }
    }
}

/*Función que permite continuar una partida previamente guardada del modo "PC vs Jugador".
 @param:
 - archivo_guardado: Nombre del archivo donde se encuentra la partida guardada.*/
void continuarPCvsJUG(char *archivo_guardado) {
    // Variables principales
    int tablero[8][8]; // Arreglo que representa el estado del tablero
    char j1[MAX], cpu[MAX] = "CPU"; // Nombres del jugador y la CPU
    int jugador, modo; // Jugador actual (1 para jugador, 2 para CPU) y modo de juego
    int fichas_j1 = 0, fichas_cpu = 0; // Contadores de fichas para el jugador y la CPU
    int movimientos[8][8]; // Arreglo que almacena los movimientos válidos
    int movimientos_disponibles, f, c, x, y, k, j; // Variables para coordenadas y contadores
    int max_fichas, mejor_fila, mejor_columna; // Variables para determinar el mejor movimiento de la CPU

    // Cargar la partida guardada desde el archivo
    if (cargar_partida(archivo_guardado, tablero, j1, cpu, &jugador, &modo) == 0) {
        printf("No se pudo cargar la partida desde %s.\n", archivo_guardado);
        return;
    }

    printf("Partida cargada exitosamente. Continuando...\n");

    // Ciclo principal del juego
    while (1) {
        // Reiniciar contadores de fichas de los jugadores
        fichas_j1 = 0;
        fichas_cpu = 0;
        // Contas las fichas actuales del tablero
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                if (tablero[x][y] == 1) fichas_j1++; // Contar fichas del jugador
                else if (tablero[x][y] == 2) fichas_cpu++; // Contar fichas del CPU
            }
        }

        // Mostrar el tablero y las fichas de cada jugador
        imp_contenido_tablero(tablero);
        printf("Fichas - %s: %d | %s: %d\n", j1, fichas_j1, cpu, fichas_cpu);

        // Mostrar turno del jugador actual
        if (jugador == 1) {
            printf("Turno del Jugador 1 (%s):\n", j1);
        } else {
            printf("Turno del Jugador 2 (CPU):\n");
            printf("CPU calculando movimiento...\n");
        }

        // Calcular movimientos válidos para el jugador actual
        movimientos_validos(tablero, jugador, movimientos);

        // Verificar si hay movimientos válidos disponibles
        movimientos_disponibles = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if (movimientos[k][j] > 0) movimientos_disponibles = 1;
            }
        }

        if (movimientos_disponibles == 0) {
            // Si no hay movimientos válidos, el jugador pierde su turno
            printf("El Jugador %d no tiene movimientos válidos. Turno perdido.\n", jugador);
             // Cambiar al siguiente jugador
              if (jugador == 1) {
        jugador = 2;
    } else {
        jugador = 1;
    }
        } else {
            if (jugador == 1) {
                // Pedir coordenadas del jugador y validar movimiento
                recibir_verificar_coordenada(&f, &c, tablero);
                while (movimientos[f][c] == 0) {
                    printf("Movimiento inválido. Intenta de nuevo.\n");
                    recibir_verificar_coordenada(&f, &c, tablero);
                }
            } else {
                // Determinar el mejor movimiento de la CPU
                max_fichas = 0;
                mejor_fila = -1;
                mejor_columna = -1;
                for (k = 0; k < 8; k++) {
                    for (j = 0; j < 8; j++) {
                        if (movimientos[k][j] > max_fichas) {
                            max_fichas = movimientos[k][j];
                            mejor_fila = k;
                            mejor_columna = j;
                        }
                    }
                }
                f = mejor_fila;
                c = mejor_columna;
                printf("El CPU seleccionó la fila %d y columna %d.\n", f, c);
            }

            // Actualizar el tablero con el movimiento realizado
            tablero[f][c] = jugador;
            analizar(f, c, tablero, jugador);

            // Preguntar si el jugador desea guardar el progreso
            printf("¿Deseas guardar el progreso? (1: Sí, 0: No): ");
            int guardar;
            scanf("%d", &guardar);
            if (guardar == 1) {
                guardar_partida(archivo_guardado, tablero, j1, cpu, jugador, fichas_j1, fichas_cpu, modo);
            }

         // Cambiar turno al siguiente jugador

         if (jugador == 1) {
            jugador = 2;
        } 
        
        else {
        jugador = 1;
        }
        }

        // Verificar si el juego ha terminado
        if (fichas_j1 + fichas_cpu == 64 || movimientos_disponibles == 0) {
            if (fichas_j1 > fichas_cpu) {
                printf("¡Victoria para %s con %d fichas!\n", j1, fichas_j1);
            } else if (fichas_cpu > fichas_j1) {
                printf("¡Victoria para %s con %d fichas!\n", cpu, fichas_cpu);
            } else {
                printf("¡Empate con %d fichas cada uno!\n", fichas_j1);
            }
            break;
        }
    }
}
