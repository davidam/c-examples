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
// C program to illustrate 
// open system call 
#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h> 
extern int errno; 
int main() 
{	 
	// if file does not have in directory 
	// then file foo.txt is created. 
	int fd = open("foo.txt", O_RDONLY | O_CREAT); 
	
	printf("fd = %d/n", fd); 
	
	if (fd ==-1) 
	{ 
		// print which type of error have in a code 
		printf("Error Number % d\n", errno); 
		
		// print program detail "Success or failure" 
		perror("Program");				 
	} 
	return 0; 
} 
