#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"



void intarray_debug (intarray T)
{
  int i;
  for(i=0 ; i<T.len; i++)
    {
      printf (" %d ", T.data[i]);
    }
  RC;
}

intarray intarray_create (int len)
{
  intarray A;
  A.len = len;
  A.data = malloc (sizeof (int) * len);
  return A;
}

/* intarray T = intarray_create (1000); */
/* intarray_set (T , x , y); */

void intarray_destroy (intarray T)
{
  free (T.data);
}

int intarray_get (intarray T , int i)
{
  assert (i >= 0);
  assert (i < T.len);
  return T.data[i];
 }

void intarray_set ( intarray T, int i, int n)
{
  assert (i >=0 );
  assert (i < T.len);
  T.data[i] = n;
}

int intarray_length (intarray T)
{
  return T.len;
}

int intarray_get_min(intarray T)
{
  int n;
  int m;
  m = intarray_get (T,0);
  
  for(n = 1; n < intarray_length (T) ; n++)
      {
	int T_i = intarray_get (T , n);
	if (T_i<m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

intarray intarray_concat(intarray T1, intarray T2)
{
  intarray T = intarray_create (intarray_length (T1) + intarray_length (T2));
  int i,j;
  j = intarray_length(T1);
  for(i=0 ; i < intarray_length (T1); i++)
    {
      /*EXPL: T.data[i] = T1.data[i]; */
      /*EXPL: T.data[i] = intarray_get (T1 ;i);*/
      intarray_set (T, i, intarray_get (T1 ,i));
    }
  for(i=0; i < intarray_length (T2); i++)
    {
      intarray_set (T , (j+i) , intarray_get (T2, i));
    }
  return T;
}

void int_swap (int *m, int *n)
{
  int tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}


int intarray_seek_min_index (intarray T ,int start)
{
  int i, m , index_min;
  m = T.data[start];
  index_min = start;
    
  for (i = start +1 ; i < intarray_length (T) ; i++)
      {
	if  (T.data[i] <  m)
	  {
	  m = T.data[i];
	  index_min = i;
	  }
      }
  return index_min;
}
void intarray_sort1 (intarray T)/* tri par selection du minimum)*/
{
  int i;
  for(i = 0 ; i < intarray_length( T ) ; i++)
    {
      int_swap (T.data + i, T.data + intarray_seek_min_index(T , i));
    intarray_debug(T);
    }
}
/*
void intarray_sort2 (intarray T)
{
int i, index_min;
for (i = 0; i <= intarray_length(T) - 2; i++)
{
index_min = intarray_seek_min_index (T , i);
int_swap (T.data + i , T.data + index_min);
}
}
*/
int string_to_int(char * ch)/*ne traite que les positifs*/
{
  int r = 0;
  int i;
  for(i=0; ch[i] != 0 ;i++)
    {
      assert ((ch[i] >= '0') && (ch[i] <= '9'));
      r *=10;
      r += (((int) ch[i] - 48));
    }
  return r;
}


int  intarray_sum (intarray T)/* somme de tt les entiers*/
{
  int i;
  int sum = 0;
  for (i = 0; i < T.len ; i++)
    {
      sum += intarray_get(T, i);
    }
  return sum;
}



float intarray_average (intarray T)/* renvoi la moyenne*/
{
 
  float s = intarray_sum(T);
  return (s /T.len);
}


float intarray_median (intarray T)/* renvoi la mediane du tableau */ 
{
  intarray T2 = intarray_clone (T);
  intarray_sort1(T2);
  float med;
  if(T.len % 2 == 1)
    {
  int j = T.len / 2;
  med =intarray_get(T , j);
    }
  else
    {
      int i = T2.data[(T2,(T.len - 1) / 2)];
      int n = T2.data[(T2,(T.len + 1) / 2)];
      med = ((i + n) / 2.0);
    }
  intarray_destroy(T2);
  return med;
}

int intarray_get_max (intarray T)/* cherche le chiffre le plus grand*/
{
  int n;
  int m;
  m = intarray_get (T,0);
  
  for(n = 1; n < intarray_length (T) ; n++)
      {
	int T_i = intarray_get (T , n);
	if (T_i > m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}


intarray intarray_clone (intarray T)
{
  intarray U = intarray_create (T.len);
  int i;
  for (i = 0 ; i < T.len ; i++)
    {
      U.data[i] = T.data[i];
    }
  return U;
}


void intarray_arg(int a, char* c[]) 
{
  if(  a >= 2 )
  {
  int taille = a - 1;
  intarray T = intarray_create (taille);
  int i;
  for (i = 0 ; i < taille ; i++)
    {
      T.data[i] = string_to_int ( c[i + 1] );
    }
  {
    int mn = intarray_get_min (T);
    int mx = intarray_get_max (T);
    float ave = intarray_average (T);
    float med = intarray_median (T);
    printf("vous avez entre %d nombre(s).\n", taille);
    printf("Le plus petit est %d , le plus grand est %d.\n", mn , mx);
    printf("L'etendue est de %d\n" , mx - mn);
    printf("La moyenne arithmetique s'eleve a %f.\n",ave);
    printf("La mediane est egale a %f.\n",med);
    printf("Vous avez entre les valeurs suivantes :\n");
    intarray_debug (T); RC;
    printf("Soit , par ordre croissant :\n");
    intarray_sort1 (T);
  }
  intarray_destroy(T);
 }
 }
