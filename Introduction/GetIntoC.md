# C Language - Essentials

## Basic structure of a program
A C program usually starts with a main function. Example:

```c
#include <stdio.h>

int main(void) {
  printf("Hello World");
  return 0;
}
```

- Header `#include <stdio.h>` is crutial as it tells the C compiler to include the header file **stdio.h**. This file contains essential input/output functions such as printf, scanf, fclose, getchar, etc.
- **main** is the core program. It executes all logic and returns an exit code (hence it is of type int). Main can be of type **void** aswell, however not recommended as its not standard and might not work on every compiler (prevents the program of returning an exit status code to the OS). Inside the parenthesis sits the arguments. If lack of arguments, it is a good practise to explicitly tell the compiler that the program takes no arguments through **main(void)**. Empty parenthesis **main()** means in C that the program can take an unknown number of arguments rather than 0.
- The body includes all logic and is locate inside brackets `{}`
- The program usually end with return 0 (explicitly telling the compiler that the program ran and ended with success), although this can be omitted in modern C/C++ (C99 and later)

## Compiler
Piece of software which grabs the C code and translates into machine code. A C compiler compiles in 4 stages:

1. **Preprocessing** — Analyses directives (started with #) such as #include or #define
2. **Compilation** — Translates C code into Assembly code and checks errors
3. **Assembly** — The assembler converts Assembly code into binary code
4. **Linking** — Merges the binary code with the precompiled code from system libraries, and then is generated an executable

### GCC
GCC (GNU Compiler Collection) is one of the C compilers used on this course, commonly used in GNU/Linux environments.

Some examples of usage:

| Command | Description |
|---|---|
| `gcc main.c` | Compiles the file and generates an executable of standard name 'a' |
| `gcc main.c -o name` | Compiles the file and generates an executable with a specified name with flag -o |
| `gcc main1.c main2.c -o program` | Compiles multiple files and combines them into an executable program |
| `gcc -std=c99 main.c -o program` | Compiles with C99 |
| `gcc -std=c11 main.c -o program` | Compiles with C11 |
| `gcc -E main.c -o main.i` | After preprocessing, generates expanded file .i |
| `gcc -S main.c` | After compilation, generates assembly file |
| `gcc -c main.c` | After assembly, generates object .o without creating an executable |

---

## Variables
A variable is a named region of memory that stores a value of a given type. In C, every variable must be declared with a type before use. C is a statically typed language, so the type doesn't change after declaration.

```c
int age = 21;
float pi = 3.14f;
char grade = 'A';
```

- Declaration reserves the memory; initialization gives it a first value. They can be done separately (`int x; x = 5;`) or together (`int x = 5;`)
- An uninitialized local variable has **garbage value** (whatever was left in that memory slot before) it's good practise to always initialize
- Variable names: must start with a letter or underscore, can contain letters/digits/underscores, are case-sensitive, and cannot be a reserved keyword (`int`, `return`, `for`, etc.)
- **Scope**: a variable declared inside `{}` only exists inside that block (local scope). A variable declared outside any function is **global** and visible to the whole file
- **Lifetime**: local variables live on the stack and are destroyed when the block ends; global variables live for the whole program duration

## Data Types

### Basic types
| Type | Typical size | Description |
|---|---|---|
| `char` | 1 byte | Single character / small integer |
| `int` | 4 bytes | Standard integer |
| `float` | 4 bytes | Single precision floating point |
| `double` | 8 bytes | Double precision floating point |
| `void` | — | Represents "no type" (used for functions that return nothing, or generic pointers) |

Sizes are not fixed by the language and they depend on the platform/compiler. That's why `sizeof` exists instead of assuming a fixed byte count.

### Modifiers
Modifiers change the range/precision of a base type:

- `short` / `long` / `long long` — change the size (and range) of `int`
- `signed` / `unsigned` — controls whether negative values are allowed
  - `signed int` (default for `int`): can represent negative and positive numbers
  - `unsigned int`: only non-negative numbers, but doubles the positive range since no bit is used for the sign

```c
short int a;        // usually 2 bytes
long int b;         // usually 8 bytes (platform dependent)
unsigned int c;      // 0 to ~4 billion instead of -2 billion to +2 billion
long long int d;    // guaranteed at least 64 bits
```

### Derived / user types (preview — covered in detail later)
- Arrays — collections of same-type elements
- Pointers — variables that store memory addresses
- Structs — collections of different-type elements grouped together
- `typedef` — creates an alias for an existing type, often used with structs:

```c
typedef struct {
  int x;
  int y;
} Point;

Point p1; // instead of "struct Point p1;"
```

## sizeof
`sizeof` is a compile-time operator and not a function, although it looks like one, that returns the size, in bytes, of a type or variable. Its return type is `size_t`.

```c
printf("%zu\n", sizeof(int));      // typically 4
printf("%zu\n", sizeof(char));     // always 1, by definition
printf("%zu\n", sizeof(double));   // typically 8

int arr[10];
printf("%zu\n", sizeof(arr));      // 40 (10 * sizeof(int)) - only works on real arrays, not decayed pointers
printf("%zu\n", sizeof(arr) / sizeof(arr[0])); // classic idiom to get number of elements
```

- `sizeof(char)` is guaranteed by the standard to always be 1 (this is the "byte" unit C is built around)
- Very useful together with `malloc` to allocate the right amount of memory: `malloc(n * sizeof(int))`
- On an array (not a pointer), `sizeof` gives the **whole block size**; the moment an array is passed to a function it decays to a pointer and `sizeof` inside that function would give the pointer size (4 or 8 bytes) instead — a classic beginner trap

## const
`const` marks a variable (or pointer target) as read-only after initialization. Attempting to modify it is a compile-time error.

```c
const float PI = 3.14159f;
PI = 3.0; // compile error: assignment of read-only variable
```

With pointers, `const` placement matters a lot:

```c
const int *p1;       // pointer to a constant int -> *p1 = 5 is illegal, p1 = &other is legal
int *const p2 = &x;   // constant pointer to int   -> *p2 = 5 is legal, p2 = &other is illegal
const int *const p3;  // constant pointer to constant int -> neither is legal
```

Rule of thumb: read the declaration right-to-left around the `*`. `const` applies to whatever is immediately to its left (or, if nothing is to its left, to whatever is immediately to its right).

Using `const` on function parameters (especially pointers) is good practise — it documents and enforces that the function won't modify the caller's data:

```c
void printArray(const int *arr, int size);
```

## Operations (Operators)

### Arithmetic
`+  -  *  /  %` (modulo, integers only)

- Integer division truncates: `7 / 2` is `3`, not `3.5`
- `%` only works on integer types

### Relational
`==  !=  >  <  >=  <=` — all return `int` (0 = false, non-zero = true; C has no dedicated boolean type pre-C99)

### Logical
`&&  ||  !` — short-circuit evaluation: in `a && b`, if `a` is false, `b` is never evaluated

### Bitwise
`&  |  ^  ~  <<  >>` — operate directly on the bits of integer types

```c
int a = 5;      // 0101
int b = 3;      // 0011
a & b;          // 0001 -> 1
a | b;          // 0111 -> 7
a ^ b;          // 0110 -> 6 (XOR)
~a;             // bitwise NOT (inverts every bit)
a << 1;         // shift left  -> multiply by 2  -> 10 (1010)
a >> 1;         // shift right -> divide by 2   -> 2  (0010)
```

### Assignment
`=  +=  -=  *=  /=  %=  &=  |=  ^=  <<=  >>=`

### Increment / Decrement
`++  --` — prefix (`++x`, increments then returns) vs postfix (`x++`, returns then increments) matters when the expression is used inline:

```c
int x = 5;
int y = x++; // y = 5, x becomes 6
int z = ++x; // x becomes 7, z = 7
```

### Ternary
```c
int max = (a > b) ? a : b;
```

### Comma and sizeof
`,` sequences expressions; `sizeof` was already covered above but is technically an operator too.

## Comments
```c
// Single-line comment

/* Multi-line
   comment */
```
- Comments are stripped in the preprocessing stage and have zero runtime cost
- Good practise: comment **why**, not **what** (the code already says what it does)

---

## Memory
Understanding how a C program's memory is laid out is fundamental before tackling pointers. A running process is typically divided into these regions:

| Segment | Contents | Lifetime |
|---|---|---|
| **Text/Code** | The compiled machine instructions | Whole program |
| **Data / BSS** | Global and `static` variables (initialized / zero-initialized) | Whole program |
| **Heap** | Dynamically allocated memory (`malloc`, `calloc`, `realloc`) | Until explicitly `free`d |
| **Stack** | Local variables, function parameters, return addresses | Duration of the function call |

- The **stack** grows and shrinks automatically as functions are called and return. It is fast but limited in size (stack overflow if you recurse too deep or allocate huge local arrays)
- The **heap** is managed manually by the programmer in C (no garbage collector). It's bigger but slower to allocate from and must be freed explicitly or it leaks
- Every variable, no matter where it lives, has an **address** — a location in memory. This is what pointers store

## Pointers
A pointer is a variable whose value is a **memory address**. It "points to" the location of another variable.

```c
int x = 10;
int *p = &x;   // p stores the address of x

printf("%d\n", x);    // 10 (the value)
printf("%p\n", (void*)&x); // the address of x
printf("%p\n", (void*)p);  // same address, since p holds &x
printf("%d\n", *p);   // 10 (dereferencing p -> the value stored at that address)
```

### Key operators
- `&` (address-of): gets the address of a variable
- `*` (dereference, when used on a pointer): accesses/modifies the value at that address
- `*` (when used in a declaration): declares a variable as a pointer of that type, e.g. `int *p;`

### Why the type matters
The pointer's type tells the compiler how many bytes to read/write when dereferencing, and how much to move when doing pointer arithmetic. `int *` and `char *` both "just store an address", but the compiler treats them very differently.

```c
int *p;     // points to an int  -> *p reads/writes 4 bytes
char *c;    // points to a char  -> *c reads/writes 1 byte
double *d;  // points to a double -> *d reads/writes 8 bytes
```

### Pointer arithmetic
Adding to a pointer moves it by `N * sizeof(type)` bytes, not by N raw bytes. This is what makes `p++` correctly move to the *next element*, regardless of the type's size.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;   // arrays decay to a pointer to their first element
printf("%d\n", *p);       // 10
printf("%d\n", *(p + 1)); // 20
p++;
printf("%d\n", *p);       // 20
```

### Void pointers
`void *` is a generic pointer — it can hold the address of any type, but cannot be dereferenced directly (the compiler doesn't know the size). Must be cast to a concrete type first. `malloc` returns `void *` for this reason.

### Pointers to pointers
```c
int x = 5;
int *p = &x;
int **pp = &p;   // pp holds the address of p

**pp = 10; // x is now 10
```
Common in situations like `char **argv` (array of strings) or when a function needs to modify a caller's pointer (e.g. reallocating a buffer inside a helper function).

### Function pointers
A pointer can also store the address of a function, enabling callbacks and dispatch tables:

```c
int add(int a, int b) { return a + b; }

int (*op)(int, int) = add;
printf("%d\n", op(2, 3)); // 5
```

### NULL pointers and dangling pointers
- A pointer that isn't pointing anywhere valid should be set to `NULL` explicitly — an uninitialized pointer holds garbage and dereferencing it is undefined behaviour
- A **dangling pointer** points to memory that has already been freed (or to a local variable that has gone out of scope). Using it is undefined behaviour, even if it "seems to work" — see Memory Errors below

## Arrays
An array is a fixed-size, contiguous block of memory holding elements of the same type.

```c
int arr[5] = {1, 2, 3, 4, 5};
int zeros[10] = {0};       // first element 0, rest are zero-initialized too
int inferred[] = {1, 2, 3}; // size inferred as 3 from the initializer
```

- Indexing starts at 0. `arr[0]` is the first element, `arr[4]` the last (for a 5-element array)
- `arr[i]` is literally syntactic sugar for `*(arr + i)` — this is why array indexing and pointer arithmetic are so closely related in C
- **C does not check array bounds.** Reading/writing `arr[10]` on a 5-element array compiles fine and is undefined behaviour at runtime — it may corrupt other memory silently. This is one of the most common sources of bugs in C
- Array size must be known at compile time for a normal (stack) array, unless using **VLAs** (Variable Length Arrays, C99, size known at runtime but still stack-allocated — risky for large sizes since the stack is limited)

### Arrays and pointers: what "decay" means
When an array is used in most expressions (passed to a function, assigned to a pointer), it **decays** into a pointer to its first element. The array itself still "knows" its full size (via `sizeof`), but the decayed pointer does not.

```c
void printSize(int arr[]) {
  printf("%zu\n", sizeof(arr)); // size of a pointer (e.g. 8), NOT the array!
}

int main(void) {
  int arr[10];
  printf("%zu\n", sizeof(arr)); // 40 -> real array size here
  printSize(arr);               // but decays once passed to the function
}
```
This is why functions that receive arrays almost always also receive an explicit size parameter.

### Multidimensional arrays
```c
int matrix[3][4]; // 3 rows, 4 columns, contiguous in memory (row-major order)
matrix[1][2] = 7;
```
Internally this is one contiguous block of `3 * 4 * sizeof(int)` bytes; `matrix[i][j]` is equivalent to accessing offset `i * 4 + j` from the base address.

## Strings
C has **no dedicated string type**. A string is just a `char` array terminated by a special sentinel byte, the **null terminator** `'\0'` (value 0).

```c
char greeting[] = "Hello"; // actually 6 bytes: 'H','e','l','l','o','\0'
char name[20] = "Diogo";   // reserves 20 bytes, uses 6 (5 chars + '\0'), rest unused
char *literal = "Hello";   // pointer to a string literal (read-only memory!)
```

- The null terminator is what tells string functions (`printf("%s", ...)`, `strlen`, etc.) where the string ends. Without it, those functions will keep reading past the array into whatever memory comes next — undefined behaviour
- `char name[20] = "Diogo";` is mutable; `char *literal = "Hello";` points to a **string literal**, which is typically stored in read-only memory — attempting `literal[0] = 'h';` is undefined behaviour (often a segfault)
- To get a *mutable* copy of a literal, copy it into an array: `char buf[] = "Hello";` (this one is fine to modify, it's a local array initialized from the literal, not the literal itself)

### Iterating a string
```c
char *s = "Hello";
for (int i = 0; s[i] != '\0'; i++) {
  putchar(s[i]);
}
```
or with a pointer directly:
```c
while (*s != '\0') {
  putchar(*s);
  s++;
}
```

### Strings and pointers
`char *s` and `char s[]` behave similarly when *reading*, but:
- `char s[] = "hi";` allocates a local mutable array
- `char *s = "hi";` points at a string literal — do not write through it

## Functions and Arguments
```c
int add(int a, int b) {
  return a + b;
}
```
- A function has a **return type**, a **name**, a **parameter list**, and a **body**
- If it returns nothing, the return type is `void`
- Must be either declared (**prototype**) or defined before it's used — otherwise the compiler doesn't know its signature. Prototypes are usually placed in a header file (`.h`) or at the top of the `.c` file:

```c
int add(int a, int b); // prototype/declaration
```

### Pass by value vs pass by "reference"
C is strictly **pass by value** — a function always receives a *copy* of the argument. To let a function modify the caller's variable, you must pass a **pointer** to it (simulating pass-by-reference):

```c
void increment(int x) {
  x++; // only modifies the local copy, has no effect outside
}

void incrementPtr(int *x) {
  (*x)++; // modifies the actual variable through its address
}

int main(void) {
  int n = 5;
  increment(n);
  printf("%d\n", n);    // still 5
  incrementPtr(&n);
  printf("%d\n", n);    // now 6
}
```
- Arrays are the one exception that "looks like" pass-by-reference, but it's actually because arrays decay to a pointer when passed — the function receives a pointer to the original data, not a copy of it
- `static` local variables inside a function retain their value between calls (they live in the Data segment, not the stack)

## Structs
A struct groups several variables (possibly of different types) under one name.

```c
struct Point {
  int x;
  int y;
};

struct Point p1 = {10, 20};
p1.x = 5;                 // dot operator for direct access
```

### Structs and pointers
```c
struct Point *pp = &p1;
pp->x = 15;      // arrow operator: shorthand for (*pp).x
(*pp).x = 15;    // equivalent, but arrow is idiomatic
```

### typedef with structs
```c
typedef struct {
  int x;
  int y;
} Point;

Point p2 = {1, 2}; // no need to write "struct Point" every time
```

### Nested and self-referential structs
Structs can contain other structs, or a pointer to their own type (essential for linked lists / trees):

```c
struct Node {
  int value;
  struct Node *next; // must be a pointer - a struct cannot contain itself by value (infinite size)
};
```

### Struct size and padding
`sizeof(struct)` is not always the sum of its members' sizes — the compiler may insert **padding** bytes between members for memory alignment (e.g. so a 4-byte `int` starts at an address multiple of 4). This matters for low-level memory layout work.

## Dynamic Memory
Memory allocated from the **heap** at runtime, whose size doesn't need to be known at compile time and whose lifetime is controlled explicitly by the programmer. Declared in `<stdlib.h>`.

| Function | Purpose |
|---|---|
| `malloc(size)` | Allocates `size` bytes, uninitialized (garbage content) |
| `calloc(n, size)` | Allocates space for `n` elements of `size` bytes each, zero-initialized |
| `realloc(ptr, newSize)` | Resizes a previous allocation, preserving existing content up to the smaller of the two sizes |
| `free(ptr)` | Releases memory back to the system |

```c
int n = 5;
int *arr = malloc(n * sizeof(int));
if (arr == NULL) {
  // allocation failed - always check this
  return 1;
}

for (int i = 0; i < n; i++) arr[i] = i * i;

arr = realloc(arr, 10 * sizeof(int)); // grow to 10 ints
if (arr == NULL) {
  // realloc failed - original block is still valid if this happens!
}

free(arr);
arr = NULL; // good practise: avoid a dangling pointer after freeing
```

- Always check the return value against `NULL` — allocation can fail (out of memory)
- Every successful `malloc`/`calloc`/`realloc` must eventually be matched with exactly one `free` — no more, no less
- After `free(ptr)`, `ptr` still holds the old address (a **dangling pointer**) unless you manually set it to `NULL`. Using it afterwards is undefined behaviour
- `realloc` **may move the block** to a new address if it can't grow in place — always reassign its return value; never do `realloc(ptr, size)` without capturing the result, or you risk a leak if it fails and returns `NULL` while overwriting your only reference to the original block

## NULL
`NULL` is a macro (defined in several standard headers, e.g. `<stddef.h>`) representing a **null pointer** — a pointer that intentionally points to nothing/nowhere valid. Its actual value is implementation-defined (commonly `0` or `(void*)0`), but should never be compared to `0` directly in your own reasoning — always use the `NULL` macro for clarity.

Common uses:
- Initializing a pointer that doesn't point anywhere yet: `int *p = NULL;`
- Checking if an allocation failed: `if (ptr == NULL)`
- Marking the end of a pointer array (e.g. `argv[argc]` is always `NULL`)
- Setting a pointer to `NULL` after `free`ing it, to avoid dangling-pointer bugs

Dereferencing a `NULL` pointer (`*p` when `p == NULL`) is undefined behaviour — on most systems it crashes immediately with a segmentation fault, which is actually useful for debugging (fails fast and loud).

## Command Line Arguments
`main` can receive arguments passed when the program is executed from a shell:

```c
int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  return 0;
}
```
- `argc` (argument count): number of arguments, **including the program name itself**
- `argv` (argument vector): array of C strings; `argv[0]` is the program's name/path, `argv[argc]` is always `NULL`
- All arguments arrive as strings — converting `argv[1]` to a number requires functions like `atoi`, `strtol`, etc.

```
$ ./program input.txt 42
argc = 3
argv[0] = "./program"
argv[1] = "input.txt"
argv[2] = "42"
```

## Environment Variables
Variables set in the shell/OS environment (e.g. `PATH`, `HOME`), accessible from a C program via `<stdlib.h>`:

```c
#include <stdlib.h>

