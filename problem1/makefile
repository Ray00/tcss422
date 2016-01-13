CC = gcc

default: fifoqueue_test

fifoqueue_test:  fifoqueue_test.c fifoqueue.o
	$(CC) -c fifoqueue_test.c fifoqueue.o pcb.o -o fifoqueue_test

fifoqueue.o: fifoqueue.c fifoqueue.h pcb.o
	$(CC) -c fifoqueue.c pcb.o -o fifoqueue.o

pcb.o:  pcb.c pcb.h
	$(CC) -c pcb.c -o pcb.o	

clean:
	rm -f *.o

