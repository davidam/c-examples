#include <stdio.h>
 
struct product
{
    char name[30];
    int stock;
    float price, dis;
};
 
void main()
{
     struct product p1 ={"GNU Emacs", 35,298.56, 2.32};
     //     clrscr();
     printf("Name=%s,\nStock=%d,\nPrice=$%.2f,\nDiscount=%.2f%.", p1.name, p1.stock, p1.price,p1.dis);
     //getch();
}
