#include<iostream>
using namespace std;

int k=0; 	// for storing the maximum element of input array

/* Method to sort the array */
void sort_func(int A[],int B[],int n)    
{
	int count[k+1],t;
	for(int i=0;i<=k;i++)
	{
		//Initialize array count
		count[i] = 0;
	}
	for(int i=0;i<n;i++)
	{
	    // count the occurrence of elements u of A 
	    // & increment count[u] where u=A[i]
		t = A[i];
		count[t]++;			
	}
	for(int i=1;i<=k;i++)
	{
	    // Updating elements of count array 
		count[i] = count[i]+count[i-1];            
	}
	for(int i=0;i<n;i++)
	{
		// Add elements of array A to array B
		t = A[i];
		B[count[t]] = t;          
	    // Decrement the count value by 1
		count[t]=count[t]-1;		
	}
}
int main()
{
	int n;
	cout<<"Enter the size of the array :";
	cin>>n;
	
	// A is the input array and will store elements entered by the user
	// B is the output array having the sorted elements	
	int A[n],B[n]; 
	cout<<"Enter the array elements: ";
	for(int i=0;i<n;i++)        
	{
		cin>>A[i];
		if(A[i]>k)
		{
			// k will have the maximum element of A[]
			k = A[i];              
		}
	}
	
	sort_func(A,B,n);        
	
	// Printing the elements of array B
	for(int i=1;i<=n;i++)       
	{
		cout<<B[i]<<" ";
	}
	
	cout<<"\n";
	return 0;
}