char *home = getenv("HOME");
if (home != NULL) {
  printf("Home: %s\n", home);
}
```
- `getenv` returns `NULL` if the variable doesn't exist — always check
- The returned pointer refers to internal storage — don't modify it directly, and don't rely on it staying valid across further `getenv`/`setenv` calls
- `setenv(name, value, overwrite)` and `unsetenv(name)` (POSIX, `<stdlib.h>`) can modify the environment for the current process and its children
- Main can also receive the environment directly as a third (non-standard but widely supported) parameter: `int main(int argc, char *argv[], char *envp[])`

## getopt
A POSIX helper (`<unistd.h>`) for parsing command-line **flags** (like `-v`, `-o file`) in a standardized way.

```c
#include <unistd.h>

int opt;
int verbose = 0;
char *outfile = NULL;

// "vo:" means: -v takes no argument, -o requires an argument (the ':')
while ((opt = getopt(argc, argv, "vo:")) != -1) {
  switch (opt) {
    case 'v':
      verbose = 1;
      break;
    case 'o':
      outfile = optarg; // global variable set by getopt with the option's argument
      break;
    case '?':
      fprintf(stderr, "Unknown option\n");
      return 1;
  }
}
```
- `optarg`: global pointer set to the argument of the current option (when it takes one)
- `optind`: index of the next non-option argument in `argv`, useful to keep processing positional arguments after the flags
- A `:` after a letter in the options string means that option requires an argument; `::` (GNU extension) means the argument is optional

## C Headers
A header file (`.h`) contains declarations (function prototypes, macros, type/struct definitions) shared between multiple `.c` files, without containing the actual implementation.

### Common standard headers
| Header | Provides |
|---|---|
| `<stdio.h>` | Input/output: `printf`, `scanf`, file functions |
| `<stdlib.h>` | General utilities: `malloc`, `free`, `atoi`, `exit`, `getenv`, `rand` |
| `<string.h>` | String manipulation: `strlen`, `strcpy`, `strcmp`, etc. |
| `<math.h>` | Math functions: `sqrt`, `pow`, `sin`, etc. (link with `-lm` on gcc) |
| `<ctype.h>` | Character classification/conversion: `isdigit`, `toupper`, etc. |
| `<unistd.h>` | POSIX OS functions: `getopt`, `fork`, `read`/`write` (Linux/Unix only) |
| `<stddef.h>` | Core types like `size_t`, `NULL`, `ptrdiff_t` |
| `<limits.h>` / `<float.h>` | Min/max values for integer/floating types |
| `<time.h>` | Date/time functions |
| `<assert.h>` | `assert()` macro for debugging checks |

### Writing your own header
```c
// mylib.h
#ifndef MYLIB_H  // include guard: prevents the file being processed twice
#define MYLIB_H

