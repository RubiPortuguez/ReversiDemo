proyecto.out: proyecto.o logica.o tablero.o menu.o gameplay.o
	gcc -o proyecto.out proyecto.o logica.o tablero.o menu.o gameplay.o
proyecto.o: proyecto.c
	gcc -c proyecto.c
logica.o: logica.c
	gcc -c logica.c
tablero.o: tablero.c
	gcc -c tablero.c
menu.o: menu.c
	gcc -c menu.c
gameplay.o: gameplay.c
	gcc -c gameplay.c
clean :
	rm *.o
	rm *.out
