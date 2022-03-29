#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

  int a = 0;
  int b = 0;
 
  a = atoi(argv[1]);
  b = atoi(argv[2]);
 
  printf(" %d + %d  = %d \n", a , b , a+b); 
  printf(" %d - %d  = %d \n", a , b , a-b); 
  printf(" %d * %d  = %d \n", a , b , a*b); 
  printf(" %d / %d  = %d \n", a , b , a/b); 
 
 return 0;
 
}
