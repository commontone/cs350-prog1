all: prog1sorter prog1generator

prog1sorter: prog1sorter.o
	gcc prog1sorter.o -o prog1sorter -g
	
prog1sorter.o: prog1sorter.c
	gcc -c prog1sorter.c -o prog1sorter.o
	
prog1generator: prog1generator.o
	gcc prog1generator.o -o prog1generator -g
	
prog1generator.o: prog1generator.o
	gcc -c prog1generator.c -o prog1generator.o
	
checkmemSort: prog1sorter
	valgrind ./prog1sorter
	
runSort: prog1sorter
	./prog1sorter
	
clean:
	rm *.o prog1generator prog1sorter vgcore.*