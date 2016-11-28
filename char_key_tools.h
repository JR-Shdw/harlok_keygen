#ifndef __CHAR_KEY_TOOLS_H__
#define __CHAR_KEY_TOOLS_H__


#include "intarray.h"


typedef struct _char_table *char_table;
typedef struct _key_list key_list;
typedef struct _char_table_2D *char_table_2D;


struct _char_table
{
  char* data;
  int len;
  int alloc;
};

struct _key_list
{
  char* list;
  int size;
  int num;
};

struct _char_table_2D
{
  char_table* data;
  int len;
  int alloc;
};


/////////// key_list f() /////////////
extern key_list key_list_create(int size, int num);
extern char_table key_table_create(int len, int alloc);
extern void list_destroy ( key_list data);
extern void key_gen_store (key_list C ,char_table key, int size, int l);
extern void print_key(char_table key, int size);
extern void print_list_debug(key_list L, int size ,int num);

/////////// hkkeygen f() /////////////

extern int random_value(int to);
extern void key_gen(char_table key, char_table keymap, int size, int random_to );
extern char_table ASCII_key_set();//a refaire
extern char_table ASCII_key_set_cli(char_table opt, char_table_2D ASCII);
extern char_table_2D TYPABLE_ASCII_table();

/////////// cli f() ////////////

extern void intarray_cli_args_check(intarray I);
extern char_table cli_get_flags (char **args, int argn);
extern char_table_2D cli_get_int (char **args, int argn);

/////////// char_table f() ///////////  
extern void str_copy_to_char_table (char * str,char_table table);
extern char_table int_to_char_table (int n);
extern int char_table_to_int (char_table j);
extern char_table char_table_input(void);
extern void char_table_add (char_table A, char n);
extern char_table empty_char_table_create (int alloc);
extern char_table standard_empty_char_table_create (void);
extern char_table ext_char_table_create (int len, int alloc);
extern void char_table_set (char_table C, int i, char n);
extern void ext_char_table_set (char_table T, int i, char n);
extern void char_table_alloc_more (char_table T, int new_alloc);
extern void table_destroy (char_table key);
extern void char_table_print (char_table C);
extern char_table char_table_concat(char_table T1, char_table T2);
extern char char_table_get (char_table T , int i);

/////////// misc f() ///////////
extern char_table get_secure_input();
extern void display_help (void);

/////////// char_table_2D f() ////////////
extern char_table_2D char_table_2D_create (int len);
extern char_table_2D ext_char_table_2D_create (int len, int alloc);
extern char_table_2D empty_char_table_2D_create(int alloc);
extern char_table_2D standard_empty_char_table_2D_create (void);
extern void char_table_2D_destroy (char_table_2D S);
extern void char_table_2D_and_char_table_destroy(char_table_2D S);
extern char_table char_table_2D_get (char_table_2D S , int i);
extern void char_table_2D_set (char_table_2D S , int i , char_table n);
extern void ext_char_table_2D_set ( char_table_2D S, int i, char_table n);
extern int char_table_2D_length (char_table_2D S);
extern void char_table_2D_add(char_table_2D S, char_table j);
extern void char_table_2D_delete(char_table_2D S, int loc);
extern void char_table_2D_alloc_more(char_table_2D T , int new_alloc);
extern intarray char_table_2D_to_intarray(char_table_2D T);// a ecrire

///////////// file f() /////////////

#endif



