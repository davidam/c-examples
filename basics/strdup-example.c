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

/* strdup() : */
/* Syntax : char *strdup(const char *s); */
/* This function returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by s. The memory obtained is done dynamically using malloc and hence it can be freed using free(). */
/* It returns a pointer to the duplicated string s. */
// C program to demonstrate strdup() 
#include<stdio.h> 
#include<string.h> 
  
int main() 
{ 
    char source[] = "GeeksForGeeks"; 
  
    // A copy of source is created dynamically 
    // and pointer to copy is returned. 
    char* target = strdup(source);  
  
    printf("%s\n", target); 
    return 0; 
} 
