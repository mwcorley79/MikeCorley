// Compiler command: gcc CstringDemoGotcha.c
// Run Command: ./a.out

#include<stdio.h>
#include<string.h>

int main()
{
   // a literal string stored in executable image (immutable)
   char* astr  = "a string literal";
   printf("%s\n", astr);
   //astr[0] = 'b';  //don't try this
   //printf("%s\n", astr);
   
   char bstr[]="b string literal";
   printf("%s\n",bstr);
   bstr[0] = 'a';  //this is okay
   printf("%s\n",bstr);

   char cstr[100];
   strncpy(cstr, astr, 100);
   printf("Copy of astr: %s\n",cstr);
   
    if(strncmp(cstr, astr,100) == 0)
       printf("They are equal!\n");
  
    return 0;
}

