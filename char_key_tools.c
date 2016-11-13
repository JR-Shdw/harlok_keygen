#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "char_key_tools.h"

#define RC printf ("\n")

/* a -> alphabet
   n -> numeric
   s -> special
   --number
ex hkeygen -ans 10 -> create a password of size 10

ex hkeygen -a 15 --number 100 -> generate 100 password of size 15




*/


key_list key_list_create(int size, int num)
{
  key_list L;
  L.size = size;
  L.num = num;
  L.list = malloc (size * num);
  return L;
}
 
char_table key_table_create(int len, int alloc)
{
  char_table A = malloc (sizeof (struct _char_table));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc(sizeof (char) * alloc);
  return A;
}


int key_get_size()
{
  int n;
  printf("Specify the size of the password : ");
  fscanf(stdin,"%d",&n);
   return n;
}

int key_get_number()
{
	int l;
	printf("Specify the number of generated password  : ");
	fscanf(stdin,"%d",&l);
	
  return l;
}


char_table ASCII_key_set()
{
  char_table A = standard_empty_char_table_create ();
  char input[10];
  char input2;
  char* ASCII_set;
  char i;
  int j;
 menu:
  fprintf(stdout,"Harlock System Keygen Version 0.90\n\n[1] Alphabet character\n[2] Numeric characters\n[3] Alphanumeric characters\n[4] Alphabet plus special symbol\n[5] Numeric plus special characters\n[6] Special characters\n[7] Alphanumeric plus special characters\n[8] Help\n[9] Exit\nYour selection : " ); 
  fscanf(stdin,"%10s",input);
  i = input[0];
while  (i < 49 || i > 57)
{
 
  fprintf(stdout,"\n[1] Alphabet character\n[2] Numeric characters\n[3] Alphanumeric characters\n[4]Alphabet plus special symbol\n[5] Numeric plus special characters\n[6] Special characterS\n[7] Alphanumeric plus special characters\n[8] Help\n[9] Exit\nYour selection : "); 
  fscanf(stdin,"%10s", input);
  i = input[0];
}

 switch(i)
   {
     
   case '1':
     {
       ASCII_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
       break;
     }
   case '2':
     {
       ASCII_set = "1234567890";
       break;
     }
   case '3':
     {
       ASCII_set  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";break;

     }
   case '4':
     {
       ASCII_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&' (-)=$*!.?:;,<>~#{[|`^@]}";break;

     }
     
   case '5':
     {
       ASCII_set = "1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}";
       break;
     }
   case '6':
     {
       ASCII_set = "&' (-)=$*!.?:;,<>~#{[|`^@]}";
       break;
     }
   case '7':
     {
       ASCII_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}";
       break;
     }
   case '8':
     {
       fprintf(stdout,"\n[1]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n[2]1234567890\n[3]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\n[4]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&' (-)=$*!.?:;,<>~#{[|`^@]}\n[5]1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}\n[6]&' (-)=$*!.?:;,<>~#{[|`^@]}\n[7]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}\n\n");
       
       goto menu;
     }
   case '9':
     {
      
       ASCII_set = NULL;
       return A;
     }
     
   default:
     goto menu;
    
     
   }

 for (j = 0; j < strlen(ASCII_set); j++)
   {
     ext_char_table_set (A, j, ASCII_set[j]);
   }

 ASCII_set = NULL;
 return A;

 
}




int random_value (int to)
{
  long unsigned int randomA = random() % (to);
  return randomA;
}
      
void print_key (char_table key, int size)
{
	long unsigned int n;
	for(n = 0 ; n < size; n++)
	{
	  printf("%c",key->data[n]);
	}
}

void print_list_debug(key_list L, int size ,int num)
{
  long unsigned int m;
for(m = 0 ; m < (num * size) ; m++)
   {
     printf("%c",L.list[m]);
   }
}


void key_gen(char_table key,char_table keymap, int size, int random_to )
{
  int i,a ;
for (i=0; i<size ;i++)
  {
	key->data[i] = keymap->data[random_value(random_to)];
  }
}


void table_destroy (char_table key)
{
  free (key->data);
  free (key);
}

void list_destroy ( key_list data)
{
  free (data.list);
}
    
void key_gen_store (key_list C ,char_table key, int size, int l)
{
  int n;
  int a; 
  for( n = 0 ; n < size ; n++)
  {
	a = n +(size * l);
    C.list[a] = key->data[n];
  }
} 

void str_copy_to_char_table(char * str,char_table table)
  
{
  int i;
  for (i = 0;  i < (strlen(str)); i++)
    table->data[i] = str[i];
}

char_table int_to_char_table (int n)
{
  {
    char* tmp;
    int i = 0;
    char_table T;
    if (n == 0)
      {
       
	tmp[0] = '0';
	tmp[1] = '\0';
	T = key_table_create(2,2);
	T->data[0] = tmp[0];
	T->data[1] = tmp[1];
	tmp = NULL;
	return T;
      }
    
    else
      {
	while (n != 0)
	  {
	    tmp[i] = ((n % 10) + '0');
	    n /= 10;
	    i++;
	  }
	T = key_table_create(strlen(tmp),strlen(tmp));
	for(i=0; i< strlen(tmp); i++)
	  {
	    T->data[i] =  tmp[((strlen(tmp)-1)-i)];
	  }
	tmp = NULL;
	return T;
      }
  }
}

int char_table_to_int (char_table j) /* assume j is an int */
{
  int r = 0;
  int i;
  for (i = 0; i < j->len; i++)
    {
      r *= 10;
      r += (((int) j->data[i]) - 48);
    }
  return r;
}


char_table char_table_input(void)
{
  char_table j = standard_empty_char_table_create ();
  char c = getchar ();
  while (c != '\n')
    {
      char_table_add(j, c);
      c = getchar ();
    }
  return j;
}


void char_table_add (char_table A, char n) 
{
  ext_char_table_set (A, A->len, n);
}

char_table empty_char_table_create (int alloc)
{
  return ext_char_table_create (0, alloc);
}


char_table standard_empty_char_table_create (void)
{
  return ext_char_table_create (0, 10);
}

char_table ext_char_table_create (int len, int alloc)
{
  {
    char_table A = malloc (sizeof (struct _char_table));
    A->len = len;
    A->alloc = alloc;
    A->data = malloc ((sizeof(char)) * alloc );
    return A;
  }
}



void char_table_set (char_table C, int i, char n)
{
  C->data[i] = n;
}

void ext_char_table_set (char_table T, int i, char n)
{
  if (i >= T->alloc)
    char_table_alloc_more (T, i * 2);
  if (i >= T->len)
    T->len = i + 1;
  char_table_set (T, i, n);
}

void char_table_alloc_more (char_table T, int new_alloc)
{
  char* tmp = malloc ((sizeof(char))* new_alloc);
  int i;
  for (i = 0; i < T->len; i++)
    {
      tmp[i] = T->data[i];
    }
  free (T->data);
  T->data = tmp;
  T->alloc = new_alloc;
}

char_table get_secure_input()
{
  int i;
  char tmp [4];
  fscanf(stdin,"%3s",tmp);
  char_table T = empty_char_table_create(5);
  for (i = 0 ;i < strlen(tmp); i++)
    {
      char_table_add(T, tmp[i]);
    }
  return T;
}
  
