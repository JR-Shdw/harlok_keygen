/*.h = header */
/* < repertoire biblio standard > */
/* " repertoire perso " */
/* int argc taille de la chaine de commande du main 
   char * argv[] chaine enregistrer par le main pour entrer des lignes de commandes */

#define RC printf ("\n")

typedef struct _intarray intarray;

struct _intarray
{
  int* data;
  int len;
};




extern void intarray_debug (intarray T);
extern intarray intarray_create (int len);
extern void intarray_destroy (intarray T);
extern int intarray_get (intarray T , int i);
/* int a = T.data[i] */
/* int a = intarray_get (T, i); */
extern void intarray_set (intarray T , int i , int n);
/* T.data(i) = n; */
/* intarray_set (T, i, n); */
extern int intarray_length (intarray T);
/* int a = T.len; */
/* int a = intarray_length (T); */
extern int intarray_get_min (intarray T);
extern intarray intarray_concat (intarray T1, intarray T2);
extern void int_swap (int *m, int *n);
extern int intarray_seek_min_index (intarray T ,int start);
extern void intarray_sort1 (intarray T);/* tri par selection du minimum)*/
extern int string_to_int(char * ch);
/* exercices */
extern int  intarray_sum (intarray T);
extern float intarray_average (intarray T);
extern float intarray_median (intarray T);
extern int intarray_get_max (intarray T);
extern intarray intarray_clone (intarray T);

extern void intarray_arg(int a, char* c[]); 
