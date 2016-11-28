#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "intarray.h"


typedef intarray heap;


void intarray_print (intarray T)
{
  int i;
  for (i= 0; i< T->len; i++)
    {
      printf(" %d ", T->data[i]);
    }
	RC;
}

void intarray_debug (intarray T)
{
  int i;
  printf("intarray, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      printf (" %d ", T->data[i]);
    }
  RC;
}

/*intarray intarray_create (int len)
{
  intarray A = malloc (sizeof (struct _intarray));
  A->len = len;
  A->alloc = len;
  A->data = malloc (sizeof (int) * len);
  return A;
  }*/

intarray intarray_create(int len)
{
  /* intarray T = ext_intarray_create(len, len);
  return T;*/
  return ext_intarray_create(len, len);
}

intarray ext_intarray_create (int len, int alloc)
{
  assert ((len >=0) && (alloc > 0) && (len <=alloc));
  {
  intarray A = malloc (sizeof (struct _intarray));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc (sizeof (intdata) * alloc);
  return A;
  }
}

intarray empty_intarray_create(int alloc)
{
  return ext_intarray_create(0 , alloc);
}
/* intarray T = intarray_create (1000); */
/* intarray_set (T , x , y); */

void intarray_alloc_more(intarray T , int new_alloc)
{
  int * tmp = malloc (sizeof (intdata) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
    tmp[i] = T->data[i];
    }		       
      free (T->data);
      T->data = tmp;
      T->alloc = new_alloc;
}		    

intarray standard_empty_intarray_create (void)
{
  return ext_intarray_create ( 0, INTARRAY_DEFAULT_ALLOC);
}

void intarray_destroy (intarray T)
{
  free (T->data);
  free (T);
}

intdata intarray_get (intarray T , int i)
{
  assert (i >= 0);
  assert (i < T->len);
  return T->data[i];
 }

void intarray_set ( intarray T, int i, intdata n)
{
  assert (i >=0 );
  assert (i < T->len);
  T->data[i] = n;
}

void ext_intarray_set ( intarray T, int i, intdata n)
{
  if (i >= T->alloc)
    intarray_alloc_more (T,i *2);
  if (i >=T->len)
    T->len = i+1;
  intarray_set(T, i, n);
}



int intarray_length (intarray T)
{
  return T->len;
}

void intarray_add(intarray T, intdata n)
{
  ext_intarray_set(T, T->len , n);    
}

void intarray_delete(intarray T, int loc)/*modifie l'ordre du tableau*/
{
  assert (T->len > 0);
  assert (loc < T->len);
  T->data[loc] = T->data[T->len-1];
  T->len--;
} 
 



intdata intarray_get_min(intarray T)
{
  int n;
  intdata m;
  m = intarray_get (T,0);
  
  for(n = 1; n < intarray_length (T) ; n++)
      {
	intdata T_i = intarray_get (T , n);
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
      /*EXPL: T->data[i] = T1->data[i]; */
      /*EXPL: T->data[i] = intarray_get (T1 ;i);*/
      intarray_set (T, i, intarray_get (T1 ,i));
    }
  for(i=0; i < intarray_length (T2); i++)
    {
      intarray_set (T , (j+i) , intarray_get (T2, i));
    }
  return T;
}


void D_intarray_concat(intarray T1 , intarray T2)
{
  intdata n;
  for (n = 0; n < intarray_length(T2); n++)
    intarray_add(T1 , intarray_get(T2 ,n));
		   
 }		 



