## CS50 — Week 7: SQL

**Harvard University** · David J. Malan  
**Topic:** Relational databases, SQL queries, designing schemas, indexes, transactions, security vulnerabilities, and using Python with SQL.

---

## Table of Contents

1. [What is a Database?](#1-what-is-a-database)
2. [Flat Files vs Relational Databases](#2-flat-files-vs-relational-databases)
3. [SQLite and How to Use It](#3-sqlite-and-how-to-use-it)
4. [Tables, Rows, and Columns](#4-tables-rows-and-columns)
5. [SQL Data Types](#5-sql-data-types)
6. [Creating Tables — CREATE TABLE](#6-creating-tables--create-table)
7. [Inserting Data — INSERT INTO](#7-inserting-data--insert-into)
8. [Querying Data — SELECT](#8-querying-data--select)
9. [Filtering — WHERE](#9-filtering--where)
10. [Sorting — ORDER BY](#10-sorting--order-by)
11. [Limiting — LIMIT and OFFSET](#11-limiting--limit-and-offset)
12. [Aggregate Functions](#12-aggregate-functions)
13. [Grouping — GROUP BY and HAVING](#13-grouping--group-by-and-having)
14. [Updating Data — UPDATE](#14-updating-data--update)
15. [Deleting Data — DELETE](#15-deleting-data--delete)
16. [Primary Keys and Foreign Keys](#16-primary-keys-and-foreign-keys)
17. [Relationships — One-to-One, One-to-Many, Many-to-Many](#17-relationships--one-to-one-one-to-many-many-to-many)
18. [Joining Tables — JOIN](#18-joining-tables--join)
19. [Indexes](#19-indexes)
20. [Transactions](#20-transactions)
21. [SQL with Python — cs50 and sqlite3](#21-sql-with-python--cs50-and-sqlite3)
22. [SQL Security — Injection Attacks](#22-sql-security--injection-attacks)
23. [Database Design Best Practices](#23-database-design-best-practices)
24. [Problem Set 7 — Movies and Fiftyville](#24-problem-set-7--movies-and-fiftyville)
25. [Quick Reference Cheat Sheet](#25-quick-reference-cheat-sheet)

---

## 1. What is a Database?

A **database** is an organized collection of data stored and accessed electronically. A **Database Management System (DBMS)** is the software that manages it.

### Why Not Just Use Files?

Imagine storing 1 million student records in a `.csv` file:

```
name,age,grade
Alice,20,A
Bob,22,B
Charlie,19,A
...
```

Problems with flat files at scale:

| Problem | Example |
|---|---|
| **Slow search** | Finding all grade-A students = scan every row = O(n) |
| **No relationships** | How do you link students to courses? Duplicate data everywhere |
| **No integrity** | Nothing stops `age = "banana"` or a missing required field |
| **No concurrency** | Two programs writing simultaneously corrupt the file |
| **No transactions** | If power cuts mid-write, data is half-written |

Databases solve all of these.

### What a DBMS Gives You

- **Fast queries** — indexes make search O(log n) or O(1)
- **Structured data** — defined schema with enforced types
- **Relationships** — link data across tables without duplication
- **Integrity constraints** — enforced rules (can't be NULL, must be unique, etc.)
- **Concurrency** — multiple users can safely read/write at the same time
- **Transactions** — all-or-nothing operations that keep data consistent

---

## 2. Flat Files vs Relational Databases

### Flat File (CSV)

```csv
title,year,rating,director
The Dark Knight,2008,9.0,Christopher Nolan
Inception,2010,8.8,Christopher Nolan
Interstellar,2014,8.7,Christopher Nolan
```

Problems:
- "Christopher Nolan" is repeated 3 times — **redundancy**
- If his name is misspelled once, results are inconsistent — **anomaly**
- Changing his name requires updating every row — **update anomaly**

### Relational Database

Split into related tables:

**movies** table:

| id | title | year | rating | director_id |
|---|---|---|---|---|
| 1 | The Dark Knight | 2008 | 9.0 | 1 |
| 2 | Inception | 2010 | 8.8 | 1 |
| 3 | Interstellar | 2014 | 8.7 | 1 |

**directors** table:

| id | name |
|---|---|
| 1 | Christopher Nolan |

Now "Christopher Nolan" exists in exactly **one place**. Update it once — automatically reflected everywhere.

This is the core principle: **Don't Repeat Yourself (DRY)** applied to data.

---

## 3. SQLite and How to Use It

**SQLite** is a lightweight, serverless, file-based relational database. CS50 uses it because it requires no setup — the entire database lives in a single `.db` file.

### Starting SQLite

```bash
sqlite3 movies.db        # open (or create) movies.db
sqlite3                  # open in-memory (temporary, for testing)
```

### SQLite Dot Commands (Meta-commands)

These are SQLite-specific — not SQL. They start with `.`:

```bash
.tables              # list all tables
.schema              # show CREATE TABLE statements for all tables
.schema tablename    # show schema for one table
.headers on          # show column names in output
.mode column         # format output in columns
.mode csv            # output as CSV
.quit                # exit SQLite
.read file.sql       # run SQL commands from a file
.import file.csv t   # import CSV into table t
.output file.txt     # write output to file instead of screen
.help                # list all dot commands
```

### Recommended Setup Before Querying

```bash
sqlite3 movies.db
.headers on
.mode column
```

Now output looks like:

```
id          title             year        rating
----------  ----------------  ----------  ----------
1           The Dark Knight   2008        9.0
```

---

## 4. Tables, Rows, and Columns

A relational database organizes data into **tables** (also called **relations**).

```
Table: students
┌────┬─────────┬─────┬──────┐
│ id │  name   │ age │  gpa │  ← columns (attributes/fields)
├────┼─────────┼─────┼──────┤
│  1 │ Alice   │  20 │  3.9 │  ← row (record/tuple)
│  2 │ Bob     │  22 │  3.2 │  ← row
│  3 │ Charlie │  19 │  3.7 │  ← row
└────┴─────────┴─────┴──────┘
```

| Term | Also Called | Meaning |
|---|---|---|
| **Table** | Relation | A named grid of data |
| **Column** | Attribute, Field | A named property (type is fixed) |
| **Row** | Record, Tuple | One entry in the table |
| **Cell** | — | The value at one column in one row |
| **Schema** | — | The structure definition of a table |

---

## 5. SQL Data Types

### SQLite Types

SQLite uses a flexible type system with 5 core storage classes:

| Type | Stores | Examples |
|---|---|---|
| `INTEGER` | Whole numbers | `1`, `-5`, `1000000` |
| `REAL` | Floating-point numbers | `3.14`, `-0.5`, `9.8` |
| `TEXT` | Strings of any length | `"Alice"`, `"hello world"` |
| `BLOB` | Raw binary data | Images, files |
| `NULL` | Missing / unknown value | `NULL` |

### Standard SQL Types (used in other databases)

| SQL Type | Meaning | SQLite Equivalent |
|---|---|---|
| `INT` / `INTEGER` | Whole number | `INTEGER` |
| `SMALLINT` | Small integer | `INTEGER` |
| `BIGINT` | Large integer | `INTEGER` |
| `FLOAT` / `REAL` | Decimal number | `REAL` |
| `DOUBLE PRECISION` | High-precision decimal | `REAL` |
| `CHAR(n)` | Fixed-length string | `TEXT` |
| `VARCHAR(n)` | Variable-length string, max n | `TEXT` |
| `TEXT` | Unlimited string | `TEXT` |
| `DATE` | Date value | `TEXT` (stored as string) |
| `TIMESTAMP` | Date + time | `TEXT` or `INTEGER` |
| `BOOLEAN` | True/false | `INTEGER` (0 or 1) |
| `NUMERIC` | Flexible numeric | `REAL` or `INTEGER` |

### NULL in SQL

`NULL` means **unknown** or **missing** — it is not the same as `0` or `""`.

```sql
-- NULL is special -- you can't use = NULL
-- Use IS NULL or IS NOT NULL instead

SELECT * FROM students WHERE phone IS NULL;
SELECT * FROM students WHERE phone IS NOT NULL;
```

---

## 6. Creating Tables — CREATE TABLE

### Basic Syntax

```sql
CREATE TABLE table_name (
    column1 TYPE CONSTRAINTS,
    column2 TYPE CONSTRAINTS,
    ...
);
```

### Common Constraints

| Constraint | Meaning |
|---|---|
| `NOT NULL` | Column cannot be empty |
| `UNIQUE` | Every value in column must be different |
| `PRIMARY KEY` | Unique identifier for each row (implies NOT NULL + UNIQUE) |
| `AUTOINCREMENT` | Integer automatically increments with each new row |
| `DEFAULT value` | Use this value if none provided |
| `CHECK (condition)` | Value must satisfy this condition |
| `FOREIGN KEY` | Links to a primary key in another table |

### Example — Students Table

```sql
CREATE TABLE students (
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    name  TEXT    NOT NULL,
    age   INTEGER NOT NULL CHECK(age >= 0),
    gpa   REAL    DEFAULT 0.0,
    email TEXT    UNIQUE
);
```

### Example — Movies Database

```sql
CREATE TABLE movies (
    id      INTEGER PRIMARY KEY AUTOINCREMENT,
    title   TEXT    NOT NULL,
    year    INTEGER NOT NULL,
    rating  REAL
);

CREATE TABLE directors (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE movies_directors (
    movie_id    INTEGER NOT NULL,
    director_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id)    REFERENCES movies(id),
    FOREIGN KEY(director_id) REFERENCES directors(id)
);
```

### DROP TABLE — Delete a Table

```sql
DROP TABLE students;                    -- delete table (error if doesn't exist)
DROP TABLE IF EXISTS students;          -- delete only if it exists (safe)
```

### ALTER TABLE — Modify a Table

```sql
ALTER TABLE students ADD COLUMN phone TEXT;           -- add column
ALTER TABLE students RENAME COLUMN gpa TO grade_avg;  -- rename column
ALTER TABLE students RENAME TO learners;              -- rename table
```

---

## 7. Inserting Data — INSERT INTO

### Basic Syntax

```sql
INSERT INTO table_name (column1, column2, ...)
VALUES (value1, value2, ...);
```

### Examples

```sql
-- Insert one row (all columns)
INSERT INTO students (name, age, gpa, email)
VALUES ('Alice', 20, 3.9, 'alice@example.com');

-- Insert one row (omit optional columns — they get DEFAULT or NULL)
INSERT INTO students (name, age)
VALUES ('Bob', 22);

-- Insert multiple rows at once
INSERT INTO students (name, age, gpa) VALUES
    ('Charlie', 19, 3.7),
    ('Diana',   21, 3.5),
    ('Eve',     20, 3.8);
```

> ⚠️ String values in SQL use **single quotes** `'Alice'` — not double quotes. Double quotes are for column/table names.

---

## 8. Querying Data — SELECT

`SELECT` is the most important SQL command — it retrieves data.

### Basic Syntax

```sql
SELECT column1, column2 FROM table_name;
SELECT * FROM table_name;   -- * means all columns
```

### Examples

```sql
-- Select specific columns
SELECT name, gpa FROM students;

-- Select all columns
SELECT * FROM students;

-- Select with expression
SELECT name, age * 2 AS double_age FROM students;

-- Select distinct values (no duplicates)
SELECT DISTINCT year FROM movies;

-- Count total rows
SELECT COUNT(*) FROM movies;
```

### Column Aliases — AS

```sql
SELECT name AS student_name,
       gpa  AS grade_point_average
FROM students;
```

Output uses the alias as the column header.

### Expressions in SELECT

```sql
SELECT
    title,
    year,
    2024 - year AS age_of_film,
    rating * 10 AS score_out_of_100
FROM movies;
```

---

## 9. Filtering — WHERE

`WHERE` filters rows — only returns rows where the condition is true.

### Basic Comparisons

```sql
SELECT * FROM students WHERE age = 20;
SELECT * FROM students WHERE gpa > 3.5;
SELECT * FROM students WHERE name = 'Alice';
SELECT * FROM movies  WHERE year != 2020;
SELECT * FROM movies  WHERE rating >= 8.0;
```

### Logical Operators — AND, OR, NOT

```sql
-- Both conditions must be true
SELECT * FROM students WHERE age > 18 AND gpa >= 3.5;

-- At least one condition must be true
SELECT * FROM movies WHERE year = 2020 OR year = 2021;

-- Negate condition
SELECT * FROM students WHERE NOT age = 20;
SELECT * FROM students WHERE age != 20;   -- same as above
```

### BETWEEN — Range Check

```sql
SELECT * FROM movies  WHERE year BETWEEN 2000 AND 2010;
SELECT * FROM students WHERE gpa BETWEEN 3.0 AND 4.0;
-- BETWEEN is inclusive: year >= 2000 AND year <= 2010
```

### IN — Multiple Values

```sql
-- Instead of: WHERE year = 2020 OR year = 2021 OR year = 2022
SELECT * FROM movies WHERE year IN (2020, 2021, 2022);

-- NOT IN
SELECT * FROM students WHERE name NOT IN ('Alice', 'Bob');
```

### LIKE — Pattern Matching

```sql
-- % matches any sequence of characters
-- _ matches exactly one character

SELECT * FROM movies WHERE title LIKE 'The%';       -- starts with "The"
SELECT * FROM movies WHERE title LIKE '%Dark%';     -- contains "Dark"
SELECT * FROM movies WHERE title LIKE '%Knight';    -- ends with "Knight"
SELECT * FROM students WHERE name LIKE '_ob';       -- "Bob", "Rob", etc.
SELECT * FROM movies WHERE title LIKE 'The _ Dark%'; -- one char between
```

> ⚠️ `LIKE` is **case-insensitive** in SQLite for ASCII characters.

### IS NULL / IS NOT NULL

```sql
SELECT * FROM students WHERE email IS NULL;
SELECT * FROM students WHERE email IS NOT NULL;

-- NEVER use = NULL or != NULL -- they always return nothing!
-- Wrong:  WHERE email = NULL
-- Right:  WHERE email IS NULL
```

---

## 10. Sorting — ORDER BY

```sql
-- Ascending (default)
SELECT * FROM students ORDER BY gpa;
SELECT * FROM students ORDER BY gpa ASC;

-- Descending
SELECT * FROM students ORDER BY gpa DESC;

-- Sort by name alphabetically
SELECT * FROM students ORDER BY name;

-- Sort by multiple columns
SELECT * FROM students ORDER BY gpa DESC, name ASC;
-- Primary sort: gpa descending
-- Secondary sort: name ascending (when gpa values are equal)

-- Sort by column position (1-based)
SELECT name, gpa FROM students ORDER BY 2 DESC;
-- Same as ORDER BY gpa DESC
```

---

## 11. Limiting — LIMIT and OFFSET

### LIMIT — Cap the Number of Results

```sql
-- Return only first 10 rows
SELECT * FROM movies ORDER BY rating DESC LIMIT 10;

-- Top-5 highest rated movies
SELECT title, rating FROM movies ORDER BY rating DESC LIMIT 5;
```

### OFFSET — Skip Rows (Pagination)

```sql
-- Skip first 10, return next 10
SELECT * FROM movies ORDER BY year LIMIT 10 OFFSET 10;

-- Page 1 (rows 1-10):   LIMIT 10 OFFSET 0
-- Page 2 (rows 11-20):  LIMIT 10 OFFSET 10
-- Page 3 (rows 21-30):  LIMIT 10 OFFSET 20
-- Page n:               LIMIT 10 OFFSET (n-1)*10
```

---

## 12. Aggregate Functions

Aggregate functions compute a single value from a group of rows.

| Function | Description | Example |
|---|---|---|
| `COUNT(*)` | Count all rows | `COUNT(*)` |
| `COUNT(col)` | Count non-NULL values in column | `COUNT(email)` |
| `COUNT(DISTINCT col)` | Count unique non-NULL values | `COUNT(DISTINCT year)` |
| `SUM(col)` | Total of all values | `SUM(budget)` |
| `AVG(col)` | Average of all values | `AVG(rating)` |
| `MIN(col)` | Smallest value | `MIN(year)` |
| `MAX(col)` | Largest value | `MAX(rating)` |

### Examples

```sql
-- Total number of movies
SELECT COUNT(*) FROM movies;

-- Average rating of all movies
SELECT AVG(rating) FROM movies;
SELECT ROUND(AVG(rating), 2) FROM movies;   -- rounded to 2 decimal places

-- Highest and lowest rated movies
SELECT MAX(rating), MIN(rating) FROM movies;

-- Number of distinct years with movies
SELECT COUNT(DISTINCT year) FROM movies;

-- Total earnings across all movies
SELECT SUM(gross) FROM movies;
```

---

## 13. Grouping — GROUP BY and HAVING

### GROUP BY — Aggregate Per Group

`GROUP BY` groups rows with the same value in a column and applies aggregate functions to each group.

```sql
-- Count movies per year
SELECT year, COUNT(*) AS movie_count
FROM movies
GROUP BY year;

-- Average rating per director
SELECT director_id, ROUND(AVG(rating), 2) AS avg_rating
FROM movies
GROUP BY director_id;

-- Most prolific year (most movies released)
SELECT year, COUNT(*) AS count
FROM movies
GROUP BY year
ORDER BY count DESC
LIMIT 1;
```

### HAVING — Filter Groups (like WHERE but for groups)

`WHERE` filters rows **before** grouping. `HAVING` filters groups **after** grouping.

```sql
-- Years with more than 100 movies
SELECT year, COUNT(*) AS count
FROM movies
GROUP BY year
HAVING count > 100;

-- Directors with average rating above 8.0
SELECT director_id, AVG(rating) AS avg_rating
FROM movies
GROUP BY director_id
HAVING avg_rating > 8.0;
```

### Query Execution Order

Understanding this order prevents many bugs:

```
1. FROM        -- which table(s)
2. JOIN        -- combine tables
3. WHERE       -- filter rows
4. GROUP BY    -- form groups
5. HAVING      -- filter groups
6. SELECT      -- choose columns / compute expressions
7. DISTINCT    -- remove duplicates
8. ORDER BY    -- sort
9. LIMIT       -- cap results
10. OFFSET     -- skip rows
```

---

## 14. Updating Data — UPDATE

### Basic Syntax

```sql
UPDATE table_name
SET column1 = value1, column2 = value2, ...
WHERE condition;
```

### Examples

```sql
-- Update one student's GPA
UPDATE students SET gpa = 4.0 WHERE name = 'Alice';

-- Update multiple columns at once
UPDATE students
SET gpa = 3.8, age = 21
WHERE id = 2;

-- Increment a value
UPDATE students SET age = age + 1 WHERE id = 1;

-- Update everyone's rating by a percentage
UPDATE movies SET rating = rating * 1.1;
```

> ⚠️ **Always include WHERE with UPDATE.** Without `WHERE`, every single row is updated. This is a common and catastrophic mistake.

```sql
-- DANGEROUS — updates ALL rows!
UPDATE students SET gpa = 0.0;

-- SAFE — updates only Alice
UPDATE students SET gpa = 0.0 WHERE name = 'Alice';
```

---

## 15. Deleting Data — DELETE

### Basic Syntax

```sql
DELETE FROM table_name WHERE condition;
```

### Examples

```sql
-- Delete one student
DELETE FROM students WHERE id = 5;

-- Delete all students with GPA below 2.0
DELETE FROM students WHERE gpa < 2.0;

-- Delete all movies from before 1950
DELETE FROM movies WHERE year < 1950;
```

> ⚠️ **Always include WHERE with DELETE.** Without `WHERE`, every single row is deleted — the table is emptied.

```sql
-- CATASTROPHIC — deletes ALL data from the table!
DELETE FROM students;

-- SAFE
DELETE FROM students WHERE id = 5;
```

### DELETE vs DROP TABLE vs TRUNCATE

| Command | Effect |
|---|---|
| `DELETE FROM t WHERE ...` | Remove specific rows |
| `DELETE FROM t` | Remove all rows (table still exists) |
| `DROP TABLE t` | Remove the entire table (data + structure) |
| `TRUNCATE TABLE t` | Remove all rows fast (not in SQLite, but in MySQL/PostgreSQL) |

---

## 16. Primary Keys and Foreign Keys

### Primary Key

A **primary key** uniquely identifies each row in a table.

- Must be `NOT NULL`
- Must be `UNIQUE`
- Usually an auto-incrementing integer called `id`
- Each table should have exactly one primary key

```sql
CREATE TABLE students (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);
```

After inserting rows, `id` is automatically assigned:

```
id | name
---+----------
 1 | Alice
 2 | Bob
 3 | Charlie
```

### Foreign Key

A **foreign key** is a column in one table that references the primary key of another table. It **enforces relationships**.

```sql
CREATE TABLE enrollments (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER NOT NULL,
    course_id  INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(course_id)  REFERENCES courses(id)
);
```

This means:
- `student_id` must be the `id` of an existing student
- You can't enroll a student that doesn't exist
- You can't delete a student who has enrollments (referential integrity)

### Enabling Foreign Keys in SQLite

SQLite does **not** enforce foreign keys by default. You must enable it:

```sql
PRAGMA foreign_keys = ON;
```

Or in Python:

```python
db.execute("PRAGMA foreign_keys = ON")
```

---

## 17. Relationships — One-to-One, One-to-Many, Many-to-Many

Designing how tables relate to each other is the essence of database design.

### One-to-One (1:1)

Each row in Table A corresponds to exactly one row in Table B.

**Example:** Each student has exactly one student profile.

```sql
CREATE TABLE students (
    id   INTEGER PRIMARY KEY,
    name TEXT
);

CREATE TABLE student_profiles (
    id         INTEGER PRIMARY KEY,
    student_id INTEGER UNIQUE,        -- UNIQUE enforces 1:1
    bio        TEXT,
    photo_url  TEXT,
    FOREIGN KEY(student_id) REFERENCES students(id)
);
```

### One-to-Many (1:N)

One row in Table A corresponds to many rows in Table B.

**Example:** One director makes many movies. Many movies belong to one director.

```sql
CREATE TABLE directors (
    id   INTEGER PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE movies (
    id          INTEGER PRIMARY KEY,
    title       TEXT NOT NULL,
    year        INTEGER,
    director_id INTEGER,              -- foreign key on the "many" side
    FOREIGN KEY(director_id) REFERENCES directors(id)
);
```

```
directors                movies
id | name                id | title         | director_id
---+---------            ---+---------------+-----------
 1 | Nolan               1  | Dark Knight   | 1
 2 | Spielberg           2  | Inception     | 1
                         3  | Jaws          | 2
                         4  | Schindler's   | 2
```

### Many-to-Many (M:N)

One row in Table A can relate to many rows in Table B, and vice versa.

**Example:** A movie can have many actors. An actor can be in many movies.

```sql
-- Can't put all actors in movies table or all movies in actors table
-- Need a JUNCTION TABLE (also called join table or bridge table)

CREATE TABLE movies (
    id    INTEGER PRIMARY KEY,
    title TEXT NOT NULL
);

CREATE TABLE people (
    id   INTEGER PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE stars (           -- junction table
    movie_id  INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    PRIMARY KEY(movie_id, person_id),   -- composite primary key
    FOREIGN KEY(movie_id)  REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
```

```
movies           stars              people
id | title       movie_id|person_id  id | name
---+---------    --------+---------  ---+---------
 1 | Batman       1      |  101       101 | Christian Bale
 2 | American     1      |  102       102 | Heath Ledger
                  2      |  101       103 | Amy Adams
                  2      |  103
```

This is the pattern used in CS50's actual `movies.db`.

---

## 18. Joining Tables — JOIN

A `JOIN` combines rows from two or more tables based on a related column.

### INNER JOIN (most common)

Returns only rows where the join condition is satisfied in **both** tables.

```sql
-- Get movie titles with their directors' names
SELECT movies.title, directors.name AS director
FROM movies
JOIN directors ON movies.director_id = directors.id;
```

Output:
```
title              | director
-------------------+-----------------
The Dark Knight    | Christopher Nolan
Inception          | Christopher Nolan
Jaws               | Steven Spielberg
```

### Using Table Aliases

```sql
SELECT m.title, d.name AS director
FROM movies AS m
JOIN directors AS d ON m.director_id = d.id
WHERE m.year > 2000
ORDER BY m.year DESC;
```

Aliases make queries shorter and more readable.

### Joining Multiple Tables

```sql
-- Get movie title and all actors in it
SELECT m.title, p.name AS actor
FROM movies m
JOIN stars  s ON m.id  = s.movie_id
JOIN people p ON s.person_id = p.id
WHERE m.title = 'The Dark Knight'
ORDER BY p.name;
```

### LEFT JOIN

Returns **all rows from the left table**, plus matching rows from the right. If no match, right side columns are `NULL`.

```sql
-- All directors, even if they have no movies in our database
SELECT d.name, m.title
FROM directors d
LEFT JOIN movies m ON d.id = m.director_id
ORDER BY d.name;
```

```
director          | title
------------------+---------
Christopher Nolan | Dark Knight
Christopher Nolan | Inception
George Lucas      | NULL        ← no movies in our DB
```

### RIGHT JOIN

Opposite of LEFT JOIN — all rows from the right table.

```sql
-- Not supported in SQLite (use LEFT JOIN with tables swapped instead)
```

### FULL OUTER JOIN

All rows from both tables — NULLs where no match on either side.

```sql
-- Not supported in SQLite
-- Simulate with UNION of LEFT JOIN and RIGHT JOIN
```

### JOIN Types Summary

```
Table A     Table B
┌───┐       ┌───┐
│ A │       │ B │
│   │  ∩    │   │
└───┘       └───┘

INNER JOIN:  only ∩ (intersection — rows in both)
LEFT JOIN:   all of A + ∩ (all left rows, right NULLs where no match)
RIGHT JOIN:  all of B + ∩ (all right rows, left NULLs where no match)
FULL OUTER:  all of A ∪ B (everything, NULLs where no match)
```

### Self Join

A table joined to itself — useful for hierarchical data.

```sql
-- Find pairs of students with the same GPA
SELECT a.name AS student1, b.name AS student2, a.gpa
FROM students a
JOIN students b ON a.gpa = b.gpa AND a.id < b.id
ORDER BY a.gpa DESC;
```

---

## 19. Indexes

An **index** is a data structure that makes queries faster — like the index at the back of a book.

Without an index: `SELECT * FROM movies WHERE title = 'Inception'` scans every row — O(n).  
With an index on `title`: the query uses the index to find the row directly — O(log n).

### Creating an Index

```sql
-- Create index on a single column
CREATE INDEX idx_title ON movies(title);

-- Create index on multiple columns (composite index)
CREATE INDEX idx_name_year ON movies(title, year);

-- Create unique index (enforces uniqueness)
CREATE UNIQUE INDEX idx_email ON students(email);

-- View all indexes on a table
.schema students   -- shows indexes in SQLite

-- Drop an index
DROP INDEX idx_title;
```

### When to Use Indexes

```sql
-- Good candidates for indexing:
-- 1. Columns used in WHERE clauses frequently
CREATE INDEX idx_year   ON movies(year);
CREATE INDEX idx_rating ON movies(rating);

-- 2. Columns used in JOIN conditions
CREATE INDEX idx_director_id ON movies(director_id);

-- 3. Columns used in ORDER BY
CREATE INDEX idx_name ON students(name);

-- 4. Foreign key columns (good practice)
CREATE INDEX idx_movie_id  ON stars(movie_id);
CREATE INDEX idx_person_id ON stars(person_id);
```

### When NOT to Index

- Columns you rarely search or filter on
- Small tables (full scan is fast enough)
- Columns with very few distinct values (like `gender = 'M'/'F'` — doesn't help much)
- Tables that are written to very frequently (indexes slow down INSERT/UPDATE/DELETE)

### The Cost of Indexes

| Operation | Without Index | With Index |
|---|---|---|
| SELECT (search) | O(n) — slow | O(log n) — fast |
| INSERT | Fast | Slightly slower (index must be updated) |
| UPDATE | Fast | Slightly slower |
| DELETE | Fast | Slightly slower |
| Disk space | Less | More (index stored separately) |

> **Rule of thumb:** Index columns you read from frequently; avoid over-indexing columns you write to frequently.

---

## 20. Transactions

A **transaction** is a group of SQL operations that are treated as a single, atomic unit — either **all succeed** or **all are rolled back** as if they never happened.

### The ACID Properties

| Property | Meaning |
|---|---|
| **Atomicity** | All operations succeed, or none do |
| **Consistency** | Database moves from one valid state to another |
| **Isolation** | Concurrent transactions don't interfere |
| **Durability** | Committed changes survive crashes |

### Why Transactions Matter — The Bank Transfer Problem

```sql
-- Transfer $100 from Alice to Bob

-- Step 1
UPDATE accounts SET balance = balance - 100 WHERE name = 'Alice';

-- ← CRASH HERE ← Alice lost $100 but Bob never got it!

-- Step 2
UPDATE accounts SET balance = balance + 100 WHERE name = 'Bob';
```

Without a transaction, a crash between steps leaves the database in an inconsistent state.

### Using Transactions

```sql
BEGIN TRANSACTION;

UPDATE accounts SET balance = balance - 100 WHERE name = 'Alice';
UPDATE accounts SET balance = balance + 100 WHERE name = 'Bob';

COMMIT;    -- save both changes permanently

-- If something goes wrong:
ROLLBACK;  -- undo everything back to BEGIN TRANSACTION
```

### Transactions in Practice

```sql
BEGIN TRANSACTION;

INSERT INTO orders (customer_id, total) VALUES (1, 59.99);
INSERT INTO order_items (order_id, product_id, qty) VALUES (last_insert_rowid(), 42, 2);
UPDATE inventory SET stock = stock - 2 WHERE product_id = 42;

COMMIT;
```

If any statement fails, `ROLLBACK` brings everything back to the state before `BEGIN`.

### SQLite Auto-commit

In SQLite, every single statement that modifies data is automatically wrapped in a transaction if you don't explicitly use `BEGIN`. This is called **autocommit** mode.

---

## 21. SQL with Python — cs50 and sqlite3

### Using CS50's SQL Library

CS50 provides a simple `SQL` class that makes database queries easy:

```python
from cs50 import SQL

# Open the database
db = SQL("sqlite:///movies.db")

# SELECT — returns a list of dicts
rows = db.execute("SELECT * FROM movies WHERE year = ?", 2008)
for row in rows:
    print(row["title"], row["rating"])

# INSERT — returns the new row's id
new_id = db.execute("INSERT INTO students (name, age) VALUES (?, ?)", "Alice", 20)
print(new_id)   # e.g. 5

# UPDATE — returns number of rows affected
count = db.execute("UPDATE students SET gpa = ? WHERE name = ?", 3.9, "Alice")
print(count)   # e.g. 1

# DELETE — returns number of rows deleted
count = db.execute("DELETE FROM students WHERE id = ?", 5)
```

> The `?` placeholder is crucial for security — see SQL Injection section.

### Return Values from cs50.SQL

| Operation | Returns |
|---|---|
| `SELECT` | List of dicts: `[{"col": val, ...}, ...]` |
| `INSERT` | Integer — `id` of the new row |
| `UPDATE` | Integer — number of rows affected |
| `DELETE` | Integer — number of rows deleted |

### Using Python's Built-in sqlite3

```python
import sqlite3

# Connect to database
conn = sqlite3.connect("movies.db")
conn.row_factory = sqlite3.Row   # makes rows accessible by column name

# Create a cursor
cursor = conn.cursor()

# Execute a query
cursor.execute("SELECT * FROM movies WHERE year = ?", (2008,))
rows = cursor.fetchall()

for row in rows:
    print(row["title"])

# Insert data
cursor.execute("INSERT INTO students (name, age) VALUES (?, ?)", ("Alice", 20))
conn.commit()   # MUST commit to save changes!

# Get the new row's id
print(cursor.lastrowid)

# Always close the connection
conn.close()
```

### Using Context Manager (Recommended Pattern)

```python
import sqlite3

with sqlite3.connect("movies.db") as conn:
    conn.row_factory = sqlite3.Row
    cursor = conn.cursor()

    cursor.execute("SELECT title, rating FROM movies ORDER BY rating DESC LIMIT 10")
    rows = cursor.fetchall()

    for row in rows:
        print(f"{row['title']}: {row['rating']}")

# Connection auto-closes when 'with' block exits
```

### Fetching Results

```python
cursor.execute("SELECT * FROM movies")

# Fetch one row at a time
row = cursor.fetchone()

# Fetch all rows at once
rows = cursor.fetchall()

# Fetch in batches
rows = cursor.fetchmany(100)

# Iterate directly (memory efficient for large results)
for row in cursor:
    print(row)
```

### Complete Python + SQL Example

```python
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

# Create table if not exists
db.execute("""
    CREATE TABLE IF NOT EXISTS students (
        id    INTEGER PRIMARY KEY AUTOINCREMENT,
        name  TEXT    NOT NULL,
        house TEXT,
        birth INTEGER
    )
""")

# Load from CSV file
with open("students.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        db.execute(
            "INSERT INTO students (name, house, birth) VALUES (?, ?, ?)",
            row["name"], row["house"], row["birth"]
        )

# Query and display
rows = db.execute("SELECT name, house FROM students ORDER BY house, name")
for row in rows:
    print(f"{row['name']} — {row['house']}")
```

---

## 22. SQL Security — Injection Attacks

**SQL injection** is one of the most common and dangerous web security vulnerabilities. It occurs when user input is directly inserted into a SQL query without sanitization.

### The Vulnerability

```python
# ❌ DANGEROUS — NEVER DO THIS
username = input("Username: ")
password = input("Password: ")

# User enters: username = "' OR '1'='1"
rows = db.execute(
    "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'"
)
```

What the query becomes:

```sql
SELECT * FROM users
WHERE username = '' OR '1'='1'
AND password = ''
```

`'1'='1'` is always true — this returns **all users** and logs in without a valid password!

### Classic Injection Attack Examples

```
Input: ' OR '1'='1
→ WHERE username = '' OR '1'='1' AND password = ''
→ Always true — bypasses login!

Input: '; DROP TABLE users; --
→ WHERE username = ''; DROP TABLE users; --'
→ Deletes the entire users table!

Input: ' UNION SELECT name, password FROM admins --
→ Appends admin credentials to the result!
```

### The Fix — Always Use Parameterized Queries

```python
# ✅ SAFE — use ? placeholders (cs50.SQL)
rows = db.execute(
    "SELECT * FROM users WHERE username = ? AND password = ?",
    username, password
)

# ✅ SAFE — use ? placeholders (sqlite3)
cursor.execute(
    "SELECT * FROM users WHERE username = ? AND password = ?",
    (username, password)
)
```

With parameterized queries, the input is **never interpreted as SQL**. The `?` value is treated as plain data, so `' OR '1'='1'` is compared literally as a string — it won't match any username.

### Named Placeholders

```python
# Using named placeholders in sqlite3
cursor.execute(
    "SELECT * FROM users WHERE username = :name AND age > :age",
    {"name": username, "age": min_age}
)
```

### Why Parameterized Queries Work

```
Without params:  "SELECT * FROM users WHERE name = '" + input + "'"
                  The input is CONCATENATED into the SQL string
                  The database sees: one big SQL string to parse

With params:     "SELECT * FROM users WHERE name = ?"  +  separate_data
                  The SQL structure is fixed FIRST, then data is added
                  The database sees: SQL template + safe literal value
```

The database **never evaluates** the data value as SQL code.

### Other Security Best Practices

```python
# Validate and sanitize input before using it
def safe_get_year(user_input):
    try:
        year = int(user_input)
        if year < 1888 or year > 2030:
            raise ValueError("Year out of range")
        return year
    except ValueError:
        return None

# Limit permissions — use a DB user that can only SELECT, not DROP
# Never expose your database directly to the internet
# Use HTTPS for all data transmission
# Hash passwords with bcrypt — never store plain text passwords
```

---

## 23. Database Design Best Practices

### Normalization

**Normalization** is the process of structuring a database to reduce redundancy and improve integrity.

#### First Normal Form (1NF)

- Each column contains **atomic** (indivisible) values
- No repeating groups

```sql
-- ❌ Violates 1NF — multiple values in one cell
students: id=1, name='Alice', courses='Math, English, Science'

-- ✅ 1NF — atomic values
students:    id=1, name='Alice'
enrollments: student_id=1, course='Math'
enrollments: student_id=1, course='English'
enrollments: student_id=1, course='Science'
```

#### Second Normal Form (2NF)

- Must be in 1NF
- Every non-key column depends on the **entire** primary key (no partial dependency)

#### Third Normal Form (3NF)

- Must be in 2NF
- No transitive dependencies — non-key columns depend only on the key, not on other non-key columns

```sql
-- ❌ Violates 3NF — zip_code determines city (transitive dependency)
students: id, name, zip_code, city

-- ✅ 3NF — separate out the dependency
students: id, name, zip_code
zip_codes: zip_code, city
```

### Naming Conventions

```sql
-- Table names: lowercase, plural, snake_case
CREATE TABLE students (...);
CREATE TABLE course_enrollments (...);

-- Column names: lowercase, snake_case, descriptive
student_id, first_name, created_at, is_active

-- Primary keys: typically named 'id'
-- Foreign keys: tablename_id (e.g., student_id, movie_id)

-- Indexes: idx_tablename_columnname
CREATE INDEX idx_movies_year ON movies(year);
```

### Column Design Rules

```sql
-- Always use NOT NULL unless absence is truly meaningful
name TEXT NOT NULL

-- Use appropriate default values
is_active  INTEGER NOT NULL DEFAULT 1
created_at TEXT    NOT NULL DEFAULT CURRENT_TIMESTAMP

-- Use CHECK constraints to enforce business rules
age  INTEGER CHECK(age >= 0 AND age <= 150)
gpa  REAL    CHECK(gpa >= 0.0 AND gpa <= 4.0)
type TEXT    CHECK(type IN ('student', 'teacher', 'admin'))
```

### Schema Design Example — School Database

```sql
CREATE TABLE schools (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT    NOT NULL UNIQUE,
    city TEXT    NOT NULL
);

CREATE TABLE teachers (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    name      TEXT    NOT NULL,
    email     TEXT    NOT NULL UNIQUE,
    school_id INTEGER NOT NULL,
    FOREIGN KEY(school_id) REFERENCES schools(id)
);

CREATE TABLE courses (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    title      TEXT    NOT NULL,
    credits    INTEGER NOT NULL DEFAULT 3,
    teacher_id INTEGER,
    FOREIGN KEY(teacher_id) REFERENCES teachers(id)
);

CREATE TABLE students (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    name      TEXT    NOT NULL,
    email     TEXT    NOT NULL UNIQUE,
    school_id INTEGER NOT NULL,
    FOREIGN KEY(school_id) REFERENCES schools(id)
);

CREATE TABLE enrollments (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER NOT NULL,
    course_id  INTEGER NOT NULL,
    grade      REAL,
    UNIQUE(student_id, course_id),
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(course_id)  REFERENCES courses(id)
);

-- Indexes for all foreign keys
CREATE INDEX idx_teachers_school  ON teachers(school_id);
CREATE INDEX idx_courses_teacher  ON courses(teacher_id);
CREATE INDEX idx_students_school  ON students(school_id);
CREATE INDEX idx_enroll_student   ON enrollments(student_id);
CREATE INDEX idx_enroll_course    ON enrollments(course_id);
```

---

## 24. Problem Set 7 — Movies and Fiftyville

### Part 1 — Movies

You are given `movies.db` with this schema:

```sql
CREATE TABLE movies (
    id      INTEGER,
    title   TEXT NOT NULL,
    year    NUMERIC,
    PRIMARY KEY(id)
);

CREATE TABLE stars (
    movie_id  INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id)  REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);

CREATE TABLE directors (
    movie_id  INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id)  REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);

CREATE TABLE people (
    id       INTEGER,
    name     TEXT NOT NULL,
    birth    NUMERIC,
    PRIMARY KEY(id)
);

CREATE TABLE ratings (
    movie_id INTEGER NOT NULL,
    rating   REAL NOT NULL,
    votes    INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id)
);
```

### Key Queries for Movies Problems

```sql
-- 1. All movies from 2008
SELECT title FROM movies WHERE year = 2008;

-- 2. Birth year of Emma Stone
SELECT birth FROM people WHERE name = 'Emma Stone';

-- 3. All movies from 2018 ordered by title
SELECT title FROM movies WHERE year = 2018 ORDER BY title;

-- 4. Top 5 highest rated movies (100,000+ votes)
SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.votes >= 100000
ORDER BY ratings.rating DESC
LIMIT 5;

-- 5. All movies starring Tom Hanks
SELECT title FROM movies
JOIN stars  ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Tom Hanks';

-- 6. Movies directed by AND starring the same person
SELECT title FROM movies
JOIN directors d ON movies.id = d.movie_id
JOIN stars     s ON movies.id = s.movie_id
WHERE d.person_id = s.person_id;

-- 7. Movies where both actor A and actor B starred
SELECT title FROM movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id AND p1.name = 'Brad Pitt'
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id AND p2.name = 'Cate Blanchett';
```

### Part 2 — Fiftyville

A mystery: a crime occurred in Fiftyville. You get `fiftyville.db` and must answer:
- Who committed the crime?
- What city did they escape to?
- Who helped them escape?

The database contains tables like `crime_scene_reports`, `interviews`, `atm_transactions`, `phone_calls`, `flights`, `passengers`, `airports`, `people`, `bank_accounts`.

### Fiftyville Investigation Strategy

```sql
-- Step 1: Find the crime scene report
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Step 2: Find witness interviews from that day
SELECT name, transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

-- Step 3: Follow the clues (bakery security footage)
SELECT name FROM people
JOIN bakery_security_logs b ON people.license_plate = b.license_plate
WHERE b.year = 2021 AND b.month = 7 AND b.day = 28
AND b.hour = 10 AND b.minute BETWEEN 15 AND 25
AND b.activity = 'exit';

-- Step 4: Check ATM withdrawals
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Step 5: Cross-reference to narrow suspects
-- Use INTERSECT to find people matching multiple clues
SELECT name FROM people
JOIN bakery_security_logs b ON people.license_plate = b.license_plate
WHERE b.year = 2021 AND b.month = 7 AND b.day = 28

INTERSECT

SELECT name FROM people
JOIN bank_accounts  ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.day = 28 AND atm_location = 'Leggett Street';

-- Step 6: Find the earliest flight out the next day
SELECT f.id, airports.city FROM flights f
JOIN airports ON f.destination_airport_id = airports.id
WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
ORDER BY f.hour, f.minute
LIMIT 1;

-- Step 7: Find passengers on that flight matching suspects
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = (
    SELECT id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    ORDER BY hour, minute LIMIT 1
);
```

### Key SQL Patterns for Fiftyville

```sql
-- INTERSECT — rows appearing in BOTH queries
query_A
INTERSECT
query_B;

-- Subquery in WHERE
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions WHERE ...
    )
);

-- EXISTS
SELECT name FROM suspects s
WHERE EXISTS (
    SELECT 1 FROM phone_calls
    WHERE caller = s.phone_number AND day = 28
);
```

---

## 25. Quick Reference Cheat Sheet

### Core SQL Commands

```sql
-- CREATE
CREATE TABLE t (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL);

-- INSERT
INSERT INTO t (name) VALUES ('Alice');

-- SELECT
SELECT * FROM t;
SELECT col1, col2 FROM t WHERE condition ORDER BY col1 DESC LIMIT 10;

-- UPDATE
UPDATE t SET col = value WHERE condition;

-- DELETE
DELETE FROM t WHERE condition;

-- DROP
DROP TABLE IF EXISTS t;
```

### SELECT Clauses in Order

```sql
SELECT   columns
FROM     table
JOIN     other_table ON condition
WHERE    row_filter
GROUP BY grouping_column
HAVING   group_filter
ORDER BY sort_column DESC
LIMIT    n
OFFSET   m;
```

### Joins Quick Reference

```sql
-- INNER JOIN — only matching rows
FROM a JOIN b ON a.id = b.a_id

-- LEFT JOIN — all left rows + matching right
FROM a LEFT JOIN b ON a.id = b.a_id

-- Self join
FROM t a JOIN t b ON a.col = b.col AND a.id != b.id
```

### Aggregate Functions

```sql
COUNT(*), COUNT(col), COUNT(DISTINCT col)
SUM(col), AVG(col), MIN(col), MAX(col)
ROUND(AVG(col), 2)
```

### Python with SQL (cs50)

```python
from cs50 import SQL
db = SQL("sqlite:///file.db")

rows = db.execute("SELECT * FROM t WHERE col = ?", value)
db.execute("INSERT INTO t (col) VALUES (?)", value)
db.execute("UPDATE t SET col = ? WHERE id = ?", value, id)
db.execute("DELETE FROM t WHERE id = ?", id)
```

### Parameterized Queries (ALWAYS use these)

```python
# cs50
db.execute("SELECT * FROM t WHERE name = ?", name)

# sqlite3
cursor.execute("SELECT * FROM t WHERE name = ?", (name,))

# NEVER concatenate user input into SQL strings!
```

### Key Rules for Week 7

| Rule | Why It Matters |
|---|---|
| Always use `WHERE` with `UPDATE` and `DELETE` | Without it, every row is modified/deleted |
| Always use `?` placeholders for user input | Prevents SQL injection attacks |
| Use `IS NULL` not `= NULL` | `= NULL` always returns no rows in SQL |
| Use single quotes for string values `'Alice'` | Double quotes are for identifiers, not values |
| Primary keys should be integers | Faster to index, join, and compare |
| Index foreign key columns | Dramatically speeds up JOIN queries |
| Enable `PRAGMA foreign_keys = ON` in SQLite | SQLite ignores FK constraints by default |
| Use transactions for multi-step operations | Ensures atomicity — all or nothing |
| `HAVING` filters groups; `WHERE` filters rows | `WHERE` runs before `GROUP BY`, `HAVING` after |
| `JOIN` = `INNER JOIN` by default | Only returns rows matching on both sides |

---

*CS50 Week 7 Notes · Harvard University · David J. Malan*
