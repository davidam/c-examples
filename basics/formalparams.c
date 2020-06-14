/* Copyright (C) 2020  David Arroyo Menéndez
   Author: David Arroyo Menéndez <davidam@gnu.org>
   Maintainer: David Arroyo Menéndez <davidam@gnu.org>
   This file is software with freedom of class; you can
   redistribute it and/or modify it  only for the working
   class under the terms of the Working Class License
   published by David Arroyo Menéndez.
   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   Working Class License for more details.
   You should have received a copy of the Working Class License along
   with c-examples; see the file COPYING. If not, see
   <https://github.com/davidam/workingclasslicense>.
*/


#include <stdio.h>
 
/* global variable declaration */
int a = 20;

/* function to add two integers */
int sum(int a, int b) {

   printf("value of a in sum() = %d\n",  a);
   printf("value of b in sum() = %d\n",  b);

   return a + b;
}


int main () {

  /* local variable declaration in main function */
  int a = 10;
  int b = 20;
  int c = 0;

  printf ("value of a in main() = %d\n",  a);
  c = sum(a, b);
  printf ("value of c in main() = %d\n",  c);

  return 0;
}

