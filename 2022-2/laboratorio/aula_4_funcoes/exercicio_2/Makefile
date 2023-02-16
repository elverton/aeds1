programa: main.o massa.o
	gcc main.o massa.o -o programa

main.o: main.c
	gcc -c main.c

massa.o: massa.c massa.h
	gcc -c massa.c

executa: programa
	./programa

limpa:
	rm *.o programa
