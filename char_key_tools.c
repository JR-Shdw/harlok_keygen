//HarlokSOFTWARE 2016
//tools for char manipulation 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "char_key_tools.h"

#define RC printf ("\n")

/* 
   -------Options for keygen program------
   a -> alphabet
   n -> numeric
   s -> special
   --number
   ex hkeygen -ans 10 -> create a password of size 10

   ex hkeygen -a 15 --number 100 -> generate 100 password of size 15

   ---------  NOTE : --------------
   ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
   1234567890
   &~"'(-_@)=#{[|`\^]}$*%!:;,?./^

   ASCII CHART
   Alphabet : 65-90 97-122
   Numeric : 48-57
   other : 32-47 58-64 91-96 123-126
*/

////////////// key_list f() ////////////

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

char_table ASCII_key_set(char_table_2D ASCII) //non cli version return NULL if exit
{
  char input[10];
  char * menu = "\n[1] Alphabet character\n[2] Numeric characters\n[3] Alphanumeric characters\n[4] Alphabet plus special symbol\n[5] Numeric plus special characters\n[6] Special characters\n[7] Alphanumeric plus special characters\n[8] Help\n[9] Exit\nYour selection : ";
  char * help = "\n[1]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n[2]1234567890\n[3]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\n[4]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&' (-)=$*!.?:;,<>~#{[|`^@]}\n[5]1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}\n[6]&' (-)=$*!.?:;,<>~#{[|`^@]}\n[7]abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890&' (-)=$*!.?:;,<>~#{[|`^@]}\n\n";
  char * author = "HarlokSOFTWARE";
  char * name = "hkkeygen";
  char * version = "Version 0.91";
  char i;
  int ASCII_set;
 menu:
  fprintf(stdout,"%s %s %s %s", author, name, version, menu); 
  fscanf(stdin,"%10s", input);
  i = input[0];
  while  (i < 49 || i > 57)
    {
      fprintf(stdout,"%s", menu); 
      fscanf(stdin,"%10s", input);
      i = input[0];
    }
  switch(i)
    { // H->0 A->1 N->2 O->3 AN->4 NO->5 AO->6 ANO->7
     case '1':
      {
	ASCII_set = 1; break;
      }
    case '2':
      {
	ASCII_set = 2; break;
      }
    case '3':
      {
	ASCII_set = 4; break;
      }
    case '4':
      {
	ASCII_set = 6; break;
      }
    case '5':
      {
	ASCII_set = 5; break;
      }
    case '6':
      {
	ASCII_set = 3; break;
      }
    case '7':
      {
	ASCII_set = 7; break;
      }
    case '8':
      {
	fprintf(stderr, "%s\n", help); goto menu;
      }
    case '9':
      {
	menu = NULL; help = NULL; author = NULL;
	name = NULL; version = NULL;
        return NULL;
      }
    default:
      goto menu;
    }
  menu = NULL; help = NULL; author = NULL;
  name = NULL; version = NULL;
  return ASCII->data[ASCII_set];
}


/* a -> alphabet
   n -> numeric
   s -> special
*/

char_table cli_get_flags (char **args, int argn)
{
  int i, j;
  
  char_table flags = ext_char_table_create (0, 5);
  if (argn > 1)
    {
      if(argn > 20)
	{
	  argn = 20;
	}
      for (i = 1; i < argn; i++)
	{
	  if(args[i] != NULL )
	    {
	      if(args[i][0] == '-')
		{
		  for ( j = 1; j < (int)strlen(args[i]); j++)
		    {
		      char_table_add(flags, args[i][j]);
		    }
		}
	    }
	}
    }
    
  return flags;
}

char_table_2D cli_get_int(char **args, int argn)
{
  int i, j, k = 0;
  
  char_table_2D int_args = ext_char_table_2D_create (0, 2);
  if (argn > 10)
    {
      argn= 20;
    }
  for (i = 1; i < argn; i++)
    {
      if(args[i] != NULL)
	{
	  if(args[i][0] != '-')
	    {
	      char_table C = ext_char_table_create(0, 4);
	      
	      for ( j = 0; j < (int)strlen(args[i]); j++)
		{
		  char_table_add(C, args[i][j]);
		  k++;
		}
	      char_table_2D_add(int_args, C);
	    }
	}
    }
      
  return int_args;
}

