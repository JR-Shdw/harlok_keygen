harlockkeygen : char_key_tools.o harlockkeygen.o
	gcc char_key_tools.o harlockkeygen.o -o ./harlockkeygen

harlockkeygen.o : harlockkeygen.c char_key_tools.h
	gcc -c harlockkeygen.c

char_key_tools.o : char_key_tools.c char_key_tools.h
	gcc -c char_key_tools.c
