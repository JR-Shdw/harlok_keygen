/*.h = header */
/* < repertoire biblio standard > */
/* " repertoire perso " */
/* int argc taille de la chaine de commande du main 
   char * argv[] chaine enregistrer par le main pour entrer des lignes de commandes */
//jol algorithme facon Jacque Olivier Lapeyre
#ifndef __JSTR_H__
#define __JSTR_H__


#define RC printf ("\n")
#define JSTR_DEFAULT_ALLOC 10

#include "intarray.h"

typedef struct _jstr *jstr;
typedef char* regstr;
typedef char chardata;




struct _jstr
{
  char* data;
  int len;
  int alloc;
};




extern jstr arg_string_concat(int argc, char* argv[]);
extern int jstr_equal_substr(jstr j1, int s1, int c1, jstr j2, int s2);
extern int jstr_equal(jstr j1, jstr j2);
extern int jstr_compare(jstr j1, jstr j2);
extern intarray jstr_find_substr_indices(jstr sub, jstr j);
extern intarray jstr_find_proper_substr_indices(jstr sub, jstr j);


extern int jstr_equal_substr_jol(jstr j1, int s1, int c1, jstr j2, int s2);
extern int jstr_equal_jol(jstr j1, jstr j2);
extern int jstr_compare_jol(jstr j1, jstr j2);
extern intarray jstr_find_substr_indices_jol(jstr sub, jstr j);
extern intarray jstr_find_proper_substr_indices_jol(jstr sub, jstr j);


extern jstr regstr_to_jstr(char* S);
extern char* jstr_to_regstr(jstr J);

extern void jstr_debug (jstr T);
extern void jstr_print (jstr T);
extern jstr jstr_create (int len);
extern jstr ext_jstr_create (int len, int alloc);
extern jstr empty_jstr_create(int alloc);
extern jstr standard_empty_jstr_create (void);
extern void jstr_destroy (jstr T);
extern chardata jstr_get (jstr T , int i);
/* int a = T.data[i] */
/* int a = jstr_get (T, i); */
extern void jstr_set (jstr T , int i , chardata n);
extern void ext_jstr_set ( jstr T, int i, chardata n);
/* T.data(i) = n; */
/* jstr_set (T, i, n); */
extern int jstr_length (jstr T);
/* int a = T.len; */
/* int a = jstr_length (T); */
extern void jstr_add(jstr T, chardata n);
extern void jstr_delete(jstr T, int loc);

extern chardata jstr_get_min (jstr T);
extern jstr jstr_concat (jstr T1, jstr T2);
extern void D_jstr_concat(jstr T1, jstr T2);
extern int jstr_seek_min_index (jstr T ,int start);
extern void jstr_sort1 (jstr T);/* tri par selection du minimum)*/
extern int jstr_num_occur(jstr T, chardata n);
extern int jstr_recherche(jstr T, chardata n);
extern chardata jstr_sum (jstr T);
extern float jstr_average (jstr T);
extern float jstr_median (jstr T);
extern chardata jstr_get_max (jstr T);
extern jstr jstr_clone (jstr T);
extern void jstr_arg(int a, char* c[]); 
//extern int string_to_int(char * ch);
extern void char_swap (char *m, char *n);


#endif
