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


#include<iostream>
#include<cmath>

using namespace std;
int jump_Search(int a[], int n, int item) {
   int i = 0;
   int m = sqrt(n); //initializing block size= √(n)

   while(a[m] <= item && m < n) { 
      // the control will continue to jump the blocks 
      i = m;  // shift the block
      m += sqrt(n);
      if(m > n - 1)  // if m exceeds the array size
         return -1; 
   }

   for(int x = i; x<m; x++) { //linear search in current block
      if(a[x] == item)
         return x; //position of element being searched 
   }
   return -1;
}

int main() {
   int n, item, loc;
   cout << "\n Enter number of items: ";
   cin >> n;
   int arr[n]; //creating an array of size n
   cout << "\n Enter items: ";

   for(int i = 0; i< n; i++) {
      cin >> arr[i];
   }

   cout << "\n Enter search key to be found in the array: ";
   cin >> item;
   loc = jump_Search(arr, n, item);
   if(loc>=0)
      cout << "\n Item found at location: " << loc;
   else
      cout << "\n Item is not found in the list.";
}
