shell: shell.o
	gcc -o shell shell.o

shell.o:
	gcc -c shell.c

clean:
	rm shell.o
	rm shell
	rm shell.h.gch