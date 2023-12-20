CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
SOURCE=crawler.c curl.c bag.c pagedir.c hashtable.c url.c
OBJ=crawler.o curl.o hashtable.o bag.o pagedir.o url.o
HEADER=crawler.h curl.h hashtable.h pagedir.h url.h bag.h

crawler: ${OBJ} ${HEADER}
	$(CC) $(OBJ) $(CFLAGS) -o crawler -lcurl

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c 

clean:
	rm -rf crawler
	rm -rf *.o
