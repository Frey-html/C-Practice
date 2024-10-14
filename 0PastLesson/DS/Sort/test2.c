#include <stdio.h>
 
int main ()
{
   FILE *fp;
 
   fp = fopen("file.txt", "w+");
   for( int i = 0 ; i <= 10; i++ )
   {
      fputc(i + '0', fp);
   }
   fclose(fp);
 
   return(0);
}