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

#include <stdio.h>

int main( int argc, char *argv[] )  {

   printf("Program name %s\n", argv[0]);
 
   if( argc == 2 ) {
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
