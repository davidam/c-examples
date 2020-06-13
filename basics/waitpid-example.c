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
// C program to demonstrate waitpid() 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
void waitexample() 
{ 
    int i, stat; 
    pid_t pid[5]; 
    for (i=0; i<5; i++) 
    { 
        if ((pid[i] = fork()) == 0) 
        { 
            sleep(1); 
            exit(100 + i); 
        } 
    } 
  
    // Using waitpid() and printing exit status 
    // of children. 
    for (i=0; i<5; i++) 
    { 
        pid_t cpid = waitpid(pid[i], &stat, 0); 
        if (WIFEXITED(stat)) 
            printf("Child %d terminated with status: %d\n", 
                   cpid, WEXITSTATUS(stat)); 
    } 
} 
  
// Driver code 
int main() 
{ 
    waitexample(); 
    return 0; 
} 
