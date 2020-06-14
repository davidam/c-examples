/* Copyright (C) 2020  David Arroyo Menéndez
   Author: David Arroyo Menéndez <davidam@gnu.org>
   Maintainer: David Arroyo Menéndez <davidam@gnu.org>
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
#include <stdlib.h>
#include <sys/file.h>
#include <linux/random.h>


#define BUFFER_SIZE 67108864
#define BUFFER_1 "buffer1"
#define BUFFER_2 "buffer2"
 
int main() {
 
    FILE *fOut, *fIn;
 
    printf("\nI/O test with traditional glibc functions.\n\n");
 
    // Grab a BUFFER_SIZE buffer.
    // The buffer will have random data in it but we don't care about that.
    printf("Allocating 64 MB buffer:                     ");
    char *buffer = (char *) malloc(BUFFER_SIZE);
    printf("DONE\n");
 
    // Write the buffer to fOut
    printf("Writing data to first buffer:                ");
    fOut = fopen(BUFFER_1, "wb");
    fwrite(buffer, sizeof(char), BUFFER_SIZE, fOut);
    fclose(fOut);
    printf("DONE\n");
 
    printf("Copying data from first file to second:      ");
    fIn = fopen(BUFFER_1, "rb");
    fOut = fopen(BUFFER_2, "wb");
    fread(buffer, sizeof(char), BUFFER_SIZE, fIn);
    fwrite(buffer, sizeof(char), BUFFER_SIZE, fOut);
    fclose(fIn);
    fclose(fOut);
    printf("DONE\n");
 
    printf("Freeing buffer:                              ");
    free(buffer);
    printf("DONE\n");
 
    printf("Deleting files:                              ");
    remove(BUFFER_1);
    remove(BUFFER_2);
    printf("DONE\n");
 
    return 0;
 
}
