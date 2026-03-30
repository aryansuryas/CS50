# CS50 — Week 6: Python

**Harvard University** · David J. Malan  
**Topic:** Transitioning from C to Python — syntax, types, functions, libraries, file I/O, and re-implementing everything you built in C, but faster and cleaner.

---

## Table of Contents

1. [Python vs C — The Big Picture](#1-python-vs-c--the-big-picture)
2. [Running Python](#2-running-python)
3. [Variables and Types](#3-variables-and-types)
4. [Printing and Input](#4-printing-and-input)
5. [Conditionals](#5-conditionals)
6. [Loops](#6-loops)
7. [Functions](#7-functions)
8. [Exceptions and Error Handling](#8-exceptions-and-error-handling)
9. [Strings in Python](#9-strings-in-python)
10. [Lists](#10-lists)
11. [Tuples](#11-tuples)
12. [Dictionaries](#12-dictionaries)
13. [Sets](#13-sets)
14. [Command-Line Arguments — sys.argv](#14-command-line-arguments--sysargv)
15. [File I/O in Python](#15-file-io-in-python)
16. [Python Libraries and Modules](#16-python-libraries-and-modules)
17. [Regular Expressions — re](#17-regular-expressions--re)
18. [Object-Oriented Programming in Python](#18-object-oriented-programming-in-python)
19. [Re-implementing CS50 Problems in Python](#19-re-implementing-cs50-problems-in-python)
20. [Problem Set 6 Overview](#20-problem-set-6-overview)
21. [Quick Reference Cheat Sheet](#21-quick-reference-cheat-sheet)

---

## 1. Python vs C — The Big Picture

Python is a **high-level, interpreted, dynamically-typed** language. Compared to C, it trades some performance for an enormous gain in developer speed, readability, and built-in functionality.

### Key Philosophical Differences

| Concept | C | Python |
|---|---|---|
| **Type system** | Static — types declared at compile time | Dynamic — types inferred at runtime |
| **Memory** | Manual — you call `malloc` and `free` | Automatic — garbage collector handles it |
| **Compilation** | Compiled to machine code before running | Interpreted line by line at runtime |
| **Syntax** | Verbose, explicit, semicolons, braces | Concise, whitespace-based, no braces |
| **Error detection** | Mostly at compile time | Often at runtime |
| **Speed** | Very fast | Slower (10–100x) but rarely matters |
| **Standard library** | Small — you include what you need | Enormous — "batteries included" |
| **Use cases** | Systems, OS, embedded, performance | Web, data science, scripting, AI, automation |

### Side-by-Side: Hello World

```c
// C — hello.c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

```python
# Python — hello.py
print("Hello, World!")
```

Python has **no** `#include`, **no** `int main(void)`, **no** semicolons, **no** return statement required, **no** compile step.

### How Python Works Internally

```
hello.py  (your source code)
    │
    ▼  Python Interpreter (CPython)
    │  Compiles to bytecode (.pyc) — happens automatically
    │
    ▼  Python Virtual Machine (PVM)
       Executes the bytecode

No separate compile step needed — just run: python hello.py
```

---

## 2. Running Python

### Running a Python File

```bash
python hello.py
# or on some systems:
python3 hello.py
```

### The Python REPL (Interactive Mode)

Type `python` or `python3` with no arguments to enter the **Read-Eval-Print Loop** — great for experimenting:

```bash
$ python3
>>> print("Hello")
Hello
>>> 2 + 3
5
>>> x = 10
>>> x * 2
20
>>> exit()
```

### Running in CS50's Codespace

```bash
python hello.py        # run the file
python -i hello.py     # run then drop into interactive mode
```

### Python Shebangs (making scripts executable)

```python
#!/usr/bin/env python3
print("Hello!")
```

```bash
chmod +x hello.py
./hello.py
```

---

## 3. Variables and Types

### No Type Declarations Needed

```python
x = 50          # int
y = 3.14        # float
name = "Alice"  # str
active = True   # bool (capital T/F!)
nothing = None  # NoneType (like NULL in C)
```

Python figures out the type from the value assigned. Types are associated with **values**, not variable names.

### Checking Types

```python
type(50)        # <class 'int'>
type(3.14)      # <class 'float'>
type("hello")   # <class 'str'>
type(True)      # <class 'bool'>
type(None)      # <class 'NoneType'>
```

### Dynamic Typing

A variable can change its type at any time:

```python
x = 10       # x is an int
x = "hello"  # x is now a str — perfectly valid in Python
x = [1, 2]   # x is now a list
```

### Python's Built-in Types

| Type | Example | C Equivalent |
|---|---|---|
| `int` | `42`, `-7`, `1000000` | `int`, `long` |
| `float` | `3.14`, `-0.5` | `float`, `double` |
| `str` | `"hello"`, `'world'` | `string` (char array) |
| `bool` | `True`, `False` | `bool` |
| `list` | `[1, 2, 3]` | array |
| `tuple` | `(1, 2, 3)` | struct (sort of) |
| `dict` | `{"key": "val"}` | hash table / struct |
| `set` | `{1, 2, 3}` | — |
| `None` | `None` | `NULL` |

### Type Conversion (Casting)

```python
int("42")       # "42" → 42
float("3.14")   # "3.14" → 3.14
str(100)        # 100 → "100"
bool(0)         # 0 → False
bool(1)         # 1 → True
bool("")        # "" → False  (empty string is falsy)
bool("hi")      # "hi" → True
```

---

## 4. Printing and Input

### `print()`

```python
print("Hello, World!")          # Hello, World!
print("Score:", 95)             # Score: 95
print("x =", 10, "y =", 20)    # x = 10 y = 20

# f-strings (formatted string literals) — most modern, preferred
name = "Alice"
age = 20
print(f"Hello, {name}! You are {age} years old.")
# Hello, Alice! You are 20 years old.

# Formatting numbers
pi = 3.14159
print(f"Pi is approximately {pi:.2f}")  # Pi is approximately 3.14

# Print with custom separator and end
print("a", "b", "c", sep="-")   # a-b-c
print("Hello", end="")          # no newline at end
print("World")                  # HelloWorld
```

### `input()`

```python
name = input("What is your name? ")
age  = input("How old are you? ")   # always returns a STRING

# Must convert if you want a number:
age = int(input("How old are you? "))
gpa = float(input("What is your GPA? "))
```

> ⚠️ `input()` **always returns a string**. If you need a number, explicitly convert with `int()` or `float()`.

### f-Strings in Depth

```python
x = 42
print(f"{x}")           # 42
print(f"{x:05d}")       # 00042  (padded with zeros, width 5)
print(f"{x:>10}")       # right-align in width 10
print(f"{x:<10}")       # left-align in width 10
print(f"{x:^10}")       # center in width 10
print(f"{3.14159:.3f}") # 3.142  (3 decimal places)
print(f"{1000000:,}")   # 1,000,000  (comma separator)
```

---

## 5. Conditionals

### Basic if / elif / else

```python
score = 85

if score >= 90:
    print("Grade: A")
elif score >= 80:
    print("Grade: B")
elif score >= 70:
    print("Grade: C")
else:
    print("Grade: F")
```

Key differences from C:
- **No parentheses** around the condition (optional but discouraged)
- **Colon `:` at end** of each condition line
- **Indentation** (4 spaces) defines the block — **no curly braces**

### Ternary (Inline Conditional)

```python
# Python syntax: value_if_true if condition else value_if_false
result = "Pass" if score >= 60 else "Fail"
label  = "even" if x % 2 == 0 else "odd"
```

### Logical Operators — English Words

```python
# C uses &&, ||, !
# Python uses and, or, not

if age >= 18 and age < 65:
    print("Working age")

if name == "Alice" or name == "Bob":
    print("Known user")

if not active:
    print("Inactive")
```

### Comparison Operators

```python
x == y    # equal
x != y    # not equal
x > y     # greater than
x < y     # less than
x >= y    # greater than or equal
x <= y    # less than or equal

# Python bonus — chained comparisons!
0 <= score <= 100   # True if score is between 0 and 100 inclusive
```

### Truthiness and Falsiness

In Python, many values are **falsy** (treated as False in a boolean context):

```python
# Falsy values:
False, 0, 0.0, "", [], {}, (), None, set()

# Everything else is truthy

# Examples
if name:            # True if name is not empty string
    print("Has name")

if scores:          # True if scores list is not empty
    print("Has scores")

if not errors:      # True if errors list is empty
    print("No errors")
```

### `match` Statement (Python 3.10+ — like switch)

```python
command = input("Enter command: ")

match command:
    case "quit":
        print("Quitting...")
    case "help":
        print("Commands: quit, help, run")
    case "run":
        print("Running!")
    case _:                    # default
        print("Unknown command")
```

---

## 6. Loops

### `while` Loop

```python
i = 0
while i < 5:
    print(i)
    i += 1
```

### `for` Loop — Iterating Over a Sequence

Python's `for` loop is much more powerful than C's — it iterates directly over items:

```python
# Iterate over a list
for name in ["Alice", "Bob", "Charlie"]:
    print(name)

# Iterate over a string (character by character)
for char in "hello":
    print(char)

# Iterate over a range of numbers
for i in range(5):          # 0, 1, 2, 3, 4
    print(i)

for i in range(1, 6):       # 1, 2, 3, 4, 5
    print(i)

for i in range(0, 10, 2):   # 0, 2, 4, 6, 8 (step=2)
    print(i)

for i in range(5, 0, -1):   # 5, 4, 3, 2, 1 (count down)
    print(i)
```

### `range()` in Detail

```python
range(stop)           # 0 to stop-1
range(start, stop)    # start to stop-1
range(start, stop, step)  # start to stop-1, increment by step

list(range(5))        # [0, 1, 2, 3, 4]
list(range(2, 8))     # [2, 3, 4, 5, 6, 7]
list(range(0, 10, 3)) # [0, 3, 6, 9]
```

### `enumerate()` — Index + Value

```python
names = ["Alice", "Bob", "Charlie"]

for i, name in enumerate(names):
    print(f"{i}: {name}")
# 0: Alice
# 1: Bob
# 2: Charlie
```

### `break` and `continue`

```python
# break — exit the loop entirely
for i in range(10):
    if i == 5:
        break
    print(i)       # prints 0 1 2 3 4

# continue — skip to next iteration
for i in range(10):
    if i % 2 == 0:
        continue
    print(i)       # prints 1 3 5 7 9
```

### Nested Loops — Mario Pyramid

```python
height = 4

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)
```

Output:
```
   #
  ##
 ###
####
```

Python string multiplication makes this far cleaner than C!

---

## 7. Functions

### Defining a Function

```python
def function_name(parameter1, parameter2):
    # body — indented 4 spaces
    return value   # optional
```

### Basic Examples

```python
def greet(name):
    print(f"Hello, {name}!")

def square(n):
    return n * n

def add(a, b):
    return a + b

# Calling functions
greet("Alice")        # Hello, Alice!
result = square(5)    # 25
total  = add(3, 4)    # 7
```

### Default Parameters

```python
def greet(name, greeting="Hello"):
    print(f"{greeting}, {name}!")

greet("Alice")               # Hello, Alice!
greet("Bob", "Good morning") # Good morning, Bob!
```

### Keyword Arguments

```python
def describe(name, age, city):
    print(f"{name} is {age} from {city}")

# Call with keyword args in any order
describe(age=20, city="Boston", name="Alice")
```

### Returning Multiple Values

Python functions can return multiple values as a **tuple**:

```python
def min_max(numbers):
    return min(numbers), max(numbers)

lo, hi = min_max([3, 1, 4, 1, 5, 9])
print(lo, hi)   # 1 9
```

### `*args` — Variable Number of Arguments

```python
def total(*args):
    return sum(args)

total(1, 2, 3)        # 6
total(10, 20, 30, 40) # 100
```

### `**kwargs` — Keyword Arguments as Dictionary

```python
def display(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

display(name="Alice", age=20, city="Boston")
```

### Functions are First-Class Objects

In Python, functions can be assigned to variables, passed to other functions, and returned from functions:

```python
def square(x):
    return x * x

f = square        # assign function to variable
print(f(5))       # 25

# Pass function as argument
def apply(func, value):
    return func(value)

apply(square, 4)  # 16
```

### Lambda Functions (Anonymous Functions)

```python
square = lambda x: x * x
add    = lambda x, y: x + y

square(5)   # 25
add(3, 4)   # 7

# Common use: as a key for sorting
names = ["Charlie", "Alice", "Bob"]
names.sort(key=lambda name: name[0])   # sort by first letter
```

### Scope — Local vs Global

```python
x = 10   # global

def foo():
    x = 20      # local — does NOT change the global x
    print(x)    # 20

foo()
print(x)        # 10 — unchanged

# To modify a global variable inside a function:
def bar():
    global x
    x = 99

bar()
print(x)   # 99
```

---

## 8. Exceptions and Error Handling

In C, you handle errors with return codes and if statements. Python uses **exceptions**.

### What is an Exception?

When something goes wrong, Python **raises** an exception — an error object that interrupts normal program flow. If not caught, it prints an error and stops the program.

```python
int("abc")       # ValueError: invalid literal for int()
10 / 0           # ZeroDivisionError: division by zero
"hi"[10]         # IndexError: string index out of range
int(None)        # TypeError: int() argument must be a string
open("nope.txt") # FileNotFoundError: No such file or directory
```

### `try` / `except`

```python
try:
    x = int(input("Enter a number: "))
    print(f"You entered: {x}")
except ValueError:
    print("That's not a valid number!")
```

### Catching Multiple Exceptions

```python
try:
    result = int(input("Number: ")) / int(input("Divisor: "))
    print(result)
except ValueError:
    print("Please enter integers only")
except ZeroDivisionError:
    print("Cannot divide by zero")
```

### `except Exception as e` — Catch All + See the Error

```python
try:
    x = int(input("Number: "))
except Exception as e:
    print(f"Error: {e}")
```

### `else` and `finally` Clauses

```python
try:
    x = int(input("Number: "))
except ValueError:
    print("Invalid!")
else:
    # runs only if NO exception occurred
    print(f"Success: {x}")
finally:
    # runs ALWAYS — exception or not
    print("Done.")
```

### `raise` — Throwing Your Own Exceptions

```python
def divide(a, b):
    if b == 0:
        raise ValueError("Divisor cannot be zero")
    return a / b

try:
    divide(10, 0)
except ValueError as e:
    print(e)   # Divisor cannot be zero
```

### Common Python Exceptions

| Exception | When Raised |
|---|---|
| `ValueError` | Wrong type/value for a function (`int("abc")`) |
| `TypeError` | Operation on incompatible types |
| `IndexError` | List/string index out of range |
| `KeyError` | Dictionary key doesn't exist |
| `ZeroDivisionError` | Division or modulo by zero |
| `FileNotFoundError` | File doesn't exist |
| `AttributeError` | Object doesn't have that attribute |
| `NameError` | Variable used before being defined |
| `ImportError` | Module not found |
| `OverflowError` | Arithmetic result too large |

---

## 9. Strings in Python

Python strings are **immutable** sequences of Unicode characters. They are much more powerful than C's char arrays.

### Creating Strings

```python
s1 = "Hello"         # double quotes
s2 = 'World'         # single quotes — same thing
s3 = """Multi
line"""              # triple quotes — spans multiple lines
s4 = f"Hello, {name}"  # f-string
```

### String Operations

```python
s = "Hello, World!"

len(s)            # 13 — length
s[0]              # 'H' — indexing (0-based)
s[-1]             # '!' — negative index from end
s[7:12]           # 'World' — slicing [start:end] (end exclusive)
s[7:]             # 'World!' — slice to end
s[:5]             # 'Hello' — slice from start
s[::2]            # every other character
s[::-1]           # reversed: '!dlroW ,olleH'

s.upper()         # 'HELLO, WORLD!'
s.lower()         # 'hello, world!'
s.strip()         # remove leading/trailing whitespace
s.lstrip()        # remove leading whitespace
s.rstrip()        # remove trailing whitespace
s.replace("World", "Python")  # 'Hello, Python!'
s.split(", ")     # ['Hello', 'World!'] — split into list
", ".join(["a","b","c"])      # 'a, b, c' — join list into string
s.startswith("Hello")  # True
s.endswith("!")        # True
s.find("World")        # 7 — first index of substring (-1 if not found)
s.count("l")           # 3 — count occurrences
s.isalpha()            # False (has comma and space)
s.isdigit()            # False
s.isalnum()            # False
```

### String Concatenation

```python
# + operator
greeting = "Hello" + ", " + "World"

# * operator — repeat
print("ha" * 3)    # hahaha
print("-" * 20)    # --------------------

# f-string (preferred)
name = "Alice"
greeting = f"Hello, {name}!"
```

### String Immutability

Unlike C char arrays, Python strings **cannot be modified** in place:

```python
s = "hello"
s[0] = "H"    # ❌ TypeError: 'str' object does not support item assignment

# Instead, create a new string:
s = "H" + s[1:]    # ✅ 'Hello'
```

### String Slicing

```python
s = "Hello, World!"
#    0123456789...

s[0:5]    # "Hello"  — indices 0,1,2,3,4
s[7:12]   # "World"  — indices 7,8,9,10,11
s[7:]     # "World!" — from 7 to end
s[:5]     # "Hello"  — from start to 4
s[-6:-1]  # "World"  — last 6 chars, stop before last

# Step
s[::1]    # "Hello, World!"    — every char
s[::2]    # "Hlo ol!"          — every other char
s[::-1]   # "!dlroW ,olleH"   — reversed
```

---

## 10. Lists

A Python **list** is like a C array, but:
- **Dynamically sized** — grows and shrinks automatically
- **Mixed types** — can hold any combination of types
- **Built-in methods** — sort, search, add, remove, etc.

### Creating Lists

```python
numbers = [1, 2, 3, 4, 5]
names   = ["Alice", "Bob", "Charlie"]
mixed   = [1, "two", 3.0, True, None]
empty   = []
nested  = [[1, 2], [3, 4], [5, 6]]
```

### Accessing and Modifying

```python
numbers = [10, 20, 30, 40, 50]

numbers[0]       # 10 — first element
numbers[-1]      # 50 — last element
numbers[1:3]     # [20, 30] — slice
numbers[0] = 99  # modify element
```

### List Methods

```python
numbers = [3, 1, 4, 1, 5]

numbers.append(9)          # add to end: [3, 1, 4, 1, 5, 9]
numbers.insert(2, 99)      # insert at index 2: [3, 1, 99, 4, 1, 5, 9]
numbers.remove(1)          # remove first occurrence of 1
numbers.pop()              # remove and return last element
numbers.pop(0)             # remove and return element at index 0
numbers.sort()             # sort in place (ascending)
numbers.sort(reverse=True) # sort descending
numbers.reverse()          # reverse in place
numbers.index(4)           # index of value 4
numbers.count(1)           # count occurrences of 1
numbers.clear()            # remove all elements
len(numbers)               # number of elements
```

### List Functions

```python
numbers = [3, 1, 4, 1, 5, 9, 2, 6]

len(numbers)      # 8
sum(numbers)      # 31
min(numbers)      # 1
max(numbers)      # 9
sorted(numbers)   # returns NEW sorted list (original unchanged)
```

### Checking Membership

```python
if 42 in numbers:
    print("Found!")

if "Alice" not in names:
    print("Not found")
```

### List Comprehensions — Pythonic Power

Create a new list from an expression applied to each item:

```python
# [expression for item in iterable if condition]

squares = [x * x for x in range(1, 6)]
# [1, 4, 9, 16, 25]

evens = [x for x in range(10) if x % 2 == 0]
# [0, 2, 4, 6, 8]

words = ["hello", "world", "python"]
upper = [w.upper() for w in words]
# ['HELLO', 'WORLD', 'PYTHON']

# Without list comprehension (C-style):
squares = []
for x in range(1, 6):
    squares.append(x * x)
```

### Iterating Lists

```python
names = ["Alice", "Bob", "Charlie"]

# Simple iteration
for name in names:
    print(name)

# With index
for i, name in enumerate(names):
    print(f"{i}: {name}")

# Two lists together with zip
ages = [20, 25, 30]
for name, age in zip(names, ages):
    print(f"{name} is {age}")
```

---

## 11. Tuples

A **tuple** is like a list but **immutable** — it cannot be changed after creation.

```python
point    = (3, 4)           # tuple with 2 values
rgb      = (255, 128, 0)    # RGB color
student  = ("Alice", 20, 3.9)  # mixed types
single   = (42,)            # single-element tuple — needs trailing comma!
empty    = ()               # empty tuple
```

### Accessing Tuple Elements

```python
point = (3, 4)
point[0]    # 3
point[1]    # 4
point[-1]   # 4

x, y = point   # tuple unpacking
print(x, y)    # 3  4
```

### When to Use Tuples vs Lists

| | List | Tuple |
|---|---|---|
| **Mutable** | ✅ Yes | ❌ No |
| **Syntax** | `[1, 2, 3]` | `(1, 2, 3)` |
| **Performance** | Slightly slower | Slightly faster |
| **Use when** | Collection may change | Fixed data (coordinates, RGB, records) |
| **Dict key?** | ❌ Can't (unhashable) | ✅ Yes |

---

## 12. Dictionaries

A **dictionary** is Python's built-in hash table — stores **key-value pairs** with O(1) average lookup.

### Creating Dictionaries

```python
# Literal syntax
student = {
    "name": "Alice",
    "age": 20,
    "gpa": 3.9
}

# Empty dictionary
d = {}
d = dict()

# From two lists
keys   = ["a", "b", "c"]
values = [1, 2, 3]
d = dict(zip(keys, values))   # {"a": 1, "b": 2, "c": 3}
```

### Accessing Values

```python
student["name"]          # "Alice"
student.get("name")      # "Alice"
student.get("phone")     # None (no KeyError if missing)
student.get("phone", "N/A")  # "N/A" (default if missing)
```

> ⚠️ `d["key"]` raises `KeyError` if key doesn't exist. Use `.get()` for safe access.

### Modifying Dictionaries

```python
student["age"] = 21         # update existing key
student["email"] = "a@b.c"  # add new key
del student["gpa"]           # delete a key

student.update({"age": 22, "city": "Boston"})  # update multiple
```

### Dictionary Methods

```python
d = {"a": 1, "b": 2, "c": 3}

d.keys()          # dict_keys(["a", "b", "c"])
d.values()        # dict_values([1, 2, 3])
d.items()         # dict_items([("a",1), ("b",2), ("c",3)])
d.pop("a")        # remove key "a", return its value
d.clear()         # empty the dict
len(d)            # number of key-value pairs
"a" in d          # True — check key existence
```

### Iterating Dictionaries

```python
d = {"name": "Alice", "age": 20}

for key in d:
    print(key)

for key, value in d.items():
    print(f"{key}: {value}")

for value in d.values():
    print(value)
```

### Dictionary Comprehensions

```python
squares = {x: x*x for x in range(1, 6)}
# {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

filtered = {k: v for k, v in d.items() if v > 10}
```

### Nested Dictionaries

```python
people = {
    "Alice": {"age": 20, "city": "Boston"},
    "Bob":   {"age": 25, "city": "NYC"}
}

people["Alice"]["age"]     # 20
people["Bob"]["city"]      # "NYC"
```

---

## 13. Sets

A **set** is an unordered collection of **unique** elements. Great for membership testing and removing duplicates.

```python
s = {1, 2, 3, 4}
s = set()            # empty set (NOT {} — that's an empty dict!)
s = set([1, 2, 2, 3, 3, 4])  # {1, 2, 3, 4} — duplicates removed
```

### Set Operations

```python
a = {1, 2, 3, 4}
b = {3, 4, 5, 6}

a | b    # union: {1, 2, 3, 4, 5, 6}
a & b    # intersection: {3, 4}
a - b    # difference: {1, 2}
a ^ b    # symmetric difference: {1, 2, 5, 6}

2 in a   # True — O(1) membership test
7 in a   # False

a.add(5)       # add element
a.remove(1)    # remove element (KeyError if not found)
a.discard(1)   # remove if present (no error if missing)
len(a)         # number of elements
```

### Remove Duplicates from a List

```python
names = ["Alice", "Bob", "Alice", "Charlie", "Bob"]
unique = list(set(names))
# ["Alice", "Bob", "Charlie"] — order not guaranteed
```

---

## 14. Command-Line Arguments — sys.argv

```python
import sys

# sys.argv is a list of strings
# sys.argv[0] = script name
# sys.argv[1] = first argument, etc.

if len(sys.argv) != 2:
    print("Usage: python hello.py name")
    sys.exit(1)

name = sys.argv[1]
print(f"Hello, {name}!")
```

```bash
$ python hello.py Alice
Hello, Alice!
```

### sys.exit()

```python
import sys

sys.exit()      # exit with code 0 (success)
sys.exit(0)     # explicit success
sys.exit(1)     # error — non-zero = failure
sys.exit("Error message")  # print message to stderr and exit 1
```

### argparse — Professional Argument Parsing

```python
import argparse

parser = argparse.ArgumentParser(description="Greet someone")
parser.add_argument("name", help="Name to greet")
parser.add_argument("--count", type=int, default=1,
                    help="Number of times to greet")
args = parser.parse_args()

for _ in range(args.count):
    print(f"Hello, {args.name}!")
```

```bash
$ python greet.py Alice --count 3
Hello, Alice!
Hello, Alice!
Hello, Alice!
```

---

## 15. File I/O in Python

### Opening and Reading Files

```python
# Method 1 — with statement (recommended: auto-closes file)
with open("file.txt", "r") as f:
    content = f.read()        # read entire file as one string

# Method 2 — read line by line
with open("file.txt", "r") as f:
    for line in f:
        print(line.strip())   # strip() removes trailing newline

# Method 3 — read all lines into a list
with open("file.txt", "r") as f:
    lines = f.readlines()     # ["line1\n", "line2\n", ...]

# Method 4 — read one line at a time
with open("file.txt", "r") as f:
    line = f.readline()       # just the first line
```

### Writing to Files

```python
# Write mode — creates file or overwrites existing
with open("output.txt", "w") as f:
    f.write("Hello, File!\n")
    f.write("Line 2\n")

# Append mode — adds to existing file
with open("output.txt", "a") as f:
    f.write("Line 3\n")

# Using print() to write to a file
with open("output.txt", "w") as f:
    print("Hello!", file=f)
    print("Score:", 95, file=f)
```

### File Open Modes

| Mode | Meaning |
|---|---|
| `"r"` | Read (default) — file must exist |
| `"w"` | Write — creates or overwrites |
| `"a"` | Append — adds to end |
| `"x"` | Create — fails if file exists |
| `"r+"` | Read and write |
| `"rb"` | Read binary |
| `"wb"` | Write binary |

### Reading a CSV File

```python
import csv

with open("students.csv", "r") as f:
    reader = csv.DictReader(f)   # first row is headers
    for row in reader:
        print(row["name"], row["age"])
```

### Writing a CSV File

```python
import csv

with open("output.csv", "w", newline="") as f:
    writer = csv.DictWriter(f, fieldnames=["name", "age"])
    writer.writeheader()
    writer.writerow({"name": "Alice", "age": 20})
    writer.writerow({"name": "Bob",   "age": 25})
```

### Checking if a File Exists

```python
import os

if os.path.exists("data.txt"):
    print("File exists")

if os.path.isfile("data.txt"):
    print("Is a file")

if os.path.isdir("data"):
    print("Is a directory")
```

---

## 16. Python Libraries and Modules

### Importing Modules

```python
import math                    # import entire module
from math import sqrt          # import specific function
from math import sqrt, pi, e   # import multiple
import math as m               # import with alias
from math import *             # import everything (generally avoid)
```

### The `math` Module

```python
import math

math.sqrt(16)         # 4.0
math.pow(2, 10)       # 1024.0
math.floor(3.7)       # 3
math.ceil(3.2)        # 4
math.round(3.5)       # 4 (Python 3 uses banker's rounding)
round(3.14159, 2)     # 3.14 (built-in, no import needed)
math.pi               # 3.141592653589793
math.e                # 2.718281828459045
math.log(100, 10)     # 2.0 (log base 10)
math.log(math.e)      # 1.0 (natural log)
math.factorial(5)     # 120
math.gcd(12, 8)       # 4
math.inf              # infinity
```

### The `random` Module

```python
import random

random.random()                # random float: 0.0 <= x < 1.0
random.randint(1, 10)          # random int: 1 to 10 inclusive
random.choice(["a","b","c"])   # random item from list
random.choices([1,2,3], k=2)   # 2 random items with replacement
random.shuffle(my_list)        # shuffle list in place
random.sample(my_list, 3)      # 3 unique random items (no replacement)
random.seed(42)                # set seed for reproducibility
```

### The `sys` Module

```python
import sys

sys.argv          # command-line arguments list
sys.exit(1)       # exit with code
sys.version       # Python version string
sys.path          # list of directories Python searches for modules
sys.stdin         # standard input
sys.stdout        # standard output
sys.stderr        # standard error
print("Error!", file=sys.stderr)   # write to stderr
```

### The `os` Module

```python
import os

os.getcwd()                 # current working directory
os.listdir(".")             # list files in directory
os.path.exists("file.txt")  # check if path exists
os.path.join("dir", "file") # build path safely
os.mkdir("new_dir")         # create directory
os.remove("file.txt")       # delete file
os.rename("old.txt", "new.txt")  # rename file
os.environ.get("HOME")      # get environment variable
```

### The `string` Module

```python
import string

string.ascii_lowercase   # 'abcdefghijklmnopqrstuvwxyz'
string.ascii_uppercase   # 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
string.ascii_letters     # upper + lower combined
string.digits            # '0123456789'
string.punctuation       # '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
```

### The `statistics` Module

```python
import statistics

data = [2, 4, 4, 4, 5, 5, 7, 9]

statistics.mean(data)     # 5.0
statistics.median(data)   # 4.5
statistics.mode(data)     # 4
statistics.stdev(data)    # 2.0
statistics.variance(data) # 4.0
```

---

## 17. Regular Expressions — `re`

**Regular expressions (regex)** are patterns for matching, searching, and extracting text.

### Importing and Basic Usage

```python
import re

# re.search(pattern, string) — search anywhere in string
# Returns a Match object if found, None if not

result = re.search(r"\d+", "abc 123 def")
if result:
    print(result.group())   # "123"
```

### Common Pattern Syntax

| Pattern | Matches |
|---|---|
| `.` | Any single character (except newline) |
| `\d` | Any digit `[0-9]` |
| `\D` | Any non-digit |
| `\w` | Any word character `[a-zA-Z0-9_]` |
| `\W` | Any non-word character |
| `\s` | Any whitespace (space, tab, newline) |
| `\S` | Any non-whitespace |
| `^` | Start of string |
| `$` | End of string |
| `*` | 0 or more of previous |
| `+` | 1 or more of previous |
| `?` | 0 or 1 of previous |
| `{n}` | Exactly n of previous |
| `{n,m}` | Between n and m of previous |
| `[abc]` | Any one of a, b, c |
| `[^abc]` | Any character NOT a, b, c |
| `[a-z]` | Any lowercase letter |
| `(abc)` | Capture group |
| `a\|b` | a or b |

### `re` Functions

```python
import re

text = "Hello, my number is 617-555-0100 and email is alice@example.com"

# re.search — find first match anywhere
m = re.search(r"\d{3}-\d{3}-\d{4}", text)
print(m.group())   # 617-555-0100

# re.match — match at START of string only
m = re.match(r"Hello", text)
print(m.group())   # Hello

# re.fullmatch — entire string must match
m = re.fullmatch(r"\d+", "12345")
print(m)           # Match object

# re.findall — return all matches as a list
numbers = re.findall(r"\d+", "1 cat, 2 dogs, 3 birds")
print(numbers)     # ['1', '2', '3']

# re.sub — replace matches
result = re.sub(r"\d", "#", "abc123def456")
print(result)      # abc###def###

# re.split — split by pattern
parts = re.split(r"\s+", "hello   world   python")
print(parts)       # ['hello', 'world', 'python']
```

### Flags

```python
re.search(r"hello", text, re.IGNORECASE)    # case-insensitive
re.search(r"hello", text, re.I)             # same — short form
re.search(r"^hello", text, re.MULTILINE)    # ^ matches each line start
```

### Practical Regex Examples

```python
# Validate email (simplified)
email = "alice@example.com"
if re.fullmatch(r"\w+@\w+\.\w+", email):
    print("Valid email")

# Validate US phone number
phone = "617-555-0100"
if re.fullmatch(r"\d{3}-\d{3}-\d{4}", phone):
    print("Valid phone")

# Extract all emails from text
emails = re.findall(r"\w+@\w+\.\w+", large_text)

# Validate password (8+ chars, at least one digit)
if re.search(r"(?=.*\d).{8,}", password):
    print("Password is strong")
```

---

## 18. Object-Oriented Programming in Python

Python is a fully object-oriented language. Everything in Python is an object.

### Defining a Class

```python
class Student:
    # Constructor — called when creating a new Student
    def __init__(self, name, age, gpa):
        self.name = name   # instance attribute
        self.age  = age
        self.gpa  = gpa

    # Instance method
    def greet(self):
        print(f"Hi, I'm {self.name}!")

    def is_honor_roll(self):
        return self.gpa >= 3.5

    # __str__ — defines what print(student) shows
    def __str__(self):
        return f"Student({self.name}, {self.age}, GPA {self.gpa})"
```

### Creating and Using Objects

```python
# Create instances
alice = Student("Alice", 20, 3.9)
bob   = Student("Bob",   22, 3.2)

# Access attributes
print(alice.name)   # Alice
print(bob.age)      # 22

# Call methods
alice.greet()                    # Hi, I'm Alice!
print(alice.is_honor_roll())     # True
print(bob.is_honor_roll())       # False

# __str__
print(alice)   # Student(Alice, 20, GPA 3.9)
```

### Class Variables vs Instance Variables

```python
class Student:
    school = "Harvard"    # class variable — shared by all instances

    def __init__(self, name):
        self.name = name  # instance variable — unique to each instance

alice = Student("Alice")
print(alice.school)         # Harvard
print(Student.school)       # Harvard
Student.school = "MIT"
print(alice.school)         # MIT — all instances see the change
```

### Inheritance

```python
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age  = age

    def introduce(self):
        print(f"I'm {self.name}, age {self.age}")


class Student(Person):      # Student inherits from Person
    def __init__(self, name, age, gpa):
        super().__init__(name, age)   # call parent constructor
        self.gpa = gpa

    def study(self):
        print(f"{self.name} is studying")

    def introduce(self):    # override parent method
        super().introduce()
        print(f"My GPA is {self.gpa}")


alice = Student("Alice", 20, 3.9)
alice.introduce()   # I'm Alice, age 20 \n My GPA is 3.9
alice.study()       # Alice is studying
```

### Special (Dunder) Methods

```python
class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):      # print(v) → "(3, 4)"
        return f"({self.x}, {self.y})"

    def __repr__(self):     # dev representation
        return f"Vector({self.x}, {self.y})"

    def __add__(self, other):   # v1 + v2
        return Vector(self.x + other.x, self.y + other.y)

    def __len__(self):      # len(v) → 2
        return 2

    def __eq__(self, other):    # v1 == v2
        return self.x == other.x and self.y == other.y
```

---

## 19. Re-implementing CS50 Problems in Python

A major goal of Week 6 is to see how Python simplifies C programs.

### Mario (Pyramid)

```python
# C needed nested loops with spaces and hashes
# Python: string multiplication does it in 2 lines

height = int(input("Height: "))
while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)
```

### Caesar Cipher

```python
import sys

if len(sys.argv) != 2:
    sys.exit("Usage: python caesar.py key")

try:
    key = int(sys.argv[1])
except ValueError:
    sys.exit("Key must be an integer")

if key < 0:
    sys.exit("Key must be non-negative")

plaintext = input("plaintext:  ")
ciphertext = ""

for c in plaintext:
    if c.isupper():
        ciphertext += chr((ord(c) - ord('A') + key) % 26 + ord('A'))
    elif c.islower():
        ciphertext += chr((ord(c) - ord('a') + key) % 26 + ord('a'))
    else:
        ciphertext += c

print(f"ciphertext: {ciphertext}")
```

### `ord()` and `chr()` in Python

```python
ord('A')    # 65 — character to ASCII number
ord('a')    # 97
chr(65)     # 'A' — ASCII number to character
chr(97)     # 'a'
```

### Readability (Grade Level)

```python
import re

text = input("Text: ")

letters    = len(re.findall(r"[a-zA-Z]", text))
words      = len(text.split())
sentences  = len(re.findall(r"[.!?]", text))

L = 100 * letters / words
S = 100 * sentences / words
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
```

### DNA

```python
import csv
import sys

if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py database sequence")

# Load sequence
with open(sys.argv[2]) as f:
    sequence = f.read()

# Load database
with open(sys.argv[1]) as f:
    reader = csv.DictReader(f)
    strs = reader.fieldnames[1:]   # STR names (skip "name" column)

    # Count max consecutive repeats of each STR in sequence
    counts = {}
    for str_name in strs:
        max_count = 0
        count = 0
        i = 0
        while i < len(sequence):
            if sequence[i:i+len(str_name)] == str_name:
                count += 1
                max_count = max(max_count, count)
                i += len(str_name)
            else:
                count = 0
                i += 1
        counts[str_name] = max_count

    # Match against database
    for row in reader:
        if all(int(row[s]) == counts[s] for s in strs):
            print(row["name"])
            sys.exit(0)

print("No match")
```

---

## 20. Problem Set 6 Overview

Problem Set 6 asks you to re-implement your CS50 C programs in Python.

### hello.py

```python
name = input("What's your name? ")
print(f"hello, {name}")
```

### mario.py (Less)

```python
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        pass

for i in range(1, height + 1):
    print("#" * i)
```

### mario.py (More)

```python
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        pass

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)
```

### cash.py / credit.py

```python
# cash.py — greedy algorithm for change
while True:
    try:
        cents = round(float(input("Change owed: ")) * 100)
        if cents >= 0:
            break
    except ValueError:
        pass

coins = 0
for coin in [25, 10, 5, 1]:
    coins += cents // coin
    cents %= coin

print(coins)
```

### Tips for All Problem Set 6 Programs

| Tip | Detail |
|---|---|
| Input validation with `try/except` | Use `try: int(input())` with `except ValueError` |
| String methods replace ctype | `s.isupper()`, `s.islower()`, `s.isalpha()`, `s.isdigit()` |
| `chr()` and `ord()` replace ASCII math | `ord('A')` = 65, `chr(65)` = 'A' |
| List instead of arrays | `scores = []` then `scores.append(x)` |
| No `#include` needed | Python imports only what you explicitly use |
| `sys.argv` for command-line args | Don't forget `import sys` |
| `sys.exit()` for early exit | Cleaner than multiple `return` statements |

---

## 21. Quick Reference Cheat Sheet

### Python vs C Quick Comparison

```python
# C                              # Python
# int x = 5;                     x = 5
# printf("%i\n", x);             print(x)
# scanf("%s", name);             name = input()
# // comment                     # comment
# for (int i=0; i<5; i++)        for i in range(5):
# while (x > 0) { }              while x > 0:
# if (x == y) { }                if x == y:
# int arr[5] = {1,2,3,4,5};      arr = [1, 2, 3, 4, 5]
# strlen(s)                      len(s)
# strcmp(a, b) == 0              a == b
# NULL                           None
# true / false                   True / False
# && || !                        and or not
```

### Common Built-in Functions

```python
len(x)         # length of string/list/dict/tuple
type(x)        # type of x
int(x)         # convert to int
float(x)       # convert to float
str(x)         # convert to string
bool(x)        # convert to bool
list(x)        # convert to list
tuple(x)       # convert to tuple
range(n)       # range object
print(x)       # output to stdout
input(prompt)  # read from stdin
open(f, mode)  # open a file
sorted(x)      # return sorted copy
reversed(x)    # return reversed iterator
enumerate(x)   # (index, value) pairs
zip(a, b)      # pair elements from two iterables
map(f, x)      # apply f to each element
filter(f, x)   # keep elements where f returns True
sum(x)         # sum of iterable
min(x)         # minimum value
max(x)         # maximum value
abs(x)         # absolute value
round(x, n)    # round to n decimal places
```

### String Methods Quick Reference

```python
s.upper()          s.lower()          s.strip()
s.split()          s.join()           s.replace(a, b)
s.startswith(x)    s.endswith(x)      s.find(x)
s.count(x)         s.isalpha()        s.isdigit()
s.isalnum()        s.isupper()        s.islower()
s.isspace()        s.title()          s.center(n)
```

### List Methods Quick Reference

```python
lst.append(x)      lst.insert(i, x)   lst.remove(x)
lst.pop()          lst.pop(i)         lst.sort()
lst.reverse()      lst.index(x)       lst.count(x)
lst.clear()        lst.copy()         lst.extend(other)
```

### File I/O Pattern

```python
# Read
with open("file.txt", "r") as f:
    for line in f:
        print(line.strip())

# Write
with open("file.txt", "w") as f:
    f.write("Hello\n")
    print("World", file=f)
```

### Exception Handling Pattern

```python
try:
    x = int(input("Number: "))
except ValueError:
    print("Not a number")
except ZeroDivisionError:
    print("Can't divide by zero")
else:
    print("Success:", x)
finally:
    print("Done")
```

### Key Rules for Week 6

| Rule | Why It Matters |
|---|---|
| `input()` always returns a string | Always convert: `int(input())` |
| Indentation IS the syntax | Wrong indentation = wrong logic or SyntaxError |
| Python is 0-indexed like C | `list[0]` is first, `list[-1]` is last |
| Strings are immutable | Can't do `s[0] = 'H'` — must build new string |
| `==` works for strings | Unlike C — no `strcmp` needed |
| `True` / `False` are capitalized | `true` and `false` are NameErrors |
| `None` is not `0` or `False` | Use `if x is None:` not `if x == None:` |
| Use `with open()` for files | Auto-closes file even if exception occurs |
| `len()` works on strings, lists, dicts | No `strlen()` needed |
| `not in` and `in` for membership | `if "alice" in names:` — much cleaner than C |

---

*CS50 Week 6 Notes · Harvard University · David J. Malan*
