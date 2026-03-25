# CS50 — Week 0: Scratch & Computational Thinking

**Harvard University** · David J. Malan  
**Topic:** How computers think, how to think like a programmer, and building your first programs in Scratch.

---

## Table of Contents

1. [What is Computer Science?](#1-what-is-computer-science)
2. [Representing Information — Binary](#2-representing-information--binary)
3. [How Computers Store Data](#3-how-computers-store-data)
4. [Representing Text — ASCII & Unicode](#4-representing-text--ascii--unicode)
5. [Representing Images, Video & Sound](#5-representing-images-video--sound)
6. [Algorithms](#6-algorithms)
7. [Pseudocode](#7-pseudocode)
8. [Abstraction](#8-abstraction)
9. [Introduction to Scratch](#9-introduction-to-scratch)
10. [Core Programming Concepts in Scratch](#10-core-programming-concepts-in-scratch)
11. [Functions in Scratch](#11-functions-in-scratch)
12. [Loops in Scratch](#12-loops-in-scratch)
13. [Conditionals in Scratch](#13-conditionals-in-scratch)
14. [Variables in Scratch](#14-variables-in-scratch)
15. [Events in Scratch](#15-events-in-scratch)
16. [Problem Set 0 Tips](#16-problem-set-0-tips)
17. [Key Takeaways](#17-key-takeaways)

---

## 1. What is Computer Science?

Computer science is fundamentally about **problem solving**.

```
INPUT  ──────►  [ BLACK BOX ]  ──────►  OUTPUT
```

You take some input, process it somehow, and produce an output. The "black box" in the middle is where the interesting work happens — that is what we are learning to build.

### The Core Problem-Solving Loop

Every program, no matter how complex, follows this pattern:

- **Input** — information you give the computer (keyboard, mouse click, file, sensor, etc.)
- **Processing** — the instructions the computer follows (your code / algorithm)
- **Output** — the result (text on screen, a sound, a saved file, etc.)

**Examples:**

| Input | Processing | Output |
|---|---|---|
| You type a search query | Google's ranking algorithm | A list of web results |
| A photo | Face-detection algorithm | A tagged photo |
| Numbers on a spreadsheet | Sum formula | A total |

> **Key idea:** Computers are not smart on their own. They only do exactly what you tell them. The intelligence comes from *you* — the programmer.

---

## 2. Representing Information — Binary

Computers, at their lowest level, only understand two states:

- **0** — off / no electrical signal
- **1** — on / electrical signal present

This is called **binary** (base-2). Each 0 or 1 is called a **bit** (binary digit).

### Why Binary?

Hardware is made of billions of tiny transistors — tiny switches that are either *on* or *off*. Binary maps perfectly to this physical reality.

### Counting in Binary vs Decimal

In our everyday **decimal** (base-10) system, each column represents a power of 10:

```
Decimal place values:
... 1000  100  10  1
```

In **binary** (base-2), each column represents a power of 2:

```
Binary place values:
... 128  64  32  16  8  4  2  1
```

### Converting Binary to Decimal — Step by Step

**Example: What is `0 1 1 0 1` in decimal?**

```
Position:   16   8   4   2   1
Bit:         0   1   1   0   1

Calculate:
  0 × 16  =   0
  1 ×  8  =   8
  1 ×  4  =   4
  0 ×  2  =   0
  1 ×  1  =   1
              ──
  Total   =  13
```

So `01101` in binary = **13** in decimal.

### Converting Decimal to Binary — Step by Step

**Example: Convert 50 to binary**

Repeatedly divide by 2 and note the remainders:

```
50 ÷ 2 = 25  remainder 0
25 ÷ 2 = 12  remainder 1
12 ÷ 2 =  6  remainder 0
 6 ÷ 2 =  3  remainder 0
 3 ÷ 2 =  1  remainder 1
 1 ÷ 2 =  0  remainder 1

Read remainders bottom to top: 1 1 0 0 1 0
```

So **50** in decimal = **110010** in binary.

### Quick Reference: 0–15 in Binary

| Decimal | Binary |
|---|---|
| 0 | 0000 |
| 1 | 0001 |
| 2 | 0010 |
| 3 | 0011 |
| 4 | 0100 |
| 5 | 0101 |
| 6 | 0110 |
| 7 | 0111 |
| 8 | 1000 |
| 9 | 1001 |
| 10 | 1010 |
| 11 | 1011 |
| 12 | 1100 |
| 13 | 1101 |
| 14 | 1110 |
| 15 | 1111 |

---

## 3. How Computers Store Data

### Bits and Bytes

| Unit | Size | Notes |
|---|---|---|
| **Bit** | 1 bit | Smallest unit — a single 0 or 1 |
| **Nibble** | 4 bits | Half a byte |
| **Byte** | 8 bits | Can represent 256 values (0–255) |
| **Kilobyte (KB)** | 1,024 bytes | A short text document |
| **Megabyte (MB)** | 1,024 KB | A photo or song |
| **Gigabyte (GB)** | 1,024 MB | A movie |
| **Terabyte (TB)** | 1,024 GB | A large hard drive |

### Why 8 bits = 1 byte?

8 bits gives us 2⁸ = **256** possible combinations (0–255). This range is enough to represent all standard English characters, basic symbols, and small numbers — making it a natural, useful chunk size.

### Memory vs Storage

- **RAM (Memory):** Temporary, fast, used while programs run. Lost when power is off.
- **Storage (SSD/HDD):** Permanent, slower, keeps data even when power is off.

---

## 4. Representing Text — ASCII & Unicode

### ASCII

Computers only understand numbers. So early engineers made a table that maps numbers to characters — this is **ASCII** (American Standard Code for Information Interchange).

- Each character is stored as a number (0–127)
- Uses 7 bits

**Key ASCII values to know:**

| Character | Decimal | Binary |
|---|---|---|
| `A` | 65 | 01000001 |
| `B` | 66 | 01000010 |
| `Z` | 90 | 01011010 |
| `a` | 97 | 01100001 |
| `z` | 122 | 01111010 |
| `0` | 48 | 00110000 |
| `9` | 57 | 00111001 |
| Space | 32 | 00100000 |

**Example:** The word `HI` is stored as `72 73` in decimal, or `01001000 01001001` in binary.

### The Problem with ASCII

ASCII was designed for English. It only covers 128 characters and cannot represent:

- Accented characters: `é`, `ñ`, `ü`
- Non-Latin scripts: Arabic, Chinese, Hindi, Japanese
- Emoji: 😊, 🎉, ❤️

### Unicode

**Unicode** is the solution. It is a universal standard that can represent over **1.1 million characters** from every language and writing system on Earth.

- **UTF-8** is the most common Unicode encoding — backward compatible with ASCII
- Uses 1–4 bytes per character
- Emoji are just Unicode characters: 😊 = U+1F60A

> When you send someone a 😊, your phone is actually sending the number `128522` (or `U+1F60A`), and their phone's software looks up that number and renders the correct emoji image.

---

## 5. Representing Images, Video & Sound

### Images — Pixels and RGB

A digital image is a grid of tiny colored squares called **pixels** (picture elements).

Each pixel's color is described by mixing three values:

| Channel | Controls |
|---|---|
| **R** — Red | Amount of red light (0–255) |
| **G** — Green | Amount of green light (0–255) |
| **B** — Blue | Amount of blue light (0–255) |

This is the **RGB color model**.

**Examples:**

| Color | R | G | B |
|---|---|---|---|
| Black | 0 | 0 | 0 |
| White | 255 | 255 | 255 |
| Red | 255 | 0 | 0 |
| Green | 0 | 255 | 0 |
| Blue | 0 | 0 | 255 |
| Yellow | 255 | 255 | 0 |
| Orange | 255 | 165 | 0 |

With 3 channels × 8 bits each = **24 bits per pixel**.  
A 1920×1080 image has 2,073,600 pixels × 3 bytes = ~6 MB of raw data (before compression).

### Resolution

The more pixels, the sharper the image:

- **Low resolution:** 320×240 pixels
- **HD:** 1280×720 pixels
- **Full HD:** 1920×1080 pixels
- **4K:** 3840×2160 pixels

### Video

Video is just a rapid sequence of images (frames) played back fast enough that your brain perceives motion.

- Standard video: **24–30 frames per second (fps)**
- Smooth motion: **60 fps**
- Slow-motion: recorded at high fps, played back at low fps

### Sound

Sound is represented as **waveforms** — measurements of air pressure over time.

- **Sample rate:** How many measurements per second (e.g., 44,100 Hz = CD quality)
- **Bit depth:** How precise each measurement is (e.g., 16-bit)
- Higher sample rate + higher bit depth = better quality, larger file size

---

## 6. Algorithms

An **algorithm** is a step-by-step set of instructions for solving a problem.

The same problem can have many different algorithms — some much faster than others. Choosing the right algorithm is one of the most important skills in computer science.

### Example: Finding a Name in a Phone Book

Imagine a phone book with 1,000 pages and you want to find "John Harvard."

#### Algorithm 1 — Linear Search (page by page)

```
Open to page 1
If John Harvard is here → done!
Otherwise, turn to the next page
Repeat until found or book ends
```

- **Worst case:** 1,000 steps (last page or not there)
- **Best case:** 1 step (first page)
- **Speed:** Slow — grows linearly with the size of the input

#### Algorithm 2 — Linear Search (2 pages at a time)

```
Open to page 1
Check 2 pages at a time
```

- Twice as fast as Algorithm 1
- But still **linear** — still 500 steps in the worst case

#### Algorithm 3 — Binary Search (divide and conquer)

```
Open to the middle of the book
If John Harvard is to the left → discard the right half
If John Harvard is to the right → discard the left half
Repeat with the remaining half
```

- **Worst case:** ~10 steps for 1,000 pages (because 2¹⁰ = 1,024)
- **This is massively faster!**

### Big-O Notation — Measuring Algorithm Speed

Big-O describes how an algorithm's runtime **scales** with input size `n`.

| Notation | Name | Example | 1,000 inputs → steps |
|---|---|---|---|
| O(1) | Constant time | Accessing an array index | Always 1 |
| O(log n) | Logarithmic | Binary search | ~10 |
| O(n) | Linear | Linear search | 1,000 |
| O(n log n) | Log-linear | Merge sort | ~10,000 |
| O(n²) | Quadratic | Bubble sort | 1,000,000 |

> The smaller the Big-O, the faster the algorithm scales. O(log n) is dramatically better than O(n) for large inputs.

### Visualizing the Difference

```
Steps
  │
  │        O(n²)
  │       /
  │      /
  │     /   O(n)
  │    /   /
  │   /   /  O(log n)
  │  /   /  /
  │ /   /  / ──────── O(1)
  └─────────────────────── Input Size (n)
```

---

## 7. Pseudocode

**Pseudocode** is a way to plan your algorithm in plain English before writing actual code. It's not a real programming language — it's just a structured way to think through logic.

### Rules of Pseudocode

- Write one action per line
- Be precise and unambiguous
- Use indentation to show structure
- Use keywords like: `if`, `else`, `while`, `for`, `return`

### Example: Finding the Smallest Number in a List

```
Set min to the first number in the list
For each remaining number in the list
    If the number is less than min
        Set min to that number
Return min
```

### Example: Checking if a Number is Prime

```
If number is less than 2
    Return "not prime"
For each integer i from 2 to number - 1
    If number is divisible by i
        Return "not prime"
Return "prime"
```

### Why Pseudocode Matters

- Forces you to **think before you code**
- Makes bugs easier to spot **before** they become code
- Language-independent — the same logic works in any language
- Useful in interviews, team discussions, and documentation

---

## 8. Abstraction

**Abstraction** is the idea of simplifying complexity by hiding unnecessary details.

You use abstraction every day:

- You **drive a car** without knowing how the engine works
- You **use a microwave** without knowing the physics of electromagnetic waves
- You **call a function** without knowing exactly how it's implemented inside

### Abstraction in Programming

In programming, abstraction means:

- Building **functions** so you can reuse logic without rewriting it
- Using **libraries** so you don't reinvent common tools
- Writing code at a **high level** that reads like human language, even though the machine runs binary

### Layers of Abstraction in a Computer

```
Your Program (Python, C, JavaScript...)
         ↓
Operating System (Windows, macOS, Linux)
         ↓
Machine Code (binary instructions)
         ↓
Hardware (transistors, circuits)
         ↓
Physics (electricity, quantum mechanics)
```

Each layer hides the complexity below it. You don't need to understand transistors to write Python.

### Why Abstraction is a Superpower

Without abstraction:
- Every programmer would have to rewrite sorting, math, I/O from scratch
- Programs would be millions of lines of low-level code

With abstraction:
- You call `sort()` and it just works
- You focus on solving your actual problem, not the plumbing

---

## 9. Introduction to Scratch

**Scratch** is a visual, block-based programming language made by MIT. It's used in CS50 Week 0 to teach programming concepts *without* the syntax burden of a text-based language.

- Website: [scratch.mit.edu](https://scratch.mit.edu)
- Programs are called **projects**
- Logic is assembled by dragging and snapping colorful blocks together

### The Scratch Interface

```
┌─────────────────────────────────────────────────────┐
│  Block Palette  │     Scripts Area     │   Stage     │
│                 │                      │  (preview)  │
│  [Motion]       │  when 🚩 clicked     │             │
│  [Looks]        │  ┌─────────────────┐ │   🐱        │
│  [Sound]        │  │  say "Hello!" 2s│ │             │
│  [Events]       │  └─────────────────┘ │             │
│  [Control]      │                      │             │
│  [Sensing]      │                      │             │
│  [Operators]    │                      │             │
│  [Variables]    │                      │             │
│  [My Blocks]    │                      │             │
└─────────────────────────────────────────────────────┘
```

| Component | Description |
|---|---|
| **Stage** | Where your project runs — the visual output area |
| **Sprite** | A character or object on the stage (the cat by default) |
| **Backdrop** | The background image of the stage |
| **Block Palette** | All available blocks, organized by category |
| **Scripts Area** | Where you drag blocks to build your program |

### Block Categories

| Category | Color | Used For |
|---|---|---|
| Motion | Dark blue | Moving sprites around the stage |
| Looks | Purple | Changing appearance, saying things |
| Sound | Pink | Playing sounds and music |
| Events | Yellow | Starting scripts (green flag, key press, etc.) |
| Control | Orange | Loops, if-statements, waiting |
| Sensing | Light blue | Detecting input, touching, asking questions |
| Operators | Green | Math, comparisons, string operations |
| Variables | Dark orange | Storing and changing data |
| My Blocks | More pink | Creating custom functions |

---

## 10. Core Programming Concepts in Scratch

All programming, in every language, comes down to a small set of fundamental building blocks. Scratch teaches all of them visually.

### The 6 Core Concepts

| Concept | What It Means | Scratch Example |
|---|---|---|
| **Sequence** | Instructions run one after another, top to bottom | Stack blocks vertically |
| **Loops** | Repeat a block of instructions multiple times | `repeat 10` / `forever` |
| **Conditions** | Run code only if something is true | `if <touching edge?> then` |
| **Variables** | Store and change a value | `set [score] to 0` |
| **Functions** | A named, reusable set of instructions | `My Blocks` → `define jump` |
| **Events** | Trigger code when something happens | `when 🚩 clicked` |

### Scratch ↔ Real Programming Language Comparison

| Concept | Scratch | C (Week 1) | Python |
|---|---|---|---|
| Print to screen | `say "Hello!"` | `printf("Hello");` | `print("Hello")` |
| Get user input | `ask [] and wait` | `get_string("Name: ")` | `input("Name: ")` |
| Store a value | `set [x] to 5` | `int x = 5;` | `x = 5` |
| Loop N times | `repeat 10` | `for (int i = 0; i < 10; i++)` | `for i in range(10):` |
| Conditional | `if <> then` | `if (condition)` | `if condition:` |
| Custom function | `define myBlock` | `void myFunction()` | `def my_function():` |

---

## 11. Functions in Scratch

Functions let you **group instructions** under a name, so you can reuse them without copying blocks over and over.

### Creating a Custom Block (Function)

1. Click **My Blocks** → **Make a Block**
2. Name it (e.g., `jump`)
3. Add the steps inside the `define jump` hat block
4. Call it anywhere in your project by using the `jump` block

```
define jump
    change y by 50
    wait 0.3 seconds
    change y by -50
```

Now you can call `jump` anywhere in your project instead of repeating those 3 blocks every time.

### Why Functions Are Important

- **Avoid repetition** — write the logic once, use it many times
- **Easier to fix** — if `jump` has a bug, fix it in one place, not everywhere you copied blocks
- **Readable** — code that says `jump`, `shoot`, `check_score` is easier to understand than a wall of raw blocks
- This is the principle of **DRY: Don't Repeat Yourself**

### Parameters in Custom Blocks

Custom blocks can accept **inputs** (parameters) to make them flexible:

```
define move steps (distance)
    move (distance) steps

→ call: move steps 10
→ call: move steps 50
```

---

## 12. Loops in Scratch

Loops **repeat** a set of blocks multiple times.

### Types of Loops in Scratch

#### `repeat n` — runs exactly n times

```
repeat 4
    move 100 steps
    turn 90 degrees
```
This draws a square.

#### `forever` — runs until the project stops

```
forever
    if <touching edge?> then
        turn 180 degrees
    move 10 steps
```
This makes a sprite bounce around forever.

#### `repeat until <condition>` — runs until a condition becomes true

```
repeat until <(score) > 10>
    wait 1 second
    change score by 1
```

### When to Use Each

| Loop | Use When |
|---|---|
| `repeat n` | You know exactly how many times |
| `forever` | You want something to run continuously (game loop, animation) |
| `repeat until` | You want to loop until something happens |

---

## 13. Conditionals in Scratch

Conditionals let your program **make decisions** — run different code depending on whether something is true or false.

### `if <condition> then`

```
if <touching color [red]?> then
    say "Ouch!" for 1 second
```

The block inside only runs if the sprite is touching red.

### `if <condition> then ... else`

```
if <(score) > 10> then
    say "You win!"
else
    say "Keep trying!"
```

Only one branch runs — either the `then` part or the `else` part, never both.

### Nested Conditionals

You can put an `if` inside another `if`:

```
if <(score) > 50> then
    if <(lives) > 0> then
        say "Level up!"
    else
        say "Game over!"
```

### Boolean Operators

You can combine conditions using:

| Operator | Meaning | Example |
|---|---|---|
| `<A> and <B>` | Both must be true | `<score > 5> and <lives > 0>` |
| `<A> or <B>` | At least one must be true | `<touching wall?> or <touching enemy?>` |
| `not <A>` | Inverts true/false | `not <touching edge?>` |

---

## 14. Variables in Scratch

A **variable** is a named box in memory that stores a value you can read and change.

### Creating a Variable

1. Click **Variables** → **Make a Variable**
2. Name it (e.g., `score`, `lives`, `timer`)
3. Choose: **For all sprites** (global) or **For this sprite only** (local)

### Using Variables

```
when 🚩 clicked
set [score] to 0
set [lives] to 3

forever
    if <touching [coin]?> then
        change [score] by 1

    if <touching [enemy]?> then
        change [lives] by -1
```

### Common Variable Operations

| Block | What It Does |
|---|---|
| `set [x] to 0` | Assign a value |
| `change [x] by 1` | Add to the current value |
| `show variable [x]` | Display value on stage |
| `hide variable [x]` | Hide the display |

### Lists (Arrays)

Scratch also has **lists** — variables that store multiple values:

```
add [Alice] to [names]
add [Bob] to [names]
item 1 of [names]   → "Alice"
length of [names]   → 2
```

Lists in Scratch map directly to **arrays** in other languages.

---

## 15. Events in Scratch

**Events** are triggers — they start a script when something specific happens.

### Common Event Blocks

| Block | Triggers When |
|---|---|
| `when 🚩 clicked` | User clicks the green flag (start) |
| `when [space] key pressed` | A specific keyboard key is pressed |
| `when this sprite clicked` | User clicks on this sprite |
| `when backdrop switches to [x]` | Background changes |
| `when I receive [message]` | Another script broadcasts a message |
| `broadcast [message]` | Sends a message to trigger other scripts |

### Broadcasting — Communication Between Sprites

`broadcast` and `when I receive` let different sprites communicate:

**Sprite 1 (Player):**
```
if <touching [enemy]?> then
    broadcast [game over]
```

**Sprite 2 (Score Display):**
```
when I receive [game over]
    say "Game Over!"
    stop all
```

This is a simple form of **event-driven programming** — the same pattern used in web development (button clicks, mouse events, etc.).

---

## 16. Problem Set 0 Tips

The Week 0 problem set asks you to build a Scratch project that:

- Has at least **2 sprites** (not just the default cat)
- Has at least **3 scripts** total
- Uses at least **1 conditional** (`if`)
- Uses at least **1 loop** (`repeat`, `forever`, or `repeat until`)
- Uses at least **1 variable**
- Is **interactive** — responds to keyboard or mouse input
- Runs for at least **10 seconds**

### Project Ideas

| Idea | Sprites | Interaction | Concepts Used |
|---|---|---|---|
| Simple game (Pong, Pac-Man-like) | Ball, paddle, walls | Arrow keys | loops, variables, conditionals, events |
| Interactive story / animation | Characters, backdrop | Click to advance | events, broadcast, conditionals |
| Quiz game | Question sprite, score display | Click answers | variables, conditionals, events |
| Music visualizer | Notes, animations | Spacebar to play | loops, events, sound |
| Maze game | Player, walls, exit | Arrow keys | conditionals, events, loops |

### Common Mistakes to Avoid

| Mistake | Fix |
|---|---|
| Only one script total | Spread logic across multiple sprites and hat blocks |
| No interactivity | Add `when [key] pressed` or `when sprite clicked` |
| Forgetting to initialize variables | Always `set [score] to 0` at start with `when 🚩 clicked` |
| Infinite loops with no exit | Use `repeat until` or `broadcast [stop]` to end |
| Too simple — no challenge | Add a score, timer, lives, or multiple levels |

---

## 17. Key Takeaways

These are the most important concepts from Week 0 — understanding these deeply will make all future weeks much easier.

### Computation is just manipulation of numbers

At the hardware level, everything — text, images, sound, video — is stored as binary numbers (0s and 1s). All computation is arithmetic on those numbers.

### Algorithms are everywhere

Anytime you solve a step-by-step problem — making a recipe, giving directions, following a process — you are following an algorithm. Computer programs are just very precise, formal algorithms.

### Efficiency matters

Two algorithms can solve the same problem but at wildly different speeds. A binary search (O(log n)) on 1 billion records takes ~30 steps. A linear search (O(n)) takes 1 billion steps. Choosing the right algorithm is often more impactful than hardware or language choice.

### Abstraction lets you build big things

No one person understands every layer of a modern computer system — from physics to hardware to OS to your app. Abstraction at each layer makes it possible to build incredible complexity from manageable pieces.

### The concepts in Scratch are universal

Every concept from Week 0 carries forward:

| Week 0 Concept | Week 1+ Equivalent |
|---|---|
| `repeat 10` | `for` loop |
| `if <> then / else` | `if / else` statement |
| `set [x] to 0` | `int x = 0;` |
| `define myBlock` | `void myFunction()` |
| `when 🚩 clicked` | `int main(void)` |
| `ask [] and wait` | `get_string()` |
| `say []` | `printf()` |

> **The syntax changes. The thinking doesn't.**

---

*CS50 Week 0 Notes · Harvard University · David J. Malan*
