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
// Sample program to show that memcpy() can loose data. 
#include <stdio.h> 
#include <string.h> 
int main() 
{ 
  char csrc[100] = "Dame\n"; 
  memcpy(csrc+5, csrc, strlen(csrc)+1); 
  printf("%s", csrc); 
  memmove(csrc+5, csrc, strlen(csrc)+1); 
  printf("%s", csrc); 
  return 0; 
} 
