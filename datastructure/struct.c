/* Copyright (C) 2020  David Arroyo Menéndez
   Author: David Arroyo Menéndez <davidam@gnu.org>
   Maintainer: David Arroyo Menéndez <davidam@gnu.orgxs>
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
 
struct product
{
  char name[30];
  int stock, price, dis;
}
 
main()
{
  struct product p1 = {"GNU Emacs", 35, 298, 2};
  printf("Name=%s,\nStock=%d,\nPrice=%d,\nDiscount=%d.", p1.name, p1.stock, p1.price, p1.dis);
}
