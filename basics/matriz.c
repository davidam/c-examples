/* Copyright (C) 2020  David Arroyo Menéndez
   Author: David Arroyo Menéndez <davidam@libresoft>
   Maintainer: David Arroyo Menéndez <davidam@libresoft>
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


/* Matriz bidimensional. */

#include <stdio.h>

void main() /* Rellenamos una matriz */
{
  int x,i,numeros[3][4];
  /* rellenamos la matriz */
  for (x=0;x<3;x++)
    for (i=0;i<4;i++)
      scanf("%d",&numeros[x][i]);
  /* visualizamos la matriz */
  puts("--------------------------------");

  for (x=0;x<3;x++) {
    for (i=0;i<4;i++) {
      printf("%d, ",numeros[x][i]);
    }
    printf("\n");
  }
}