char_table_2D TYPABLE_ASCII_table()
{  /*  ASCII CHART
      Alphabet : 65-90 97-122
      Numeric : 48-57
      other : 32-47 58-64 91-96 123-126 */  
  int i = 0;
  char* help = "Usage: hkkeygen_cli [options] [number] [size] ...\nOptions:\n-a			Alphanumeric characters\n-n			Numeric characters\n-s			Special characters\n\nreport bugs to bug@harloks.com";

  int al1 = 65; int al2 = 90; int al3 = 97; int al4 = 122; int nu1 = 48; int nu2 = 57; int ot1 = 32; int ot2 = 47;int ot3 = 58; int ot4 = 64;int ot5 =91;int ot6 = 96; int ot7 = 123;int ot8 = 126;
  
  char_table_2D C = empty_char_table_2D_create (8);
  char_table H = empty_char_table_create (strlen(help));
  char_table A = empty_char_table_create (52);
  char_table N = empty_char_table_create (10);
  char_table O = empty_char_table_create (32);
  str_copy_to_char_table(help, H);
  
  while(i < 128)
    {
      if(((i >= al1) && (i<= al2)) || ((i >= al3) && (i <= al4)))
	{
	  char_table_add (A, (char)i );
	}
          
      if((i >= nu1) && (i<= nu2))
	{
	  char_table_add (N, (char)i );
	}
      
      if(((i >= ot1) && (i<= ot2)) || ((i >= ot3) && (i <= ot4)) || ((i >= ot5) && (i<= ot6)) || ((i >= ot7) && (i <= ot8)))
	{
	  char_table_add (O, (char)i );
	}
      i ++;
    }
  fprintf(stderr,"%s", help);
  char_table_print(H);
  char_table_2D_add(C, H);//0
  char_table_2D_add(C, A);//1
  char_table_2D_add(C, N);//2
  char_table_2D_add(C, O);//3
  char_table AN = char_table_concat(A, N);//4
  char_table NO = char_table_concat(N, O);//5
  char_table AO = char_table_concat(A, O);//6
  char_table ANO = char_table_concat(AN, O);//7
  char_table_2D_add(C, AN);
  char_table_2D_add(C, NO);
  char_table_2D_add(C, AO);
  char_table_2D_add(C, ANO);
  help = NULL; return C;
}

char_table ASCII_key_set_cli(char_table opt, char_table_2D ASCII)//cli version
{
  int ASCII_set, flag_len = 0;
  char a1 = '!', a2 = '!', a3 = '!';
  if (opt->len != 0)
    {
      flag_len = opt->len;
      if (flag_len > 3)
	{
	  flag_len = 3;
	}
      if(flag_len == 1)
	{
	  a1 = opt->data[0];
	}
      if(flag_len == 2)
	{
	  a1 = opt->data[0];
	  a2 = opt->data[1];
	}
      if(flag_len == 3)
	{
	  a1 = opt->data[0];
	  a2 = opt->data[1];
	  a3 = opt->data[2];
	}
    }
  if (opt->len == 0)
    {
      a1 = 'a';flag_len ++;
      a2 = 'n';flag_len ++;
    }
  switch((int)a1)
    {// H->0 A->1 N->2 O->3 AN->4 NO->5 AO->6 ANO->7
    case 97:// a == 97
      {
	if (flag_len == 1)
	  {
	    ASCII_set = 1;break;
	  }
	if (flag_len == 2)
	  {
	    if (a2 == 'n')
	      {
		ASCII_set = 4;break;
	      }
	    if (a2 == 's')
	      {
		ASCII_set = 6;break;
	      }
	    else
	      {
		ASCII_set = 0;break;
	      }
	  }
	if (flag_len == 3)
	  {
	    if (((a2 == 's') && (a3 == 'n')) || ((a2 == 'n') && (a3 == 's')))
	      {
		ASCII_set = 7;break;
	      }
	  }
	else
	  {
	    ASCII_set = 0;break;
	  }
      }
    case 110: //n == 110
      {
	if (flag_len == 1)
	  {
	    ASCII_set = 2; break;
	  }
	if (flag_len == 2)
	  {
	    if (a2 == 'a')
	      {
		ASCII_set = 4; break;
	      }
	    if (a2 == 's')
	      {
		ASCII_set = 5; break;
	      }
	    else
	      {
		ASCII_set = 0; break;
	      }
	  }
	if (flag_len == 3)
	  {
	    if (((a2 == 's') && (a3 == 'a')) || ((a2 == 'a') && (a3 == 's') ))
	      {
		ASCII_set = 7; break;
	      }
	    else
	      {
		ASCII_set = 0; break;
	      }
	  }
      }
    case 115: //s == 115
      {
	if (flag_len == 1)
	  {
	    ASCII_set = 3; break;
	  }
	if (flag_len == 2)
	  {
	    if (a2 == 'a')
	      {
		ASCII_set  = 4; break;
	      }
	    if (a2 == 'n')
	      {
		ASCII_set = 5; break;
	      }
	    else
	      {
		ASCII_set = 0; break;
	      }
	  }
	if (flag_len == 3)
	  {
	    if (((a2 == 'n') && (a3 == 'a')) || ((a2 == 'a') && (a3 == 'n')))
	      {
		ASCII_set = 7; break;
	      }
	    else
	      {
		ASCII_set = 0; break;
	      }
	  }
      }
    default:
      {
	ASCII_set = 0; break;
      }
    }
  return ASCII->data[ASCII_set];
}


