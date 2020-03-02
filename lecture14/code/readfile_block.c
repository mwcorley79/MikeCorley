
// Compiler command: gcc -o block_cp readfile_block.c
// Run command: block_cp  source_file  dest_file  4096   

#include <stdio.h>
#include <stdlib.h>

/* HW # 8 complete the function (below) to copy files a block at a time */

void copyFileByBlock(const char* source_file, const char* dest_file, size_t block_size)
{
    // allocate buffer large enough to hold block_size bytes, check to see of malloc successful not NULL)   
 
    // open the source file, check for success

    // open the destination file, check for success

    //read source file a block at time, write dest file a block at a time   

    /* read a block (fread)
       while(bytes read from fread > 0)
       {
          write block (fwrite)
          if the bytes written != to the bytes read)
          {
             display an error and exit the program
          }
          
          read a block (fread)
       }

      close the source file
      close the dest file

      free the buffer
    */
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
     fprintf(stderr, "Usage: block_cp  source-file  dest-file  block-size\n");
     return 1;
   }

   char* source_file = argv[1];
   char* dest_file = *(argv + 2);  // demonstrate using pointer syntax to index array
   int block_size =  atoi(argv[3]);
   copyFile(source_file, dest_file);

   //  *** uncomment when completed  
   // copyFileByBlock(source_file, dest_file, block_size);

   return 0;  
}
