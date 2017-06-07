#include <stdio.h>

int main();
void get_values (int *, int *);

int main()
{
  int num1, num2;
  get_values (&num1, &num2);
  printf ("num1 = %d and num2 = %d\n\n", num1, num2);
  return 0;
}


void get_values (int *num_ptr1, int *num_ptr2)
{
  *num_ptr1 = 10;
  *num_ptr2 = 20;
}
