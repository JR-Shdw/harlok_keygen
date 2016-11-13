/* Harlock Security Keygen alpha 0.10 */



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "char_key_tools.h"

#define RC printf ("\n")

int main (int argc ,char  *argv[])
{
 int  n;
 int size, num;
 char_table key ,csize, cnumber;
 
char_table keymap= ASCII_key_set();
 
 int key_l = keymap->len;
 
 if( key_l == 0)
   {
      key = NULL;
      csize = NULL;
      cnumber = NULL;
      table_destroy(keymap);
      return EXIT_SUCCESS;
   }
 
 fprintf(stdout,"enter the size : ");
 csize = get_secure_input();
 
 fprintf(stdout,"enter the number : ");
 cnumber = get_secure_input();
 RC;
 
 size = char_table_to_int (csize);
 num = char_table_to_int (cnumber);


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