int intarray_seek_min_index (intarray T ,int start)
{
  int i, index_min;
  intdata m = T->data[start];
  index_min = start;
    
  for (i = start +1 ; i < intarray_length (T) ; i++)
      {
	if  (T->data[i] <  m)
	  {
	  m = T->data[i];
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
      int_swaph (T->data + i, T->data + intarray_seek_min_index(T , i));
    }
}
/*
void intarray_sort2 (intarray T)
{
int i, index_min;
for (i = 0; i <= intarray_length(T) - 2; i++)
{
index_min = intarray_seek_min_index (T , i);
int_swap (T->data + i , T->data + index_min);
}
}
*/


intdata  intarray_sum (intarray T)/* somme de tt les entiers*/
{
  int i;
  intdata sum = 0;
  for (i = 0; i < T->len ; i++)
    {
      sum += intarray_get(T, i);
    }
  return sum;
}



float intarray_average (intarray T)/* renvoi la moyenne*/
{
 
  float s = intarray_sum(T);
  return (s /T->len);
}


float intarray_median (intarray T)/* renvoi la mediane du tableau */ 
{
  intarray T2 = intarray_clone (T);
  intarray_sort1(T2);
  float med;
  if(T->len % 2 == 1)
    {
  int j = T->len / 2;
  med =intarray_get(T , j);
    }
  else
    {
      int i = T2->data[(T2,(T->len - 1) / 2)];
      int n = T2->data[(T2,(T->len + 1) / 2)];
      med = ((i + n) / 2.0);
    }
  intarray_destroy(T2);
  return med;
}

intdata intarray_get_max (intarray T)/* cherche le chiffre le plus grand*/
{
  int n;
  intdata m = intarray_get (T,0);
  
  for(n = 1; n < intarray_length (T) ; n++)
      {
	intdata T_i = intarray_get (T , n);
	if (T_i > m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

int intarray_num_occur(intarray T, intdata n)
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

intarray intarray_clone (intarray T)
{
  intarray U = intarray_create (T->len);
  int i;
  for (i = 0 ; i < T->len ; i++)
    {
      U->data[i] = T->data[i];
    }
  return U;
}


void intarray_arg(int a, char* c[]) 
{
  if(  a >= 2 )
    {
      int taille = a - 1;
      intarray T = empty_intarray_create(2);
      int i;
      for (i = 0 ; i < taille ; i++)
	{
	  intarray_add(T, string_to_inth ( c[i + 1]));
	}
      {
	int mn = intarray_get_min (T);
	int mx = intarray_get_max (T);
	float ave = intarray_average (T);
	float med = intarray_median (T);
	printf("vous avez entre %d nombre(s).\n", taille);
	printf("Le plus petit est %d , le plus grand est %d .\n", mn , mx);
	printf("L'etendue est de %d\n" , mx - mn);
	printf("La moyenne arithmetique s'eleve a %f .\n",ave);
	printf("La mediane est egale a %f .\n",med);
	printf("Vous avez entre les valeurs suivantes :\n");
	intarray_debug (T); RC;
	printf("Soit , par ordre croissant :\n");
	intarray_sort1 (T);
	intarray_debug(T);
      }
      intarray_destroy(T);
    }
 }
 
 void scanf_pos_floath (float *n)
{
	scanf("%f", n);
	while ((*n) <= 0.0)
	{
		printf("Entrez un nombre strictement positif->\n");
		scanf("%f",n);
	}
}

 void scanf_pos_inth (int *n)
{
  scanf("%d", n);
while ((*n) <= 0)
	{
		printf("Entrez un nombre strictement positif.\n");
		scanf("%d",n);
	}
  }

 int factorielle (int n)
{
  int a =1 ,i;
  assert ( (n >= 0)&&(n <= 13) );
  for(i= 1; i <= n; i++)
    {
      a *= i;
    }
  return a;
}
 
 
 int recherche_nombre(intarray T, intdata n)
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

int string_to_inth(char * ch)/*ne traite que les positifs*/
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

 
 void int_swaph (int *m, int *n)
{
  int tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

intarray intarray_index_sorted (intarray T)
{
  int min, index_min = T->len, i , n;
  intarray sorted_index = intarray_create(T->len); 

  for (i = 0; i < T->len; i++)

    {
      min = (T->len+1);

	for(n = 0; n < T->len; n++)
      {
      if (T->data[n] < min)
	{
	index_min = n;
	min = T->data[index_min];
	}
      
      }
    sorted_index->data[i] = index_min;
    T->data[index_min] = T->len+1;
    }

  return sorted_index;
}


intarray diviseur(int n)
{
  
int i;
intarray T = standard_empty_intarray_create();
i = 1;
while (i <= n)
{
	if( n%i == 0)
	{
	  intarray_add(T,i);

	}
i++;
}
 return T;
 
}


void print_premier(intarray I,int n)
{
  if (I->len == 2)
    printf("%i\n", n);
}


int premier_1(int m)
{
  intarray T = diviseur(m);
  int len = intarray_length(T);
  intarray_destroy(T);
  if ( len == 2)
    return 1;
  else
    return 0;
}

int premier_2(int m)
{
  if (m == 1)
    return 0;
  else
    {
      int i;
      for (i = 2 ; i < m ; i++)
	{
	  if (m % i == 0)
	    return 0;
	}
      return 1;
    }
}

int square(int n)
{
  return n*n;
}

int premier_3(int m)
{
  if (m == 1)
    return 0;
  else if( m ==2 )
    return 1;
  else
    {
      int i;
      for (i = 2 ; i < square (m) + 1 ; i++)
	{
	  if (m % i == 0)
	    return 0;
	}
      return 1;
    }
}


intarray random_intarray(int len)
{
  intarray I = intarray_create(len);
  int i;
  for (i = 0; i < len; i++)
    {
      intarray_set(I, i, rand() % 10000);
    }
  return I;
}

intarray args_to_intarray_2(int from,int to , char **args)
{
  intarray I = empty_intarray_create(to -1);
  int i;
  for (i = from; i < to ; i++)
    {
      intarray_add(I, atoi(args[i]));
    }
  return I;
}

intarray args_to_intarray(int nb , char **args)
{
  intarray I = empty_intarray_create(nb -1);
  int i;
  for (i = 1; i < nb ; i++)
    {
      intarray_add(I, atoi(args[i]));
    }
  return I;
}

intarray intarray_clone_heap_sort_by_min(intarray I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error intarray_clone_heap_sort_by_min intarray is empty");
      return NULL;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  
  heap_sort_by_min(heap_sort, I);
  
  
  intarray J = empty_intarray_create(I->len);
  for(i = 0; i < I->len; i++)
    {
      intarray_add(J, heap_get_head_value(heap_sort));
      heap_del_head_val_by_min(heap_sort);
    }
  
  heap_destroy(&heap_sort);
  return J;
}

void intarray_D_heap_sort_by_min(intarray I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error intarray_D_heap_sort_by_min intarray is empty");
      return;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  heap_sort_by_min(heap_sort, I);
  
  for(i = 0; i < I->len; i++)
    {
      I->data[i] = heap_get_head_value(heap_sort);
      heap_del_head_val_by_min(heap_sort);
    }
  heap_destroy(&heap_sort);
}


intarray intarray_clone_heap_sort_by_max(intarray I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error intarray_clone_heap_sort_by_max intarray is empty");
      return NULL;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  
  heap_sort_by_max(heap_sort, I);
  
 
  intarray J = empty_intarray_create(I->len);
  for(i = 0; i < I->len; i++)
    {
      intarray_add(J, heap_get_head_value(heap_sort));
      heap_del_head_val_by_max(heap_sort);
      
    }
  heap_destroy(&heap_sort);
  return J;
}

void intarray_D_heap_sort_by_max(intarray I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error intarray_D_heap_sort_by_max intarray is empty");
      return;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  heap_sort_by_max(heap_sort, I);
  
  for(i = 0; i < I->len; i++)
    {
      I->data[i] = heap_get_head_value(heap_sort);
      
      heap_del_head_val_by_max(heap_sort);
      
    }
  heap_destroy(&heap_sort);
}

heap heap_create_empty(int alloc)
{
  intarray I = empty_intarray_create(alloc);
  return I;
}
 
heap heap_ext_create(int len)
{
  intarray j = ext_intarray_create(len, len);
  return j;
}

heap heap_destroy(heap* H)
{
  intarray_destroy(*H);
  (*H) = NULL;
}

bool heap_is_empty( heap H)
{
  return (H->len == 0);
}

int heap_count_children(heap H, int i)
{
  int lc = (i*2)+1;
  if (lc >= H->len)
    return 0;
  else if( (lc + 1) >= H->len)
    return 1;
  else
    return 2;
}
 
void heap_sort_by_min(heap H, intarray I)
{
  int i;
  for (i = 0; i < I->len; i++)
    {
      intarray_add(H, I->data[i]);
      int index = H->len -1;
      
      while(heap_has_parent(H, index))
	{
	  int parent_index = heap_parent_index(index);
	  if (H->data[index] < H->data[heap_parent_index(index)])
	    {
	      int_swaph(H->data + index, H->data + heap_parent_index(index));
	      index = parent_index;
	     }
	  else
	    break;
	}	
    }
}

void heap_sort_by_max(heap H, intarray I)
{
  int i;
  
  for (i = 0; i < I->len; i++)
    {
      
      
      intarray_add(H, I->data[i]);
      int index = H->len - 1;
      while(heap_has_parent(H, index))
	{
	  int parent_index = heap_parent_index(index);
	  if (H->data[index] > H->data[parent_index])
	    {
	      int_swaph(H->data + index, H->data + parent_index);
	      index = parent_index;
	    }
	  else
	    break;
	}	
    }
}

int heap_parent_index(int x)
{
// impair (n-1)/2 pair (n/2)-1
  return (x -1)/2;
}

int heap_left_child_index(int x)
{
// (nx2)+1 impair
  
  return (2  * x + 1);
}
int heap_right_child_index(int x)
{
// (n+1)x2 pair
  return (2 * x + 2) ;
}
intdata heap_get_parent(heap H, int x)
{
  return intarray_get(H, heap_parent_index(x));
}

intdata heap_get_head_value(heap H)
{
      return intarray_get(H, 0);
}

void heap_del_head_val_by_min(heap H)
{
if (H->len ==  1)
    {
      H->len = 0;
    }
 else
   {
     int last = H->len -1;
     int index;
     H->data[0] = H->data[last];
     index = 0;
     H->len--;
     while(heap_count_children( H, index) > 0)
       {
	 int smallest_child_index = heap_get_small_child_index(H, index);
	 if (H->data[index] > H->data[heap_get_small_child_index(H,index)])
	   {
	     int_swaph(H->data + index, H->data + smallest_child_index);
	     index = smallest_child_index;
	   }
	 else
	   break;
       }

    }
 
}

void heap_del_head_val_by_max(heap H)
{

 if (H->len ==  1)
    {
      H->len = 0;
    }
 else
   {
     int last = H->len -1;
     int index;
     H->data[0] = H->data[last];
     index = 0;
     H->len--;
     while(heap_count_children( H, index) > 0)
       {
	 int biggest_child_index = heap_get_big_child_index(H, index);
	 if (H->data[index] < H->data[biggest_child_index])
	   {
	     int_swaph(H->data + index, H->data + biggest_child_index);
	     index = biggest_child_index;
	   }
	 else
	   break;
       }

    }
 
}

int heap_get_small_child_index(heap H,int x)
{
  if (heap_count_children(H, x) == 1)
    return heap_left_child_index(x);
  else
    {
      if (intarray_get(H,heap_left_child_index(x)) > (intarray_get(H,heap_right_child_index(x))))
	return heap_right_child_index(x);
  
      if (intarray_get(H,heap_left_child_index(x)) <= (intarray_get(H,heap_right_child_index(x))))
	{
	  return heap_left_child_index(x);
	}
    }
 }

int heap_get_big_child_index(heap H,int x)
{
  if (heap_count_children(H, x) == 1)
    return heap_left_child_index(x);
  else
    {
      if (intarray_get(H,heap_left_child_index(x)) < (intarray_get(H,heap_right_child_index(x))))
	return heap_right_child_index(x);
  
      if (intarray_get(H,heap_left_child_index(x)) >= (intarray_get(H,heap_right_child_index(x))))
	{
	  return heap_left_child_index(x);
	}
    }
 }

bool heap_is_parent_smaller(heap H, int x)
{
  return ( intarray_get(H, x) > intarray_get(H , heap_parent_index( x)));
}
 
bool heap_is_parent_bigger(heap H, int x)
{
  return ( intarray_get(H, x) < intarray_get(H , heap_parent_index( x)));   
}

bool heap_has_parent(heap H, int x)
{
  return (x > 0);
} 
