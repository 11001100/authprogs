PROG = authprogs
OBJS = ap_str.o ap_log.o ap.o

CC = gcc
CFLAGS= -Wall
LDFLAGS =

.c.o:
	$(CC) -c $(CFLAGS) $*.c

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

clean :
	rm -f *.o $(PROG)
