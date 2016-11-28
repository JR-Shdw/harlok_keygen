#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


#include "jstr.h"
#include "intarray.h"

typedef char chardata;
typedef char* regstr;




void jstr_alloc_more(jstr T , int new_alloc);


jstr arg_string_concat(int argc,char* argv[])
{
  jstr j = ext_jstr_create(argc , (argc*argc));
  int i,k = 0;
  char* copy;
  for (i = 1 ; i < argc ;i++)
    {
      copy = argv[i];
      printf("argv[%d] :  %s " ,i, copy);
      for (k= 0; k < strlen(copy);k++) 
      {
	jstr_add (j ,copy[k]);
      }
    }
      return j;
}




int jstr_equal_substr(jstr j1, int s1, int c1, jstr j2, int s2)
{
  
  
  int i;
  int l = (c1 - s1);
  int equal = 0;
  printf("c1:%d s1:%d s2:%d l:%d",c1, s1, s2, l);
  
  for (i = 0; i < l+1; i++)
    {
    
      if (j1->data[(s1)+i] == j2->data[(s2)+i])
	{
     	  equal++;
	}
    }
  
  if(equal == (l+1))
    {
      return 1;
    }
  else
    {
      return 0;
    }
 }


int jstr_equal(jstr j1, jstr j2)
{
  int i,lgth = j1->len;
  int equal = 0;
  
  if( j1->len == j2->len)
    {
      for (i = 0; i < lgth; i++)
	{
	
	  if (j1->data[i] == j2->data[i])
	    {
	      equal++;
	    }
	}
  
      if(equal == (lgth))
	{
      	  return 1;
	}
      else
	{
	  return 0;
	}
    }

  else
    return 0;
}


int jstr_compare(jstr J1, jstr J2)
{
  int min_len, i, c,equal;

  if (J1->len < J2->len)
    {
    min_len = J1->len;
    equal = 0;
    }
  
  else if (J1->len > J2->len)
	   {
	   min_len = J2->len;
	   equal = 0;
	   }
  
  else if (J1->len == J2->len)
	   {
	   min_len = J1->len;
	   equal = 1;
	   }
  
  for (i = 0;  i < min_len; i++)
    {
      if( J1->data[i] < J2->data[i])
	{
	c = -1;
	return c;
	}
      else if( J1->data[i] > J2->data[i])
	{
	c = 1;
	return c;
	}
      else if(J1->data[i] == J2->data[i])
	c = 0;
    }

  if(c == 0 && equal == 0)
    {
      if(J1->len < J2->len)
	c = -1;
      if(J1->len > J2->len)
	c = 1;
    }
  else if(c == 0 && equal == 1)
	   c = 0;

  return c;
}


  
jstr regstr_to_jstr(char* S)
{
  jstr J = standard_empty_jstr_create();
  int i = 0;
  while(S[i] != 0)
    {
      jstr_add (J ,S[i]);
      i++;
    }
  return J;
}


char* jstr_to_regstr(jstr J)
{
  char* S = malloc (sizeof (chardata)* (J->len + 1));
  int i;
  for (i = 0; i < J->len; i++)
    {
      S[i] = J->data[i];
    }
  S[J->len] = (char) 0;
  return S;
}

intarray jstr_find_substr_indices(jstr sub, jstr j)
{
  int k,i = 0 ;
  int l = 0;
  intarray occ = ext_intarray_create(2 ,2);
  int equal = 0;
  while ( (i + sub->len) < j->len)
    {
      for(i = 0 ; i < ((j->len+1) - sub->len) ; i++)
	{
	  equal = 0;
	  for(k = 0 ; k < sub->len ; k++)
	    {
	      if(sub->data[k] == j->data[i+k])
		{
		  equal ++;
		  if(equal == sub->len)
		    {
		      ext_intarray_set(occ, l, i);
		      l++;
		    }
		}

	    }
	}
    }
  
  return occ;
}


