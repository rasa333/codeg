CFLAGS  = -O3
LDFLAGS = -s
LIBS    = -lm
CC      = gcc
prg     = codeg


%.o : %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $<

objects        		     := $(patsubst %.c,%.o,$(wildcard *.c))


all $(prg)	: $(objects)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(prg) $(objects) $(LIBS)

clean	   : 
	        rm -f $(prg) core *.o
 
	   
