# C-and-Bash

There are scripts that use OS functions to read files, directories and run specific piping commands

------------------------------------

cp_files.sh -> This program explores the current directory, its files and subdirectories recursively
if it finds files with suffix *.c then it clones and names *.c.orig

recursive_ls.c -> This program outputs all the files and directories that are in current directory
recursively

piping.c -> This program executes the pattern prog1 && prog2 | prog3 > file, where {prog1, prog2, prog3, file}
are arguments. Overall it writes the output in file which is absolute path to spesific file
