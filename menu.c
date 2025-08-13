#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>
#include <time.h>
#define TAM 20000
#define MAX 200

/* Función que solicita y almacena los nombres de los jugadores.
@param:  
- j1: Arreglo de caracteres donde se almacenará el nombre del Jugador 1.
- j2: Arreglo de caracteres donde se almacenará el nombre del Jugador 2.*/
void nombres (char j1[], char j2[])
{
  // Solicitar y leer el nombre del Jugador 1
  printf("Ingresa el nombre del Jugador 1: \n");
  scanf("%[^\n]", j1);
  getchar();

   // Solicitar y leer el nombre del Jugador 2
  printf("Ingresa el nombre del Jugador 2: \n");
  scanf("%[^\n]", j2);
  getchar();
}

/* Función que genera un núemro aleatorio para determianr el jugador inicial.
@return:  
- Un número entero aleatorio entre 1 y 10.*/
int random_jugador(void) {
  int resultado;

  // Inicializar la semilla para el generador de números aleatorios
  srand(time(NULL));

  // Generar un número aleatorio entre 1 y 10
  resultado = rand() % 10 + 1;

  return resultado;
}

/* Función que muestra el manual de usuario leyendo su contenido de un archivo de texto.
@return:  
- 1 si el usuario presiona '0' para regresar al menú principal.
- 0 si se presiona cualquier otra tecla.*/
int manual (void)
{


  FILE *manualuser;          // Puntero para manejar el archivo del manual
  char texto[TAM];           // Arreglo para almacenar el contenido del archivo
  char opcion;               // Variable para capturar la opción ingresada por el usuario
  int i = 0;                 // Índice para iterar sobre el texto


  // Abrir el archivo "MANUAL_DE_USUARIO.txt" en modo de lectura
  manualuser = fopen("MANUAL_DE_USUARIO.txt", "r");


  printf("ABRIENDO MANUAL... \n");
  system("sleep 0.3");
  system ("clear");
  system("sleep 0.1");

  // Leer y mostrar el contenido del archivo carácter por carácter
  while (fscanf(manualuser, "%c", &texto[i]) != EOF)
    {
      printf("%c", texto[i]);
      system("sleep 0.0001");
    }

  fclose(manualuser);

   // Solicitar al usuario que presione '0' para regresar al menú principal
  printf("PRESIONA 0 PARA REGRESAR AL MENU PRINCIPAL: \n");
  scanf("%c", &opcion);
  getchar();

  // Retornar 1 si se presiona '0', de lo contrario, retornar 0
  if (opcion == '0')
    {
      return 1;
    }


  else
    {
      return 0;
    }
}

/* Función que despliega el menú principal del juego y captura la opción seleccionada.
@return:  
@return:
- 1 si el usuario selecciona jugar contra la CPU.
- 2 si el usuario selecciona jugar contra otro jugador.
- 3 si el usuario selecciona ver el manual de usuario.
- 5 si el usuario selecciona cargar una partida.
- 0 si el usuario selecciona salir del juego.*/
int desplegar_menu (void)
{


  char opcion[MAX]; // Arreglo para capturar la opción ingresada por el usuario
  int i; // Variable de control para iterar por la entrada

  // Desplegar las opciones del menú principal
  printf("BIENVENIDO A REVERSI :) \n");
  printf("\n");
  printf("SELECCIONA EL MODO DE JUEGO \n");
  printf("\n");
  printf("ESCRIBE 1 PARA JUGAR CONTRA LA CPU \n");
  printf("\n");
  printf("ESCRIBE 2 PARA JUGAR CONTRA OTRO JUGADOR \n");
  printf("\n");
  printf("ESCRIBE h para desplegar el manual de usuario \n");
  printf("\n");
  printf("ESCRIBE load para cargar una partida desde un archivo existente \n");
  printf("\n");
  printf("ESCRIBE exit para salir del juego \n");
  printf("\n");
 
  // Leer la entrada del usuario
  scanf("%[^\n]", opcion);
  getchar();

  // Evaluar la opción seleccionada carácter por carácter
  for (i = 0; opcion[i] != '\0'; i++)
    {
      if (opcion[i] == '1')
	{
	  return 1; // Jugar contra la CPU
	}
      else if (opcion[i] == '2')
	{
	  return 2; // Jugar contra otro jugador
	}
      else if (opcion[i] == 'h')
	{
	  return 3; // Ver manual de usuario
	}
    }

  // Verificar si se ingresó "exit" o "load" como opciones completas
  if (strcmp(opcion, "exit"))
    {
      return 0; // Salir del juego
    }

  else if (strcmp(opcion, "load"))
    {
      return 5; // Cargar una partida
    }

  
}


/* Función para determinar aleatoriamente quién inicia
int random_selec(void) {
  int resultado;


  // Inicializar la semilla para el generador de números aleatorios
  srand(time(NULL));


  // Generar un número aleatorio entre 1 y 10
  resultado = rand() % 10 + 1;


  return resultado;
}*/

