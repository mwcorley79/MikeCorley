#!/bin/bash
for i in {1..5}; 
   do 
    printf "starting client: %i\n\n" $i
    ./client2; 
   done
