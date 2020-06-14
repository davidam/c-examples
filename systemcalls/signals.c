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
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
 
void sig_handler(int signum){
 
  printf("Inside handler function\n");
}
 
int main(){
 
  signal(SIGALRM,sig_handler); // Register signal handler
 
  alarm(4);  // Scheduled alarm after 4 seconds
  alarm(1);  // Scheduled alarm after 1 seconds
 
  for(int i=1;;i++){
 
    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
}
 
return 0;
}