int random_value (int to)
{
  long unsigned int randomA = random() % (to);
  return randomA;
}
      
void print_key (char_table key, int size)
{
  int n;
  for(n = 0 ; n < size; n++)
    {
      printf("%c",key->data[n]);
    }
}

void print_list_debug(key_list L, int size ,int num)
{
  int m;
  for(m = 0 ; m < (num * size) ; m++)
    {
      printf("%c",L.list[m]);
    }
}


void key_gen(char_table key,char_table keymap, int size, int random_to )
{
  int i;
  for (i=0; i<size ;i++)
    {
      key->data[i] = keymap->data[random_value(random_to)];
    }
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

/////////////// char_table f() ////////////////

void table_destroy (char_table key)
{
  free (key->data);
  free (key);
}

   
void str_copy_to_char_table(char * str,char_table table)
  
{
  int i;
  for (i = 0;  i < ((int)strlen(str)); i++)
    table->data[i] = str[i];
}

char_table int_to_char_table (int n)
{
  {
    int i = 0;
    char_table T;
    if (n == 0)
      {
	char* tmp;
	tmp[0] = '0';
	tmp[1] = '\0';
	T = key_table_create(2,2);
	T->data[0] = tmp[0];
	T->data[1] = tmp[1];
	tmp = NULL; return T;
      }
    else
      {
	char* tmp;
	while (n != 0)
	  {
	    tmp[i] = ((n % 10) + '0');
	    n /= 10;
	    i++;
	  }
	T = key_table_create(strlen(tmp),strlen(tmp));
	for(i=0; i< (int)strlen(tmp); i++)
	  {
	    T->data[i] =  tmp[(((int)strlen(tmp)-1)-i)];
	  }
	tmp = NULL; return T;
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
  char_table A = malloc (sizeof (struct _char_table));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc ((sizeof(char)) * alloc );
  return A;
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

void char_table_print (char_table C)
{
  int n;
  for(n = 0 ; n < C->len; n++)
    {
      printf("%c",C->data[n]);
    }
}


char_table get_secure_input()
{
  int i;
  char tmp [4];
  fscanf(stdin,"%3s",tmp);
  char_table T = empty_char_table_create(5);
  for (i = 0 ;i < (int)strlen(tmp); i++)
    {
      char_table_add(T, tmp[i]);
    }
  return T;
}
  
void intarray_cli_args_check(intarray I)
{
  int num_bound, size_bound, num_def, size_def;
  num_bound = 1000000;
  size_bound = 100;
  num_def = 1;
  size_def = 10;
    
  if (I->len != 0)
    {
      if (I->data[0] < 1) //number check
	{
	  intarray_set(I,0, num_def);
	}
      if (I->data[0] > num_bound)
	{
	  intarray_set(I,0, num_bound);
	}
    }
  if (I->len == 0 )
    intarray_add(I,num_def);
 
  if(I->len > 1) 
    {
      if (I->data[1] < 1 )//size check
	{
	  intarray_set (I,1, size_def);
	}
      if (I->data[1] > size_bound)
	{
	  intarray_set (I,1, size_bound);
	}
    }
  if (I->len == 1)
    intarray_add(I,size_def);
}





void display_help (void)
{
  fprintf(stdout,"Usage: hkkeygen_cli [options] [number] [size] ...\nOptions:\n-a			Alphanumeric characters\n-n			Numeric characters\n-s			Special characters\n\nreport bugs to bug@harloks.com"); 
}


char_table char_table_concat(char_table T1, char_table T2)
{
  int i, j, k;
  j = T1->len;
  k = T2->len;
  char_table T = ext_char_table_create (j + k, j + k);
  for(i=0 ; i < j ; i++)
    {
      char_table_set (T, i, char_table_get (T1 ,i));
    }
  for(i=0; i < k; i++)
    {
      char_table_set (T , (j+i) , char_table_get (T2, i));
    }
  return T;
}

char char_table_get (char_table T , int i)
{
  assert (i >= 0);
  assert (i < T->len);
  return T->data[i];
}

//////////////// char_table_2D f() ////////////////


char_table_2D char_table_2D_create(int len)
{
  return ext_char_table_2D_create(len, len);
}

char_table_2D ext_char_table_2D_create (int len, int alloc)
{
  assert ((len >= 0) && (alloc > 0) && (len <= alloc));
  {
    char_table_2D A = malloc (sizeof (struct _char_table_2D));
    A->len = len;
    A->alloc = alloc;
    A->data = malloc (sizeof (char_table) * alloc);
    {
      int i;
      for (i = 0; i < alloc; i++)
	{
	  A->data[i] = NULL;
	}
    }
    return A;
  }
}

char_table_2D empty_char_table_2D_create(int alloc)
{
  return ext_char_table_2D_create(0 , alloc);
}

void char_table_2D_destroy (char_table_2D T)
{
  free (T->data);
  free (T);
}

void char_table_2D_and_char_table_destroy (char_table_2D T)
{
  int i;
  for (i = 0; i < T->len; i++)
    {
      table_destroy (T->data[i]);
    }
  free (T->data);
  free (T);
}


char_table char_table_2D_get (char_table_2D T , int i)
{
  if (( i < 0 ) || (i >= T->len))
    {
      printf("char_table_2D_get : l'index %d est invalide.\n",i);
      printf("les valeurs valides sont entre 0 et %d.\n", T->len -1);
      return NULL;
    }
  return T->data[i];
}

void char_table_2D_set ( char_table_2D T, int i, char_table j)
{

  if (( i < 0 ) || (i >= T->len))
    {
      printf("char_table_2D_set : l'index %d est invalide.\n",i);
      printf("les valeurs valides sont entre 0 et %d.\n", T->len -1);
      return;
    }
  if (T->data[i] != NULL)
    {
      table_destroy ( T->data[i]);
    } 
  T->data[i] = j;
}

void ext_char_table_2D_set ( char_table_2D T, int i, char_table n)
{
  if (i >= T->alloc)
    char_table_2D_alloc_more (T,i *2);
  if (i >= T->len)
    T->len = i+1;
  char_table_2D_set(T, i, n);
}



int char_table_2D_length (char_table_2D T)
{
  return T->len;
}

void char_table_2D_add(char_table_2D T, char_table j)
{
  ext_char_table_2D_set(T, T->len , j);    
}

void char_table_2D_delete(char_table_2D T, int loc)/*modifie l'ordre du tableau*/
{
  int i;
  if ((loc < 0) || ( loc >= T->len))
    {
      printf ("char_table_2D_delete : index invalide %d.\n", loc);
      return;
    }
  table_destroy (T->data[loc]);

  for (i = loc + 1; i < T->len; i++)
    T->data[i - 1] = T->data[i];
  
  T->len--;
} 

 
void char_table_2D_alloc_more(char_table_2D T , int new_alloc)
{
  char_table * tmp = malloc (sizeof (char_table) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
      tmp[i] = T->data[i];
    }
  for( i =T->len; i < new_alloc; i++)
    {
      tmp[i] = NULL;
    }
  free (T->data);
  T->data = tmp;
  T->alloc = new_alloc;
}		    

intarray char_table_2D_to_intarray(char_table_2D T)
{
  int i;
  int alloc = T->len;
  if (T->len == 0)
    {
      alloc = 1;
    }
  intarray I = ext_intarray_create (0,alloc );
  for( i=0 ; i < T->len ; i++)
    {
      if(T->data[i] != NULL)
	intarray_add(I, char_table_to_int (T->data[i]));
    }
  return I;
}

/////////////// file f() ///////////////

