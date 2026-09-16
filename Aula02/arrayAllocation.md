# Arrays  
## Array allocation
**■ int nums[5] = {7, 11, -1, 0, 33};**  
  => Allocates in memory an array with 5 integers  
  => The compiler can determine its size if size is not directly specified: int nums[] = {7, 11, -1, 0, 33};  
  
## Arrays as functions params/args
■ **int findmin(int nums[], unsigned n) {  
  ...  
}**  
  => A function can receive an array and the number of elements as its parameters  
  
**Example:**  
■ int data[] = {7, 11, -1, 0, 33};  
■ findmin(data, 5);  
  
**This function is equivalent as writing:**  
■ int findmin(int *nums, unsigned n) { ... }  
  => Parameter nums receives a pointer to the array, pointing to its first element  
  
## Strings
In C, Strings are arrays of chars (ended by a null character)  
**Example**  
■ char str[] = "SUI" (or char str[] = {'S', 'U', 'I', '\0'})  
■ In memory => 'S' 'U' 'I' '\0'  
  
## argc & argv
■ int main(unsigned argc, char *argv[]) {...}  
  => argc stands for argument count (number of arguments provided in a terminal)  
  => argv stands for argument vector. Its an array of Strings which contains the arguments  
**Example:**  
■ Command: ./hello world 7  
argc = 3  
argv[0] = "./hello"  
argv[1] = "world"  
argv[2] = "7"  
  
## size_t
size_t is an unsigned integer used to represent the amount of objects on memory.  
■ int main(size_t argc, char **argv) {...}  
■ typedef unsigned int size_t  
