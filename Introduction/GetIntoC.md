## C Language - Essentials  
# Basic structure of a program  
A C program usually starts with a main function. Example:  
  
#include <stdio.h>  
  
int main(void) {  
  printf("Hello World");  
  return 0;  
}  
  
■ Header '#include <stdio.h>' is crutial as it tells the C compiler to include the header file stdio.h. This file contains essential input/output functions such as printf, scanf, fclose, getchar, etc.  
■ main is the core program. It executes all logic and returns an exit code (hence it is of type int). Main can be of type void aswell, however not recommended as its not standard and might not work on every compiler (prevents the program of returning an exit status code to the OS). Inside the parenthesis sits the arguments. If lack of arguments, it is a good practise to explicitly tell the compiler that the program takes no arguments through main(void). Empty parenthesis main() means in C that the program can take an unknown number of arguments rather than 0.  
■ The body includes all logic and is locate inside brackets {}  
■ The program usually end with return 0 (explicitly telling the compiler that the program ran and ended with success), although this can be omitted in modern C/C++ (C99 and later)  
  
# Compiler
