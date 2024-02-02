CC = gcc

steamshortcut: main.o launcher.o
	$(CC) -o steamshortcut main.c launcher.o

steamshortcut.o: main.c launcher.h
	$(CC) -c main.c

launcher.o: launcher.c launcher.h
	$(CC) -c launcher.c

clean:
	rm -f steamshortcut *.o