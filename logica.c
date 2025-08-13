/*Funciones para el funcionamiento lógico del juego */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/* Función que analiza puntos alrededor de un punto dado en el tablero y cambia las fichas.
@param:  
- fila: La fila del punto central a analizar.
- columna: La columna del punto central a analizar.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar las fichas que se deben cambiar. */
void analizar(int fila, int columna, int tablero[8][8],int jugador){
    //printf("La fila es %d y la columna %d \n" , fila,columna);
    // Índices para recorrer las filas y columnas. Valores que representan al jugador actual (val) y al oponente (comp).
    int i,j,letra,val,comp;

     // Determinar los valores de jugador y oponente para las comparaciones.
    if ( jugador==1 ){
        // Fichas del jugador 1
        val = 1;
        // Fichas del oponente
        comp = 2;
    } else if ( jugador==2 ){
        // Fichas del jugador 2
        val = 2;
        //Fichas del oponente
        comp = 1;
    }
    
    //Analizar las posiciones alrededor del punto central
    //Recorre las filas 
    for( j = (fila -1 ) ; j < (fila + 2) ; j++){
        // Recorre las columnas
        for ( i = (columna-1) ; i < (columna + 2) ; i++){
            // Verificar que se este en el rango del tablero
            if (j >= 0 && j < 8 && i >= 0 && i < 8) {
                // Exclusión del punto central para el análisis
                if ( ! ( j==fila && i==columna ) ){
                    if( tablero[j][i] == comp ){
                        /*letra = j + 65 ;
                        printf("La coordenada %c,%d no es 0, es %d \n",letra,i,tablero[j][i]);*/
                        // Establecer los ocho caminos posibles para cambiar las fichas 
                        // Arriba derecha 
                        if ( j==(fila-1) && i==(columna+1) ){
                            arriba_derecha(fila,columna,tablero,jugador);
                        // Derecha 
                        } else if ( j==(fila) && i==(columna+1) ){
                            derecha(fila,columna,tablero,jugador);
                        // Abajo derecha 
                        } else if ( j==(fila+1) && i==(columna+1) ){
                            abajo_derecha(fila,columna,tablero,jugador);
                        // Abajo
                        } else if ( j==(fila+1) && i==(columna) ){
                            abajo(fila,columna,tablero,jugador);
                        // Abajo izquierda
                        } else if ( j==(fila+1) && i==(columna-1) ){
                            abajo_izquierda(fila,columna,tablero,jugador);
                        // Izquierda
                        } else if ( j==(fila) && i==(columna-1) ){
                            izquierda(fila,columna,tablero,jugador);
                        // Izquierda arriba
                        } else if ( j==(fila-1) && i==(columna-1) ){
                            arriba_izquierda(fila,columna,tablero,jugador);
                        // Arriba 
                        } else if ( j==(fila-1) && i==(columna) ){
                            arriba(fila,columna,tablero,jugador);
                        }
                    }
                }
            }
        }
    }
}


