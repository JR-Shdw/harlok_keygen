/* Harlock Security Keygen alpha 0.10 - CLI version */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "char_key_tools.h"
#include "intarray.h"

#define RC printf ("\n")

int main (int argc, char *argv[])
{
  int n;
  int size, num;
  char_table key;

  /* construire la table ASCII */
  char_table_2D ASCII = TYPABLE_ASCII_table();

  /* parser les flags (-a, -n, -s) */
  char_table flags = cli_get_flags(argv, argc);

  /* parser les arguments entiers (size, number) */
  char_table_2D int_args = cli_get_int(argv, argc);
  intarray I = char_table_2D_to_intarray(int_args);

  /* verifier et borner les arguments */
  intarray_cli_args_check(I);

  /* I[0] = number, I[1] = size (conforme a intarray_cli_args_check) */
  size = intarray_get(I, 1);
  num = intarray_get(I, 0);

  /* selectionner le charset selon les flags */
  char_table keymap = ASCII_key_set_cli(flags, ASCII);
  int key_l = keymap->len;

  if (key_l == 0)
    {
      /* FIX: cleanup correct */
      intarray_destroy(I);
      char_table_2D_and_char_table_destroy(int_args);
      table_destroy(flags);
      char_table_2D_and_char_table_destroy(ASCII);
      return EXIT_SUCCESS;
    }

  key = key_table_create(size, size);

  /* srand plus necessaire: random_value utilise /dev/urandom */
  for (n = 0; n < num; n++)
    {
      key_gen(key, keymap, size, key_l);
      print_key(key, size);
      fprintf(stdout, "\n");
    }
  RC;

  table_destroy(key);
  intarray_destroy(I);
  char_table_2D_and_char_table_destroy(int_args);
  table_destroy(flags);
  /* keymap est un element de ASCII, pas un malloc separe */
  char_table_2D_and_char_table_destroy(ASCII);

  return EXIT_SUCCESS;
}
