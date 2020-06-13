#include <stdio.h>

void main () {

  int var = 45;
  int *pVar;
  pVar = &var;
  printf("Dirección de var: %p \n", pVar);
  printf("Valor de var: %i \n", *pVar);
  //  getch();

}
