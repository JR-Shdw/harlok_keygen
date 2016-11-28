harlockkeygen : char_key_tools.o harlockkeygen.o
	gcc char_key_tools.o harlockkeygen.o -o ./harlockkeygen

harlockkeygen_cli : intarray.o char_key_tools.o harlockkeygen_cli.o 
	gcc intarray.o char_key_tools.o harlockkeygen_cli.o -o ./harlockkeygen_cli

harlockkeygen_cli.o : harlockkeygen_cli.c char_key_tools.h
	gcc -c harlockkeygen_cli.c

harlockkeygen.o : harlockkeygen.c char_key_tools.h
	gcc -c harlockkeygen.c

intarray.o : intarray.c intarray.h
	gcc -c intarray.c

char_key_tools.o : char_key_tools.c char_key_tools.h
	gcc -c char_key_tools.c
