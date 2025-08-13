// Definición de funciones

// FUNCIONES PARA EL MENU DEL JUEGO
void maingame (int c, char *texto[]);
void nombres (char j1[], char j2[]);
int desplegar_menu(void);
int manual(void);

int random_jugador (void);

// FUNCIONES PARA LA JUGABILIDAD
void JUGvsJUG();
void PCvsJUG();
void continuarPCvsJUG(char *archivo_guardado);
void continuarJUGvsJUG(char *archivo_guardado);

// FUNCIONES PARA VISUALIZAR EL HISTORIAL DE JUEGO

void fJUGvsJUG (char fname[]);
void fPCvsJUG (char fname[]);

// FUNCIONES PARA SALVAR Y GUARDAR LAS PARTIDAS

int seleccion(void);

void solicitar_nombre_archivo (char nombre_archivo[]);

void guardar_partida(char *archivo, int tablero[8][8], char jugador1[], char jugador2[], int jugador_actual, int fichas_j1, int fichas_j2, int modo);

int cargar_partida(char *filename, int tablero[8][8], char j1[], char j2[], int *jugador, int *modo);


// Función para llenar el tablero con 0
void llenar_tablero(int tablero[8][8]);
void imp_contenido_tablero(int tablero[8][8]);
void llenar_tablero_ceros(int tablero[8][8]);

// Análisis de un punto al rededor de 8 
void analizar(int fila, int columna, int tablero[8][8], int jugador);
void arriba_derecha(int fila, int columna, int tablero[8][8],int jugador);
void derecha(int fila, int columna, int tablero[8][8],int jugador);
void abajo_derecha(int fila, int columna, int tablero[8][8],int jugador);
void abajo(int fila, int columna, int tablero[8][8],int jugador);
void arriba_izquierda(int fila, int columna, int tablero[8][8],int jugador);
void abajo_izquierda(int fila, int columna, int tablero[8][8],int jugador);
void izquierda(int fila, int columna, int tablero[8][8],int jugador);
void arriba(int fila, int columna, int tablero[8][8],int jugador);

// Llenado de las coordenadas
void recibir_verificar_coordenada(int *fila, int *columna, int tablero[8][8]);
int pedir_fila(void);
int pedir_columna(void);

// Final del juego 
int casillas_vacias(int tablero[8][8]);

// Analisis de movimientos validos 
void movimientos_validos(int tablero[8][8],int jugador,int movimientos[8][8]);
void movimientos_validos_derecha(int tablero[8][8],int jugador,int movimientos[8][8]);
void movimientos_validos_izquierda(int tablero[8][8],int jugador,int movimientos[8][8]);
void movimientos_validos_arriba(int tablero[8][8],int jugador,int movimientos[8][8]);
void movimientos_validos_abajo(int tablero[8][8],int jugador,int movimientos[8][8]);
void movimientos_validos_diagonal_abajo_derecha(int tablero[8][8], int jugador, int movimientos[8][8]);
void movimientos_validos_diagonal_abajo_izquierda(int tablero[8][8], int jugador, int movimientos[8][8]);
void movimientos_validos_diagonal_arriba_izquierda(int tablero[8][8], int jugador, int movimientos[8][8]);
void movimientos_validos_diagonal_arriba_derecha(int tablero[8][8], int jugador, int movimientos[8][8]); 
