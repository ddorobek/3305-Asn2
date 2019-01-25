CC=gcc
CFLAGS=-c
CMATH=-lm
PFLAG=-pthread

all: clean myOS 

myOS: myOS.o shell.o execute.o tokenize.o simulator.o simulate.o job.o linked_list.o linked_stack.o helper.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG)

myOS.o: myOS.c myOS.h
	$(CC) $(CFLAGS) -o $@ $<

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -o $@ $<

execute.o: execute.c execute.h
	$(CC) $(CFLAGS) -o $@ $<

tokenize.o: tokenize.c tokenize.h
	$(CC) $(CFLAGS) -o $@ $<

simulator.o: simulator.c simulator.h
	$(CC) $(CFLAGS) -o $@ $<

simulate.o: simulate.c simulate.h
	$(CC) $(CFLAGS) -o $@ $<  $(PFLAG)

job.o: job.c job.h
	$(CC) $(CFLAGS) -o $@ $<

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o $@ $<

linked_stack.o: linked_stack.c linked_stack.h
	$(CC) $(CFLAGS) -o $@ $<

helper.o: helper.c helper.h 
	$(CC) $(CFLAGS) -o $@ $<

test: clean myOS
	bash ./tests/run.sh

clean:
	rm -f *.o myOS report.txt system.out