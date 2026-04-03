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

 /* FIX: ASCII_key_set prend la table ASCII en parametre */
 char_table_2D ASCII = TYPABLE_ASCII_table();
 char_table keymap = ASCII_key_set(ASCII);
 
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


 /* srand plus necessaire: random_value utilise /dev/urandom */
 for(n=0;n<num;n++)
 {
   key_gen( key ,keymap ,size,  key_l);
   print_key( key, size);
   fprintf(stdout,"\n");
  }
RC;
 table_destroy(key);
 /* keymap est un element de ASCII, pas un malloc separe */
 char_table_2D_and_char_table_destroy(ASCII);
 table_destroy(csize);
 table_destroy(cnumber);

  return EXIT_SUCCESS;
}
