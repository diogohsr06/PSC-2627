# C Language - Essentials  
## Basic structure of a program  
A C program usually starts with a main function. Example:  
  
```c
```
```c
#include <stdio.h>  
  
int main(void) {  
  printf("Hello World");  
  return 0;  
}  
```  
```
  
■ Header '#include <stdio.h>' is crutial as it tells the C compiler to include the header file **stdio.h**. This file contains essential input/output functions such as printf, scanf, fclose, getchar, etc.  
■ **main** is the core program. It executes all logic and returns an exit code (hence it is of type int). Main can be of type **void** aswell, however not recommended as its not standard and might not work on every compiler (prevents the program of returning an exit status code to the OS). Inside the parenthesis sits the arguments. If lack of arguments, it is a good practise to explicitly tell the compiler that the program takes no arguments through **main(void)**. Empty parenthesis **main()** means in C that the program can take an unknown number of arguments rather than 0.  
■ The body includes all logic and is locate inside brackets {}  
■ The program usually end with return 0 (explicitly telling the compiler that the program ran and ended with success), although this can be omitted in modern C/C++ (C99 and later)  
```  
  
## Compiler  
Piece of software which grabs the C code and translates into machine code. A C compiler compiles in 4 stages:  
  
■ Preprocessing: Analyses directives (started with #) such as #include or #define;  
■ Compilation: Translates C code into Assembly code and checks errors;  
■ Assembly: The assembler converts Assembly code into binary code;  
■ Linking: Merges the binary code with the precompiled code from system libraries, and then is generated an executable.  
  
### GCC  
GCC (GNU Compiler Collection) is one of the C compilers used on this course, commonly used in GNU/Linux environments.  
Some examples of usage:  
> gcc main.c  
Compiles the file and generates an executable of standard name 'a'.  
  
> gcc main.c -o name  
Compiles the file and generates an executable with a specified name with flag -o.  
  
> gcc main1.c main2.c -o program  
Compiles multiple files and combines them into an executable program.  
  
> gcc -std=c99 main.c -o program  
Compiles with C99  
  
> gcc -std=c11 main.c -o program  
Compiles with C11  
  
> gcc -E main.c -o main.i  
After preprocessing, generates expanded file .i  
  
> gcc -S main.c  
After compilation, generates assembly file.  
  
> gcc -c main.c  
After assembly, generates object .o without creating an executable.  
  
## Variables  
