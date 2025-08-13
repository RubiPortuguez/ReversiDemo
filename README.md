# Reversi en C

Este proyecto implementa el clásico juego **Reversi** (u Othello) en lenguaje C, jugable desde la terminal.  
Incluye modos **Jugador vs Jugador**, **Jugador vs CPU**, soporte para guardar/cargar partidas y visualizar un historial de juego.

---

## 📋 Características

- Tablero de **8x8** con posición inicial estándar.
- **2 modos de juego**:
  - Jugador vs Jugador
  - Jugador vs CPU (con selección automática de movimientos por parte de la máquina)
- Guardado y carga de partidas.
- Historial de juego en archivo.
- Manual de usuario integrado.
- Validación de movimientos y aplicación automática de las reglas.
- Interfaz por consola.

---

## 🛠️ Requisitos

- Compilador **GCC** o compatible.
- Sistema operativo tipo Unix/Linux (uso de comandos `clear` y `sleep`).
- Makefile incluido para compilación.

---

## ⚙️ Instalación

Clona el repositorio y compila el proyecto:

```bash
git clone <URL-del-repositorio>
cd <directorio-del-proyecto>
make
```

Esto generará el ejecutable `proyecto.out`.

---

## ▶️ Ejecución

Puedes ejecutar el juego desde la terminal con los siguientes comandos:

### Modos directos:
```bash
./proyecto.out -n 1   # CPU vs Jugador
./proyecto.out -n 2   # Jugador vs Jugador
./proyecto.out -h     # Mostrar manual de usuario
```

### Con opciones de archivo:
```bash
./proyecto.out -n <modo> -t <archivo>  # Abrir historial de un archivo
./proyecto.out -l <archivo>            # Cargar última partida guardada
```

### Desde el menú interactivo:
```bash
./proyecto.out -n
```
El menú te permitirá elegir entre:
- Jugar contra CPU
- Jugar contra otro jugador
- Ver el manual
- Cargar partida
- Salir

---

## 🎮 Cómo jugar

- El tablero usa:
  - `.` → casilla vacía
  - `O` → ficha del Jugador 1
  - `X` → ficha del Jugador 2
- En tu turno, ingresa las coordenadas (fila y columna) para colocar tu ficha.
- Un movimiento es válido si capturas al menos una ficha del oponente, alineándola entre la ficha que colocas y otra de las tuyas (horizontal, vertical o diagonal).
- Si no tienes movimientos válidos, pierdes el turno.
- El juego termina cuando:
  - El tablero está lleno, o
  - Ningún jugador puede mover.

---

## 📌 Ejemplo visual

**Posición inicial:**
```
  0 1 2 3 4 5 6 7
0 . . . . . . . .
1 . . . . . . . .
2 . . . . . . . .
3 . . . O X . . .
4 . . . X O . . .
5 . . . . . . . .
6 . . . . . . . .
7 . . . . . . . .
```

**Jugador X coloca ficha en (5,4):**
```
  0 1 2 3 4 5 6 7
0 . . . . . . . .
1 . . . . . . . .
2 . . . . . . . .
3 . . . O X . . .
4 . . . X X X . .
5 . . . . X . . .
6 . . . . . . . .
7 . . . . . . . .
```
Las fichas `O` capturadas se voltean a `X`.

---

## 💾 Guardar y cargar partidas

Durante la partida, puedes:
- **Guardar** → El juego solicitará un nombre de archivo para almacenar el estado.
- **Cargar** → Usando `./proyecto.out -l <archivo>` podrás retomar la partida.

---

## 📂 Estructura del proyecto

```
├── proyecto.c           # Punto de entrada (main)
├── menu.c               # Menú principal y flujo de ejecución
├── gameplay.c           # Lógica de juego y modos
├── tablero.c            # Visualización y manejo del tablero
├── logica.c             # Reglas y validación de movimientos
├── funciones.h          # Declaración de funciones
├── MANUAL_DE_USUARIO.txt# Manual de usuario en texto
├── Makefile             # Compilación
└── .gitignore
```

---

## 👥 Autores

- Rubi  
- Nuri  
- Orlando  