/* Funciones que dependeran de la dirección en la que se tenga que cambiar las fichas*/
/* Función que analiza y voltea fichas en la dirección arriba-derecha en el tablero.
@param: 
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void arriba_derecha(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia arriba en filas
    int j = fila-1;
    // Índice para moverse hacia la derecha en columnas
    int i = columna+1;
    // Posición inicial de la fila desde donde se comenzará a voltear las fichas
    int j0 = fila-1;
    //  Posición inicial de la columna desde donde se comenzará a voltear las fichas
    int i0 = columna+1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de las casillas en la dirección arriba-derecha
    voltear=0;
    // Condición para no salir del rango del tablero
    while( j>=0 && i<8 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[j][i]==0){
            return;
        // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[j][i]==comp ) {
            voltear++;
            // Si se encuentra una ficha del jugador actual
        } else if ( tablero[j][i]==val ) {
            // Verificar si hay fichas del oponente para voltear
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (j0 > j && i0 < i) {
                    tablero[j0][i0] = val; // Voltear la ficha a favor del jugador actual
                    // Mover hacia abajo en filas
                    j0--;
                    // Mover hacia la izquierda en columnas
                    i0++;
                }
            }
            return;
        }
    // Avanzar en la dirección arriba-derecha
    j--;
    i++;
    }
    //Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección derecha en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void derecha(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia la derecha en columnas
    int i = columna+1;
    //  Posición inicial de la columna desde donde se comenzará a voltear las fichas
    int i0 = columna+1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de las casillas en la dirección derecha
    voltear=0;
    // Condición para no salir del rango del tablero
    while( i<8 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección 
        if (tablero[fila][i]==0){
            return;
        // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[fila][i]==comp ) {
            voltear++;
        // Si se encuentra una ficha del jugador actual
        } else if ( tablero[fila][i]==val ) {
            // Verificar si hay fichas del oponente para voltear
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás
                while (i0 < i) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[fila][i0] = val;
                    // Mover hacia la derecha en columnas
                    i0++;
                }
            }
            return;
        }
    // Avanzar en la dirección derecha 
    i++;
    }
    //Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningpun cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección abajo-derecha en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void abajo_derecha(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia abajo en filas
    int j = fila+1;
    // Índice para moverse hacia la derecha en columnas
    int i = columna+1;
     // Posición inicial de la fila desde donde se comenzará a voltear las fichas
    int j0 = fila+1;
     // Posición inicial de la columna desde donde se comenzará a voltear las fichas
    int i0 = columna+1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    
    voltear=0;
    // Condición para no salir del rango del tablero
    while( j<8 && i<8 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[j][i]==0){
            return;
        // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[j][i]==comp ) {
            voltear++;
        // Si se encuentra una ficha del jugador actual
        } else if ( tablero[j][i]==val ) {
            // Verificar si hay fichas del oponente para voltear
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (j0 < j && i0 < i) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[j0][i0] = val;
                    // Mover hacia abajo en filas
                    j0++;
                    // Mover hacia la derecha en columnas
                    i0++;
                }
            }
            return;
        }
    // Avanzar en la dirección abajo-derecha
    j++;
    i++;
    }
    // Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección abajo en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void abajo(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
     // Índice para moverse hacia abajo en filas
    int j = fila+1;
    // Posición inicial de la fila desde donde se comenzará a voltear las fichas
    int j0 = fila+1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de los puntos en esa dirección
    voltear=0;
    // Condición para no salir del rango del tablero
    while( j<8 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[j][columna]==0){
            return;
         // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[j][columna]==comp ) {
            voltear++;
        // Si se llega a una casilla del jugador en turno
        } else if ( tablero[j][columna]==val ) {
            // Verificar si hay fichas por cambiar
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (j0 < j ) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[j0][columna] = val;
                    // Mover hacia abajo en filas
                    j0++;
                }
            }
            return;
        }
    // Avanzar en la dirección abajo
    j++;
    }
    // Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección arriba-izquierda en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void arriba_izquierda(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia arriba en filas
    int j = fila-1;
    // Índice para moverse hacia la izquierda en columnas
    int i = columna-1;
    // Posición inicial de la fila desde donde se comenzará a voltear las fichas
    int j0 = fila-1;
    // Posición inicial de la columna desde donde se comenzará a voltear las fichas
    int i0 = columna-1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de los puntos en esa dirección
    voltear=0;
    // Condición para no salir del rango del tablero
    while( j>=0 && i>=0 ){
         // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[j][i]==0){
            return;
         // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[j][i]==comp ) {
            voltear++;
        // Si se llega a una casilla del jugador en turno
        } else if ( tablero[j][i]==val ) {
            // Verificar si hay fichas por cambiar
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (j0 > j && i0 > i) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[j0][i0] = val;
                    // Mover hacia arriba en filas
                    j0--;
                    // Mover hacia la izquierda en columnas
                    i0--;
                }
            }
            return;
        }
    // Avanzar en la dirección arriba-izquierda
    j--;
    i--;
    }
    // Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección abajo-izquierda en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/

void abajo_izquierda(int fila, int columna, int tablero[8][8],int jugador){
  // Declarar variable
  // Valores para representar al jugador actual (val) y al oponente (comp)
  // Contador para las fichas del oponente que pueden ser volteadas
  int val,comp,voltear;
  // Índice para moverse hacia abajo en filas
  int j = fila+1;
  // Índice para moverse hacia la izquierda en columnas
  int i = columna-1;
  // Posición inicial de la fila desde donde se comenzará a voltear las fichas
  int j0 = fila+1;
  // Posición inicial de la columna desde donde se comenzará a voltear las fichas
  int i0 = columna-1;

  // Establecer el jugador para ver con que número se va a comparar
  if ( jugador==1 ){
    val = 1;
    comp = 2;
  } else if ( jugador==2 ){
    val = 2;
    comp = 1;
  }

  // Análisis de los puntos en esa dirección
  voltear=0;
  // Condición para no salir del rango del tablero
  while( j<8 && i>=0 ){
    // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
    if (tablero[j][i]==0){
      return;
    }
    // Si se encuentra una ficha del oponente, incrementar el contador
    else if ( tablero[j][i] == comp )
      {
	voltear++;
        // Si se llega a una casilla del jugador en turno
      }
  else if ( tablero[j][i]==val )
    {
      // Verificar si hay fichas por cambiar
      if (voltear>0)
	{ 
	  // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
	  while (j0 < j && i0 > i)
	    {
	      // Voltear la ficha a favor del jugador actual
	      tablero[j0][i0] = val;
	      // Mover hacia abajo en filas
	      j0++;
	      // Mover hacia la izquierda en columnas
	      i0--;
	    }
	}
      return;
    }
  // Avanzar en la dirección abajo-izquierda
  j++;
  i--;
}
// Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
return;
}

/* Función que analiza y voltea fichas en la dirección izquierda en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void izquierda(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia la izquierda en columnas
    int i = columna-1;
    // Posición inicial de la columna desde donde se comenzará a voltear las fichas
    int i0 = columna-1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de los puntos en esa dirección
    voltear=0;
    // Condición para no salir del rango del tablero
    while( i>=0 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[fila][i]==0){
            return;
        // Si se encuentra una ficha del oponente, incrementar el contador
        } else if ( tablero[fila][i]==comp ) {
            voltear++;
        // Si se llega a una casilla del jugador en turno
        } else if ( tablero[fila][i]==val ) {
            // Verificar si hay fichas por cambiar
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (i0 > i) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[fila][i0] = val;
                    // Mover hacia la izquierda en columnas
                    i0--;
                }
            }
            return;
        }
    // Avanzar en la dirección "izquierda"
    i--;
    }
    // Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que analiza y voltea fichas en la dirección arriba en el tablero
@param:
- fila: Fila inicial desde donde comienza el análisis.
- columna: Columna inicial desde donde comienza el análisis.
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2), para determinar qué fichas deben ser volteadas*/
void arriba(int fila, int columna, int tablero[8][8],int jugador){
    // Declarar variable
    // Valores para representar al jugador actual (val) y al oponente (comp)
    // Contador para las fichas del oponente que pueden ser volteadas
    int val,comp,voltear;
    // Índice para moverse hacia arriba en filas
    int j = fila-1;
    // Posición inicial de la fila desde donde se comenzará a voltear las fichas
    int j0 = fila-1;

    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Análisis de los puntos en esa dirección
    voltear=0;
    // Condición para no salir del rango del tablero
    while( j>=0 ){
        // Si se encuentra una casilla vacía, se termina el análisis en esta dirección
        if (tablero[j][columna]==0){
            return;
        // Si se encuentra una ficha del oponente, incrementar el contador
        }else if ( tablero[j][columna]==comp ) {
            voltear++;
        // Si se llega a una casilla del jugador en turno
        } else if ( tablero[j][columna]==val ) {
            // Verificar si hay fichas por cambiar
            if (voltear>0) { 
                // Cambiar las fichas desde el análisis inicial hasta la ficha que encierra las demás   
                while (j0 > j) {
                    // Voltear la ficha a favor del jugador actual
                    tablero[j0][columna] = val;
                    // Mover hacia arriba en filas
                    j0--;
                }
            }
            return;
        }
    // Avanzar en la dirección arriba
    j--;
    }
    // Si se recorre todo el rango sin encontrar una ficha del jugador, no se realiza ningún cambio
    return;
}

