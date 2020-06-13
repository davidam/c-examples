/* Below program is written in C++ language */

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
   with Circular Queue; see the file COPYING. If not, see
   <https://github.com/davidam/workingclasslicense>.
*/

#include<iostream>

using namespace std;

#define SIZE 10

class CircularQueue
{
    int a[SIZE];
    int rear;   //same as tail
    int front;  //same as head
  
    public:
    CircularQueue()
    {
        rear = front = -1;
    }
    
    // function to check if queue is full
    bool isFull()
    {
        if(front == 0 && rear == SIZE - 1)
        {
            return true;
        }
        if(front == rear + 1) 
        {
            return true;
        }
        return false;
    }
    
    // function to check if queue is empty
    bool isEmpty()
    {
        if(front == -1) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    
    //declaring enqueue, dequeue, display and size functions
    void enqueue(int x);     
    int dequeue();
    void display();
    int size();
};

// function enqueue - to add data to queue
void CircularQueue :: enqueue(int x)
{
    if(isFull())
    {
        cout << "Queue is full";
    } 
    else 
    {
        if(front == -1)
        {   
            front = 0;
        }
        rear = (rear + 1) % SIZE;   // going round and round concept
        // inserting the element
        a[rear] = x;
        cout << endl << "Inserted " << x << endl;
    }
}

// function dequeue - to remove data from queue
int CircularQueue :: dequeue()
{
    int y;
    
    if(isEmpty())
    {
        cout << "Queue is empty" << endl;
    } 
    else 
    {
        y = a[front];
        if(front == rear)
        {
            // only one element in queue, reset queue after removal
            front = -1;
            rear = -1;
        }
        else 
        {
            front = (front+1) % SIZE;
        }
        return(y);
    }
}

void CircularQueue :: display()
{
    /* Function to display status of Circular Queue */
    int i;
    if(isEmpty()) 
    {
        cout << endl << "Empty Queue" << endl;
    }
    else
    {
        cout << endl << "Front -> " << front;
        cout << endl << "Elements -> ";
        for(i = front; i != rear; i= (i+1) % SIZE)
        {
            cout << a[i] << "\t";
        }
        cout << a[i];
        cout << endl << "Rear -> " << rear;
    }
}

int CircularQueue :: size()
{
    if(rear >= front)
    {
        return (rear - front) + 1;
    }
    else
    {
        return (SIZE - (front - rear) + 1);
    }
}

// the main function
int main()
{
    CircularQueue cq;
    cq.enqueue(10);
    cq.enqueue(100);
    cq.enqueue(1000);
    
    cout << endl << "Size of queue: " << cq.size();
    
    cout << endl << "Removed element: " << cq.dequeue();
    
    cq.display();
    
    return 0;
}
