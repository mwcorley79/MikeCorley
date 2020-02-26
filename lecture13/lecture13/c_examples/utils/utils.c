#include<stdio.h>
#include<string.h>
#include<math.h>

unsigned toHexDigit(int ch)
{
   //if(isdigit(ch)
   if(ch >= '0' && ch <= '9')
      return (ch - '0');
   else if(ch >= 'A' && ch <= 'F')
      return 10 + (ch - 'A');
   else
      return -1;
}

unsigned long atoh(int base, const char* num, int max)
{
   int len = strnlen(num, max);
   unsigned long val = 0;

   for(int exp = 0; exp < len; ++exp)
   {
      val += ( ((unsigned) pow(base, exp))  * toHexDigit(num[exp]));
   }

   return val;
}



int main(int argc, char* argv[])
{
   char num[] = "AAAA";
   int len;
   printf("The length of the string is: %d\n", (len = strnlen(num,8)));
   
   for(int i = 0;  i < len; ++i)
   {
      printf("%d ", toHexDigit(num[i]));
   }
   printf("\n"); 

   unsigned val;
   printf("Number val is: %#X\n", (val = (unsigned) atoh(16, num, 8)));

   return 0;
}

/* unsigned atoi(int base, char num[], int n)
{
   char digits={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
  

   int len = strnlen(num,n)
   for(int i=0; i < len; ++i)
   {
       unsigned digit 
   }

*/
