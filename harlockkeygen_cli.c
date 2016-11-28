/* Harlock Security Keygen alpha 0.10 */



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "char_key_tools.h"
#include "intarray.h"

#define RC printf ("\n")

int main (int argc ,char  *argv[])
{
 int  n;
 int size, num;
 char_table key ,csize, cnumber;
 
char_table keymap= ASCII_key_set_cli( argv[1]);
 intarray I = args_to_intarray_2(2 ,3, argv);
   if (I[0] < 1) 
     {
       I[0] = 8;
       frpintf(stderr,"unvalid size set to 8");
     }
 if (I[1] < 1 )
   I[1] = 1;

 int key_l = keymap->len;
 
 if( key_l == 0)
   {
      key = NULL;
      csize = NULL;
      cnumber = NULL;
      table_destroy(keymap);
      return EXIT_SUCCESS;
   }
 
 
 csize = I[0];
 
 
 cnumber = I[1];
 RC;
 
 //size = char_table_to_int (csize);
 //num = char_table_to_int (cnumber);


 key = key_table_create(size,size);


 srand ( time(NULL) );
 for(n=0;n<num;n++)
 {
   key_gen( key ,keymap ,size,  key_l);
   print_key( key, size);
   fprintf(stdout,"\n");
  }
RC;
 table_destroy(key);
 table_destroy(keymap);
 table_destroy(csize);
 table_destroy(cnumber);

  return EXIT_SUCCESS;
}
