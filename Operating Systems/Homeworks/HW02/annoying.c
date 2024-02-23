/* annoying.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int i = 0;
  while (i < 2)
  {
    printf( "Hey, get back to work!\n" );
    sleep( 1 );
    i += 1;
  }
  exit(EXIT_FAILURE);
  return EXIT_SUCCESS;
}