/* Función que verifica si aún hay casillas vacías en el tablero
@param:
- tablero: Estado actual del tablero.
@return:
- 1 si el tablero esta lleno (sin casillas vacías).
- 0 si hay al menos una casilla vacía.*/
int casillas_vacias(int tablero[8][8]){
    // Variables para recorrer las filas (i) y columnas (j) del tablero
    int i,j,vacias;  
    // Inicialmente se asume que el tablero está lleno
    vacias = 1; 
    // Recorrer todas las casillas del tablero
    // Recorre las columnas
    for (j=0 ; j<8 ; j++){
        // Recorre las filas
        for (i=0 ; i<8 ; i++){
            // Si se encuentra una casilla vacía (valor 0), cambiar el estado.
            if (tablero[i][j] == 0){
                // Indicar que hay casillas vacías.
                vacias = 0; 
            }
        } 
    }
    // Retorna 1 si no se encontraron casillas vacías, 0 en caso contrario
    return vacias;
}

/* Función que verifica y calcula los movimientos válidos para un jugador en el tablero
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se llenará con los movimientos válidos.
CADA POSICIÓN TENDRÁ UN 1 SI EL MOVIMIENTO ES VÁLIDO O UN 0 SI NO LO ES.

ESTA FUNCIÓN LLAMA A MÁS FUNCIONES PARA EVALUAR TODAS LAS DIRECCIONES
(VERTICAL, HORIZONTAL Y DIAGONALES) Y ACTUALIZA EL TABLERO DE MOVIMIENTOS VÁLIDOS*/
void movimientos_validos(int tablero[8][8],int jugador,int movimientos[8][8]){
    // Inicializar la matriz de movimientos a 0 (sin movimientos válidos)
    llenar_tablero_ceros(movimientos);
    // Verificar movimientos válidos en todas las direcciones
    movimientos_validos_derecha(tablero,jugador,movimientos);
    movimientos_validos_izquierda(tablero,jugador,movimientos);
    movimientos_validos_arriba(tablero,jugador,movimientos);
    movimientos_validos_abajo(tablero,jugador,movimientos);
    movimientos_validos_diagonal_abajo_derecha(tablero,jugador,movimientos);
    movimientos_validos_diagonal_abajo_izquierda(tablero,jugador,movimientos);
    movimientos_validos_diagonal_arriba_derecha(tablero,jugador,movimientos);
    movimientos_validos_diagonal_arriba_izquierda(tablero,jugador,movimientos);
}

