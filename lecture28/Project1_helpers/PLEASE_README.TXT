*** PLEASE see the updated Project 1 statement on the class web page ***

Description:
MinShell: CSE 384 (spring 2020) Project 1 helper/starter code  
This a minimal shell implemention capable of basic commands:
setting/displaying shell variables, shell history, and running external programs

Dependencies:  
 GNU readline:           https://tiswww.case.edu/php/chet/readline/rltop.html
 Installation:           sudo apt-get install libreadline-dev 
 Build/Compiler command: g++ -o msh minShell.cpp CommandManager.cpp Process.cpp -lreadline
 Run Command:           ./msh
