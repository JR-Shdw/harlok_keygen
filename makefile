CC = gcc
CFLAGS = -Wall -Wextra -lm

harlockkeygen : char_key_tools.o intarray.o harlockkeygen.o
	$(CC) char_key_tools.o intarray.o harlockkeygen.o -o ./harlockkeygen $(CFLAGS)

harlockkeygen_cli : intarray.o char_key_tools.o harlockkeygen_cli.o
	$(CC) intarray.o char_key_tools.o harlockkeygen_cli.o -o ./harlockkeygen_cli $(CFLAGS)

harlockkeygen_cli.o : harlockkeygen_cli.c char_key_tools.h intarray.h
	$(CC) -c harlockkeygen_cli.c $(CFLAGS)

harlockkeygen.o : harlockkeygen.c char_key_tools.h intarray.h
	$(CC) -c harlockkeygen.c $(CFLAGS)

intarray.o : intarray.c intarray.h
	$(CC) -c intarray.c $(CFLAGS)

char_key_tools.o : char_key_tools.c char_key_tools.h intarray.h
	$(CC) -c char_key_tools.c $(CFLAGS)

all : harlockkeygen harlockkeygen_cli

clean :
	rm -f *.o *.gch harlockkeygen harlockkeygen_cli

.PHONY : all clean