/* Función que verifica y marca los movimientos válidos hacia la derecha en el tablero
para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos hacia la derecha.*/
void movimientos_validos_derecha(int tablero[8][8],int jugador,int movimientos[8][8]){
    // Índices para recorrer el tablero (filas y columnas).
    // Valores que representan al jugador actual (val) y al oponente (comp).
    // Contador de fichas del oponente que podrían ser volteadas.
    int i,j,val,comp,voltear;
    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Recorrer las filas del tablero
    for (j=0 ; j<8 ; j++){
        // Iniciar en la primera columna de cada fila
        i = 0;
        // Recorrer las columnas en la fila actual
        while (i<8){
             // Si se encuentra una ficha del jugador actual
            if (tablero[j][i]==val){
                // Avanzar a la siguiente columna
                i++; 
                // Reiniciar el contador de fichas del oponente para esta dirección
                voltear=0; 
                // Verificar si hay fichas del oponente hacia la derecha
                while(tablero[j][i]==comp){
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++; 
                    // Continuar avanzando hacia la derecha
                    i++; 
                }
                // Si se encuentra una casilla vacía y hay fichas del oponente para voltear
                if (tablero[j][i] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[j][i] =  movimientos[j][i] + voltear;           
                 }
             } else {
                // Avanzar a la siguiente columna si no se encuentra la ficha del jugador
                i++;
             }
         }

    }
    return; 
}

/* Función que verifica y marca los movimientos válidos hacia la izquierda en el tablero
para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos hacia la izquierda.*/
void movimientos_validos_izquierda(int tablero[8][8],int jugador,int movimientos[8][8]){
    // Índices para recorrer el tablero (filas y columnas)
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i,j,val,comp,voltear;
    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Recorrer las filas del tablero
    for (j=0 ; j<8 ; j++){
        // Iniciar en la última columna de cada fila
        i = 7;
        // Recorrer las columnas hacia la izquierda en la fila actual
        while (i>=0){
            // Si se encuentra una ficha del jugador actual
            if (tablero[j][i]==val){
                 // Avanzar hacia la izquierda
                i--; 
                // Reiniciar el contador de fichas del oponente para esta dirección
                voltear=0; 
                // Verificar si hay fichas del oponente hacia la izquierda
                while(tablero[j][i]==comp){
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++; 
                    // Continuar avanzando hacia la izquierda
                    i--;  
                }
                // Si se encuentra una casilla vacía y hay fichas del oponente para voltear
                if (tablero[j][i] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[j][i] =  movimientos[j][i] + voltear;           
                 }
             } else {
                // Avanzar a la siguiente columna si no se encuentra la ficha del jugador
                i--;
             }
         }

    }
    return; 
}

