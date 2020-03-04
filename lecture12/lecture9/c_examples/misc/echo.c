#include<stdio.h>

int main (int argc, char* argv[])
{
    int ch;
    while( (ch = getchar()) != EOF)
        printf("%c", ch);

   return 0;
}
