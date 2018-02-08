all: prog1sorter prog1generator

prog1sorter: prog1sorter.o timing.o
	gcc prog1sorter.o timing.o -o prog1sorter -g
	
prog1sorter.o: prog1sorter.c readArgs.h timing.h
	gcc -c prog1sorter.c -o prog1sorter.o -g
	
prog1generator: prog1generator.o timing.o
	gcc prog1generator.o timing.o -o prog1generator -g
	
prog1generator.o: prog1generator.c readArgs.h timing.h
	gcc -c prog1generator.c -o prog1generator.o -g
	
timing.o: timing.c timing.h
	gcc -c timing.c -o timing.o -g
	
checkmemSort: prog1sorter
	valgrind --track-origins=yes ./prog1sorter $(ARGS)
	
checkmemGen: prog1sorter
	valgrind --track-origins=yes ./prog1generator $(ARGS)
	
runSort: prog1sorter
	./prog1sorter $(ARGS)
	
runGen: prog1generator
	./prog1generator $(ARGS)
	
clean:
	rm *.o prog1generator prog1sorter vgcore.*