/* Función que verifica y marca los movimientos válidos hacia abajo en el tablero
para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos hacia abajo.*/
void movimientos_validos_abajo(int tablero[8][8],int jugador,int movimientos[8][8]){
    // Índices para recorrer el tablero (filas y columnas)
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i,j,val,comp,voltear;
    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Recorrer las columnas del tablero
    for (i=0 ; i<8 ; i++){
        // Iniciar en la primera fila de cada columna
        j = 0;

        // Recorrer las filas hacia abajo en la columna actual
        while (j<8){
            // Si se encuentra una ficha del jugador actual
            if (tablero[j][i]==val){
                // Avanzar a la siguiente fila
                j++; 
                // Reiniciar el contador de fichas del oponente para esta dirección
                voltear=0; 
                // Verificar si hay fichas del oponente hacia abajo
                while(tablero[j][i]==comp){
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++; 
                    // Continuar avanzando hacia abajo
                    j++; 
                }
                // Si se encuentra una casilla vacía y hay fichas del oponente para voltear
                if (tablero[j][i] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[j][i] =  movimientos[j][i] + voltear;           
                 }
             } else {
                // Avanzar a la siguiente fila si no se encuentra la ficha del jugador
                j++;
             }
         }

    }
    return; 
}

/* Función que verifica y marca los movimientos válidos hacia arriba en el tablero
para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos hacia arriba.*/
void movimientos_validos_arriba(int tablero[8][8],int jugador,int movimientos[8][8]){
    // Índices para recorrer el tablero (filas y columnas)
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i,j,val,comp,voltear;
    // Establecer el jugador para ver con que número se va a comparar
    if ( jugador==1 ){
        val = 1;
        comp = 2;
    } else if ( jugador==2 ){
        val = 2;
        comp = 1;
    }

    // Recorrer las filas del tablero
    for (i=0 ; i<8 ; i++){
        // Iniciar en la última fila de cada columna
        j = 7;
        // Recorrer las filas hacia arriba en la columna actual
        while (j>=0){
            // Si se encuentra una ficha del jugador actual
            if (tablero[j][i]==val){
                // Avanzar hacia arriba
                j--; 
                // Reiniciar el contador de fichas del oponente para esta dirección
                voltear=0; 
                /// Verificar si hay fichas del oponente hacia arriba 
                while(tablero[j][i]==comp){
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++; 
                    // Continuar avanzando hacia arriba
                    j--; 
                }
                // Si se encuentra una casilla vacía y hay fichas del oponente para voltear
                if (tablero[j][i] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[j][i] =  movimientos[j][i] + voltear;           
                 }
             } else {
                // Avanzar a la fila siguiente si no se encuentra la ficha del jugador
                j--;
             }
         }

    }
    return; 
}

/* Función que verifica y marca los movimientos válidos en la dirección diagonal hacia abajo 
en el tablero para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos en esta dirección.*/
void movimientos_validos_diagonal_abajo_derecha(int tablero[8][8], int jugador, int movimientos[8][8]){
    // Índices para recorrer el tablero (filas y columnas)
    // Variables auxiliares para recorrer en diagonal
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i, j, x, y, val, comp, voltear;
    // Establecer el jugador para ver con qué número se va a comparar
    if (jugador == 1) {
        val = 1;
        comp = 2;
    } else if (jugador == 2) {
        val = 2;
        comp = 1;
    }

    // Recorrer las casilas del tablero
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            // Verificar si se encuentra una ficha del jugador actual
            if (tablero[j][i] == val) {
                // Avanzar una fila hacia abajo
                x = j + 1; 
                // Avanzar una columna hacia la derecha
                y = i + 1; 
                // Reiniciar el contador de fichas del oponente
                voltear = 0;   

                // Recorrer en diagonal hacia abajo a la derecha mientras no se salga del tablero
                while (x < 8 && y < 8 && tablero[x][y] == comp) {
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++; 
                    // Avanzar hacia abajo
                    x++;       
                    // Avanzar hacia la derecha
                    y++;       
                }

                // Verificar si se encontró un espacio vacío y hay fichas del oponente para voltear
                if (x < 8 && y < 8 && tablero[x][y] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[x][y] = movimientos[x][y] + voltear;
                }
            }
        }
    }
    return;
}

