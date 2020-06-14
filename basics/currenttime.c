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

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval tv;
  time_t t;
  struct tm *info;
  char buffer[64];
 
  gettimeofday(&tv, NULL);
  t = tv.tv_sec;

  info = localtime(&t);
  printf("%s",asctime (info));
  strftime (buffer, sizeof buffer, "Today is %A, %B %d.\n", info);
  printf("%s",buffer);
  strftime (buffer, sizeof buffer, "The time is %I:%M %p.\n", info);
  printf("%s",buffer);

  return 0;
}
