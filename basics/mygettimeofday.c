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

#include <sys/time.h>
#include <stdio.h>
 
int main() {
 
  struct timeval start, end;
  gettimeofday(&start, NULL);
 
  for (int i = 0; i <1e5 ; i++) {
  }
 
  gettimeofday(&end, NULL);
  printf("Time taken to count to 10^5 is : %ld micro seconds\n", 
    ((end.tv_sec * 1000000 + end.tv_usec) - 
    (start.tv_sec * 1000000 + start.tv_usec)));

  return 0;
}
