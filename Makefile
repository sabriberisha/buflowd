CC		= gcc
CFLAGS		= -Wall -g -export-dynamic
OBJS		= buflowd.o traffic.o flow.o flowdata.o

all:		buflowd

buflowd:	$(OBJS)
		$(CC) $(CFLAGS) -o buflowd $(OBJS) -pthread
		rm -f *.o

clean:		
		rm -f buflowd
		rm -f *.o
		rm -f *.core
		@sh -c 'for i in `ls *.c` ; do echo indent $$i ;  indent $$i -i2 -di2 -npsl -nfcb -nlp -d0 -bl ; rm $$i.BAK ; done'

buflowd.o:	buflowd.c
traffic.o:	traffic.c
flow.o:		flow.c
flowdata.o:	flowdata.c