intarray jstr_find_proper_substr_indices(jstr sub, jstr j)
{
  int k,i = 0 ;
  int l = 0;
  intarray occ = ext_intarray_create(2 ,2);
  int equal = 0;
  while ( (i + sub->len) < j->len)
    {
      for(i = 0 ; i < ((j->len+1) - sub->len) ; i++ )
	{
	  equal = 0;
	  for(k = 0 ; k < sub->len ; k++)
	    {
	      if(sub->data[k] == j->data[i+k])
		{
		  equal ++;
		  if(equal == sub->len)
		    {
		      ext_intarray_set(occ, l, i);
		      l++;
		      i += sub->len-1; 
		    }
		}

	    }
	}
    }
  
  return occ;
}

void jstr_print (jstr T)
{
  int i;
  for (i = 0; i< T->len; i++)
    {
      printf("%c", T->data[i]);
    }
  RC;
}
	   

void jstr_debug (jstr T)
{
  int i;
  printf("jstr, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      printf ("%c", T->data[i]);
    }
  RC;
}


jstr jstr_create(int len)
{
  return ext_jstr_create(len, len);
}

jstr ext_jstr_create (int len, int alloc)
{
  assert ((len >=0) && (alloc > 0) && (len <=alloc));
  {
  jstr A = malloc (sizeof (struct _jstr));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc (sizeof (chardata) * alloc);
  return A;
  }
}

jstr empty_jstr_create(int alloc)
{
  return ext_jstr_create(0 , alloc);
}
/* jstr T = jstr_create (1000); */
/* jstr_set (T , x , y); */

void jstr_alloc_more(jstr T , int new_alloc)
{
  char* tmp = malloc (sizeof (chardata) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
    tmp[i] = T->data[i];
    }		       
      free (T->data);
      T->data = tmp;
      T->alloc = new_alloc;
}		    

jstr standard_empty_jstr_create (void)
{
  return ext_jstr_create ( 0, JSTR_DEFAULT_ALLOC);
}

void jstr_destroy (jstr T)
{
  free (T->data);
  free (T);
}

chardata jstr_get (jstr T , int i)
{
  assert (i >= 0);
  assert (i < T->len);
  return T->data[i];
 }

void jstr_set ( jstr T, int i, chardata n)
{
  assert (i >=0 );
  assert (i < T->len);
  T->data[i] = n;
}

void ext_jstr_set ( jstr T, int i, chardata n)
{
  if (i >= T->alloc)
    jstr_alloc_more (T,i *2);
  if (i >=T->len)
    T->len = i+1;
  jstr_set(T, i, n);
}



int jstr_length (jstr T)
{
  return T->len;
}

void jstr_add(jstr T, chardata n)
{
  ext_jstr_set(T, T->len , n);    
}

void jstr_delete(jstr T, int loc)/*modifie l'ordre du tableau*/
{
  assert (T->len > 0);
  assert (loc < T->len);
  T->data[loc] = T->data[T->len-1];
  T->len--;
} 
 



