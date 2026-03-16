# 🎓 Harvard CS50x — Introduction to Computer Science 2025

![CS50](https://img.shields.io/badge/Harvard-CS50x-crimson?style=for-the-badge&logo=harvard&logoColor=white)
![Language](https://img.shields.io/badge/Languages-C%20%7C%20Python%20%7C%20SQL%20%7C%20JS-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-In%20Progress-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> **CS50x** is Harvard University's introduction to the intellectual enterprises of computer science and the art of programming — for concentrators and non-concentrators alike, with or without prior programming experience.
>
> *Taught by Professor David J. Malan*

---

## 📚 Table of Contents

- [About CS50x](#-about-cs50x)
- [Course Structure](#-course-structure)
- [Weekly Breakdown](#-weekly-breakdown)
  - [Week 0 — Scratch](#week-0--scratch)
  - [Week 1 — C](#week-1--c)
  - [Week 2 — Arrays](#week-2--arrays)
  - [Week 3 — Algorithms](#week-3--algorithms)
  - [Week 4 — Memory](#week-4--memory)
  - [Week 5 — Data Structures](#week-5--data-structures)
  - [Week 6 — Python](#week-6--python)
  - [Week 7 — SQL](#week-7--sql)
  - [Week AI — Artificial Intelligence](#week-ai--artificial-intelligence)
  - [Week 8 — HTML, CSS, JavaScript](#week-8--html-css-javascript)
  - [Week 9 — Flask](#week-9--flask)
  - [Week 10 — The End](#week-10--the-end)
  - [Final Project](#-final-project)
- [Core Tools & Resources](#-core-tools--resources)
- [CS50 Library Reference](#-cs50-library-reference)
- [Key Concepts Glossary](#-key-concepts-glossary)
- [Official Links](#-official-links)
- [Repository Structure](#-repository-structure)
- [Academic Honesty](#-academic-honesty)

---

## 🏛 About CS50x

CS50x teaches you how to **think algorithmically and solve problems efficiently**, with an emphasis on correctness, design, and style. More than teaching you to program in one language, it teaches you to program *fundamentally* — so you can teach yourself any new language.

| Detail | Info |
|---|---|
| 🎓 Institution | Harvard University |
| 👨‍🏫 Instructor | Prof. David J. Malan |
| 🌐 Platform | edX / OpenCourseWare |
| 📅 Version | CS50x 2026 |
| 🗓️ Duration | 11 Weeks + Final Project |
| 💰 Cost | Free (Certificate optional) |
| 🔗 Official Site | [cs50.harvard.edu/x](https://cs50.harvard.edu/x) |

---

## 🗂 Course Structure

Each week follows this workflow:

```
Watch Lecture → Watch Section (recommended)
                     ↓
              Watch Shorts (recommended)
                     ↓
              Submit Problem Set
```

After all weeks: **Submit Final Project**

---

## 📅 Weekly Breakdown

---

### Week 0 — Scratch

> **Introduction to computational thinking using visual, block-based programming.**

**Core Concepts:**
- Computational thinking
- Abstraction
- Algorithms
- Pseudocode
- Functions, Loops, Conditionals, Events
- Sprites, Costumes, Backdrops

**Problem Set 0:** Build an interactive project in Scratch (game, animation, or interactive story)

**Tools:**
- [Scratch](https://scratch.mit.edu) — MIT's visual programming language

---

### Week 1 — C

> **Introduction to C and the fundamentals of programming.**

**Core Concepts:**
- Source code vs. machine code
- Compiling with `clang` / `make`
- Variables, Data Types (`int`, `float`, `char`, `string`, `bool`)
- Operators (`+`, `-`, `*`, `/`, `%`)
- Conditional statements (`if`, `else if`, `else`, `switch`)
- Loops (`for`, `while`, `do-while`)
- Functions and return types
- Command-line interface (CLI) basics
- `printf`, `scanf`
- `cs50.h` library: `get_int()`, `get_string()`, `get_float()`

**Problem Set 1:**
- `hello` — Hello, World
- `mario` (less / more comfortable) — Print pyramid patterns
- `cash` or `credit` — Greedy algorithm / Luhn's Algorithm

**Tools:**
- [cs50.dev](https://cs50.dev) — VS Code in the browser (CS50 Codespace)
- `help50` — Error message helper
- `check50` — Automated correctness checker
- `style50` — Code style checker
- `submit50` — Submission tool

---

### Week 2 — Arrays

> **Working with arrays, strings, and command-line arguments in C.**

**Core Concepts:**
- Compiling steps: preprocessing, compiling, assembling, linking
- Debugging with `debug50` and `printf`
- Arrays: declaration, indexing, iteration
- Strings as arrays of characters (`char[]`)
- String functions: `strlen()`, `toupper()`, `tolower()`, `isalpha()`, `isdigit()`
- Command-line arguments (`argc`, `argv`)
- Exit codes
- Cryptography basics

**Libraries Used:**
- `<string.h>` — String manipulation
- `<ctype.h>` — Character classification
- `<cs50.h>` — CS50 input helpers

**Problem Set 2:**
- `scrabble` — Compare scrabble word scores
- `readability` — Coleman-Liau index
- `caesar` or `substitution` — Cipher encryption

---

### Week 3 — Algorithms

> **Searching, sorting, and analyzing algorithmic efficiency.**

**Core Concepts:**
- Linear Search — O(n)
- Binary Search — O(log n)
- Bubble Sort — O(n²)
- Selection Sort — O(n²)
- Merge Sort — O(n log n)
- Big O Notation: `O`, `Ω` (Omega), `Θ` (Theta)
- Recursion & recursive functions
- Struct (`typedef struct`)
- Comparison functions

**Key Notations:**

| Notation | Meaning | Example |
|---|---|---|
| `O(1)` | Constant time | Array access |
| `O(log n)` | Logarithmic | Binary search |
| `O(n)` | Linear | Linear search |
| `O(n log n)` | Log-linear | Merge sort |
| `O(n²)` | Quadratic | Bubble sort |

**Problem Set 3:**
- `sort` — Identify sorting algorithms
- `plurality` — Plurality voting
- `runoff` or `tideman` — Ranked-choice / Condorcet voting

---

### Week 4 — Memory

> **Understanding how memory works: pointers, addresses, and dynamic allocation.**

**Core Concepts:**
- Hexadecimal (`0x...`)
- Memory addresses and pointers (`*`, `&`)
- Pointer arithmetic
- Strings as `char *`
- Dynamic memory allocation: `malloc()`, `calloc()`, `realloc()`, `free()`
- Memory layout: stack, heap, text segment
- Buffer overflows
- Valgrind for memory leak detection
- File I/O: `fopen()`, `fclose()`, `fread()`, `fwrite()`
- JPEG/BMP file structures

**Libraries:**
- `<stdlib.h>` — Memory allocation
- `<stdio.h>` — File operations

**Problem Set 4:**
- `volume` — Modify audio file volume
- `filter` (less / more) — Image filters (grayscale, sepia, blur, edge-detect)
- `recover` — Recover JPEGs from memory card

---

### Week 5 — Data Structures

> **Building and using dynamic data structures in C.**

**Core Concepts:**
- Abstract data types
- Linked lists (singly & doubly)
- Trees (binary trees, binary search trees)
- Hash tables: hashing functions, collision handling (chaining, probing)
- Tries (prefix trees)
- Queues (FIFO) and Stacks (LIFO)
- Time vs. space tradeoffs

**Structures:**

| Structure | Insert | Search | Delete | Notes |
|---|---|---|---|---|
| Array | O(n) | O(n) | O(n) | Fixed size |
| Linked List | O(1) | O(n) | O(n) | Dynamic size |
| Hash Table | O(1)* | O(1)* | O(1)* | Best case |
| Trie | O(k) | O(k) | O(k) | k = key length |
| BST | O(log n) | O(log n) | O(log n) | If balanced |

**Problem Set 5:**
- `inheritance` — Simulate genetic inheritance
- `speller` — Spell checker using a hash table

---

### Week 6 — Python

> **Transition from C to Python; high-level programming concepts.**

**Core Concepts:**
- Python syntax vs. C syntax
- Variables, types (dynamic typing)
- `if`, `elif`, `else`
- `for` and `while` loops
- Functions: `def`, `return`
- Lists, Tuples, Dicts, Sets
- `import` and modules
- File I/O with `open()`
- Regular expressions (`re` module)
- Exception handling (`try`, `except`)
- Object-Oriented Programming (OOP) basics
- `sys.argv` for command-line args

**Key Libraries:**
- `cs50` — CS50's Python library
- `sys` — System functions
- `os` — Operating system interface
- `csv` — CSV file handling
- `re` — Regular expressions
- `PIL` / `Pillow` — Image processing

**Problem Set 6 (Python ports):**
- `hello` — Hello in Python
- `mario` — Mario pyramid in Python
- `cash` or `credit` — Greedy/Luhn in Python
- `readability` — Coleman-Liau in Python
- `dna` — DNA profile matching using STRs

---

### Week 7 — SQL

> **Storing, querying, and managing data with relational databases.**

**Core Concepts:**
- Relational databases and tables
- SQL: `SELECT`, `INSERT`, `UPDATE`, `DELETE`
- Filtering: `WHERE`, `LIKE`, `IN`, `BETWEEN`
- Aggregation: `COUNT`, `SUM`, `AVG`, `MIN`, `MAX`
- Sorting: `ORDER BY`, `GROUP BY`, `HAVING`
- Joining tables: `JOIN`, `LEFT JOIN`, `INNER JOIN`
- Subqueries
- Indexes for performance
- SQLite vs. other databases
- SQL injection (security risk)
- Python + SQL with `cs50` library: `db.execute()`

**Problem Set 7:**
- `songs` — Analyze Spotify song data
- `movies` — Query IMDb movie database
- `fiftyville` — Mystery solving with SQL queries

---

### Week AI — Artificial Intelligence

> **Introduction to AI concepts: machine learning, neural networks, and prompt engineering.**

**Core Concepts:**
- Generative AI and Large Language Models (LLMs)
- Prompt Engineering: system prompts and user prompts
- Decision Trees
- Minimax algorithm (game AI)
- Machine Learning and Reinforcement Learning
- Explore vs. Exploit tradeoff
- Deep Learning and Neural Networks
- Transformer Architecture

**No Problem Set** — this is a supplemental week

---

### Week 8 — HTML, CSS, JavaScript

> **Building web pages and adding interactivity with front-end web technologies.**

**Core Concepts:**
- How the internet works: IP, DNS, TCP/IP, HTTP/HTTPS
- HTML structure: `<!DOCTYPE>`, tags, attributes, forms
- CSS selectors, properties, the box model, Flexbox
- JavaScript: variables, functions, DOM manipulation
- Events: `addEventListener`, `onclick`
- `fetch()` API and asynchronous JS
- JSON: parsing and stringifying
- Responsive design

**Key Tags & Properties:**
- HTML: `<html>`, `<head>`, `<body>`, `<div>`, `<form>`, `<input>`, `<a>`, `<img>`
- CSS: `color`, `font-size`, `margin`, `padding`, `display`, `position`
- JS: `document.querySelector()`, `document.getElementById()`, `console.log()`

**Problem Set 8:**
- `trivia` — Trivia quiz webpage
- `homepage` — Personal homepage with HTML/CSS/JS

---

### Week 9 — Flask

> **Building dynamic web applications with Python's Flask framework.**

**Core Concepts:**
- Flask routes and URL routing (`@app.route`)
- HTTP methods: `GET` and `POST`
- Jinja2 templates and template inheritance
- Forms and user input (`request.form`)
- Sessions and cookies (`session`)
- Redirects (`redirect`) and rendering templates (`render_template`)
- SQLite with Flask (`cs50` SQL library)
- REST APIs
- Cookies and state management

**Key Flask Concepts:**

```python
from flask import Flask, render_template, request, redirect, session
from cs50 import SQL

app = Flask(__name__)
db = SQL("sqlite:///database.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # handle form
        pass
    return render_template("index.html")
```

**Problem Set 9:**
- `birthdays` — Birthday tracker web app
- `finance` — Stock trading simulation (C$50 Finance)

---

### Week 10 — The End

> **Looking back at the full journey and forward into the world of CS.**

**Topics Covered:**
- Review of course concepts
- What to learn next
- Python ecosystems, web frameworks, data science
- Open source contribution
- CS50's other courses

---

## 🎯 Final Project

The **Final Project** is your opportunity to build something of your own using the skills you've learned throughout the course.

- Can be implemented in **any language(s)**
- Must draw upon CS50 course content
- Submitted via [submit.cs50.io](https://submit.cs50.io)
- Requires a short video demo (≈2 minutes) uploaded to YouTube
- Requires a `README.md` describing your project

📖 [Final Project Guidelines](https://cs50.harvard.edu/x/2026/project/)

---

## 🛠 Core Tools & Resources

| Tool | Description | Link |
|---|---|---|
| **CS50 Codespace** | Browser-based VS Code IDE | [cs50.dev](https://cs50.dev) |
| **CS50.ai** | AI-powered duck debugger | [cs50.ai](https://cs50.ai) |
| **check50** | Automated correctness checker | runs in terminal |
| **style50** | Code style linter | runs in terminal |
| **help50** | Explains compiler errors | runs in terminal |
| **submit50** | Submission tool | runs in terminal |
| **debug50** | CS50 debugger | runs in terminal |
| **CS50 Manual Pages** | C library reference | [manual.cs50.io](https://manual.cs50.io) |
| **CS50 Style Guide** | C coding standards | [cs50.readthedocs.io/style/c](https://cs50.readthedocs.io/style/c/) |

---

## 📦 CS50 Library Reference

### C — `cs50.h`

```c
#include <cs50.h>

// Input functions
bool     get_bool(string prompt);
char     get_char(string prompt);
double   get_double(string prompt);
float    get_float(string prompt);
int      get_int(string prompt);
long     get_long(string prompt);
string   get_string(string prompt);
```

### Python — `cs50` module

```python
from cs50 import get_string, get_int, get_float, SQL

name = get_string("Name: ")
age  = get_int("Age: ")

# SQL usage
db = SQL("sqlite:///database.db")
rows = db.execute("SELECT * FROM table WHERE id = ?", id)
```

---

## 📖 Key Concepts Glossary

| Term | Definition |
|---|---|
| **Abstraction** | Hiding implementation details; focusing on what, not how |
| **Algorithm** | Step-by-step instructions to solve a problem |
| **Big O Notation** | Describes the upper bound of an algorithm's time/space complexity |
| **Compilation** | Converting source code to machine code |
| **Data Structure** | A format for organizing and storing data |
| **Hash Table** | Key-value store using a hash function for O(1) lookup |
| **Pointer** | A variable that stores a memory address |
| **Recursion** | A function that calls itself |
| **Scope** | The region where a variable is accessible |
| **Stack vs. Heap** | Stack = automatic memory; Heap = manually allocated memory |
| **SQL Injection** | Security attack via malicious SQL in user input |
| **REST API** | Architectural style for building web services using HTTP |

---

## 🔗 Official Links

| Resource | Link |
|---|---|
| 🏠 CS50x Homepage | [cs50.harvard.edu/x](https://cs50.harvard.edu/x) |
| 📋 Syllabus | [cs50.harvard.edu/x/2026/syllabus](https://cs50.harvard.edu/x/2026/syllabus/) |
| 🎥 YouTube Lectures | [CS50 YouTube Playlist](https://www.youtube.com/playlist?list=PLhQjrBD2T380hlTqAU8HfvVepCcjCqTg6) |
| 💻 CS50 Codespace | [cs50.dev](https://cs50.dev) |
| 🤖 CS50 AI Duck | [cs50.ai](https://cs50.ai) |
| 📖 Manual Pages | [manual.cs50.io](https://manual.cs50.io) |
| ✅ Submission Portal | [submit.cs50.io](https://submit.cs50.io) |
| 📊 Gradebook | [cs50.me/cs50x](https://cs50.me/cs50x) |
| 💬 Discord Community | [discord.gg/cs50](https://discord.gg/cs50) |
| 📝 Ed Discussion (Q&A) | [cs50.edx.org/ed](https://cs50.edx.org/ed) |
| 🌐 edX Enrollment | [cs50.edx.org](https://cs50.edx.org) |
| 🐙 CS50 GitHub | [github.com/cs50](https://github.com/cs50) |
| 📱 Reddit Community | [reddit.com/r/cs50](https://www.reddit.com/r/cs50/) |
| 🎓 CS50 Certificate | [cs50.harvard.edu/x/2026/certificate](https://cs50.harvard.edu/x/2026/certificate/) |
| 🐍 CS50P (Python) | [cs50.harvard.edu/python](https://cs50.harvard.edu/python) |
| 🌐 CS50W (Web) | [cs50.harvard.edu/web](https://cs50.harvard.edu/web) |
| 🤖 CS50 AI | [cs50.harvard.edu/ai](https://cs50.harvard.edu/ai) |
| 🗄️ CS50 SQL | [cs50.harvard.edu/sql](https://cs50.harvard.edu/sql) |

---

## 📁 Repository Structure

```
cs50x/
│
├── week0-scratch/
│   └── project.sb3
│
├── week1-c/
│   ├── hello/
│   ├── mario/
│   └── cash/ (or credit/)
│
├── week2-arrays/
│   ├── scrabble/
│   ├── readability/
│   └── caesar/ (or substitution/)
│
├── week3-algorithms/
│   ├── plurality/
│   └── runoff/ (or tideman/)
│
├── week4-memory/
│   ├── volume/
│   ├── filter/
│   └── recover/
│
├── week5-data-structures/
│   ├── inheritance/
│   └── speller/
│
├── week6-python/
│   ├── hello/
│   ├── mario/
│   ├── readability/
│   └── dna/
│
├── week7-sql/
│   ├── songs/
│   ├── movies/
│   └── fiftyville/
│
├── week8-html-css-js/
│   ├── trivia/
│   └── homepage/
│
├── week9-flask/
│   ├── birthdays/
│   └── finance/
│
└── final-project/
    ├── README.md
    └── ...
```

---

## ⚖️ Academic Honesty

> CS50 has a clear and strict policy on academic honesty.

You are encouraged to:
- Ask classmates and others for help — so long as it doesn't reduce to another doing your work for you
- Discuss approaches and pseudocode
- Use official resources (manual pages, CS50 shorts, etc.)

You must **not**:
- Share your solutions publicly until after the submission deadline
- Copy code from others or the internet without CS50's permission
- Submit work that is not your own

📄 [Full Academic Honesty Policy](https://cs50.harvard.edu/x/2026/honesty/)

---

<div align="center">

**Made with ❤️ while taking Harvard's CS50x**

*"What ultimately matters in this course is not so much where you end up relative to your classmates but where you end up relative to yourself when you began."*
— David J. Malan

[![CS50 Certificate](https://img.shields.io/badge/Goal-CS50%20Certificate-crimson?style=flat-square)](https://cs50.harvard.edu/x/2026/certificate/)

</div>
