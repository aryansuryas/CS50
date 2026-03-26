# CS50 — Week 2: Arrays

**Harvard University** · David J. Malan  
**Topic:** How compiled programs actually work, arrays, strings, command-line arguments, and writing your own encryption.

---

## Table of Contents

1. [Compiling — Under the Hood](#1-compiling--under-the-hood)
2. [Debugging](#2-debugging)
3. [Memory & Data Types (Sizes)](#3-memory--data-types-sizes)
4. [Arrays](#4-arrays)
5. [Strings](#5-strings)
6. [String Functions — `<string.h>`](#6-string-functions--stringh)
7. [Character Functions — `<ctype.h>`](#7-character-functions--ctypeh)
8. [Command-Line Arguments](#8-command-line-arguments)
9. [Exit Codes](#9-exit-codes)
10. [Cryptography](#10-cryptography)
11. [Problem Set 2 — Caesar & Substitution](#11-problem-set-2--caesar--substitution)
12. [Quick Reference Cheat Sheet](#12-quick-reference-cheat-sheet)

---

## 1. Compiling — Under the Hood

In Week 1, you ran `make hello` and it just worked. Week 2 opens up that black box.

When you compile a C program, **four separate steps** happen in sequence:

```
hello.c  (your source code)
    │
    ▼  Step 1 — PREPROCESSING
    │  Handles all lines starting with #
    │  #include <stdio.h>  →  pastes in the full stdio.h file
    │  #define X 10        →  replaces every X with 10
    │
    ▼  Step 2 — COMPILING
    │  Translates C code → Assembly language
    │  hello.s  (assembly file — human-readable-ish instructions)
    │
    ▼  Step 3 — ASSEMBLING
    │  Translates Assembly → Machine code (binary)
    │  hello.o  (object file — not yet runnable)
    │
    ▼  Step 4 — LINKING
       Combines your object file with library object files
       (stdio, cs50, math, etc.)
       
    hello  (final executable — ready to run)
```

### Running Each Step Manually with clang

```bash
# Step 1+2 — preprocess and compile only (produces assembly)
clang -S hello.c

# Step 1+2+3 — compile and assemble only (produces object file)
clang -c hello.c

# All 4 steps — full compilation
clang -o hello hello.c

# All 4 steps with CS50 library
clang -o hello hello.c -lcs50
```

### What is Assembly?

Assembly is a human-readable version of machine code. One C line can become many assembly instructions:

```c
// C code
int x = 5 + 3;
```

```asm
; Assembly equivalent (x86)
mov eax, 5
add eax, 3
mov [x], eax
```

You don't need to write or read assembly in CS50 — but knowing it exists helps you understand what the compiler is actually doing.

### What is Linking?

When you write `printf(...)`, the *definition* of printf isn't in your file — it's in the C standard library (`libc`). The **linker** takes your compiled object file and stitches it together with the compiled library files so `printf` actually works.

```bash
# The -l flag links a library
clang -o hello hello.c -lcs50    # link cs50 library
clang -o hello hello.c -lm       # link math library (for sqrt, pow, etc.)
```

---

## 2. Debugging

Debugging is the process of finding and fixing errors (bugs) in your code.

### Types of Errors

| Error Type | When It Appears | Example |
|---|---|---|
| **Compile-time error** | During compilation | Missing `;`, wrong type |
| **Runtime error** | While the program runs | Dividing by zero, accessing bad memory |
| **Logic error** | Program runs but gives wrong output | Off-by-one in a loop |

### Method 1 — `printf` Debugging

The simplest technique: print variable values at key points to trace what's happening.

```c
int total = 0;
for (int i = 0; i < 5; i++)
{
    total += i;
    printf("DEBUG: i=%i, total=%i\n", i, total);  // trace the loop
}
```

Always remove debug `printf` statements before submitting.

### Method 2 — `debug50` (CS50's Debugger)

`debug50` is a graphical debugger built on GDB. It lets you pause your program mid-execution and inspect everything.

```bash
# First, compile with debug symbols
make hello

# Then launch the debugger
debug50 ./hello
```

#### Key Debugger Concepts

| Concept | What It Means |
|---|---|
| **Breakpoint** | A line where execution pauses so you can inspect things |
| **Step Over** | Run the next line; if it's a function call, don't go inside |
| **Step Into** | Run the next line; if it's a function call, go inside it |
| **Step Out** | Finish the current function and return to the caller |
| **Watch Variable** | Monitor a variable's value as the program runs |

#### How to Use debug50

1. Click the line number in VS Code to set a **breakpoint** (a red dot appears)
2. Run `debug50 ./hello` in the terminal
3. Program pauses at your breakpoint
4. Inspect variables in the left panel
5. Use **Step Over** to run one line at a time
6. Watch how variables change with each step

### Method 3 — Rubber Duck Debugging

Explain your code **out loud**, line by line, as if teaching it to a rubber duck. The act of explaining forces you to slow down and often reveals the bug immediately. Sounds silly — works incredibly well.

### Reading Compiler Error Messages

```bash
$ make buggy
buggy.c:5:5: error: use of undeclared identifier 'mesage'
    mesage = "hello";
    ^
```

- `buggy.c` — the file with the error
- `:5` — line 5
- `:5` — column 5
- `error:` — the problem description
- The `^` points to exactly where the problem is

> **Rule:** Always fix the **first** error first. One bug often causes a cascade of fake errors below it.

### `check50` and `style50`

```bash
check50 cs50/problems/2024/x/caesar     # auto-grade your work
style50 caesar.c                         # check code formatting
```

---

## 3. Memory & Data Types (Sizes)

Every variable in C takes up a specific number of bytes in RAM. This week, we start paying attention to those sizes.

### Sizes of Common Types

```c
#include <stdio.h>

int main(void)
{
    printf("bool:   %zu bytes\n", sizeof(bool));
    printf("char:   %zu bytes\n", sizeof(char));
    printf("int:    %zu bytes\n", sizeof(int));
    printf("long:   %zu bytes\n", sizeof(long));
    printf("float:  %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
}
```

**Typical output (64-bit system):**

| Type | Size | Range |
|---|---|---|
| `bool` | 1 byte | `true` / `false` |
| `char` | 1 byte | −128 to 127 (or 0 to 255) |
| `int` | 4 bytes | −2,147,483,648 to 2,147,483,647 |
| `long` | 8 bytes | −9.2 × 10¹⁸ to 9.2 × 10¹⁸ |
| `float` | 4 bytes | ~7 significant decimal digits |
| `double` | 8 bytes | ~15 significant decimal digits |
| `string` | 8 bytes | (it's a pointer — more in Week 4) |

### `sizeof` Operator

`sizeof(type)` returns the number of bytes a type or variable occupies. The return type is `size_t` — use `%zu` to print it.

```c
sizeof(int)      // 4
sizeof(double)   // 8
sizeof(char)     // 1

int arr[5];
sizeof(arr)      // 20  (5 × 4 bytes)
```

---

## 4. Arrays

An **array** is a sequence of values of the **same type**, stored **back-to-back in memory**, accessed by a numeric index.

### Declaring an Array

```c
// type name[size];
int scores[3];          // uninitialized — values are garbage
int scores[3] = {72, 84, 91};   // initialized with values
```

### Accessing Elements

Arrays are **zero-indexed** — the first element is at index `0`, not `1`.

```c
int scores[3] = {72, 84, 91};

scores[0]   // 72  ← first element
scores[1]   // 84
scores[2]   // 91  ← last element (index = size - 1)
scores[3]   // ⚠️  UNDEFINED BEHAVIOR — out of bounds!
```

### Modifying Elements

```c
scores[0] = 100;   // change first element to 100
scores[2]++;       // increment third element by 1
```

### Iterating Over an Array

```c
int scores[5] = {72, 84, 91, 65, 88};
int n = 5;

// Print all scores
for (int i = 0; i < n; i++)
{
    printf("Score %i: %i\n", i + 1, scores[i]);
}
```

### Computing an Average

```c
int scores[3] = {72, 84, 91};
int sum = 0;

for (int i = 0; i < 3; i++)
{
    sum += scores[i];
}

float average = (float) sum / 3;
printf("Average: %.1f\n", average);   // Average: 82.3
```

### Arrays in Memory

Array elements live **contiguously** (next to each other) in RAM.

```
scores[3] = {72, 84, 91}

Memory address:   100  101  102  103  104  105  106  107  108  109  110  111
Content (bytes):  [  72 (int)   ] [  84 (int)   ] [  91 (int)   ]
                   scores[0]       scores[1]       scores[2]
```

Each `int` takes 4 bytes, so `scores[0]` is at address 100, `scores[1]` at 104, `scores[2]` at 108.

### Arrays are Fixed Size

Once declared, an array's size **cannot change**. You can't add elements. If you need dynamic sizing, that comes in later weeks with `malloc`.

### Passing Arrays to Functions

When you pass an array to a function, you also pass its length (C doesn't track array sizes automatically):

```c
float average(int arr[], int length);

int main(void)
{
    int scores[3] = {72, 84, 91};
    printf("%.1f\n", average(scores, 3));
}

float average(int arr[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += arr[i];
    return (float) sum / length;
}
```

---

## 5. Strings

In C, a **string** is an array of `char` values ending with a special **null terminator** character: `\0` (byte value 0).

```c
string name = "HI!";
```

In memory, this looks like:

```
Index:    0    1    2    3
Char:    'H'  'I'  '!'  '\0'
Value:    72   73   33    0
```

The `\0` tells C functions "this is where the string ends." Without it, functions like `printf` wouldn't know when to stop reading.

> **Key insight:** A string of length 3 actually takes **4 bytes** — 3 characters + 1 null terminator.

### Strings are Character Arrays

```c
string name = "HI!";
// is the same as:
char name[] = {'H', 'I', '!', '\0'};
```

You can access individual characters:

```c
string name = "Alice";
printf("%c\n", name[0]);   // A
printf("%c\n", name[1]);   // l
printf("%c\n", name[4]);   // e
printf("%c\n", name[5]);   // \0  (null terminator)
```

### Iterating Over a String

```c
string s = "Hello";

for (int i = 0; s[i] != '\0'; i++)
{
    printf("%c\n", s[i]);
}
```

Or more commonly with `strlen`:

```c
#include <string.h>

int n = strlen(s);
for (int i = 0; i < n; i++)
{
    printf("%c\n", s[i]);
}
```

### String Length vs Array Size

```c
string name = "Alice";
// strlen(name) = 5   ← number of actual characters
// array size   = 6   ← 5 chars + \0
```

Always use `strlen` to get the length of a string. Don't hardcode it.

---

## 6. String Functions — `<string.h>`

Include with `#include <string.h>`

### `strlen` — String Length

```c
#include <string.h>

string s = "Hello";
int len = strlen(s);   // 5
```

### `strcmp` — Compare Two Strings

Returns `0` if strings are equal, non-zero if they differ.

```c
strcmp("apple", "apple")   // 0     — equal
strcmp("apple", "banana")  // < 0   — "apple" comes first alphabetically
strcmp("banana", "apple")  // > 0   — "banana" comes after
```

> ⚠️ **Never use `==` to compare strings.** `==` compares memory addresses (pointers), not contents. Always use `strcmp`.

```c
string answer = get_string("Answer: ");

if (strcmp(answer, "yes") == 0)
{
    printf("Confirmed!\n");
}
```

### `strcpy` — Copy a String

```c
char dest[10];
strcpy(dest, "Hello");   // copies "Hello" into dest
```

> ⚠️ Make sure the destination array is large enough, or you'll overflow memory.

### `strcat` — Concatenate Strings

```c
char result[20] = "Hello";
strcat(result, " World");
// result is now "Hello World"
```

### `strchr` — Find a Character in a String

```c
string s = "Hello";
char *pos = strchr(s, 'l');   // pointer to first 'l' in "Hello"
```

### `strstr` — Find a Substring

```c
string s = "Hello World";
char *pos = strstr(s, "World");   // pointer to "World" within s
```

---

## 7. Character Functions — `<ctype.h>`

Include with `#include <ctype.h>`

These functions work on individual `char` values.

### Testing Characters

| Function | Returns true if... | Example |
|---|---|---|
| `isupper(c)` | `c` is uppercase A–Z | `isupper('A')` → true |
| `islower(c)` | `c` is lowercase a–z | `islower('a')` → true |
| `isalpha(c)` | `c` is a letter (A–Z or a–z) | `isalpha('g')` → true |
| `isdigit(c)` | `c` is a digit 0–9 | `isdigit('5')` → true |
| `isalnum(c)` | `c` is a letter or digit | `isalnum('3')` → true |
| `isspace(c)` | `c` is whitespace (space, tab, newline) | `isspace(' ')` → true |
| `ispunct(c)` | `c` is punctuation | `ispunct('!')` → true |

### Converting Characters

| Function | What It Does | Example |
|---|---|---|
| `toupper(c)` | Converts to uppercase | `toupper('a')` → `'A'` |
| `tolower(c)` | Converts to lowercase | `tolower('A')` → `'a'` |

> These return `int`, not `char` — cast if needed: `(char) toupper(c)`

### Example — Capitalize All Letters in a String

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Input: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}
```

### How `toupper` Works Internally

ASCII values of letters:

```
'A' = 65    'a' = 97
'B' = 66    'b' = 98
...
'Z' = 90    'z' = 122
```

The difference between any uppercase and its lowercase is always **32**.

So `toupper` essentially does: `if (islower(c)) return c - 32;`

This is exactly the kind of math you use in the Caesar cipher (Problem Set 2).

---

## 8. Command-Line Arguments

Programs can receive input directly from the terminal when launched — not just via `get_string` prompts.

### The Full Signature of `main`

```c
int main(int argc, string argv[])
```

| Variable | Type | Meaning |
|---|---|---|
| `argc` | `int` | **Arg**ument **c**ount — number of words typed (includes program name) |
| `argv` | `string[]` | **Arg**ument **v**ector — array of those words as strings |

### Example

```bash
$ ./greet Alice 25
```

| `argv` index | Value |
|---|---|
| `argv[0]` | `"./greet"` |
| `argv[1]` | `"Alice"` |
| `argv[2]` | `"25"` |
| `argc` | `3` |

### Using argc and argv

```c
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./greet name\n");
        return 1;
    }

    printf("Hello, %s!\n", argv[1]);
    return 0;
}
```

```bash
$ ./greet Alice
Hello, Alice!

$ ./greet
Usage: ./greet name
```

### Converting Strings to Numbers

`argv` values are always **strings** — even if they look like numbers.

```c
argv[1]       // this is "42" — a string, not the number 42
```

To convert to an integer, use `atoi` (from `<stdlib.h>`):

```c
#include <stdlib.h>

int key = atoi(argv[1]);   // converts "42" → 42
```

| Function | Converts | Header |
|---|---|---|
| `atoi(s)` | string → int | `<stdlib.h>` |
| `atof(s)` | string → double | `<stdlib.h>` |
| `atol(s)` | string → long | `<stdlib.h>` |

> ⚠️ `atoi` returns `0` for non-numeric strings — it does not report errors. Use `strtol` for robust conversion in production code.

---

## 9. Exit Codes

When a program finishes, it returns an **exit code** to the operating system.

```c
return 0;   // success — everything went fine
return 1;   // error — something went wrong
```

### Conventions

| Code | Meaning |
|---|---|
| `0` | Success |
| `1` | General error |
| `2` | Misuse of command (wrong arguments) |
| Any non-zero | Some kind of failure |

### Checking Exit Codes in the Terminal

```bash
$ ./hello
Hello, World!
$ echo $?
0             ← exit code was 0 (success)

$ ./hello extraarg
Usage: ./hello
$ echo $?
1             ← exit code was 1 (error)
```

### Why Exit Codes Matter

Shell scripts and other programs can check exit codes to decide what to do next:

```bash
if ./my_program; then
    echo "Program succeeded"
else
    echo "Program failed"
fi
```

`check50` also uses exit codes to determine if your program behaved correctly.

---

## 10. Cryptography

**Cryptography** is the science of securing information — transforming readable data (plaintext) into unreadable data (ciphertext) so only authorized parties can read it.

### Key Terms

| Term | Definition |
|---|---|
| **Plaintext** | The original, readable message |
| **Ciphertext** | The encrypted, scrambled message |
| **Cipher** | The algorithm used to encrypt/decrypt |
| **Key** | A piece of information that controls the cipher |
| **Encryption** | Plaintext → Ciphertext |
| **Decryption** | Ciphertext → Plaintext |

```
PLAINTEXT  ──[cipher + key]──►  CIPHERTEXT
CIPHERTEXT ──[cipher + key]──►  PLAINTEXT
```

### Caesar Cipher

One of the oldest ciphers, used by Julius Caesar. Each letter is **shifted** a fixed number of places in the alphabet.

**Key = 3:**

```
A → D      N → Q
B → E      O → R
C → F  ...
```

**Example:**

```
Plaintext:   H  I
ASCII:       72 73
Shift by 3:  75 76
Ciphertext:  K  L
```

**The Formula:**

```
ciphertext[i] = (plaintext[i] - 'a' + key) % 26 + 'a'   // for lowercase
ciphertext[i] = (plaintext[i] - 'A' + key) % 26 + 'A'   // for uppercase
```

Breaking it down:

```c
char c = 'H';
int key = 3;

// Step 1: Shift to 0-based index (0=A, 1=B, ..., 25=Z)
int index = c - 'A';         // 'H' - 'A' = 72 - 65 = 7

// Step 2: Add the key and wrap around with modulo
int shifted = (index + key) % 26;   // (7 + 3) % 26 = 10

// Step 3: Convert back to ASCII
char encrypted = shifted + 'A';     // 10 + 65 = 75 = 'K'
```

**Why `% 26`?** The alphabet has 26 letters. When you shift past `Z`, you wrap around to `A`. Modulo handles this perfectly:

```
'Y' (24) + key 3 = 27 → 27 % 26 = 1 → 'B'   ✓ wraps correctly
'Z' (25) + key 3 = 28 → 28 % 26 = 2 → 'C'   ✓ wraps correctly
```

### Full Caesar Cipher Implementation

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Validate argument count
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate key is a non-negative integer
    int key = atoi(argv[1]);
    if (key < 0)
    {
        printf("Key must be non-negative.\n");
        return 1;
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    // Encrypt character by character
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            printf("%c", (c - 'A' + key) % 26 + 'A');
        }
        else if (islower(c))
        {
            printf("%c", (c - 'a' + key) % 26 + 'a');
        }
        else
        {
            printf("%c", c);   // non-alphabetic: don't change
        }
    }

    printf("\n");
    return 0;
}
```

**Test:**
```bash
$ ./caesar 13
plaintext:  Hello
ciphertext: Uryyb
```

### Substitution Cipher

A generalization of Caesar. Instead of shifting by a fixed amount, you provide a 26-letter **key** that maps each letter to a different one.

```
Key:       NQXPOMAFTRHLZYBDKVGUCESWIJ
Alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ

A → N
B → Q
C → X
...
```

**Rules for a valid substitution key:**

- Exactly 26 characters long
- Contains each letter A–Z exactly once (no repeats, no missing letters)
- Case-insensitive

---

## 11. Problem Set 2 — Caesar & Substitution

### Caesar — Step-by-Step Approach

```
1. Check argc == 2, else print usage and return 1
2. Validate argv[1] contains only digits (use isdigit())
3. Convert argv[1] to int with atoi()
4. Get plaintext with get_string()
5. Loop through each character:
   a. If uppercase: encrypt with (c - 'A' + key) % 26 + 'A'
   b. If lowercase: encrypt with (c - 'a' + key) % 26 + 'a'
   c. Otherwise: print unchanged
6. Print newline, return 0
```

**Validating that the key is all digits:**

```c
for (int i = 0, n = strlen(argv[1]); i < n; i++)
{
    if (!isdigit(argv[1][i]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
```

### Substitution — Step-by-Step Approach

```
1. Check argc == 2, else print usage and return 1
2. Validate the key:
   a. Length must be exactly 26
   b. All characters must be alphabetic (isalpha())
   c. No character may repeat (check for duplicates)
3. Get plaintext with get_string()
4. Loop through each character:
   a. If uppercase: find its index (c - 'A'), look up key[index], preserve case
   b. If lowercase: find its index (c - 'a'), look up key[index], preserve case
   c. Otherwise: print unchanged
5. Print newline, return 0
```

### Common Mistakes

| Mistake | Fix |
|---|---|
| Using `==` to compare strings | Use `strcmp()` |
| Forgetting `% 26` causes letters to go past `Z` | Always apply `% 26` before adding back `'A'` or `'a'` |
| Not preserving case in substitution | Check `isupper`/`islower` and apply `toupper`/`tolower` to key character |
| Accepting a negative key | Validate `key >= 0` |
| Off-by-one — printing `\0` | Loop `while (s[i] != '\0')` or use `strlen` as the bound |

---

## 12. Quick Reference Cheat Sheet

### Array Syntax

```c
// Declare
int arr[5];
int arr[5] = {1, 2, 3, 4, 5};

// Access (zero-indexed)
arr[0]         // first element
arr[n - 1]     // last element

// Iterate
for (int i = 0; i < n; i++)
    printf("%i\n", arr[i]);

// Length: C doesn't track it — you must track it yourself
int n = 5;     // or use sizeof(arr) / sizeof(arr[0]) for stack arrays
```

### String Tricks

```c
// Length
int len = strlen(s);

// Iterate
for (int i = 0; s[i] != '\0'; i++) { ... }
for (int i = 0, n = strlen(s); i < n; i++) { ... }

// Compare
strcmp(s1, s2) == 0    // equal

// Convert case
toupper(c)   tolower(c)

// Check type
isalpha(c)   isdigit(c)   isupper(c)   islower(c)
```

### Caesar Formula

```c
// Uppercase
(c - 'A' + key) % 26 + 'A'

// Lowercase
(c - 'a' + key) % 26 + 'a'
```

### Compilation Steps

```bash
make hello                    # full compilation (CS50 shorthand)
clang -o hello hello.c        # manual compilation
clang -o hello hello.c -lcs50 # with CS50 library
clang -o hello hello.c -lm    # with math library
```

### Important Headers

| Header | Key Functions |
|---|---|
| `<stdio.h>` | `printf`, `scanf` |
| `<cs50.h>` | `get_string`, `get_int`, etc. |
| `<string.h>` | `strlen`, `strcmp`, `strcpy`, `strcat` |
| `<ctype.h>` | `toupper`, `tolower`, `isalpha`, `isdigit` |
| `<stdlib.h>` | `atoi`, `atof`, `malloc`, `free` |

### Key Rules to Remember

| Rule | Why |
|---|---|
| Arrays are zero-indexed | `arr[0]` is first, `arr[n-1]` is last |
| Strings end with `\0` | `strlen` of `"Hi"` is 2, but it occupies 3 bytes |
| Never compare strings with `==` | Use `strcmp(s1, s2) == 0` |
| Always validate `argc` before using `argv[1]` | `argv[1]` doesn't exist if no argument was given |
| Fix the first compiler error first | Later errors are often caused by the first one |

---

*CS50 Week 2 Notes · Harvard University · David J. Malan*
