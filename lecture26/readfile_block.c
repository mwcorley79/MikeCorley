// Note: This is the C solution to HW # 8, you were asked to complete the C++ version: readfile_block.cpp
// Compiler command: gcc -o block_cp readfile_block.c
// Run Command:    ./block_cp  source-file  dest-file  block-size

#include <stdio.h>
#include <stdlib.h>

void copyFileByBlock(const char* source_file, const char* dest_file, size_t block_size)
{
    char* buf = (char*) malloc(block_size * sizeof(char));

    if(buf == NULL)
    {
      fprintf(stderr, "Error allocating memory of size %ld\n", block_size);
      exit(1);
    }

    FILE* sf = fopen(source_file, "r");
    if(sf == NULL)
    {
      fprintf(stderr, "Error opening: %s\n", source_file);
      exit(1);
    }


    FILE* df = fopen(dest_file, "w");
    if(df == NULL)
    {
      fprintf(stderr, "Error allocating memory of size %s", dest_file);
      exit(1);
    }

    int bytes_read = fread(buf, sizeof(char), block_size, sf);
    while(bytes_read > 0)
    {
       int bytes_written = fwrite(buf, sizeof(char), bytes_read, df);
       if(bytes_written != bytes_read)
       {
	     fprintf(stderr, "error writing file: %s, bytes read: %d bytes written: %d\n", dest_file, bytes_read, bytes_written);
         exit(1);
       }
       bytes_read = fread(buf, sizeof(char), block_size, sf);
    }

    fclose(df);
    fclose(sf);

    free(buf);
}


void copyFile(const char* source_file, const char* dest_file)
{
    FILE* sf = fopen(source_file, "r");
    if(sf == NULL)
    {
       fprintf(stderr, "Error opening: %s\n", source_file);
       exit(1);
    }

    // use seek functions to get file size
    fseek(sf, 0, SEEK_END);
    size_t file_size = ftell(sf);
    fseek(sf, 0, SEEK_SET); 

    // allocate buffer large enough to hold entire file
    char* buf = (char*) malloc(file_size * sizeof(char));
    if(buf == NULL)
    {
       fprintf(stderr, "Error allocating memory of size %ld\n", file_size);
       exit(1);
    }

    FILE* df = fopen(dest_file, "w");
    if(df == NULL)
    {
       fprintf(stderr, "Error allocating memory of size %s", dest_file);
       exit(1);
    }

    int bytes_read = fread(buf, sizeof(char), file_size, sf);
    int bytes_written = 0;
    if(bytes_read == file_size)
    {
       bytes_written = fwrite(buf, sizeof(char), bytes_read, df);
    }
    else
    {
       fprintf(stderr, "error writing file: %s, bytes read: %d bytes written: %d\n", dest_file, bytes_read, bytes_written);
       exit(1);
    }

    fclose(df);
    fclose(sf);

    free(buf);
}

int main(int argc, char* argv[])
{
   if(argc != 4)
   {
     fprintf(stderr, "Usage: cp  source-file  dest-file  block-size\n");
     return 1;
   }

   char* source_file = argv[1];
   char* dest_file = *(argv + 2);  // demonstrate using pointer syntax to index array
   int block_size =  atoi(argv[3]);
   //copyFileByBlock(source_file, dest_file, block_size);

   copyFile(source_file, dest_file);

   return 0;  
}
