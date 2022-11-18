compilar: coordenada.o main.o
	gcc coordenada.o main.o -o prog1 -lm
coordenada.o: coordenada.c coordenada.h
	gcc -c coordenada.c
main.o: main.c
	gcc -c main.c
clean:
	rm *.o prog1

