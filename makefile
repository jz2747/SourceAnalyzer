# File: stat/makefile
CC=gcc
CFLAGS=-g -Wall -D__USE_FIXED_PROTOTYPES__
OBJS= stat.o ch_type.o token.o in_file.o

all: stat

stat: $(OBJS)
	$(CC) $(CFLAGS) -o stat $(OBJS)

stat.o: stat.c token.h
	$(CC) $(CFLAGS) -c stat.c

ch_type.o: ch_type.c ch_type.h
	$(CC) $(CFLAGS) -c ch_type.c

token.o: token.c token.h ch_type.h in_file.h
	$(CC) $(CFLAGS) -c token.c

in_file.o: in_file.c in_file.h
	$(CC) $(CFLAGS) -c in_files.c

clean:
	rm -f stat stat.o ch_type.o token.o in_file.o