chardata jstr_get_min(jstr T)
{
  int n;
  chardata m;
  m = jstr_get (T,0);
  
  for(n = 1; n < jstr_length (T) ; n++)
      {
	chardata T_i = jstr_get (T , n);
	if (T_i<m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

jstr jstr_concat(jstr T1, jstr T2)
{
  jstr T = jstr_create (jstr_length (T1) + jstr_length (T2));
  int i,j;
  j = jstr_length(T1);
  for(i=0 ; i < jstr_length (T1); i++)
    {
      /*EXPL: T->data[i] = T1->data[i]; */
      /*EXPL: T->data[i] = jstr_get (T1 ;i);*/
      jstr_set (T, i, jstr_get (T1 ,i));
    }
  for(i=0; i < jstr_length (T2); i++)
    {
      jstr_set (T , (j+i) , jstr_get (T2, i));
    }
  return T;
}


void D_jstr_concat(jstr T1 , jstr T2)
{
  chardata n;
  for (n = 0; n < jstr_length(T2); n++)
    jstr_add(T1 , jstr_get(T2 ,n));
		   
 }		 



int jstr_seek_min_index (jstr T ,int start)
{
  int i, index_min;
  chardata m = T->data[start];
  index_min = start;
    
  for (i = start +1 ; i < jstr_length (T) ; i++)
      {
	if  (T->data[i] <  m)
	  {
	  m = T->data[i];
	  index_min = i;
	  }
      }
  return index_min;
}

void jstr_sort1 (jstr T)/* tri par selection du minimum)*/
{
  int i;
  for(i = 0 ; i < jstr_length( T ) ; i++)
    {
      char_swap (T->data + i, T->data + jstr_seek_min_index(T , i));
    }
}
/*
void jstr_sort2 (jstr T)
{
int i, index_min;
for (i = 0; i <= jstr_length(T) - 2; i++)
{
index_min = jstr_seek_min_index (T , i);
int_swap (T->data + i , T->data + index_min);
}
}
*/


chardata  jstr_sum (jstr T)/* somme de tt les entiers*/
{
  int i;
  chardata sum = 0;
  for (i = 0; i < T->len ; i++)
    {
      sum += jstr_get(T, i);
    }
  return sum;
}



float jstr_average (jstr T)/* renvoi la moyenne*/
{
 
  float s = jstr_sum(T);
  return (s /T->len);
}


float jstr_median (jstr T)/* renvoi la mediane du tableau */ 
{
  jstr T2 = jstr_clone (T);
  jstr_sort1(T2);
  float med;
  if(T->len % 2 == 1)
    {
  int j = T->len / 2;
  med =jstr_get(T , j);
    }
  else
    {
      int i = T2->data[(T2,(T->len - 1) / 2)];
      int n = T2->data[(T2,(T->len + 1) / 2)];
      med = ((i + n) / 2.0);
    }
  jstr_destroy(T2);
  return med;
}

chardata jstr_get_max (jstr T)/* cherche le chiffre le plus grand*/
{
  int n;
  chardata m = jstr_get (T,0);
  
  for(n = 1; n < jstr_length (T) ; n++)
      {
	chardata T_i = jstr_get (T , n);
	if (T_i > m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

int jstr_num_occur(jstr T, chardata n)
{
  int i;
  int o ;
  for(i=0 ; i<T->len ; i++)
    {
      if(T->data[i]==n)
	{
	  o += 1;
	}
    }  
    
  return o;
 }

jstr jstr_clone (jstr T)
{
  jstr U = jstr_create (T->len);
  int i;
  for (i = 0 ; i < T->len ; i++)
    {
      U->data[i] = T->data[i];
    }
  return U;
}



 
 
 int recherche_lettre(jstr T, chardata n)
{
  int i;
  for(i=0;i<T->len;i++)
    {
      if(T->data[i]=n)
	{
	  printf("je retourne 1");
	  return 1;
	    }
    }
  return 0;
}

/*int string_to_int(char * ch) ne traite que les positifs
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
}*/

 
 void char_swap (char *m, char *n)
{
  char tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

int jstr_equal_substr_jol (jstr J1 , int S1 , int E1, jstr J2, int S2)
{
  assert ((S1 >= 0) && (S1 <= E1) && (E1 < J1->len));
  assert((S2 >= 0) && (S2 < J2->len));
  int len = E1 - S1 +1;
  if ( S2 + len > J2->len)
    return 0;
  {
  int i;
  for(i = S1; i < len -1 ; i++)
    {
      if (J1->data[S1 + i] != J2->data[S2 + i])
	return 0;
    }
  return 1;

  }
}


int jstr_equal_jol (jstr j1, jstr j2)
{
  return (j1->len == j2->len) && jstr_equal_substr_jol (j1, 0 , j1->len -1, j2, 0);
}


intarray jstr_find_substr_indices_jol (jstr sub, jstr j)
{
  intarray I = standard_empty_intarray_create();
  int i;
  for (i = 0 ; i < j->len; i++)
    {
      if (  jstr_equal_substr_jol ( sub, 0 , sub->len -1, j , i) == 1)
	{
	  intarray_add (I,i);
	}
    }
  return I;
}

intarray jstr_find_proper_substr_indices_jol(jstr sub, jstr j )
{
 intarray I = standard_empty_intarray_create();
  int i;
  for (i = 0 ; i < j->len; i++)
    {
      if (  jstr_equal_substr_jol ( sub, 0 , sub->len -1, j , i) == 1)
	{
	  intarray_add (I,i);
	  i += (sub->len - 1);
	}
    }
  return I;
}