int add(int a, int b); // just the declaration/prototype

#endif
```
```c
// mylib.c
#include "mylib.h"
int add(int a, int b) { return a + b; } // the actual implementation
```
```c
// main.c
#include "mylib.h"
int main(void) {
  printf("%d\n", add(2, 3));
}
```
Compile together with: `gcc main.c mylib.c -o program`

- `#include <...>` — searches system directories (standard headers)
- `#include "..."` — searches the local project directory first, then system directories (your own headers)
- **Include guards** (`#ifndef`/`#define`/`#endif`, or the non-standard-but-widely-supported `#pragma once`) prevent a header's contents being duplicated if it's included multiple times (directly or indirectly), which would otherwise cause "redefinition" compile errors

## size_t
`size_t` is an **unsigned integer type** defined in `<stddef.h>` (and pulled in by most headers that need it), used to represent sizes and counts — the size of any object in memory can be represented by it, by definition. It's what `sizeof` returns, and what functions like `strlen`, `malloc`, and array indices in the standard library use.

```c
size_t len = strlen("Hello");   // 5
int *arr = malloc(10 * sizeof(int));
for (size_t i = 0; i < len; i++) { ... }
```
- Its actual size is platform dependent (commonly 4 bytes on 32-bit systems, 8 bytes on 64-bit)
- Being **unsigned**, it can never be negative — this is a common bug source: `size_t x = 0; x--;` doesn't give you `-1`, it wraps around to a huge positive number (underflow). Be careful looping backwards with `size_t` counters
- Print it with the `%zu` format specifier (not `%d`, which is for `int`)

