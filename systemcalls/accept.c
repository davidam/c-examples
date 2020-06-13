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
// C program to show accept system call is blocking call 
#include <stdio.h>                                                                                                                                        
#include <sys/types.h>                                                                                                                                    
#include <sys/socket.h>                                                                                                                                   
#include <netinet/in.h>                                                                                                                                   
#include <string.h>                                                                                                                                       
#define BACKLOG 3                                                                                                                                             
  
// Driver program                                                                                                                                                             
int main()                                                                                                                                                
{                                                                                                                                                             
        struct sockaddr_in my_addr, peer_addr;                                                                                                                
        socklen_t peer_addr_size;                                                                                                                             
        int sd, b, l, acc;                                                                                                                                    
        my_addr.sin_family = AF_INET; 
          
        // Creating socket                                                                                                                        
        sd = socket(AF_INET, SOCK_STREAM, 0);  
          
        // Binding                                                                                                                
        b = bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));                                                                                
        if(b > 0)                                                                                                                                             
                printf("Binded Successfully\n");                                                                                                              
        else                                                                                                                                                
                printf("Binding Error\n");  
        // Listening                                                                                                                  
        l = listen(sd, BACKLOG);                                                                                                                              
        if(l > 0)                                                                                                                                             
                printf("Listening...\n");                                                                                                                     
        else                                                                                                                                                
                printf("Not listening..\n");                                                                                                                  
        peer_addr_size = sizeof(struct sockaddr_in);  
          
        // Accept system call                                                                                                     
        acc = accept(sd, (struct sockaddr *)&peer_addr, &peer_addr_size);                                                                                     
        if(acc > 0)                                                                                                                                       
                printf("Accepted\n");                                                                                                                         
        else                                                                                                                                                
                printf("Not accepted\n");                                                                                                                     
}                                            
  
