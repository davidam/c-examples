#include <stdio.h>
//predeclarate

typedef struct 
{                                                               
      int value;             // will store information
      int *next;             // the reference to the next node
} pair;           

void first (pair list) {
  printf("%d\n", list.value);
}

/* int last (pair list) { */
/*   if (list.next ==  NULL) { */
/*     return list.value; */
/*   } else { */
/*     last(*list.next); */
/*   } */
/* } */


void cons (int elem, pair list) {
  pair x;
  x.value = elem;
  x.next = &list.value;
}

// TODO: Implementar rest
void print_list (pair list) {
  printf("(%d ", list.value);
  list.value = *list.next;
  printf("%d", list.value);
  if (list.next == NULL) {
    list.value = *list.next;
    printf("%d", list.value);
    list.value = *list.next;
    printf("%d", list.value);
  }
  printf(")\n", list.value);
}


int main () {
  pair x;
  x.value = 5;
  pair y;
  y.value = 9;
  //first(x);
  x.next = &y.value;
  y.next = NULL;
  //  printf("%d\n", *x.next);
  print_list(x);
  first(x);
  //  last(x);
}
