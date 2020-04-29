CC = gcc
CFLAGS = -Wall -g

all: cardlist 

cardlist: cardmain.o cardlist.o card.o
	$(CC) $(CFLAGS) -o cardlist cardmain.o card.o cardlist.o

cardlist.o: cardlist.c cardlist.h card.h
	$(CC) $(CFLAGS) -c cardlist.c

cardmain.o: cardmain.c cardlist.h card.h
	$(CC) $(CFLAGS) -c cardmain.c

card.o : card.c card.h
	$(CC) $(CFLAGS) -c card.c

.PHONY: clean
clean:
	@-rm -f *.o cardlist 
