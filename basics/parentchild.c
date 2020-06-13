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
// C program to demonstrate working of wait() 
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 

int main() 
{ 
	pid_t cpid; 
	if (fork()== 0) 
		exit(0);		 /* terminate child */
	else
		cpid = wait(NULL); /* reaping parent */
	printf("Parent pid = %d\n", getpid()); 
	printf("Child pid = %d\n", cpid); 

	return 0; 
} 