/* Función que verifica y marca los movimientos válidos en la dirección diagonal hacia abajo a la izquierda 
en el tablero para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos en esta dirección.*/
void movimientos_validos_diagonal_abajo_izquierda(int tablero[8][8], int jugador, int movimientos[8][8]) {
    // Índices para recorrer el tablero (filas y columnas)
    // Variables auxiliares para recorrer en diagonal
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i, j, x, y, val, comp, voltear;

    // Establecer el jugador para ver con qué número se va a comparar
    if (jugador == 1) {
        val = 1;
        comp = 2;
    } else if (jugador == 2) {
        val = 2;
        comp = 1;
    }

    // Recorrer todas las casillas del tablero
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            // Verificar si se encuentra una ficha del jugador actual
            if (tablero[j][i] == val) {
                // Avanzar una fila hacia abajo
                x = j + 1; 
                // Avanzar una columna hacia la izquierda
                y = i - 1; 
                // Reiniciar el contador de fichas del oponente
                voltear = 0;

                // Recorrer en diagonal hacia abajo a la izquierda mientras no se salga del tablero
                while (x < 8 && y >= 0 && tablero[x][y] == comp) {
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++;
                    // Avanzar hacia abajo
                    x++; 
                    // Avanzar hacia la izquierda
                    y--; 
                }

                // Verificar si se encontró una casilla vacía y hay fichas del oponente para voltear
                if (x < 8 && y >= 0 && tablero[x][y] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[x][y] = movimientos[x][y] + voltear;
                }
            }
        }
    }
    return;
}

/* Función que verifica y marca los movimientos válidos en la dirección diagonal hacia arriba a la
izquierda en el tablero para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos en esta dirección.*/
void movimientos_validos_diagonal_arriba_izquierda(int tablero[8][8], int jugador, int movimientos[8][8]) {
    // Índices para recorrer el tablero (filas y columnas)
    // Variables auxiliares para recorrer en diagonal
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i, j, x, y, val, comp, voltear;

    // Establecer el jugador para ver con qué número se va a comparar
    if (jugador == 1) {
        val = 1;
        comp = 2;
    } else if (jugador == 2) {
        val = 2;
        comp = 1;
    }

    // Recorrer todas las casillas del tablero
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            // Verificar si se encuentra una ficha del jugador actual
            if (tablero[j][i] == val) {
                // Avanzar una fila hacia arriba
                x = j - 1; 
                // Avanzar una columna hacia la izquierda
                y = i - 1; 
                // Reiniciar el contador de fichas del oponente
                voltear = 0; 

                // Recorrer en diagonal hacia arriba a la izquierda mientras no se salga del tablero
                while (x >= 0 && y >= 0 && tablero[x][y] == comp) {
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++;
                    // Avanzar hacia arriba
                    x--; 
                    // Avanzar hacia la izquierda
                    y--; 
                }

                // Verificar si se encontró una casilla vacía y hay fichas del oponente para voltear
                if (x >= 0 && y >= 0 && tablero[x][y] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[x][y] = movimientos[x][y] + voltear;
                }
            }
        }
    }
    return;
}

/* Función que verifica y marca los movimientos válidos en la dirección diagonal hacia arriba a la
derecha en el tablero para el jugador actual.
@param:
- tablero: Estado actual del tablero.
- jugador: El jugador actual (1 o 2) para quien se calculan los movimientos válidos.
- movimientos: Tablero de 8x8 que se actualizará para incluir los movimientos válidos en esta dirección.*/
void movimientos_validos_diagonal_arriba_derecha(int tablero[8][8], int jugador, int movimientos[8][8]) {
    // Índices para recorrer el tablero (filas y columnas)
    // Variables auxiliares para recorrer en diagonal
    // Valores que representan al jugador actual (val) y al oponente (comp)
    // Contador de fichas del oponente que podrían ser volteadas
    int i, j, x, y, val, comp, voltear;

    // Establecer el jugador para ver con qué número se va a comparar
    if (jugador == 1) {
        val = 1;
        comp = 2;
    } else if (jugador == 2) {
        val = 2;
        comp = 1;
    }

    // Recorrer todas las casillas del tablero
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            // Verificar si se encuentra una ficha del jugador actual
            if (tablero[j][i] == val) {
                // Avanzar una fila hacia arriba
                x = j - 1; 
                // Avanzar una columna hacia la derecha
                y = i + 1;
                // Reiniciar el contador de fichas del oponente
                voltear = 0; 

                // Recorrer en diagonal hacia arriba a la derecha mientras no se salga del tablero
                while (x >= 0 && y < 8 && tablero[x][y] == comp) {
                    // Incrementar el contador de posibles fichas para voltear
                    voltear++;
                    // Avanzar hacia arriba
                    x--; 
                    // Avanzar hacia la derecha
                    y++; 
                }

                // Verificar si se encontró una casilla vacía y hay fichas del oponente para voltear
                if (x >= 0 && y < 8 && tablero[x][y] == 0 && voltear > 0) {
                    // Marcar la casilla como un movimiento válido
                    movimientos[x][y] = movimientos[x][y] + voltear;
                }
            }
        }
    }
    return;
}