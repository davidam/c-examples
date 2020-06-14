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
#include <unistd.h>
#include <sys/file.h>
#include <sys/sendfile.h>
#include <linux/random.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
 
#define BUFFER_SIZE 67108864
 
int main() {
 
  int fOut, fIn;
 
  printf("\nI/O test with sendfile() and related system calls.\n\n");
 
  // Grab a BUFFER_SIZE buffer.
  // The buffer will have random data in it but we don't care about that.
  printf("Allocating 64 MB buffer:                     ");
  char *buffer = (char *) malloc(BUFFER_SIZE);
  printf("DONE\n");
 

  // Write the buffer to fOut
  printf("Writing data to first buffer:                ");
  fOut = open("buffer1", O_RDONLY);
  write(fOut, &buffer, BUFFER_SIZE);
  close(fOut);
  printf("DONE\n");
 
  printf("Copying data from first file to second:      ");
  fIn = open("buffer1", O_RDONLY);
  fOut = open("buffer2", O_RDONLY);
  sendfile(fOut, fIn, 0, BUFFER_SIZE);
  close(fIn);
  close(fOut);
  printf("DONE\n");
 
  printf("Freeing buffer:                              ");
  free(buffer);
  printf("DONE\n");
 
  printf("Deleting files:                              ");
  unlink("buffer1");
  unlink("buffer2");
  printf("DONE\n");
 
  return 0;
 
}
