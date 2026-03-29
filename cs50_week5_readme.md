# CS50 — Week 5: Data Structures

**Harvard University** · David J. Malan  
**Topic:** Linked lists, trees, hash tables, tries, queues, stacks — building and choosing the right data structure for the job.

---

## Table of Contents

1. [Recap — Arrays and Their Limits](#1-recap--arrays-and-their-limits)
2. [Linked Lists](#2-linked-lists)
3. [Linked List Operations](#3-linked-list-operations)
4. [Doubly Linked Lists](#4-doubly-linked-lists)
5. [Trees](#5-trees)
6. [Binary Search Trees](#6-binary-search-trees)
7. [Hash Tables](#7-hash-tables)
8. [Tries](#8-tries)
9. [Stacks](#9-stacks)
10. [Queues](#10-queues)
11. [Choosing the Right Data Structure](#11-choosing-the-right-data-structure)
12. [Problem Set 5 — Speller](#12-problem-set-5--speller)
13. [Quick Reference Cheat Sheet](#13-quick-reference-cheat-sheet)

---

## 1. Recap — Arrays and Their Limits

Before building new data structures, it's worth understanding exactly *why* arrays fall short in certain situations.

### What Arrays Do Well

```c
int scores[5] = {10, 20, 30, 40, 50};

scores[2]      // O(1) — instant access by index
scores[2] = 99 // O(1) — instant update
```

- **Random access in O(1)** — because elements are contiguous in memory, `arr[i]` is just `base_address + i * sizeof(type)`
- **Cache-friendly** — contiguous memory means your CPU's cache works efficiently
- **Simple** — no overhead, just raw bytes

### Where Arrays Fall Short

#### Problem 1 — Fixed Size

```c
int arr[5];   // exactly 5 ints — no more, no less
```

You must know the size at compile time (or at allocation time with `malloc`). If you need to grow, you have to:

1. `malloc` a new, larger array
2. Copy every element over
3. `free` the old array

That's O(n) just to resize — and you might waste space if you over-allocate.

#### Problem 2 — Inserting in the Middle is Expensive

To insert a value at index 2 in a sorted array of 1,000 elements:

```
Before: [1, 3, 5, 8, 10, ...]
Insert 4 at index 2:

Shift 998 elements one position right → O(n)
Then place 4 at index 2
```

#### Problem 3 — Deleting from the Middle is Expensive

Same issue — removing an element leaves a gap. You must shift all elements after it left → O(n).

### The Core Tradeoff

| Operation | Array | Linked List |
|---|---|---|
| Access by index | O(1) ✅ | O(n) ❌ |
| Insert at front | O(n) ❌ | O(1) ✅ |
| Insert at end (known size) | O(1) ✅ | O(n) or O(1) with tail pointer |
| Insert in middle | O(n) ❌ | O(1) if you have the node ✅ |
| Delete | O(n) ❌ | O(1) if you have the node ✅ |
| Memory | Contiguous ✅ | Scattered ❌ |
| Cache performance | Excellent ✅ | Poor ❌ |

---

## 2. Linked Lists

A **linked list** is a sequence of **nodes**. Each node stores:
1. A **value** (data)
2. A **pointer** to the next node

The nodes do **not** have to be contiguous in memory — each node is independently `malloc`'d anywhere on the heap, and the pointer connects them into a chain.

```
┌───────┬────┐   ┌───────┬────┐   ┌───────┬──────┐
│   1   │  ──┼──►│   2   │  ──┼──►│   3   │ NULL │
└───────┴────┘   └───────┴────┘   └───────┴──────┘
  node 1            node 2            node 3
 (at 0x100)        (at 0x580)        (at 0x220)
```

The last node's pointer is `NULL` — that marks the end of the list.

A single pointer called **`head`** points to the first node. If `head == NULL`, the list is empty.

### Defining a Node with `typedef struct`

```c
typedef struct node
{
    int number;         // the data (can be any type)
    struct node *next;  // pointer to the next node
                        // must use "struct node" (not just "node") here
                        // because the typedef isn't complete yet
}
node;
```

Why `struct node *next` and not `node *next`? Because when the compiler reads the struct definition, `node` hasn't been fully defined yet. Using the full `struct node` tag works because C knows the struct exists by name.

### Creating a Single Node

```c
node *n = malloc(sizeof(node));
if (n == NULL)
    return 1;       // always check malloc

n->number = 1;      // arrow operator: dereference + access member
n->next   = NULL;   // this node points to nothing yet
```

### Arrow Operator `->` vs Dot Operator `.`

```c
node n;      // n is a node directly on the stack
n.number     // use dot — n is NOT a pointer

node *p;     // p is a POINTER to a node
p->number    // use arrow — p IS a pointer
             // p->number is shorthand for (*p).number
```

---

## 3. Linked List Operations

### 3.1 Traversing a Linked List

Walk from `head` to `NULL`, visiting every node:

```c
// Print all values
node *current = head;
while (current != NULL)
{
    printf("%i\n", current->number);
    current = current->next;
}
```

Or with a for loop (more compact):

```c
for (node *current = head; current != NULL; current = current->next)
{
    printf("%i\n", current->number);
}
```

> ⚠️ Never move `head` itself during traversal — you'll lose the start of the list. Always use a temporary pointer like `current`.

---

### 3.2 Inserting at the Front — O(1)

Inserting at the front is cheap — just update two pointers:

```
Before:  head ──► [2] ──► [3] ──► NULL
Insert 1 at front
After:   head ──► [1] ──► [2] ──► [3] ──► NULL
```

```c
node *insert_front(node *head, int value)
{
    // 1. Create new node
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return head;   // allocation failed — return unchanged list

    // 2. Point new node to current head
    n->number = value;
    n->next   = head;

    // 3. New node IS the new head
    return n;
}

// Usage
head = insert_front(head, 1);
```

**Step by step:**

```
Step 1: Create n                   n ──► [1 | NULL]
Step 2: n->next = head             n ──► [1 | ──►[2]──►[3]──►NULL]
Step 3: head = n          head ──► [1] ──► [2] ──► [3] ──► NULL
```

---

### 3.3 Inserting at the End — O(n)

You must walk the entire list to find the last node:

```c
node *insert_end(node *head, int value)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return head;

    n->number = value;
    n->next   = NULL;

    // If list is empty, new node is the head
    if (head == NULL)
        return n;

    // Walk to the last node
    node *current = head;
    while (current->next != NULL)
        current = current->next;

    // Attach new node
    current->next = n;
    return head;
}
```

> You can make end-insertion O(1) by maintaining a **tail pointer** alongside `head`.

---

### 3.4 Inserting in Sorted Order — O(n)

Keep the list sorted as you insert:

```c
node *insert_sorted(node *head, int value)
{
    node *n = malloc(sizeof(node));
    if (n == NULL) return head;
    n->number = value;
    n->next   = NULL;

    // Case 1: list is empty OR new value belongs at front
    if (head == NULL || value < head->number)
    {
        n->next = head;
        return n;
    }

    // Case 2: find the correct position
    node *current = head;
    while (current->next != NULL && current->next->number < value)
        current = current->next;

    // Insert after current
    n->next = current->next;
    current->next = n;
    return head;
}
```

---

### 3.5 Searching a Linked List — O(n)

Linear search — no binary search possible (no random access):

```c
bool search(node *head, int target)
{
    node *current = head;
    while (current != NULL)
    {
        if (current->number == target)
            return true;
        current = current->next;
    }
    return false;
}
```

---

### 3.6 Deleting a Node — O(n)

To delete a node, you need the node *before* it (to update its `next` pointer):

```c
node *delete_value(node *head, int value)
{
    // Case 1: list is empty
    if (head == NULL)
        return NULL;

    // Case 2: delete the head
    if (head->number == value)
    {
        node *new_head = head->next;
        free(head);
        return new_head;
    }

    // Case 3: find the node before the target
    node *current = head;
    while (current->next != NULL && current->next->number != value)
        current = current->next;

    // If found, unlink and free it
    if (current->next != NULL)
    {
        node *to_delete = current->next;
        current->next = to_delete->next;
        free(to_delete);
    }

    return head;
}
```

---

### 3.7 Freeing an Entire Linked List

You **cannot** just `free(head)` — that only frees the first node. You must walk the list and free each node individually.

```c
void free_list(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        node *next = current->next;   // save next BEFORE freeing current
        free(current);
        current = next;
    }
}
```

> ⚠️ Save `current->next` **before** calling `free(current)`. After `free`, the memory is invalid — you can't access `current->next` anymore.

---

### 3.8 Full Linked List Program

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

node *insert_front(node *head, int value);
void print_list(node *head);
void free_list(node *head);

int main(void)
{
    node *head = NULL;   // empty list

    head = insert_front(head, 3);
    head = insert_front(head, 2);
    head = insert_front(head, 1);

    print_list(head);   // 1 → 2 → 3 → NULL

    free_list(head);
    return 0;
}

node *insert_front(node *head, int value)
{
    node *n = malloc(sizeof(node));
    if (n == NULL) return head;
    n->number = value;
    n->next   = head;
    return n;
}

void print_list(node *head)
{
    for (node *cur = head; cur != NULL; cur = cur->next)
        printf("%i → ", cur->number);
    printf("NULL\n");
}

void free_list(node *head)
{
    while (head != NULL)
    {
        node *next = head->next;
        free(head);
        head = next;
    }
}
```

---

## 4. Doubly Linked Lists

A **doubly linked list** adds a `prev` pointer to each node, so you can traverse in **both directions**.

```
NULL ◄── [1] ⇄ [2] ⇄ [3] ──► NULL
          ↑
         head
```

### Node Definition

```c
typedef struct node
{
    int number;
    struct node *next;
    struct node *prev;   // extra pointer backwards
} node;
```

### Trade-offs vs Singly Linked List

| | Singly | Doubly |
|---|---|---|
| Memory per node | 1 pointer overhead | 2 pointer overhead |
| Traverse forward | ✅ | ✅ |
| Traverse backward | ❌ | ✅ |
| Delete given pointer | O(n) — need prev | O(1) — have prev |
| Insert before a node | O(n) | O(1) |
| Complexity | Simple | More pointer updates |

### Inserting at the Front of a Doubly Linked List

```c
node *insert_front(node *head, int value)
{
    node *n = malloc(sizeof(node));
    if (n == NULL) return head;

    n->number = value;
    n->prev   = NULL;    // new head has no previous
    n->next   = head;    // point to old head

    if (head != NULL)
        head->prev = n;  // old head now points back to new node

    return n;            // new node is the new head
}
```

### Deleting from a Doubly Linked List — O(1) Given the Node

```c
node *delete_node(node *head, node *to_delete)
{
    // Update previous node's next pointer
    if (to_delete->prev != NULL)
        to_delete->prev->next = to_delete->next;
    else
        head = to_delete->next;   // deleting the head

    // Update next node's prev pointer
    if (to_delete->next != NULL)
        to_delete->next->prev = to_delete->prev;

    free(to_delete);
    return head;
}
```

---

## 5. Trees

A **tree** is a hierarchical data structure where:

- Each element is called a **node**
- There is exactly one **root** node at the top
- Every node (except the root) has exactly one **parent**
- Nodes can have zero or more **children**
- Nodes with no children are called **leaves**

```
          [8]          ← root
         /   \
       [3]   [10]      ← internal nodes
      /   \     \
    [1]   [6]   [14]   ← leaves (and internal)
         /  \   /
        [4] [7][13]
```

### Tree Terminology

| Term | Meaning |
|---|---|
| **Root** | The topmost node — has no parent |
| **Leaf** | A node with no children |
| **Parent** | A node directly above another |
| **Child** | A node directly below another |
| **Subtree** | Any node and all its descendants |
| **Height** | Length of longest path from root to a leaf |
| **Depth** | Distance from root to a specific node |
| **Degree** | Number of children a node has |

### Why Trees?

Trees combine some of the best properties of arrays and linked lists:

- **Hierarchical** relationships (file systems, org charts, HTML DOM)
- **Fast search** if balanced (binary search trees)
- **Dynamic** — grow and shrink at runtime like linked lists

---

## 6. Binary Search Trees

A **Binary Search Tree (BST)** is a tree where:

1. Each node has **at most 2 children** (left and right)
2. Left subtree values are **less than** the node's value
3. Right subtree values are **greater than** the node's value
4. This rule applies **recursively** to every subtree

```
         [8]
        /   \
      [3]   [10]
     /   \     \
   [1]   [6]   [14]
        /  \   /
       [4] [7][13]
```

Check: every node to the left of [8] is < 8 ✓, every node to the right is > 8 ✓. Same holds for every subtree.

### Node Definition

```c
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;
```

### Searching a BST — O(log n) if balanced

The BST property lets us eliminate half the tree at each step — just like binary search on an array:

```c
bool search(node *root, int target)
{
    // Base case: empty tree or not found
    if (root == NULL)
        return false;

    // Base case: found it
    if (root->number == target)
        return true;

    // Recursive case: go left or right
    if (target < root->number)
        return search(root->left, target);
    else
        return search(root->right, target);
}
```

**Walkthrough — searching for 7 in the tree above:**

```
search(8)  → 7 < 8  → go left
search(3)  → 7 > 3  → go right
search(6)  → 7 > 6  → go right
search(7)  → found! → true
```

Only 4 comparisons for a 10-node tree.

### Inserting into a BST

```c
node *insert(node *root, int value)
{
    // Base case: found the right empty spot
    if (root == NULL)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL) return NULL;
        n->number = value;
        n->left   = NULL;
        n->right  = NULL;
        return n;
    }

    // Recursive case
    if (value < root->number)
        root->left  = insert(root->left,  value);
    else if (value > root->number)
        root->right = insert(root->right, value);
    // If equal, ignore (no duplicates)

    return root;
}
```

### Tree Traversals

There are three standard ways to visit every node in a BST:

#### In-order Traversal — Left, Root, Right

Produces values in **sorted ascending order** — a key property of BSTs.

```c
void inorder(node *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%i ", root->number);
    inorder(root->right);
}
// Output for tree above: 1 3 4 6 7 8 10 13 14
```

#### Pre-order Traversal — Root, Left, Right

Useful for copying or serializing a tree.

```c
void preorder(node *root)
{
    if (root == NULL) return;
    printf("%i ", root->number);
    preorder(root->left);
    preorder(root->right);
}
// Output: 8 3 1 6 4 7 10 14 13
```

#### Post-order Traversal — Left, Right, Root

Useful for deleting a tree (process children before parent).

```c
void postorder(node *root)
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%i ", root->number);
}
// Output: 1 4 7 6 3 13 14 10 8
```

### Freeing a BST

Use post-order traversal — free children before the parent:

```c
void free_tree(node *root)
{
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
```

### Balanced vs Unbalanced BSTs

The O(log n) search time only holds if the tree is **balanced** — roughly equal numbers of nodes on each side.

**Balanced — O(log n):**

```
        [4]
       /   \
     [2]   [6]
    / \   / \
  [1] [3][5] [7]
```

**Unbalanced (degenerate) — O(n), no better than linked list:**

```
[1]
  \
  [2]
    \
    [3]
      \
      [4]
        \
        [5]
```

This happens when you insert already-sorted data. Self-balancing trees (AVL, Red-Black) fix this automatically — covered in upper-level CS courses.

---

## 7. Hash Tables

A **hash table** is the most important data structure in practical programming. It aims to provide **O(1) average-case** insertion, deletion, and lookup.

### Core Idea

1. Take a **key** (like a word or number)
2. Run it through a **hash function** that produces an index
3. Store the value at that index in an array

```
Key: "apple"
     ↓ hash function
Index: 3
     ↓ store in array
array[3] = "apple"
```

Later, to look up "apple":

```
"apple" → hash function → 3 → array[3] → found "apple" in O(1)!
```

### Hash Functions

A hash function maps a key to an integer index. A good hash function:

- Is **deterministic** — same key always gives same index
- Is **fast** — O(1) to compute
- **Distributes uniformly** — minimizes collisions
- **Minimizes collisions** — different keys should rarely hash to the same index

#### Simple Hash Function for Strings (first letter)

```c
int hash(string word)
{
    return toupper(word[0]) - 'A';   // A→0, B→1, ..., Z→25
}
```

#### Better Hash Function (djb2)

```c
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + tolower(c);   // hash * 33 + c

    return hash % TABLE_SIZE;
}
```

This distributes strings more uniformly — much fewer collisions.

### Collisions

A **collision** occurs when two different keys hash to the same index.

```
"alice"  → hash → 3
"alicia" → hash → 3   ← COLLISION!
```

Collisions are unavoidable (pigeonhole principle — infinite keys, finite indices). The question is how to handle them.

### Collision Resolution — Chaining

The most common approach in CS50: each array slot holds a **linked list** of all keys that hash to that index.

```
array[0] → NULL
array[1] → ["bob"] → NULL
array[2] → NULL
array[3] → ["alice"] → ["alicia"] → NULL
array[4] → ["dave"] → NULL
...
```

```c
#define TABLE_SIZE 26

typedef struct node
{
    char word[50];
    struct node *next;
} node;

// The hash table: an array of linked list heads
node *table[TABLE_SIZE];

// Initialize all buckets to NULL
for (int i = 0; i < TABLE_SIZE; i++)
    table[i] = NULL;
```

### Inserting into a Hash Table with Chaining

```c
void insert(char *word)
{
    int index = hash(word);

    // Create new node
    node *n = malloc(sizeof(node));
    if (n == NULL) return;

    strcpy(n->word, word);

    // Insert at front of the list at table[index]
    n->next = table[index];
    table[index] = n;
}
```

### Searching a Hash Table with Chaining

```c
bool search(char *word)
{
    int index = hash(word);

    // Walk the linked list at this bucket
    for (node *cur = table[index]; cur != NULL; cur = cur->next)
    {
        if (strcasecmp(cur->word, word) == 0)
            return true;
    }
    return false;
}
```

### Hash Table Performance

| Case | Time |
|---|---|
| Best case (no collisions) | O(1) |
| Average case (few collisions) | O(1) |
| Worst case (all keys same bucket) | O(n) |

The worst case is theoretically O(n) but with a good hash function and large table, it's effectively O(1) in practice.

### Load Factor

**Load factor** = number of items / number of buckets

A low load factor means fewer collisions and better performance:

```
10 words in 26 buckets → load factor = 0.38  → fast
10 words in 3 buckets  → load factor = 3.33  → slow, many collisions
```

In practice: aim for load factor < 0.7. Resize (rehash) when it gets too high.

### Collision Resolution — Open Addressing (Alternative)

Instead of chaining, find the next available slot in the array itself:

- **Linear probing:** if slot i is full, try i+1, i+2, ...
- **Quadratic probing:** try i+1², i+2², i+3², ...
- **Double hashing:** use a second hash function to determine step size

CS50 primarily uses chaining — it's simpler and handles high load factors better.

---

## 8. Tries

A **trie** (pronounced "try" — from re**trie**val) is a tree structure where each node represents **one character** of a key, and paths from root to leaf spell out complete keys.

### Visual Example — Storing Names

Storing: Hagrid, Harry, Hermione, Ron, Neville

```
root
├── H
│   ├── a
│   │   ├── g ── r ── i ── d [✓]  → "Hagrid"
│   │   └── r ── r ── y [✓]       → "Harry"
│   └── e ── r ── m ── i ── o ── n ── e [✓]  → "Hermione"
├── R
│   └── o ── n [✓]                → "Ron"
└── N
    └── e ── v ── i ── l ── l ── e [✓]  → "Neville"
```

Each `[✓]` marks a node that is the end of a valid word.

### Node Definition

For a trie using only lowercase letters:

```c
#define ALPHABET 26

typedef struct node
{
    bool is_word;                  // true if this node ends a valid word
    struct node *children[ALPHABET]; // one pointer per letter a-z
} node;
```

Each node has **26 child pointers** (one per letter). Most will be `NULL`. Memory usage is high but access is constant time.

### Inserting into a Trie

```c
node *root = NULL;   // global or passed around

bool insert(const char *word)
{
    // Create root if needed
    if (root == NULL)
    {
        root = malloc(sizeof(node));
        if (root == NULL) return false;
        root->is_word = false;
        for (int i = 0; i < ALPHABET; i++)
            root->children[i] = NULL;
    }

    node *cursor = root;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int index = tolower(word[i]) - 'a';   // 'a'→0, 'b'→1, ...

        // Create child node if it doesn't exist
        if (cursor->children[index] == NULL)
        {
            cursor->children[index] = malloc(sizeof(node));
            if (cursor->children[index] == NULL) return false;
            cursor->children[index]->is_word = false;
            for (int j = 0; j < ALPHABET; j++)
                cursor->children[index]->children[j] = NULL;
        }

        cursor = cursor->children[index];
    }

    cursor->is_word = true;   // mark end of word
    return true;
}
```

### Searching in a Trie — O(n) where n = word length

```c
bool search(const char *word)
{
    node *cursor = root;
    if (cursor == NULL) return false;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int index = tolower(word[i]) - 'a';

        if (cursor->children[index] == NULL)
            return false;   // letter not found → word doesn't exist

        cursor = cursor->children[index];
    }

    return cursor->is_word;   // true only if this completes a valid word
}
```

### Why Tries are Powerful

Searching for a word of length L takes exactly **L steps** — it doesn't matter how many words are in the trie. 10 words or 10 million words: same speed.

### Trie Trade-offs

| | Trie | Hash Table |
|---|---|---|
| Search time | O(L) — word length | O(1) average |
| Memory | High — 26 pointers per node | Lower overhead |
| Prefix search | ✅ Natural | ❌ Hard |
| Autocomplete | ✅ Easy | ❌ Hard |
| Collision-free | ✅ Always | ❌ Need to handle |

Tries excel at **prefix-based operations** — autocomplete, spell checking, IP routing tables, dictionaries.

---

## 9. Stacks

A **stack** is a data structure with one rule: **Last In, First Out (LIFO)**.

Think of a stack of plates — you add to the top and remove from the top.

```
Push 1:   [1]
Push 2:   [1][2]
Push 3:   [1][2][3]
Pop:      [1][2]     returns 3
Pop:      [1]        returns 2
```

### Stack Operations

| Operation | Description | Cost |
|---|---|---|
| `push(value)` | Add to the top | O(1) |
| `pop()` | Remove from the top | O(1) |
| `peek()` | Look at top without removing | O(1) |
| `is_empty()` | Check if stack has elements | O(1) |

### Stack with an Array

```c
#define CAPACITY 10

typedef struct
{
    int data[CAPACITY];
    int top;   // index of the top element (-1 if empty)
} Stack;

void init(Stack *s)
{
    s->top = -1;
}

bool push(Stack *s, int value)
{
    if (s->top == CAPACITY - 1)
        return false;   // stack is full
    s->data[++(s->top)] = value;
    return true;
}

int pop(Stack *s)
{
    if (s->top == -1)
        return -1;   // stack is empty
    return s->data[(s->top)--];
}

int peek(Stack *s)
{
    if (s->top == -1)
        return -1;
    return s->data[s->top];
}

bool is_empty(Stack *s)
{
    return s->top == -1;
}
```

### Stack with a Linked List

Using a linked list removes the fixed-size limitation:

```c
typedef struct stack_node
{
    int value;
    struct stack_node *next;
} stack_node;

stack_node *stack_top = NULL;

void push(int value)
{
    stack_node *n = malloc(sizeof(stack_node));
    if (n == NULL) return;
    n->value = value;
    n->next  = stack_top;
    stack_top = n;
}

int pop(void)
{
    if (stack_top == NULL) return -1;
    stack_node *temp = stack_top;
    int value = temp->value;
    stack_top = stack_top->next;
    free(temp);
    return value;
}
```

### Where Stacks are Used

- **Function call stack** — every function call pushes a frame, every return pops it
- **Undo / Redo** — most text editors use a stack for undo history
- **Bracket matching** — compilers use stacks to check matching `{`, `(`, `[`
- **Expression evaluation** — calculators, compilers
- **Backtracking algorithms** — maze solving, depth-first search

---

## 10. Queues

A **queue** is a data structure with one rule: **First In, First Out (FIFO)**.

Think of a line at a coffee shop — the first person in line is the first served.

```
Enqueue 1:   front→[1]←back
Enqueue 2:   front→[1][2]←back
Enqueue 3:   front→[1][2][3]←back
Dequeue:     front→[2][3]←back     returns 1
Dequeue:     front→[3]←back        returns 2
```

### Queue Operations

| Operation | Description | Cost |
|---|---|---|
| `enqueue(value)` | Add to the back | O(1) |
| `dequeue()` | Remove from the front | O(1) |
| `peek()` | Look at front without removing | O(1) |
| `is_empty()` | Check if queue is empty | O(1) |

### Queue with an Array (Circular Buffer)

A naive array queue wastes space — `dequeue` shifts everything. A **circular buffer** solves this:

```c
#define CAPACITY 10

typedef struct
{
    int data[CAPACITY];
    int front;   // index of front element
    int back;    // index where next element goes
    int size;    // number of elements currently in queue
} Queue;

void init(Queue *q)
{
    q->front = 0;
    q->back  = 0;
    q->size  = 0;
}

bool enqueue(Queue *q, int value)
{
    if (q->size == CAPACITY)
        return false;   // full
    q->data[q->back] = value;
    q->back  = (q->back + 1) % CAPACITY;   // wrap around
    q->size++;
    return true;
}

int dequeue(Queue *q)
{
    if (q->size == 0)
        return -1;   // empty
    int value = q->data[q->front];
    q->front = (q->front + 1) % CAPACITY;  // wrap around
    q->size--;
    return value;
}
```

### Queue with a Linked List

```c
typedef struct queue_node
{
    int value;
    struct queue_node *next;
} queue_node;

queue_node *q_front = NULL;
queue_node *q_back  = NULL;

void enqueue(int value)
{
    queue_node *n = malloc(sizeof(queue_node));
    if (n == NULL) return;
    n->value = value;
    n->next  = NULL;

    if (q_back != NULL)
        q_back->next = n;
    q_back = n;

    if (q_front == NULL)
        q_front = n;   // first element
}

int dequeue(void)
{
    if (q_front == NULL) return -1;
    queue_node *temp = q_front;
    int value = temp->value;
    q_front = q_front->next;
    if (q_front == NULL)
        q_back = NULL;   // queue is now empty
    free(temp);
    return value;
}
```

### Stack vs Queue

| | Stack (LIFO) | Queue (FIFO) |
|---|---|---|
| Add | Push to top | Enqueue to back |
| Remove | Pop from top | Dequeue from front |
| Order | Last in, first out | First in, first out |
| Real-world analogy | Stack of plates | Line at a store |
| Used for | Undo, function calls, DFS | Scheduling, BFS, print queue |

---

## 11. Choosing the Right Data Structure

This is one of the most important skills in computer science. There is no single best data structure — the right choice depends on your use case.

### Comparison Matrix

| Data Structure | Search | Insert | Delete | Memory | Best For |
|---|---|---|---|---|---|
| **Array** | O(n) / O(log n)* | O(n) | O(n) | ✅ Low | Fixed data, random access |
| **Linked List** | O(n) | O(1) front | O(n) | Medium | Frequent inserts/deletes |
| **BST (balanced)** | O(log n) | O(log n) | O(log n) | Medium | Sorted dynamic data |
| **Hash Table** | O(1) avg | O(1) avg | O(1) avg | Medium | Fast lookup by key |
| **Trie** | O(L) | O(L) | O(L) | ❌ High | Strings, prefix search |
| **Stack** | O(n) | O(1) | O(1) | Low | LIFO access |
| **Queue** | O(n) | O(1) | O(1) | Low | FIFO access |

*O(log n) for sorted arrays using binary search

### Decision Guide

```
Do you need fast lookup by a key (like a word)?
  ├── Key is a string with prefix operations needed → Trie
  └── Key can be anything → Hash Table

Do you need data in sorted order?
  ├── Data changes frequently → BST
  └── Data is mostly static → Sorted Array

Do you need to add/remove from ends only?
  ├── LIFO (last in, first out) → Stack
  └── FIFO (first in, first out) → Queue

Do you need to insert/delete frequently in the middle?
  └── Linked List

Do you need O(1) random access by index?
  └── Array
```

---

## 12. Problem Set 5 — Speller

The Week 5 problem set asks you to implement a **spell checker** in C, efficiently checking whether words in a text are in a dictionary.

### Overview

You are given `speller.c` (driver) and must implement `dictionary.c` with these four functions:

```c
bool check(const char *word);       // is this word in the dictionary?
bool load(const char *dictionary);  // load dictionary file into memory
unsigned int size(void);            // how many words in dictionary?
bool unload(void);                  // free all memory
```

### Recommended Implementation — Hash Table

A hash table with chaining gives the best balance of speed and simplicity.

#### Step 1 — Define the Node and Table

```c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define TABLE_SIZE 65536   // large prime gives fewer collisions

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

node *table[TABLE_SIZE];
unsigned int word_count = 0;
```

#### Step 2 — Hash Function

```c
unsigned int hash(const char *word)
{
    unsigned int h = 5381;
    for (int i = 0; word[i] != '\0'; i++)
        h = ((h << 5) + h) + tolower(word[i]);
    return h % TABLE_SIZE;
}
```

#### Step 3 — load()

```c
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    // Initialize table
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;

    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(n->word, word);
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
        word_count++;
    }

    fclose(file);
    return true;
}
```

#### Step 4 — check()

```c
bool check(const char *word)
{
    int index = hash(word);

    for (node *cur = table[index]; cur != NULL; cur = cur->next)
    {
        if (strcasecmp(cur->word, word) == 0)
            return true;
    }
    return false;
}
```

> Use `strcasecmp` (case-insensitive comparison) — "Hello" and "hello" are both valid spellings.

#### Step 5 — size()

```c
unsigned int size(void)
{
    return word_count;
}
```

#### Step 6 — unload()

```c
bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *cur = table[i];
        while (cur != NULL)
        {
            node *next = cur->next;
            free(cur);
            cur = next;
        }
        table[i] = NULL;
    }
    return true;
}
```

### Alternative — Trie Implementation

```c
#define ALPHABET 27   // 26 letters + apostrophe

typedef struct node
{
    bool is_word;
    struct node *children[ALPHABET];
} node;

node *root = NULL;
unsigned int word_count = 0;

int char_index(char c)
{
    return (c == '\'') ? 26 : tolower(c) - 'a';
}

bool load(const char *dictionary)
{
    root = calloc(1, sizeof(node));   // calloc zeros memory
    if (root == NULL) return false;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL) return false;

    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) == 1)
    {
        node *cursor = root;
        for (int i = 0; word[i]; i++)
        {
            int idx = char_index(word[i]);
            if (cursor->children[idx] == NULL)
            {
                cursor->children[idx] = calloc(1, sizeof(node));
                if (cursor->children[idx] == NULL)
                {
                    fclose(file);
                    return false;
                }
            }
            cursor = cursor->children[idx];
        }
        if (!cursor->is_word)
        {
            cursor->is_word = true;
            word_count++;
        }
    }

    fclose(file);
    return true;
}

bool check(const char *word)
{
    node *cursor = root;
    for (int i = 0; word[i]; i++)
    {
        int idx = char_index(word[i]);
        if (cursor->children[idx] == NULL) return false;
        cursor = cursor->children[idx];
    }
    return cursor->is_word;
}
```

### Performance Tips

| Tip | Impact |
|---|---|
| Use a large hash table (65536+) | Fewer collisions → faster check |
| Use a strong hash function (djb2) | More uniform distribution |
| Use `strcasecmp` not `strcmp` in check | Case-insensitive matching |
| Always check `malloc`/`calloc` for NULL | Prevents segfaults |
| Free every node in unload | Pass valgrind with 0 leaks |
| Track word count in load | O(1) size() function |

### Common Mistakes

| Mistake | Fix |
|---|---|
| Using too small a hash table | Use at least 1000 buckets, ideally 65536+ |
| Case-sensitive check | Use `strcasecmp` or `tolower` in hash |
| Memory leak in unload | Walk every bucket, free every node |
| Not initializing table to NULL | Loop: `table[i] = NULL` before loading |
| Forgetting apostrophes in trie | Add index 26 for `'` character |
| Double-freeing | Set pointers to NULL after freeing |

---

## 13. Quick Reference Cheat Sheet

### Linked List Node

```c
typedef struct node
{
    int value;
    struct node *next;
} node;
```

### Insert at Front

```c
node *n = malloc(sizeof(node));
if (n == NULL) return head;
n->value = value;
n->next  = head;
head = n;          // or return n
```

### Traverse

```c
for (node *cur = head; cur != NULL; cur = cur->next)
    // use cur->value
```

### Free Entire List

```c
while (head != NULL)
{
    node *next = head->next;
    free(head);
    head = next;
}
```

### BST Node

```c
typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;
```

### BST Search

```c
bool search(node *root, int target)
{
    if (root == NULL)   return false;
    if (root->value == target) return true;
    if (target < root->value) return search(root->left, target);
    return search(root->right, target);
}
```

### Hash Table with Chaining

```c
#define N 100
node *table[N];
int index = hash(key) % N;
// insert at front of table[index]
// search by walking table[index]
```

### Trie Node

```c
typedef struct node
{
    bool is_word;
    struct node *children[26];
} node;

// index: tolower(c) - 'a'
```

### Complexity Summary

| Structure | Search | Insert | Delete | Space |
|---|---|---|---|---|
| Array | O(n) | O(n) | O(n) | O(n) |
| Sorted Array | O(log n) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(1) | O(n) | O(n) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(n) |
| Hash Table | O(1) avg | O(1) avg | O(1) avg | O(n) |
| Trie | O(L) | O(L) | O(L) | O(n×ALPHA) |

### Key Rules for Week 5

| Rule | Why It Matters |
|---|---|
| Use `struct node` inside struct definition | `typedef` isn't complete yet when defining `next` |
| Use `->` for pointer members, `.` for value members | `p->val` = `(*p).val` |
| Save `next` before freeing a node | You can't read freed memory |
| Never move `head` while traversing | You'll lose the start of the list |
| Hash tables need large tables AND good hash functions | Small tables mean many collisions → O(n) |
| BST performance depends on balance | Sorted inserts make it a linked list |
| Tries use O(L) time regardless of dictionary size | L = length of the search word |
| Always run Valgrind before submitting | Every malloc must have a matching free |

---

*CS50 Week 5 Notes · Harvard University · David J. Malan*
