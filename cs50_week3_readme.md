# CS50 — Week 3: Algorithms

**Harvard University** · David J. Malan  
**Topic:** Searching, sorting, algorithm efficiency, recursion, and how to think about the speed of your code.

---

## Table of Contents

1. [Recap — What is an Algorithm?](#1-recap--what-is-an-algorithm)
2. [Searching Algorithms](#2-searching-algorithms)
3. [Big-O Notation — Measuring Efficiency](#3-big-o-notation--measuring-efficiency)
4. [Omega Ω and Theta Θ Notation](#4-omega-ω-and-theta-θ-notation)
5. [Sorting Algorithms](#5-sorting-algorithms)
6. [Recursion](#6-recursion)
7. [Merge Sort — Recursion in Action](#7-merge-sort--recursion-in-action)
8. [Comparing All Sorting Algorithms](#8-comparing-all-sorting-algorithms)
9. [Problem Set 3 — Plurality & Runoff](#9-problem-set-3--plurality--runoff)
10. [Quick Reference Cheat Sheet](#10-quick-reference-cheat-sheet)

---

## 1. Recap — What is an Algorithm?

An **algorithm** is a finite, step-by-step set of instructions that solves a problem.

Every algorithm can be judged on three things:

| Property | Question |
|---|---|
| **Correctness** | Does it always produce the right answer? |
| **Efficiency** | How fast does it run? How much memory does it use? |
| **Clarity** | Is it easy to understand, maintain, and debug? |

The big focus of Week 3 is **efficiency** — two algorithms can both be correct, but one can be *dramatically* faster.

---

## 2. Searching Algorithms

Searching means finding a target value inside a collection of data.

---

### 2.1 Linear Search

**Idea:** Check every element one by one from left to right until you find the target or exhaust the list.

```
Array: [20, 8, 3, 14, 6, 11, 5]
Target: 11

Check index 0 → 20  ✗
Check index 1 →  8  ✗
Check index 2 →  3  ✗
Check index 3 → 14  ✗
Check index 4 →  6  ✗
Check index 5 → 11  ✓  FOUND at index 5
```

#### Implementation in C

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 8, 3, 14, 6, 11, 5};
    int n = 7;
    int target = 11;

    for (int i = 0; i < n; i++)
    {
        if (numbers[i] == target)
        {
            printf("Found at index %i\n", i);
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}
```

#### Searching for Strings with Linear Search

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"Alice", "Bob", "Charlie", "Diana"};
    int n = 4;

    string target = get_string("Name: ");

    for (int i = 0; i < n; i++)
    {
        if (strcmp(names[i], target) == 0)
        {
            printf("Found %s!\n", names[i]);
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}
```

#### Performance

| Case | Steps |
|---|---|
| Best case | 1 (target is first element) |
| Worst case | n (target is last or not present) |
| Average case | n/2 |

> **Works on unsorted data.** No requirement for the array to be in order.

---

### 2.2 Binary Search

**Idea:** Repeatedly cut the search space in half by comparing the target to the middle element. Requires the array to be **sorted**.

```
Sorted Array: [3, 5, 6, 8, 11, 14, 20]
Target: 6

Step 1: middle = index 3 → value 8
        6 < 8 → search LEFT half
        Array: [3, 5, 6]

Step 2: middle = index 1 → value 5
        6 > 5 → search RIGHT half
        Array: [6]

Step 3: middle = index 0 → value 6
        6 == 6 ✓ FOUND!
```

#### Pseudocode

```
Set low = 0, high = n - 1

While low <= high:
    Set mid = (low + high) / 2

    If target == array[mid]:
        Return mid  (found!)

    Else if target < array[mid]:
        Set high = mid - 1  (search left half)

    Else:
        Set low = mid + 1   (search right half)

Return -1  (not found)
```

#### Implementation in C

```c
#include <stdio.h>

int binary_search(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid;
        else if (target < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;  // not found
}

int main(void)
{
    int numbers[] = {3, 5, 6, 8, 11, 14, 20};
    int n = 7;

    int result = binary_search(numbers, n, 6);

    if (result != -1)
        printf("Found at index %i\n", result);
    else
        printf("Not found\n");
}
```

#### Performance

| Case | Steps |
|---|---|
| Best case | 1 (target is the middle element) |
| Worst case | log₂(n) |
| Average case | log₂(n) |

#### Why log₂(n)?

Each step cuts the problem in half:

```
n = 1,000,000 elements

Step 1: 1,000,000 → 500,000
Step 2:   500,000 → 250,000
Step 3:   250,000 → 125,000
...
Step 20:        1 → found!

log₂(1,000,000) ≈ 20 steps
```

Binary search on 1 million elements takes only ~20 comparisons. Linear search could take 1,000,000.

#### Linear vs Binary Search

| | Linear Search | Binary Search |
|---|---|---|
| **Requires sorted data?** | No | Yes |
| **Best case** | O(1) | O(1) |
| **Worst case** | O(n) | O(log n) |
| **1,000 elements** | Up to 1,000 steps | Up to 10 steps |
| **1,000,000 elements** | Up to 1,000,000 steps | Up to 20 steps |

---

## 3. Big-O Notation — Measuring Efficiency

**Big-O** describes how an algorithm's runtime grows relative to the input size `n` — specifically its **worst-case** performance.

It tells you the *shape* of the growth curve, ignoring constants and small terms.

### Common Big-O Complexities (Best to Worst)

| Notation | Name | Description | Example |
|---|---|---|---|
| O(1) | Constant | Always takes the same time regardless of n | Access `arr[5]` |
| O(log n) | Logarithmic | Halves the problem each step | Binary search |
| O(n) | Linear | One operation per element | Linear search |
| O(n log n) | Log-linear | n operations, each taking log n | Merge sort |
| O(n²) | Quadratic | Nested loops over the data | Bubble sort, selection sort |
| O(2ⁿ) | Exponential | Doubles with each added element | Naive recursion |
| O(n!) | Factorial | Every permutation | Brute-force traveling salesman |

### Visualizing Growth

```
Runtime
  │                                          O(n²)
  │                                        ↗
  │                              O(n log n)
  │                           ↗
  │                  O(n)
  │              ↗
  │      O(log n)
  │   ↗
  │ ↗ O(1)
  └──────────────────────────────────────── n (input size)
```

### Formal Definition (simplified)

O(f(n)) means: for large enough n, the algorithm takes **at most** c × f(n) steps, for some constant c.

We drop constants and lower-order terms:
- `3n + 5` → O(n)
- `2n² + 100n + 7` → O(n²)
- `5 log n + 3` → O(log n)

### Why Constants Don't Matter

If Algorithm A takes `2n` steps and Algorithm B takes `100n` steps, both are O(n). For small n, B might be worse, but they grow at the same *rate*. For very large n, both are dominated by the linear term, not the constant.

---

## 4. Omega Ω and Theta Θ Notation

Big-O measures the **worst case**. But we have two more tools:

| Notation | Measures | Meaning |
|---|---|---|
| **O** (Big-O) | Worst case | Upper bound — algorithm takes *at most* this long |
| **Ω** (Omega) | Best case | Lower bound — algorithm takes *at least* this long |
| **Θ** (Theta) | Average/tight | Exact bound — algorithm takes *exactly* this long (when O and Ω match) |

### Examples

| Algorithm | O (worst) | Ω (best) | Θ (exact) |
|---|---|---|---|
| Linear search | O(n) | Ω(1) | — (they differ) |
| Binary search | O(log n) | Ω(1) | — (they differ) |
| Bubble sort (optimized) | O(n²) | Ω(n) | — (they differ) |
| Selection sort | O(n²) | Ω(n²) | Θ(n²) |
| Merge sort | O(n log n) | Ω(n log n) | Θ(n log n) |

> When O and Ω are the same, we write Θ. Selection sort is **always** O(n²) regardless of input — so Θ(n²).

---

## 5. Sorting Algorithms

Sorting means arranging elements in a specific order (usually ascending). CS50 Week 3 covers four:

- **Selection Sort**
- **Bubble Sort**
- **Insertion Sort** *(briefly)*
- **Merge Sort** *(covered in depth in Section 7)*

---

### 5.1 Selection Sort

**Idea:** Find the smallest element in the unsorted portion and swap it into position. Repeat.

```
Pass 1: [64, 25, 12, 22, 11]
         Find min (11) → swap with index 0
        [11, 25, 12, 22, 64]

Pass 2: [11, 25, 12, 22, 64]
             Find min (12) → swap with index 1
        [11, 12, 25, 22, 64]

Pass 3: [11, 12, 25, 22, 64]
                 Find min (22) → swap with index 2
        [11, 12, 22, 25, 64]

Pass 4: [11, 12, 22, 25, 64]
                     Find min (25) → already in place
        [11, 12, 22, 25, 64]  ✓ Sorted!
```

#### Pseudocode

```
For i from 0 to n-2:
    Set min_index = i
    For j from i+1 to n-1:
        If array[j] < array[min_index]:
            Set min_index = j
    Swap array[i] with array[min_index]
```

#### Implementation in C

```c
void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        // Swap
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}
```

#### Complexity

| | Complexity |
|---|---|
| Best case Ω | O(n²) — always scans the full unsorted portion |
| Worst case O | O(n²) |
| Exact Θ | Θ(n²) — always the same regardless of input |
| Space | O(1) — in-place |

> Selection sort always does the same amount of work, whether the array is sorted or not.

---

### 5.2 Bubble Sort

**Idea:** Repeatedly step through the array, compare adjacent pairs, and swap them if they're out of order. Larger values "bubble up" to the end.

```
Start: [64, 34, 25, 12, 22]

Pass 1:
[64, 34, 25, 12, 22]  → compare 64,34 → swap → [34, 64, 25, 12, 22]
[34, 64, 25, 12, 22]  → compare 64,25 → swap → [34, 25, 64, 12, 22]
[34, 25, 64, 12, 22]  → compare 64,12 → swap → [34, 25, 12, 64, 22]
[34, 25, 12, 64, 22]  → compare 64,22 → swap → [34, 25, 12, 22, 64]
                                                              ↑ 64 is in place

Pass 2:
[34, 25, 12, 22, 64]  → compare 34,25 → swap → [25, 34, 12, 22, 64]
[25, 34, 12, 22, 64]  → compare 34,12 → swap → [25, 12, 34, 22, 64]
[25, 12, 34, 22, 64]  → compare 34,22 → swap → [25, 12, 22, 34, 64]
                                                          ↑ 34 in place

... continue until no swaps needed
```

#### Pseudocode

```
Repeat n-1 times:
    Set swapped = false
    For i from 0 to n-2:
        If array[i] > array[i+1]:
            Swap array[i] and array[i+1]
            Set swapped = true
    If swapped == false:
        Break  (array is already sorted)
```

#### Implementation in C

```c
void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;  // already sorted — early exit
    }
}
```

#### Complexity

| | Complexity |
|---|---|
| Best case Ω | Ω(n) — already sorted; one pass, no swaps, early exit |
| Worst case O | O(n²) — reverse-sorted array |
| Space | O(1) — in-place |

> The early-exit optimization makes bubble sort O(n) on already-sorted data — a key advantage over selection sort.

---

### 5.3 Insertion Sort

**Idea:** Build the sorted array one element at a time. Pick each new element and insert it into its correct position among the already-sorted elements.

```
Start: [12, 11, 13, 5, 6]

i=1: [11, 12, 13, 5, 6]   insert 11 before 12
i=2: [11, 12, 13, 5, 6]   13 already in place
i=3: [ 5, 11, 12, 13, 6]  insert 5 at front
i=4: [ 5,  6, 11, 12, 13] insert 6 after 5
```

#### Complexity

| | Complexity |
|---|---|
| Best case Ω | Ω(n) — already sorted; each element just compared once |
| Worst case O | O(n²) — reverse-sorted |
| Space | O(1) — in-place |

> Insertion sort is **excellent for nearly-sorted data** and very small arrays. Many real sorting implementations use it for small subarrays.

---

## 6. Recursion

**Recursion** is when a function calls **itself** as part of its own definition.

Every recursive solution has two essential parts:

| Part | Purpose |
|---|---|
| **Base case** | The condition where the function stops calling itself |
| **Recursive case** | The part where the function calls itself with a smaller/simpler input |

> ⚠️ Without a base case, recursion never stops — you get infinite recursion and a **stack overflow**.

---

### 6.1 Factorial — Classic Recursion Example

**Mathematical definition:**

```
0! = 1              ← base case
n! = n × (n-1)!     ← recursive case
```

**Expanding the recursion:**

```
factorial(4)
= 4 × factorial(3)
= 4 × 3 × factorial(2)
= 4 × 3 × 2 × factorial(1)
= 4 × 3 × 2 × 1 × factorial(0)
= 4 × 3 × 2 × 1 × 1
= 24
```

#### Iterative Version

```c
int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}
```

#### Recursive Version

```c
int factorial(int n)
{
    // Base case
    if (n == 0)
        return 1;

    // Recursive case
    return n * factorial(n - 1);
}
```

---

### 6.2 How Recursion Works — The Call Stack

Each function call creates a **stack frame** — a block of memory holding that call's local variables and return address. Recursive calls stack up:

```
factorial(4) called
  └─ factorial(3) called
       └─ factorial(2) called
            └─ factorial(1) called
                 └─ factorial(0) called
                      returns 1
                 returns 1 × 1 = 1
            returns 2 × 1 = 2
       returns 3 × 2 = 6
  returns 4 × 6 = 24
```

Each call waits for the call below it to return. The stack unwinds from the bottom up.

> **Stack overflow** happens when recursion goes too deep and exhausts the call stack memory.

---

### 6.3 Fibonacci Sequence

```
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)   for n > 1

Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
```

#### Recursive Implementation

```c
int fibonacci(int n)
{
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

#### The Problem with Naive Fibonacci Recursion

```
fibonacci(5)
├── fibonacci(4)
│   ├── fibonacci(3)
│   │   ├── fibonacci(2)
│   │   │   ├── fibonacci(1) → 1
│   │   │   └── fibonacci(0) → 0
│   │   └── fibonacci(1) → 1
│   └── fibonacci(2)
│       ├── fibonacci(1) → 1   ← REPEATED WORK
│       └── fibonacci(0) → 0
└── fibonacci(3)
    ├── fibonacci(2)            ← REPEATED WORK
    │   ...
    └── fibonacci(1) → 1
```

`fibonacci(3)` is computed **twice**, `fibonacci(2)` three times. The time complexity is O(2ⁿ) — exponential. This is solved by **memoization** (caching) or dynamic programming, covered in later CS50 weeks.

---

### 6.4 Printing with Recursion — Drawing a Pyramid

```c
void draw(int n)
{
    // Base case
    if (n == 0)
        return;

    // Recursive case — draw smaller pyramid first, then add this row
    draw(n - 1);

    for (int i = 0; i < n; i++)
        printf("#");
    printf("\n");
}
```

Calling `draw(4)`:

```
#
##
###
####
```

The recursion reaches the base case, then unwinds — printing smallest row first as the stack collapses.

---

### 6.5 Iteration vs Recursion

Every recursive solution can be rewritten iteratively, and vice versa.

| | Recursion | Iteration |
|---|---|---|
| **Code clarity** | Often more elegant and readable | Can be more verbose |
| **Memory** | Uses call stack (risk of overflow) | Uses constant stack space |
| **Speed** | Function call overhead | Generally faster |
| **Best for** | Tree/graph traversal, divide-and-conquer | Simple loops, known iteration count |

> In CS50, recursion is introduced to build your mental model of divide-and-conquer — the strategy behind merge sort.

---

## 7. Merge Sort — Recursion in Action

**Merge sort** is a sorting algorithm that uses recursion and the divide-and-conquer strategy.

**Idea:**
1. **Divide** the array in half
2. **Recursively sort** each half
3. **Merge** the two sorted halves back together

This keeps going until you have arrays of size 1 — a single element is always sorted.

---

### 7.1 Step-by-Step Walkthrough

```
Start: [38, 27, 43, 3, 9, 82, 10]

── DIVIDE ──────────────────────────────────────────
[38, 27, 43, 3, 9, 82, 10]
         ↙               ↘
[38, 27, 43]          [3, 9, 82, 10]
    ↙      ↘             ↙        ↘
[38]    [27, 43]      [3, 9]    [82, 10]
          ↙   ↘        ↙  ↘      ↙    ↘
        [27]  [43]   [3]  [9]  [82]  [10]

── MERGE ───────────────────────────────────────────
        [27]  [43]   [3]  [9]  [82]  [10]
          ↘   ↙        ↘  ↙      ↘    ↙
        [27, 43]      [3, 9]    [10, 82]
    ↙      ↘             ↙        ↘
[38]    [27, 43]      [3, 9]    [10, 82]
         ↘   ↙             ↘    ↙
        [27, 38, 43]      [3, 9, 10, 82]
              ↘                 ↙
         [3, 9, 10, 27, 38, 43, 82]  ✓ Sorted!
```

---

### 7.2 The Merge Step in Detail

Merging two sorted arrays: `[27, 38, 43]` and `[3, 9, 10, 82]`

```
Left:   [27, 38, 43]
Right:  [ 3,  9, 10, 82]
Result: []

Compare 27 vs 3   → take 3  → Result: [3]
Compare 27 vs 9   → take 9  → Result: [3, 9]
Compare 27 vs 10  → take 10 → Result: [3, 9, 10]
Compare 27 vs 82  → take 27 → Result: [3, 9, 10, 27]
Compare 38 vs 82  → take 38 → Result: [3, 9, 10, 27, 38]
Compare 43 vs 82  → take 43 → Result: [3, 9, 10, 27, 38, 43]
Left exhausted    → take 82 → Result: [3, 9, 10, 27, 38, 43, 82]
```

---

### 7.3 Pseudocode

```
merge_sort(array):
    If length of array <= 1:
        Return array    ← base case

    Split array into left half and right half

    left  = merge_sort(left half)   ← recursive call
    right = merge_sort(right half)  ← recursive call

    Return merge(left, right)


merge(left, right):
    Create empty result array
    While left and right are not empty:
        If left[0] <= right[0]:
            Append left[0] to result
            Remove left[0] from left
        Else:
            Append right[0] to result
            Remove right[0] from right
    Append any remaining elements of left to result
    Append any remaining elements of right to result
    Return result
```

---

### 7.4 Complexity

| | Complexity |
|---|---|
| Best case Ω | Ω(n log n) |
| Worst case O | O(n log n) |
| Exact Θ | Θ(n log n) — always the same |
| Space | O(n) — needs extra memory for merging |

**Why n log n?**

- The **divide** step splits the array log₂(n) times (like binary search)
- The **merge** step at each level processes all n elements
- Total: n elements × log n levels = **n log n**

```
Level 0:  [38, 27, 43, 3, 9, 82, 10]      → n = 7 comparisons
Level 1:  [38,27,43]  [3,9,82,10]          → n = 7 comparisons
Level 2:  [38][27,43] [3,9][82,10]         → n = 7 comparisons
Level 3:  [38][27][43][3][9][82][10]       → base cases

log₂(7) ≈ 3 levels × 7 elements = ~21 total comparisons
```

---

## 8. Comparing All Sorting Algorithms

| Algorithm | Best Case Ω | Worst Case O | Space | Stable? | Notes |
|---|---|---|---|---|---|
| **Selection Sort** | Ω(n²) | O(n²) | O(1) | No | Always n² — never benefits from sorted input |
| **Bubble Sort** | Ω(n) | O(n²) | O(1) | Yes | Best on nearly-sorted data; early exit when sorted |
| **Insertion Sort** | Ω(n) | O(n²) | O(1) | Yes | Excellent for small or nearly-sorted arrays |
| **Merge Sort** | Ω(n log n) | O(n log n) | O(n) | Yes | Always n log n; needs extra memory |

### What Does "Stable" Mean?

A **stable** sort preserves the original order of equal elements.

```
Input: [(Alice, 85), (Bob, 85), (Charlie, 90)]
       (sorted by score)

Stable sort:   Alice and Bob stay in original order
Unstable sort: Bob might appear before Alice
```

Stability matters when sorting by multiple criteria (e.g., sort by score, then alphabetically within same score).

### Which to Use?

| Situation | Best Choice |
|---|---|
| Small array (< 10 elements) | Insertion sort |
| Nearly sorted data | Insertion or Bubble sort |
| General purpose, unknown data | Merge sort |
| Memory-constrained, don't care about stability | Selection sort |
| Production code | Use `qsort()` from `<stdlib.h>` — the standard library handles it |

---

## 9. Problem Set 3 — Plurality & Runoff

Week 3's problem set implements real voting systems in C.

---

### 9.1 Plurality Voting

**How it works:** Each voter votes for one candidate. The candidate with the most votes wins — simple majority.

```
Votes: Alice: 4, Bob: 3, Charlie: 2
Winner: Alice
```

**Key tasks in the problem set:**

```c
// Data structure
typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[MAX];
```

- `vote(name)` — find the candidate matching the name, increment their votes, return true. Return false if name doesn't match anyone.
- `print_winner()` — find the max vote count, print every candidate with that count (handles ties).

#### vote() Implementation Pattern

```c
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}
```

#### print_winner() Implementation Pattern

```c
void print_winner(void)
{
    // Find max votes
    int max = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
            max = candidates[i].votes;
    }

    // Print all candidates with max votes (handles ties)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
            printf("%s\n", candidates[i].name);
    }
}
```

---

### 9.2 Runoff Voting (Instant-Runoff / Ranked Choice)

**How it works:** Voters rank candidates by preference (1st choice, 2nd choice, etc.). If no candidate gets a majority (>50%), the candidate with the fewest votes is **eliminated** and their voters' ballots are redistributed to their next choice. Repeat until someone has a majority.

```
Round 1: Alice: 4, Bob: 3, Charlie: 2  → No majority (need 5/9 = 5)
Eliminate Charlie (fewest votes)
Charlie's 2 votes redistributed to 2nd choices

Round 2: Alice: 5, Bob: 4  → Alice has majority → Alice wins!
```

**Key functions to implement:**

| Function | Purpose |
|---|---|
| `vote(voter, rank, name)` | Record voter's rank-th choice preference |
| `tabulate()` | Count votes for each non-eliminated candidate based on current top preferences |
| `print_winner()` | Print winner if someone has >50% of votes |
| `find_min()` | Return the minimum vote count among non-eliminated candidates |
| `is_tie(min)` | Check if all remaining candidates are tied |
| `eliminate(min)` | Eliminate all candidates with the minimum vote count |

#### Key Data Structures

```c
// 2D array: preferences[voter][rank] = candidate index
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;
```

#### tabulate() Pattern

```c
void tabulate(void)
{
    // Reset all vote counts
    for (int i = 0; i < candidate_count; i++)
        candidates[i].votes = 0;

    // For each voter, find their top non-eliminated choice
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int pref = preferences[i][j];   // candidate index for rank j
            if (!candidates[pref].eliminated)
            {
                candidates[pref].votes++;
                break;   // count only the top remaining preference
            }
        }
    }
}
```

#### Common Mistakes in Problem Set 3

| Mistake | Fix |
|---|---|
| Using `==` to compare candidate names | Use `strcmp(candidates[i].name, name) == 0` |
| Not resetting vote counts in `tabulate()` | Set all `.votes = 0` at the start of tabulate |
| Forgetting to skip eliminated candidates | Check `!candidates[i].eliminated` |
| Printing winner only if exactly one candidate has max | Use a loop — multiple candidates can tie |
| Not handling ties in `is_tie()` | Check all non-eliminated candidates have the same votes |

---

## 10. Quick Reference Cheat Sheet

### Searching

```c
// Linear Search — O(n)
for (int i = 0; i < n; i++)
    if (arr[i] == target) return i;
return -1;

// Binary Search — O(log n) — REQUIRES SORTED ARRAY
int low = 0, high = n - 1;
while (low <= high)
{
    int mid = (low + high) / 2;
    if (arr[mid] == target) return mid;
    else if (target < arr[mid]) high = mid - 1;
    else low = mid + 1;
}
return -1;
```

### Swapping Two Elements

```c
// Always need a temp variable
int temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
```

### Recursion Template

```c
return_type function(params)
{
    // Base case — ALWAYS first
    if (base_condition)
        return base_value;

    // Recursive case — move toward base case
    return function(smaller_params);
}
```

### Big-O Complexity Reference

| O(1) | O(log n) | O(n) | O(n log n) | O(n²) |
|---|---|---|---|---|
| Array index | Binary search | Linear search | Merge sort | Bubble / Selection sort |

### Struct Syntax

```c
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

candidate c;
c.name = "Alice";
c.votes = 0;
c.eliminated = false;
```

### Key Rules for Week 3

| Rule | Why It Matters |
|---|---|
| Binary search requires sorted input | Splitting randomly gives wrong results |
| Every recursive function needs a base case | Without it: infinite recursion → stack overflow |
| Use `strcmp` not `==` for string comparison | `==` compares addresses, not content |
| Selection sort is always O(n²) | No early exit — never benefits from partially sorted data |
| Merge sort always uses O(n) extra space | It needs a temporary array to merge into |
| Bubble sort is O(n) best case (with early exit) | If no swaps happen in a pass, the array is sorted |

---

*CS50 Week 3 Notes · Harvard University · David J. Malan*
