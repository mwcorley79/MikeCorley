#----------------------------------------------------------
# makefile - demo for Project #1
#
# Jim Fawcett, CSE775 - Distributed Objects, Spring 2019
#----------------------------------------------------------
# Notes:
#   - Indentations must be a single Tab (not spaces)
#   - Dependencies are not indented
#   - commands are indented with single tab
#----------------------------------------------------------

all: FileSystem

# link FileSystem.o to create executable FileSystem
# you may add additional object files as needed

FileSystem: FileSystem.o
	g++ FileSystem.o -o FileSystem.exe

# compile FileSystem.cpp to create object file FileSystem.o
# you may add additional source files as needed
# g - default debug information
# c - compile only

FileSystem.o: FileSystem.cpp
	g++ -c -g -DTEST_FILESYSTEM -Wall FileSystem.cpp -o FileSystem.o

# remove object files
# only called if cited in all: directive

clean:
	rm *.o

