.c.o:   $*.h
	gcc -w -c $*.c

all: SCAS

SCAS:  SCAS.o
	gcc -w -o $@ $^

clean:
	rm *.o *.*~ *~ SCAS