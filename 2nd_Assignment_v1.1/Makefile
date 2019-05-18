CC = gcc
CFLAFS = -g -Wall

prog: Session.o main.o
	$(CC) $(CFLAFS) -o prog Session.o main.o
main.o: main.c 
	$(CC) $(CFLAFS) -c main.c 
Session.o: Session.c 
	$(CC) $(CFLAFS) -c Session.c

.PHONY: clean
clean:
	rm -f prog main.o Session.o