CC = gcc

steamshortcut: main.o launcher.o
	$(CC) -o steamshortcut main.o launcher.o

main.o: src/main.c src/launcher.h
	$(CC) -c src/main.c -o main.o

launcher.o: src/launcher.c src/launcher.h
	$(CC) -c src/launcher.c -o launcher.o

clean:
	rm -f steamshortcut *.o