## Format Specifiers
Used by `printf`/`scanf` family to interpret arguments correctly.

| Specifier | Type |
|---|---|
| `%d` / `%i` | int |
| `%u` | unsigned int |
| `%ld` | long |
| `%lld` | long long |
| `%f` | float / double (printf promotes float to double automatically) |
| `%lf` | double (required explicitly for `scanf`, optional for `printf`) |
| `%c` | char |
| `%s` | string (char*) |
| `%p` | pointer (address) |
| `%x` / `%X` | unsigned int in hexadecimal |
| `%o` | unsigned int in octal |
| `%zu` | size_t |
| `%%` | literal percent sign |

```c
int age = 21;
double gpa = 15.7;
char grade = 'A';
printf("Age: %d, GPA: %.2f, Grade: %c\n", age, gpa, grade); // .2f = 2 decimal places
```
- The specifier **must match the argument's actual type**, or behaviour is undefined (the compiler often warns but still compiles) — this is a very common source of subtle bugs, especially mixing up `%d` and `%ld`, or `%f` and `%lf` in `scanf`
- With `scanf`, remember to pass the **address** of the variable (except for strings, which are already a pointer): `scanf("%d", &age);` vs `scanf("%s", name);`

## String Functions
All declared in `<string.h>`.

| Function | Purpose |
|---|---|
| `strlen(s)` | Returns length of string, **not counting** the null terminator |
| `strcpy(dest, src)` | Copies `src` into `dest` (unsafe — no bounds check) |
| `strncpy(dest, src, n)` | Copies at most `n` chars (safer, but doesn't guarantee null-termination if truncated!) |
| `strcat(dest, src)` | Appends `src` to the end of `dest` (unsafe) |
| `strncat(dest, src, n)` | Appends at most `n` chars from `src` |
| `strcmp(s1, s2)` | Returns 0 if equal, negative/positive depending on lexicographic order |
| `strncmp(s1, s2, n)` | Compares at most the first `n` characters |
| `strchr(s, c)` | Returns pointer to first occurrence of char `c` in `s`, or `NULL` |
| `strstr(s, sub)` | Returns pointer to first occurrence of substring `sub` in `s`, or `NULL` |
| `strtok(s, delim)` | Splits `s` into tokens separated by `delim` (modifies the original string!) |
| `memcpy(dest, src, n)` | Copies `n` raw bytes (works for any type, not just strings) |
| `memset(ptr, value, n)` | Fills `n` bytes with `value` (often used to zero out memory) |

```c
char dest[20];
strcpy(dest, "Hello");
strcat(dest, ", World");
printf("%s (%zu chars)\n", dest, strlen(dest));

if (strcmp("abc", "abc") == 0) {
  printf("Equal!\n");
}
```

## Buffer Safety
Because C doesn't check bounds automatically, buffer handling is a major source of bugs and security vulnerabilities. Some practises to reduce risk:

- Always allocate room for the null terminator: a string of `n` visible characters needs a buffer of at least `n + 1` bytes
- Prefer the bounded versions of functions (`strncpy`, `strncat`, `snprintf`) over the unbounded ones (`strcpy`, `strcat`, `sprintf`) — although even the bounded versions have quirks (e.g. `strncpy` won't null-terminate if the source is exactly `n` chars or longer)
- With `scanf("%s", buf)`, there is **no bound at all** by default — always specify a width: `scanf("%19s", buf)` for a 20-byte buffer (leaving room for `\0`), or use `fgets` instead, which does take an explicit size
- `fgets(buf, size, stdin)` is generally the safer way to read a line, since it takes the buffer size explicitly and stops at `size - 1` characters (but note it keeps the trailing `\n` if there's room, unlike `scanf`)
- When copying/concatenating, double-check the destination buffer is big enough for the *worst case*, not just the expected case

## Memory Errors
Common categories of bugs when managing memory manually — most are **undefined behaviour**, meaning the program might crash, might corrupt unrelated data silently, or might "seem to work" until it doesn't (which makes them notoriously hard to debug):

| Error | Description |
|---|---|
| **Memory leak** | Allocated memory (`malloc`/`calloc`) that is never `free`d — the program keeps using more memory over time |
| **Dangling pointer** | A pointer that still refers to memory that has been `free`d (or a stack variable that has gone out of scope) |
| **Double free** | Calling `free()` twice on the same pointer — corrupts the heap's internal bookkeeping |
| **Use-after-free** | Reading/writing through a pointer after the memory it points to has been freed |
| **Buffer overflow / overrun** | Writing past the end of an allocated block or array — can silently corrupt adjacent memory, or be exploited as a security vulnerability |
| **Buffer underrun** | Writing before the start of an allocated block (e.g. via a negative or wrapped-around index) |
| **Null pointer dereference** | Using `*p` or `p->x` when `p == NULL` |
| **Uninitialized memory read** | Reading a variable/`malloc`'d block before giving it a value — contains garbage |
| **Stack overflow** | Exhausting the stack space, typically from deep/infinite recursion or huge local arrays |

Good habits to avoid these:
- Every `malloc`/`calloc`/`realloc` should have a clear, single owner responsible for `free`ing it
- Set pointers to `NULL` immediately after freeing them
- Check every allocation's return value before using it
- Tools like **Valgrind** (`valgrind ./program`) or **AddressSanitizer** (`gcc -fsanitize=address`) are extremely useful for catching leaks, overflows and use-after-free during development — worth getting familiar with early

## Files
File I/O uses a `FILE *` handle from `<stdio.h>`.

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
  perror("fopen failed");
  return 1;
}

char line[100];
while (fgets(line, sizeof(line), fp) != NULL) {
  printf("%s", line);
}

fclose(fp);
```

### Modes
| Mode | Meaning |
|---|---|
| `"r"` | Read (file must exist) |
| `"w"` | Write (creates file, **truncates** if it already exists) |
| `"a"` | Append (creates file if it doesn't exist, writes at the end) |
| `"r+"` | Read and write (file must exist) |
| `"w+"` | Read and write (truncates existing file / creates new) |
| `"a+"` | Read and append |
| Add `b` (e.g. `"rb"`) | Binary mode — no text translation (relevant mostly on Windows for line endings) |

### Common functions
| Function | Purpose |
|---|---|
| `fopen(path, mode)` | Opens a file, returns `FILE *` or `NULL` on failure |
| `fclose(fp)` | Closes the file, flushing any buffered writes |
| `fgets(buf, size, fp)` | Reads a line (up to `size - 1` chars or a newline), safer than `gets` |
| `fputs(str, fp)` | Writes a string |
| `fprintf(fp, fmt, ...)` | Formatted write, like `printf` but to a file |
| `fscanf(fp, fmt, ...)` | Formatted read, like `scanf` but from a file |
| `fread(ptr, size, n, fp)` | Reads `n` items of `size` bytes each (binary data) |
| `fwrite(ptr, size, n, fp)` | Writes `n` items of `size` bytes each (binary data) |
| `feof(fp)` | Returns true if end-of-file has been reached |
| `ferror(fp)` | Returns true if an error occurred on the stream |
| `rewind(fp)` | Resets the file position back to the start |
| `fseek(fp, offset, whence)` | Moves the file position (SEEK_SET/SEEK_CUR/SEEK_END) |
| `ftell(fp)` | Returns the current file position |

- Always check `fopen`'s return for `NULL` before using it — a missing file, wrong permissions, etc. will cause it to fail
- Always `fclose` files when done — leaving them open can leak file descriptors and, for writes, risks losing buffered data that never got flushed to disk
- `perror("message")` prints your message followed by a description of the last error (`errno`), very useful for debugging failed I/O calls

## Standard Streams
Three streams are automatically open for every C program, also declared in `<stdio.h>`:

| Stream | Purpose | Default destination |
|---|---|---|
| `stdin` | Standard input | Keyboard (or a redirected file/pipe) |
| `stdout` | Standard output | Terminal (or a redirected file/pipe) |
| `stderr` | Standard error | Terminal, **unbuffered/line-buffered** and kept separate from `stdout` |

```c
fprintf(stdout, "Normal output\n"); // same as printf("Normal output\n");
fprintf(stderr, "Error: something went wrong\n");
```

- `stdout` is typically **line-buffered** when connected to a terminal (flushed on `\n`) but **fully buffered** when redirected to a file — this is why output can appear "out of order" with `stderr` if you're not careful
- `stderr` is used for error/diagnostic messages specifically so they can be separated from normal output, e.g. `./program > output.txt` still shows errors on the terminal, since only `stdout` was redirected
- Redirection in the shell: `./program < input.txt > output.txt 2> errors.txt` — `<` redirects `stdin`, `>` redirects `stdout`, `2>` redirects `stderr`
- Piping: `./program1 | ./program2` connects `program1`'s `stdout` to `program2`'s `stdin`
