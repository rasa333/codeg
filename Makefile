CFLAGS  = -g
LDFLAGS = 
LIBS    = -lm
CC      = gcc
prg     = codeg


%.o : %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $<

objects        		     := $(patsubst %.c,%.o,$(wildcard *.c))


$(prg)	: $(objects)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(prg) $(objects) $(LIBS)

clean	   : 
	        rm -f $(prg) core *.o
 
	   
