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
// C program to check if a string is palindrome 
// using pointers 

#include <stdio.h> 

// Function to check if the string is palindrome 
// using pointers 
void isPalindrome(char* string) 
{ 
	char *ptr, *rev; 

	ptr = string; 

	while (*ptr != '\0') { 
		++ptr; 
	} 
	--ptr; 

	for (rev = string; ptr >= rev;) { 
		if (*ptr == *rev) { 
			--ptr; 
			rev++; 
		} 
		else
			break; 
	} 

	if (rev > ptr) 
		printf("String is Palindrome"); 
	else
		printf("String is not a Palindrome"); 
} 

// Driver code 
int main() 
{ 
	char str[1000] = "madam"; 

	isPalindrome(str); 

	return 0; 
} 
