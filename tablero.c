/* Funciones relacionadas con la interfaz gráfica */
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/* Función que inicializa el tablero de juego para Reversi.
@param:  
- tablero.*/
void llenar_tablero(int tablero[8][8]){
  // Índices para recorrer filas (i) y columnas (j)
  int i,j;  
  // Llenar el tablero con ceros
  for (j=0 ; j<8 ; j++){
    for (i=0 ; i<8 ; i++){
      // Inicializar cada casilla como vacía
      tablero[i][j] = 0;
    } 
  }
   // Configurar las posiciones iniciales del tablero de Reversi
  tablero[3][3] = 1; // Ficha del jugador 1
  tablero[3][4] = 2; // Ficha del jugador 2
  tablero[4][3] = 2; // Ficha del jugador 2
  tablero[4][4] = 1; // Ficha del jugador 1
  return;
}

/* Función que inicializa el tablero de 8x8 llenándolo con ceros.
@param:  
- tablero.*/
void llenar_tablero_ceros(int tablero[8][8]){
  int i,j;  
  // Recorrer todas las filas y columnas del tablero
  for (j=0 ; j<8 ; j++){
    for (i=0 ; i<8 ; i++){
      // Asignar 0 a cada casilla
      tablero[i][j] = 0;
    } 
  }
  return;
}

/* Función que imprime el contenido del tablero.
@param:  
- tablero.*/
void imp_contenido_tablero(int tablero[8][8]){

  int i,j;

  // Imprimir la numeración horizontal de las columnas
  printf("  0 1 2 3 4 5 6 7\n");
  // Recorrer las filas del tablero
  for (j=0 ; j<8 ; j++){
    // Imprimir la numeración vertical de la fila actual
    printf("%d ", j);
     // Recorrer las columnas de la fila actual
    for (i=0 ; i<8 ; i++){
      // Determinar qué imprimir según el valor de la casilla
      if (tablero[i][j] == 0)
    	{
	  printf(". "); // Casilla vacía
    	}
      else if (tablero[i][j] == 1)
    	{
	  printf("O "); // Casilla ocupada por el Jugador 1
    	}
      else if (tablero[i][j] == 2)
    	{
	  printf("X "); // Casilla ocupada por el Jugador 2
    	}
    }
    printf("\n");
  }
  printf("\n");
  return;

}

/* Función que pide al usuario un número de fila válido dentro del rango del tablero (0-7).
@return:  
- Un entero entre 0 y 7 que representa la fila seleccionada por el usuario.*/
int pedir_fila(void){
  // Variable para almacenar la fila ingresada por el usuario
  int a;
  // Solicitar la fila al usuario
  printf("Ingresa la columna (0-7) \n");
  scanf("%d",&a);
  getchar();

  // Validar que la fila esté dentro del rango permitido
  while (a<0 || a>=8){
    printf("La columna ingresada esta fuera del rango del tablero\nIngrese la columna dentro del rango (0-7): \n");
    scanf("%d",&a);
    getchar();
  }
  return a;
}

/* Función que pide al usuario un número de columna válido dentro del rango del tablero (0-7).
@return:  
- Un entero entre 0 y 7 que representa la columna seleccionada por el usuario.*/
int pedir_columna(void){
  // Variable para almacenar la columna ingresada por el usuario
  int b;
  // Solicitar la columna al usuario
  printf("Ingrese la fila (0-7) \n");
  scanf("%d",&b);
  getchar();

  // Validar que la columna esté dentro del rango permitido
  while (b<0 || b>=8){
    printf("La fila ingresada esta fuera del rango del tablero\nIngrese la fila dentro del rango (0-7): \n");
    scanf("%d",&b);
    getchar();
  }
  return b;
}

/* Función que solicita al usuario ingresar coordenadas (fila y columna) y verifica que
la posición seleccionada esté vacía en el tablero
@param:  
- fila: Puntero a un entero donde se almacenará la fila ingresada por el usuario.
- columna: Puntero a un entero donde se almacenará la columna ingresada por el usuario.
- tablero. Estado actual del tablero.*/ 
void recibir_verificar_coordenada(int *fila, int *columna, int tablero[8][8]){
  // Solicitar fila y columna al usuario
  *fila = pedir_fila();
  *columna = pedir_columna();

  // Verificar que la casilla seleccionada esté vacía
  while (tablero[*fila][*columna]!=0){
    printf("La coordenada ingresada ya está ocupada, ingrese los nuevos valores \n");
    *fila = pedir_fila(); // Pedir una nueva fila
    *columna = pedir_columna(); // Pedir una nueva columna
  }
  return;
}