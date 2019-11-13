.c.o:   $*.h
	gcc -w -c $*.c

all: SCAS

SCAS:  SCAS.o queue.o linked_list.o
	gcc -w -o $@ $^

clean:
	rm *.o *.*~ *~ SCAS