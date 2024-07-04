all : pseudo_shell
	
	
pseudo_shell: main.o string_parser.o command.o
	gcc -o pseudo-shell main.o string_parser.o command.o
	
	
main.o: main.c
	gcc -c main.c
	
string_parser.o: string_parser.c string_parser.h
	gcc -c string_parser.c

command.o: command.c command.h
	gcc -c command.c
	
clean:
	rm -f core *.o pseudo-shell