/* Función principal del juego que administra el flujo según los argumentos proporcionados.
@param:
- arc: Número de argumentos proporcionados al ejecutar el programa.
- texto: Arreglo de cadenas con los argumentos proporcionados.*/
void maingame(int arc, char *texto[]) 
{
    int tablero[8][8];  // Tablero principal del juego 
    int movimientos[8][8]; // Movimientos posibles 
    int f, c, ran; // Variables auxiliares 
    int jugador;  // Indica el jugador actual 
    int op; // Opción seleccionada en el menú principal
    int fichas_j1 = 0; // Contador de fichas del Jugador 1 
    int fichas_j2 = 0; // Contador de fichas del Jugador 2 
    int x, y; // Variables auxiliares
    int k, j; // Índices auxiliares
    int opc; // Opción seleccionada al mostrar el manual de usuario
    int newop; // Nueva opción seleccionada al regresar del manual
    int movimientos_disponibles; // Variable para movimientos disponibles 
    char j1[MAX]; // Nombre del Jugador 1 
    char j2[MAX]; // Nombre del Jugador 2 
    char palabra[MAX] = "CARGANDO..."; // Mensaje de carga
    char salida[MAX] = "SALIENDO ..."; // Mensaje de salida
    int i, suma = 0; // Contador y acumulador auxiliar

    // Modo de juego: Jugador vs Jugador
    if (arc == 3 && texto[1][0] == '-' && texto[1][1] == 'n' && texto[2][0] == '2') {
        JUGvsJUG();
    }

    // Modo de juego: Jugador vs CPU
    else if (arc == 3 && texto[1][0] == '-' && texto[1][1] == 'n' && texto[2][0] == '1') {
        PCvsJUG();
    }

    // Sin argumentos específicos, mostrar menú principal
    else if (arc == 2 && texto[1][0] == '-' && texto[1][1] == 'n' && texto[1][2] == '\0') {
        op = desplegar_menu();

        // Opciones del menú principal
        if (op == 1) {
            system("clear");
            printf("CARGANDO... \n");
            system("sleep 0.5");
            PCvsJUG();
            return;
        }

        if (op == 2) {
            system("clear");
            printf("CARGANDO... \n");
            system("sleep 0.5");
            JUGvsJUG();
            return;
        }

        if (op == 3) {
            system("clear");
            opc = manual();
            if (opc == 1) {
                system("clear");
                printf("Regresando al menú principal... \n");
                system("sleep 2");
                system("clear");
                newop = desplegar_menu();

                if (newop == 1) {
                    system("clear");
                    PCvsJUG();
                } else if (newop == 2) {
                    system("clear");
                    JUGvsJUG();
                }
            } else {
                printf("SALIENDO... \n");
                system("sleep 1");
                return;
            }
        }

        if (op == 0) {
            system("clear");
            for (i = 0; salida[i] != '\0'; i++) {
                system("sleep 0.1");
                printf("%c \n", salida[i]);
                system("sleep 0.1");
            }
            printf("\n");
            return;
        }
    }

    // Modo manual: Mostrar el manual y regresar al menú
    else if (arc == 2 && texto[1][0] == '-' && texto[1][1] == 'h' && texto[1][2] == '\0') {
        system("clear");
        opc = manual();
        if (opc == 1) {
            system("clear");
            printf("Regresando al menú principal... \n");
            system("sleep 2");
            newop = desplegar_menu();
            if (newop == 2) {
                system("clear");
                JUGvsJUG();
            } else if (newop == 1) {
                system("clear");
                PCvsJUG();
            }
        } else {
            printf("SALIENDO... \n");
            system("sleep 1");
            return;
        }
    }

    // Modo de juego: Jugador vs Jugador con carga de archivo
    else if (arc == 5 && texto[1][0] == '-' && texto[1][1] == 'n' && texto[2][0] == '2' && texto[3][0] == '-' && texto[3][1] == 't') {
        system("clear");
        printf("CARGANDO... \n");
        system("sleep 0.5");
        system("clear");
        fJUGvsJUG(texto[4]);
        return;
    }

    // Modo de juego: Jugador vs CPU con carga de archivo
    else if (arc == 5 && texto[1][0] == '-' && texto[1][1] == 'n' && texto[2][0] == '1' && texto[3][0] == '-' && texto[3][1] == 't') {
        system("clear");
        printf("CARGANDO... \n");
        system("sleep 0.5");
        system("clear");
        fPCvsJUG(texto[4]);
        return;
    }

    // Cargar partida guardada: CPU vs Jugador
    else if (arc == 4 && texto[1][0] == '-' && texto[1][1] == 'l' && texto[2][0] == '1') {
        continuarPCvsJUG(texto[3]);
        return;
    }

    // Cargar partida guardada: Jugador vs Jugador
    else if (arc == 4 && texto[1][0] == '-' && texto[1][1] == 'l' && texto[2][0] == '2') {
        continuarJUGvsJUG(texto[3]);
        return;
    }
}