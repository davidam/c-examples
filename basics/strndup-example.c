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

//strndup() :
//syntax: char *strndup(const char *s, size_t n);
//This function is similar to strdup(), but copies at most n bytes.

// C program to demonstrate strndup() 
#include<stdio.h> 
#include<string.h> 
  
int main() 
{ 
    char source[] = "GeeksForGeeks"; 
  
    // 5 bytes of source are copied to a new memory 
    // allocated dynamically and pointer to copied 
    // memory is returned. 
    char* target = strndup(source, 5); 
  
    printf("%s\n", target); 
    return 0; 
} 
