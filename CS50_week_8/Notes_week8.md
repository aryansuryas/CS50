# CS50 — Week 8: HTML, CSS, JavaScript

**Harvard University** · David J. Malan  
**Topic:** How the internet works, building web pages with HTML, styling with CSS, making pages interactive with JavaScript, and understanding the DOM.

---

## Table of Contents

1. [How the Internet Works](#1-how-the-internet-works)
2. [IP Addresses and DNS](#2-ip-addresses-and-dns)
3. [HTTP and HTTPS](#3-http-and-https)
4. [HTTP Methods and Status Codes](#4-http-methods-and-status-codes)
5. [HTML — HyperText Markup Language](#5-html--hypertext-markup-language)
6. [HTML Document Structure](#6-html-document-structure)
7. [HTML Elements and Tags](#7-html-elements-and-tags)
8. [HTML Forms](#8-html-forms)
9. [HTML Semantic Elements](#9-html-semantic-elements)
10. [CSS — Cascading Style Sheets](#10-css--cascading-style-sheets)
11. [CSS Selectors](#11-css-selectors)
12. [CSS Box Model](#12-css-box-model)
13. [CSS Layout — Flexbox](#13-css-layout--flexbox)
14. [CSS Layout — Grid](#14-css-layout--grid)
15. [CSS Responsive Design](#15-css-responsive-design)
16. [JavaScript — The Basics](#16-javascript--the-basics)
17. [JavaScript — Functions](#17-javascript--functions)
18. [JavaScript — The DOM](#18-javascript--the-dom)
19. [JavaScript — Events](#19-javascript--events)
20. [JavaScript — Forms and Validation](#20-javascript--forms-and-validation)
21. [JavaScript — fetch() and APIs](#21-javascript--fetch-and-apis)
22. [JavaScript — Local Storage](#22-javascript--local-storage)
23. [Problem Set 8 — Homepage](#23-problem-set-8--homepage)
24. [Quick Reference Cheat Sheet](#24-quick-reference-cheat-sheet)

---

## 1. How the Internet Works

The **internet** is a global network of computers that communicate using agreed-upon rules called **protocols**.

### The Client-Server Model

Every interaction on the web follows this pattern:

```
CLIENT                              SERVER
(your browser)                      (web server)

     1. You type a URL
     │
     ▼
     2. Browser sends HTTP REQUEST ──────────────────►  Web server receives request
                                                        finds the file / runs code
     3. Browser receives HTTP RESPONSE ◄──────────────  sends back HTML, CSS, JS
     │
     ▼
     4. Browser renders the page
```

- **Client** — the browser (Chrome, Firefox, Safari) that requests resources
- **Server** — a computer that stores websites and responds to requests
- **Request** — what the client sends (give me this page)
- **Response** — what the server sends back (here is the page)

### Protocols — The Rules of Communication

| Protocol | Full Name | Purpose |
|---|---|---|
| **TCP/IP** | Transmission Control Protocol / Internet Protocol | Core data transmission |
| **DNS** | Domain Name System | Translates domain names to IP addresses |
| **HTTP** | HyperText Transfer Protocol | Transferring web pages |
| **HTTPS** | HTTP Secure | Encrypted HTTP |
| **SMTP** | Simple Mail Transfer Protocol | Sending email |
| **FTP** | File Transfer Protocol | Transferring files |
| **SSH** | Secure Shell | Secure remote access |

### Packets

Data on the internet is not sent as one continuous stream. It is broken into small chunks called **packets**, each of which travels independently and may take a different route to the destination. They are reassembled at the other end.

```
Large file:
┌─────────────────────────────────────────────┐
│              file.html (50KB)               │
└─────────────────────────────────────────────┘
                      ↓
Split into packets:
[packet 1][packet 2][packet 3]...[packet 50]

Each takes its own route through the internet
                      ↓
Reassembled at destination:
┌─────────────────────────────────────────────┐
│              file.html (50KB)               │
└─────────────────────────────────────────────┘
```

### TCP vs UDP

| | TCP | UDP |
|---|---|---|
| **Stands for** | Transmission Control Protocol | User Datagram Protocol |
| **Reliability** | Guaranteed delivery, in order | No guarantee |
| **Speed** | Slower (acknowledgments) | Faster |
| **Use for** | Web pages, email, file transfer | Video streaming, gaming, DNS |

TCP ensures all packets arrive and in the right order. UDP is faster but doesn't guarantee delivery — acceptable for video calls where a dropped frame is better than buffering.

---

## 2. IP Addresses and DNS

### IP Addresses

Every device on the internet has an **IP address** — a unique numerical label.

#### IPv4 — Internet Protocol Version 4

```
Format: four 8-bit numbers separated by dots
Range:  0-255 for each octet

Examples:
  192.168.1.1     (common home router address)
  8.8.8.8         (Google's DNS server)
  127.0.0.1       (localhost — your own machine)
  93.184.216.34   (example.com)
```

IPv4 gives 2³² = ~4.3 billion unique addresses. We've nearly run out.

#### IPv6 — Internet Protocol Version 6

```
Format: eight groups of four hexadecimal digits
Example: 2001:0db8:85a3:0000:0000:8a2e:0370:7334
Short:   2001:db8:85a3::8a2e:370:7334

Provides 2¹²⁸ = 340 undecillion addresses — essentially unlimited
```

### Ports

A port is a number (0–65535) that identifies a specific service on a machine.

| Port | Service |
|---|---|
| 20, 21 | FTP |
| 22 | SSH |
| 25 | SMTP (email) |
| 53 | DNS |
| 80 | HTTP |
| 443 | HTTPS |
| 3000 | Common dev server |
| 5000 | Flask default |
| 8080 | Common alternative HTTP |

When you visit `https://example.com`, your browser connects to port **443** automatically.

### DNS — Domain Name System

DNS translates human-readable domain names into IP addresses.

```
You type:   www.google.com
               │
               ▼
         DNS Resolver (your ISP or 8.8.8.8)
               │
               ▼
         Root DNS Server → .com TLD Server → Google's Name Server
               │
               ▼
         Returns IP: 142.250.80.36
               │
               ▼
         Browser connects to 142.250.80.36 on port 443
```

### The Full URL Breakdown

```
https://www.example.com:443/path/page.html?name=alice&age=20#section

│       │   │           │   │              │                  │
│       │   │           │   │              │                  └── Fragment (anchor)
│       │   │           │   │              └─────────────────── Query string
│       │   │           │   └────────────────────────────────── Path
│       │   │           └────────────────────────────────────── Port
│       │   └────────────────────────────────────────────────── Domain name
│       └────────────────────────────────────────────────────── Subdomain
└────────────────────────────────────────────────────────────── Scheme/Protocol
```

---

## 3. HTTP and HTTPS

**HTTP (HyperText Transfer Protocol)** is the protocol for transferring web data between clients and servers.

### HTTP Request Structure

When your browser visits a website, it sends a request like this:

```
GET /index.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Chrome/118.0)
Accept: text/html,application/xhtml+xml
Accept-Language: en-US,en;q=0.9
Connection: keep-alive
```

Breaking it down:

```
GET /index.html HTTP/1.1
│   │           └── HTTP version
│   └──────────── Path (what resource you want)
└──────────────── Method (GET = fetch a resource)
```

### HTTP Response Structure

The server replies with:

```
HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8
Content-Length: 1234
Date: Mon, 01 Jan 2024 12:00:00 GMT

<!DOCTYPE html>
<html>
  <head>...</head>
  <body>...</body>
</html>
```

Breaking it down:

```
HTTP/1.1 200 OK
│        │   └── Status text
│        └────── Status code (200 = success)
└─────────────── HTTP version

Headers: metadata about the response
Blank line: separates headers from body
Body: the actual content (HTML, JSON, image data, etc.)
```

### HTTPS — Secure HTTP

HTTPS is HTTP encrypted with **TLS (Transport Layer Security)**.

```
HTTP:   Data travels in plain text — anyone can read it
        Browser ──── "password=secret123" ────► Server

HTTPS:  Data is encrypted — gibberish to anyone intercepting
        Browser ──── "xK3#mP9$qR..." ────────► Server
```

The padlock icon in your browser means you're using HTTPS.

**TLS Handshake (simplified):**
1. Client says hello, lists supported encryption methods
2. Server responds with its SSL certificate (proves identity)
3. Client verifies certificate with a trusted Certificate Authority (CA)
4. Both agree on encryption keys
5. All subsequent communication is encrypted

---

## 4. HTTP Methods and Status Codes

### HTTP Methods (Verbs)

| Method | Purpose | Has Body? | Idempotent? |
|---|---|---|---|
| **GET** | Retrieve a resource | No | Yes |
| **POST** | Submit data, create resource | Yes | No |
| **PUT** | Replace a resource entirely | Yes | Yes |
| **PATCH** | Partially update a resource | Yes | No |
| **DELETE** | Remove a resource | No | Yes |
| **HEAD** | GET without response body | No | Yes |
| **OPTIONS** | Ask what methods are supported | No | Yes |

**Idempotent** = calling it multiple times has the same effect as calling it once.

### GET vs POST

| | GET | POST |
|---|---|---|
| **Data sent via** | URL query string | Request body |
| **Visibility** | Visible in URL, browser history | Hidden from URL |
| **Bookmarkable** | Yes | No |
| **Max data** | ~2000 characters | No limit |
| **Use for** | Reading data, searches | Submitting forms, creating data |
| **Example** | `?name=alice&age=20` | Login forms, file uploads |

```
GET:  /search?q=cats&page=2       ← data in URL, visible
POST: /login                       ← data in body, hidden
      Body: username=alice&password=secret
```

### HTTP Status Codes

Status codes are 3-digit numbers that tell you what happened.

| Range | Category | Meaning |
|---|---|---|
| 1xx | Informational | Request received, processing |
| 2xx | Success | Request succeeded |
| 3xx | Redirection | Further action needed |
| 4xx | Client Error | Something wrong with the request |
| 5xx | Server Error | Something wrong on the server |

#### Common Status Codes

| Code | Text | Meaning |
|---|---|---|
| **200** | OK | Request succeeded — the normal response |
| **201** | Created | Resource was successfully created |
| **204** | No Content | Success but no body to return |
| **301** | Moved Permanently | Resource has permanently moved to new URL |
| **302** | Found | Temporary redirect |
| **304** | Not Modified | Cached version is still valid |
| **400** | Bad Request | Client sent malformed/invalid request |
| **401** | Unauthorized | Must authenticate first |
| **403** | Forbidden | Authenticated but no permission |
| **404** | Not Found | Resource doesn't exist |
| **405** | Method Not Allowed | HTTP method not supported for this route |
| **422** | Unprocessable Entity | Valid syntax but semantic errors |
| **429** | Too Many Requests | Rate limited |
| **500** | Internal Server Error | Server crashed or has a bug |
| **502** | Bad Gateway | Server got invalid response from upstream |
| **503** | Service Unavailable | Server temporarily down/overloaded |

---

## 5. HTML — HyperText Markup Language

**HTML** is the standard language for creating web pages. It describes the **structure and content** of a page using **elements** made of **tags**.

- **HyperText** — text that links to other text (hyperlinks)
- **Markup** — annotating content with special tags that give it meaning
- **Language** — a defined syntax and set of rules

HTML is **not** a programming language — it has no logic, loops, or conditions. It is a **markup language** that describes what content is, not how to compute something.

### HTML vs CSS vs JavaScript

```
HTML        →   STRUCTURE    (what things are — headings, paragraphs, images)
CSS         →   STYLE        (how things look — colors, fonts, layout)
JavaScript  →   BEHAVIOR     (what things do — respond to clicks, animate)
```

Like a house:

```
HTML  =  The walls, rooms, doors, windows  (structure)
CSS   =  The paint, furniture, lighting    (appearance)
JS    =  The electricity, plumbing         (functionality)
```

---

## 6. HTML Document Structure

Every valid HTML page follows this structure:

```html
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="description" content="A description of this page">
        <title>Page Title — shown in browser tab</title>
        <link rel="stylesheet" href="styles.css">
        <!-- External CSS, meta tags, scripts go here -->
        <!-- NOT visible to the user -->
    </head>
    <body>
        <!-- All visible content goes here -->
        <h1>Hello, World!</h1>
        <p>This is a paragraph.</p>

        <script src="script.js"></script>
        <!-- Scripts at bottom so HTML loads first -->
    </body>
</html>
```

### Line-by-Line Explanation

| Line | Meaning |
|---|---|
| `<!DOCTYPE html>` | Tells browser this is HTML5 (not optional) |
| `<html lang="en">` | Root element — wraps everything |
| `<head>` | Metadata container — nothing visible here |
| `<meta charset="UTF-8">` | Character encoding — supports all languages |
| `<meta name="viewport" ...>` | Makes page responsive on mobile devices |
| `<title>` | Text shown in browser tab and bookmarks |
| `<link rel="stylesheet">` | Links external CSS file |
| `<body>` | Everything the user sees |
| `<script src="...">` | Links external JavaScript file |

### Anatomy of an HTML Element

```html
<tagname attribute="value">Content goes here</tagname>
│         │         │       │                 │
│         │         │       │                 └── Closing tag
│         │         │       └──────────────────── Content
│         │         └──────────────────────────── Attribute value (always in quotes)
│         └────────────────────────────────────── Attribute name
└──────────────────────────────────────────────── Opening tag
```

### Self-Closing (Void) Elements

Some elements have no content and no closing tag:

```html
<br>           <!-- line break -->
<hr>           <!-- horizontal rule (line) -->
<img src="photo.jpg" alt="A photo">
<input type="text">
<meta charset="UTF-8">
<link rel="stylesheet" href="styles.css">
```

### Comments in HTML

```html
<!-- This is a comment — not visible to users -->
<!-- Comments can span
     multiple lines -->
```

---

## 7. HTML Elements and Tags

### Headings

```html
<h1>Largest Heading — Main Title</h1>
<h2>Second Level — Section Title</h2>
<h3>Third Level — Subsection</h3>
<h4>Fourth Level</h4>
<h5>Fifth Level</h5>
<h6>Smallest Heading</h6>
```

> Use only **one `<h1>`** per page for SEO and accessibility. Use headings in order — don't skip from h1 to h4.

### Paragraphs and Text

```html
<p>This is a paragraph. HTML collapses all whitespace to a single space.</p>

<p>This is another paragraph — browsers add space between paragraphs.</p>

<!-- Line break inside a paragraph -->
<p>Line one.<br>Line two.</p>

<!-- Horizontal rule — thematic break -->
<hr>

<!-- Preformatted text — preserves whitespace -->
<pre>
  Name:   Alice
  Age:    20
</pre>
```

### Text Formatting

```html
<strong>Bold — important text</strong>
<em>Italic — emphasized text</em>
<u>Underlined</u>
<s>Strikethrough</s>
<mark>Highlighted text</mark>
<small>Smaller text — fine print</small>
<sup>Superscript — like x<sup>2</sup></sup>
<sub>Subscript — like H<sub>2</sub>O</sub>
<code>Inline code — like printf()</code>
<kbd>Keyboard input — like Ctrl+C</kbd>
<blockquote cite="source">A long quote from somewhere</blockquote>
<q>A short inline quote</q>
<abbr title="HyperText Markup Language">HTML</abbr>
```

### Links — Anchor Tags

```html
<!-- External link -->
<a href="https://www.google.com">Visit Google</a>

<!-- Internal link (same site) -->
<a href="/about.html">About Us</a>

<!-- Link to section on same page -->
<a href="#section2">Jump to Section 2</a>
<h2 id="section2">Section 2</h2>

<!-- Open in new tab -->
<a href="https://google.com" target="_blank" rel="noopener noreferrer">Google</a>

<!-- Email link -->
<a href="mailto:alice@example.com">Email Alice</a>

<!-- Phone link (mobile) -->
<a href="tel:+16175550100">Call Us</a>

<!-- Download link -->
<a href="file.pdf" download>Download PDF</a>
```

### Images

```html
<!-- Basic image -->
<img src="photo.jpg" alt="A photo of a sunset">

<!-- Always include alt for accessibility and SEO -->
<!-- alt="" for decorative images that screen readers should skip -->

<!-- Image with width and height -->
<img src="logo.png" alt="Company Logo" width="200" height="100">

<!-- Responsive image -->
<img src="photo.jpg" alt="Photo" style="max-width: 100%;">

<!-- Figure with caption -->
<figure>
    <img src="chart.png" alt="Sales chart for Q3">
    <figcaption>Q3 2024 Sales Data</figcaption>
</figure>
```

### Lists

```html
<!-- Unordered list (bullet points) -->
<ul>
    <li>First item</li>
    <li>Second item</li>
    <li>Third item</li>
</ul>

<!-- Ordered list (numbers) -->
<ol>
    <li>Step one</li>
    <li>Step two</li>
    <li>Step three</li>
</ol>

<!-- Ordered list with custom start -->
<ol start="5" type="A">
    <li>Item E</li>
    <li>Item F</li>
</ol>

<!-- Nested lists -->
<ul>
    <li>Fruits
        <ul>
            <li>Apple</li>
            <li>Banana</li>
        </ul>
    </li>
    <li>Vegetables</li>
</ul>

<!-- Description list (term + definition) -->
<dl>
    <dt>HTML</dt>
    <dd>HyperText Markup Language — structures web content</dd>
    <dt>CSS</dt>
    <dd>Cascading Style Sheets — styles web content</dd>
</dl>
```

### Tables

```html
<table>
    <thead>
        <tr>
            <th>Name</th>
            <th>Age</th>
            <th>GPA</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Alice</td>
            <td>20</td>
            <td>3.9</td>
        </tr>
        <tr>
            <td>Bob</td>
            <td>22</td>
            <td>3.2</td>
        </tr>
    </tbody>
    <tfoot>
        <tr>
            <td colspan="3">Total: 2 students</td>
        </tr>
    </tfoot>
</table>
```

| Tag | Purpose |
|---|---|
| `<table>` | Container for the entire table |
| `<thead>` | Table header section |
| `<tbody>` | Table body section |
| `<tfoot>` | Table footer section |
| `<tr>` | Table row |
| `<th>` | Table header cell (bold, centered by default) |
| `<td>` | Table data cell |
| `colspan="n"` | Cell spans n columns |
| `rowspan="n"` | Cell spans n rows |

### Div and Span — Generic Containers

```html
<!-- div: block-level container (takes full width, starts new line) -->
<div class="card">
    <h2>Title</h2>
    <p>Content</p>
</div>

<!-- span: inline container (stays in flow of text) -->
<p>The price is <span class="price">$19.99</span> today.</p>
```

---

## 8. HTML Forms

Forms collect user input and send it to a server (or process it with JavaScript).

### Basic Form Structure

```html
<form action="/submit" method="post">
    <!-- form elements go here -->
    <button type="submit">Submit</button>
</form>
```

| Attribute | Meaning |
|---|---|
| `action` | URL to send the form data to |
| `method` | HTTP method — `get` or `post` |
| `enctype` | Encoding type — use `multipart/form-data` for file uploads |

### All Input Types

```html
<!-- Text inputs -->
<input type="text"     name="name"    placeholder="Your name">
<input type="email"    name="email"   placeholder="you@example.com">
<input type="password" name="pass"    placeholder="Password">
<input type="number"   name="age"     min="0" max="120" step="1">
<input type="tel"      name="phone"   placeholder="555-0100">
<input type="url"      name="website" placeholder="https://example.com">
<input type="search"   name="q"       placeholder="Search...">

<!-- Date and time -->
<input type="date"           name="birthday">
<input type="time"           name="meeting">
<input type="datetime-local" name="event">
<input type="month"          name="month">
<input type="week"           name="week">

<!-- Selection -->
<input type="checkbox" name="agree"   value="yes" id="agree">
<label for="agree">I agree to the terms</label>

<input type="radio" name="color" value="red"   id="red">
<label for="red">Red</label>
<input type="radio" name="color" value="blue"  id="blue">
<label for="blue">Blue</label>

<!-- Range slider -->
<input type="range" name="volume" min="0" max="100" value="50">

<!-- Color picker -->
<input type="color" name="bg" value="#ff0000">

<!-- File upload -->
<input type="file"   name="photo" accept="image/*">
<input type="file"   name="docs"  accept=".pdf,.doc" multiple>

<!-- Hidden field (sent but not shown to user) -->
<input type="hidden" name="csrf_token" value="abc123">

<!-- Submit and reset buttons -->
<input type="submit" value="Submit Form">
<input type="reset"  value="Clear Form">
```

### Labels, Textareas, and Select

```html
<!-- Label — connects to input via 'for' matching input 'id' -->
<label for="username">Username:</label>
<input type="text" id="username" name="username" required>

<!-- Textarea — multi-line text input -->
<label for="message">Message:</label>
<textarea id="message" name="message" rows="5" cols="40"
          placeholder="Enter your message..."></textarea>

<!-- Select dropdown -->
<label for="country">Country:</label>
<select id="country" name="country">
    <option value="">-- Select --</option>
    <option value="us">United States</option>
    <option value="uk" selected>United Kingdom</option>
    <option value="ca">Canada</option>
</select>

<!-- Select with groups -->
<select name="course">
    <optgroup label="Computer Science">
        <option value="cs50">CS50</option>
        <option value="cs51">CS51</option>
    </optgroup>
    <optgroup label="Mathematics">
        <option value="math">Calculus</option>
    </optgroup>
</select>

<!-- Multi-select -->
<select name="languages" multiple size="4">
    <option value="python">Python</option>
    <option value="c">C</option>
    <option value="js">JavaScript</option>
    <option value="sql">SQL</option>
</select>
```

### Form Validation Attributes

```html
<input type="text"   required>                    <!-- cannot be empty -->
<input type="text"   minlength="3" maxlength="50"> <!-- length constraints -->
<input type="number" min="0" max="100">            <!-- value range -->
<input type="text"   pattern="[A-Za-z]{3,}">       <!-- regex pattern -->
<input type="email">                               <!-- built-in email validation -->
<input type="url">                                 <!-- built-in URL validation -->
<input type="number" step="0.01">                  <!-- decimal steps -->
```

### Fieldset and Legend — Grouping Form Elements

```html
<form>
    <fieldset>
        <legend>Personal Information</legend>
        <label for="fname">First Name:</label>
        <input type="text" id="fname" name="fname">
        <label for="lname">Last Name:</label>
        <input type="text" id="lname" name="lname">
    </fieldset>

    <fieldset>
        <legend>Account Details</legend>
        <label for="email">Email:</label>
        <input type="email" id="email" name="email">
    </fieldset>

    <button type="submit">Register</button>
</form>
```

---

## 9. HTML Semantic Elements

**Semantic elements** clearly describe their meaning to both the browser and the developer.

```html
<!-- Non-semantic: tells us nothing about content -->
<div id="nav">...</div>
<div class="header">...</div>
<div id="main">...</div>

<!-- Semantic: self-describing -->
<nav>...</nav>
<header>...</header>
<main>...</main>
```

### Full Semantic Page Layout

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>My Website</title>
</head>
<body>

    <header>
        <!-- Site header — logo, site name, main navigation -->
        <nav>
            <ul>
                <li><a href="/">Home</a></li>
                <li><a href="/about">About</a></li>
                <li><a href="/contact">Contact</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <!-- Primary content of the page — only one per page -->

        <section>
            <!-- Thematically grouped content with a heading -->
            <h2>About Us</h2>
            <p>We build amazing things.</p>
        </section>

        <article>
            <!-- Self-contained content (blog post, news article) -->
            <h2>Blog Post Title</h2>
            <p>Published <time datetime="2024-01-15">January 15, 2024</time></p>
            <p>Article content...</p>
        </article>

        <aside>
            <!-- Sidebar content tangentially related to main -->
            <h3>Related Links</h3>
            <ul>
                <li><a href="#">Link 1</a></li>
            </ul>
        </aside>

    </main>

    <footer>
        <!-- Site footer — copyright, links, contact info -->
        <p>&copy; 2024 My Company. All rights reserved.</p>
    </footer>

</body>
</html>
```

### Semantic Elements Reference

| Element | Purpose |
|---|---|
| `<header>` | Introductory content, logo, navigation |
| `<nav>` | Navigation links |
| `<main>` | Primary content — unique to the page |
| `<section>` | Thematically grouped content with a heading |
| `<article>` | Self-contained content (blog post, comment) |
| `<aside>` | Secondary content, sidebars, callouts |
| `<footer>` | Footer of a section or page |
| `<figure>` | Self-contained content (image, diagram) |
| `<figcaption>` | Caption for a `<figure>` |
| `<time>` | A specific time or date |
| `<mark>` | Highlighted/relevant text |
| `<details>` | Expandable disclosure widget |
| `<summary>` | Summary/heading for `<details>` |
| `<address>` | Contact information |

---

## 10. CSS — Cascading Style Sheets

**CSS** controls the visual presentation of HTML elements — colors, fonts, spacing, layout, animations.

### Three Ways to Add CSS

#### 1. Inline CSS (least recommended)

```html
<p style="color: red; font-size: 18px;">Red paragraph</p>
```

Mixes content and style — hard to maintain.

#### 2. Internal CSS (style block in head)

```html
<head>
    <style>
        p {
            color: red;
            font-size: 18px;
        }
    </style>
</head>
```

Good for single pages. Hard to reuse across multiple pages.

#### 3. External CSS (recommended)

```html
<!-- In HTML -->
<head>
    <link rel="stylesheet" href="styles.css">
</head>
```

```css
/* In styles.css */
p {
    color: red;
    font-size: 18px;
}
```

Best practice — single CSS file controls all pages. Easy to maintain.

### CSS Syntax

```css
selector {
    property: value;
    property: value;
}

/* Example */
h1 {
    color: #1a1a1a;
    font-size: 2rem;
    font-weight: bold;
    text-align: center;
}
```

### CSS Colors

```css
/* Named colors */
color: red;
color: blue;
color: darkblue;

/* Hexadecimal */
color: #ff0000;    /* red */
color: #1a73e8;    /* Google blue */
color: #fff;       /* white (shorthand for #ffffff) */

/* RGB */
color: rgb(255, 0, 0);       /* red */
color: rgb(26, 115, 232);    /* Google blue */

/* RGBA — with transparency (0=transparent, 1=opaque) */
color: rgba(0, 0, 0, 0.5);  /* 50% transparent black */

/* HSL — Hue Saturation Lightness */
color: hsl(210, 80%, 50%);

/* HSLA */
color: hsla(210, 80%, 50%, 0.7);
```

### CSS Units

```css
/* Absolute units */
px    /* pixels — most common for screens */
pt    /* points — used for print */
cm    /* centimeters */

/* Relative units */
em    /* relative to parent element's font size */
rem   /* relative to ROOT element's font size (more predictable) */
%     /* percentage of parent element */
vw    /* viewport width — 1vw = 1% of window width */
vh    /* viewport height — 1vh = 1% of window height */
vmin  /* smaller of vw or vh */
vmax  /* larger of vw or vh */
ch    /* width of "0" character in current font */

/* Examples */
font-size: 16px;     /* fixed size */
font-size: 1rem;     /* 1 × root font size (usually 16px) */
font-size: 1.5em;    /* 1.5 × parent font size */
width: 50%;          /* half of parent's width */
width: 100vw;        /* full viewport width */
height: 100vh;       /* full viewport height */
```

---

## 11. CSS Selectors

Selectors specify which HTML elements to style.

### Basic Selectors

```css
/* Element selector — all <p> elements */
p { color: blue; }

/* Class selector — all elements with class="highlight" */
.highlight { background: yellow; }

/* ID selector — element with id="title" */
#title { font-size: 2rem; }

/* Universal selector — everything */
* { box-sizing: border-box; }

/* Grouping — apply same style to multiple selectors */
h1, h2, h3 { font-family: Arial, sans-serif; }
```

### Attribute Selectors

```css
/* Has the attribute */
input[required] { border: 2px solid red; }

/* Attribute equals value */
input[type="email"] { border-color: blue; }

/* Attribute starts with */
a[href^="https"] { color: green; }

/* Attribute ends with */
a[href$=".pdf"] { color: red; }

/* Attribute contains */
a[href*="github"] { font-weight: bold; }
```

### Combinator Selectors

```css
/* Descendant — any p inside a div (any depth) */
div p { color: blue; }

/* Child — p that is DIRECT child of div (one level only) */
div > p { color: red; }

/* Adjacent sibling — h2 immediately followed by p */
h2 + p { font-size: 1.2rem; }

/* General sibling — all p siblings after h2 */
h2 ~ p { color: gray; }
```

### Pseudo-Classes

```css
/* Link states */
a:link    { color: blue; }     /* unvisited link */
a:visited { color: purple; }   /* visited link */
a:hover   { color: red; }      /* mouse over */
a:active  { color: orange; }   /* being clicked */

/* Form states */
input:focus       { outline: 2px solid blue; }  /* currently selected */
input:disabled    { opacity: 0.5; }
input:checked     { accent-color: green; }

/* Structural */
li:first-child    { font-weight: bold; }
li:last-child     { border: none; }
li:nth-child(2)   { color: red; }         /* second child */
li:nth-child(odd) { background: #f0f0f0; } /* odd rows */
li:nth-child(even){ background: white; }
p:not(.special)   { color: gray; }        /* all p EXCEPT .special */
```

### Pseudo-Elements

```css
/* Style part of an element */
p::first-line   { font-weight: bold; }
p::first-letter { font-size: 2em; }

/* Insert content before/after element */
.required::after  { content: " *"; color: red; }
blockquote::before { content: "\201C"; font-size: 3em; }
```

### CSS Specificity

When multiple rules target the same element, **specificity** determines which wins.

```
Specificity score (higher wins):

Inline style:       1,0,0,0   (highest)
ID selector:        0,1,0,0
Class/Pseudo-class: 0,0,1,0
Element selector:   0,0,0,1   (lowest)
Universal *:        0,0,0,0

Examples:
#title              → 0,1,0,0   = 100
.highlight          → 0,0,1,0   = 010
p                   → 0,0,0,1   = 001
div p.special       → 0,0,1,2   = 012
#nav a:hover        → 0,1,1,1   = 111
```

When specificity is equal, the **last rule wins** (the cascade).

```css
p { color: blue; }   /* specificity: 001 */
p { color: red; }    /* also 001, but later → RED wins */
.para { color: green; } /* 010 → GREEN wins over both */
```

### `!important` — Override Everything

```css
p { color: blue !important; }   /* overrides everything, even higher specificity */
/* Use sparingly — makes debugging very hard */
```

---

## 12. CSS Box Model

Every HTML element is a rectangular box. The **box model** describes the layers around content.

```
┌──────────────────────────────────────────┐
│                  MARGIN                  │  ← space outside the border
│   ┌──────────────────────────────────┐   │
│   │             BORDER               │   │  ← visible border line
│   │   ┌──────────────────────────┐   │   │
│   │   │          PADDING         │   │   │  ← space between border and content
│   │   │   ┌──────────────────┐   │   │   │
│   │   │   │                  │   │   │   │
│   │   │   │     CONTENT      │   │   │   │  ← actual text/image
│   │   │   │                  │   │   │   │
│   │   │   └──────────────────┘   │   │   │
│   │   └──────────────────────────┘   │   │
│   └──────────────────────────────────┘   │
└──────────────────────────────────────────┘
```

### Box Model Properties

```css
.box {
    /* Content dimensions */
    width:  300px;
    height: 200px;

    /* Padding — inside, between content and border */
    padding: 20px;                /* all sides */
    padding: 10px 20px;           /* top/bottom | left/right */
    padding: 10px 20px 15px 5px;  /* top | right | bottom | left (clockwise) */
    padding-top:    10px;
    padding-right:  20px;
    padding-bottom: 15px;
    padding-left:   5px;

    /* Border */
    border: 2px solid #333;       /* width | style | color */
    border-radius: 8px;           /* rounded corners */
    border-top: 3px dashed red;

    /* Margin — outside, between this element and others */
    margin: 20px;
    margin: 10px auto;            /* top/bottom 10px | center horizontally */
    margin-top:    10px;
    margin-right:  auto;          /* auto = take all available space */

    /* Background */
    background-color: #f0f0f0;
    background-image: url("bg.jpg");
    background-size:    cover;    /* fill the element */
    background-position: center;
    background-repeat: no-repeat;
}
```

### `box-sizing` — The Most Important CSS Reset

By default, `width` and `height` apply to the **content only**. Padding and border are added on top.

```css
/* Default behavior — confusing */
.box {
    width: 300px;
    padding: 20px;
    border: 2px solid black;
    /* Actual total width: 300 + 40 + 4 = 344px */
}

/* Fix: box-sizing: border-box */
.box {
    box-sizing: border-box;
    width: 300px;
    padding: 20px;
    border: 2px solid black;
    /* Total width stays: 300px — padding and border included */
}

/* Apply to EVERYTHING (best practice — use this always) */
*, *::before, *::after {
    box-sizing: border-box;
}
```

---

## 13. CSS Layout — Flexbox

**Flexbox** makes it easy to arrange items in a single row or column, distribute space, and align content.

### Enable Flexbox

```css
.container {
    display: flex;   /* turns children into flex items */
}
```

### Container Properties (on the parent)

```css
.container {
    display: flex;

    /* Direction */
    flex-direction: row;            /* → left to right (default) */
    flex-direction: row-reverse;    /* ← right to left */
    flex-direction: column;         /* ↓ top to bottom */
    flex-direction: column-reverse; /* ↑ bottom to top */

    /* Wrapping */
    flex-wrap: nowrap;   /* default — all in one line, may overflow */
    flex-wrap: wrap;     /* wrap to next line if needed */

    /* Alignment on the main axis (default: horizontal) */
    justify-content: flex-start;    /* items at start */
    justify-content: flex-end;      /* items at end */
    justify-content: center;        /* items centered */
    justify-content: space-between; /* even gaps, edges flush */
    justify-content: space-around;  /* even gaps, half gaps at edges */
    justify-content: space-evenly;  /* perfectly equal gaps everywhere */

    /* Alignment on the cross axis (default: vertical) */
    align-items: stretch;     /* items fill full height (default) */
    align-items: flex-start;  /* align to top */
    align-items: flex-end;    /* align to bottom */
    align-items: center;      /* vertically center */
    align-items: baseline;    /* align text baselines */

    /* Gap between items */
    gap: 16px;            /* row and column gap */
    row-gap: 10px;
    column-gap: 20px;
}
```

### Item Properties (on the children)

```css
.item {
    flex-grow:   1;     /* can grow — share available space */
    flex-shrink: 1;     /* can shrink if needed */
    flex-basis:  auto;  /* starting size before grow/shrink */

    /* Shorthand */
    flex: 1;           /* flex-grow: 1, flex-shrink: 1, flex-basis: 0% */
    flex: 0 0 200px;   /* fixed 200px — don't grow or shrink */

    /* Override container's align-items for this item */
    align-self: center;

    /* Reorder visually (doesn't change HTML) */
    order: -1;   /* move to front */
    order: 2;    /* move later */
}
```

### Common Flexbox Patterns

```css
/* Center anything horizontally and vertically */
.container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}

/* Navigation bar */
nav {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0 20px;
}

/* Equal-width columns */
.columns {
    display: flex;
    gap: 20px;
}
.column {
    flex: 1;   /* each column gets equal share */
}

/* Card layout */
.cards {
    display: flex;
    flex-wrap: wrap;
    gap: 16px;
}
.card {
    flex: 0 0 calc(33.333% - 16px);   /* 3 per row with gap */
}
```

---

## 14. CSS Layout — Grid

**CSS Grid** is a two-dimensional layout system — handles both rows and columns simultaneously.

### Enable Grid

```css
.container {
    display: grid;
}
```

### Defining Columns and Rows

```css
.container {
    display: grid;

    /* Define 3 equal columns */
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-columns: repeat(3, 1fr);      /* same, shorthand */
    grid-template-columns: 200px 1fr 300px;     /* fixed | flexible | fixed */
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); /* responsive */

    /* Define rows */
    grid-template-rows: auto 1fr auto;    /* header | main | footer */

    /* Gap between cells */
    gap: 16px;
    row-gap: 10px;
    column-gap: 20px;
}
```

### Placing Items in the Grid

```css
.item {
    /* Span from column line 1 to column line 3 (spans 2 columns) */
    grid-column: 1 / 3;
    grid-column: span 2;   /* same — span 2 columns from current position */

    /* Span rows */
    grid-row: 1 / 3;
    grid-row: span 2;
}

/* Full-width header */
.header { grid-column: 1 / -1; }  /* -1 = last line */
```

### Named Template Areas

```css
.container {
    display: grid;
    grid-template-areas:
        "header  header  header"
        "sidebar main    main"
        "footer  footer  footer";
    grid-template-columns: 200px 1fr 1fr;
    grid-template-rows: auto 1fr auto;
}

.header  { grid-area: header; }
.sidebar { grid-area: sidebar; }
.main    { grid-area: main; }
.footer  { grid-area: footer; }
```

### Flexbox vs Grid

| | Flexbox | Grid |
|---|---|---|
| **Dimension** | One-dimensional (row OR column) | Two-dimensional (rows AND columns) |
| **Best for** | Navigation bars, toolbars, cards in a row | Full page layouts, complex 2D grids |
| **Content flow** | Content-driven | Layout-driven |
| **Browser support** | Excellent | Excellent |

---

## 15. CSS Responsive Design

Responsive design makes websites look good on all screen sizes.

### Media Queries

```css
/* Default styles (mobile-first) */
.container { width: 100%; }

/* Tablet and up */
@media (min-width: 768px) {
    .container { width: 750px; }
}

/* Desktop and up */
@media (min-width: 1024px) {
    .container { width: 960px; }
}

/* Large screens */
@media (min-width: 1200px) {
    .container { width: 1140px; }
}

/* Print */
@media print {
    nav, .sidebar { display: none; }
    body { font-size: 12pt; }
}

/* Dark mode */
@media (prefers-color-scheme: dark) {
    body { background: #1a1a1a; color: #fff; }
}
```

### Common Breakpoints

| Breakpoint | Width | Typical Device |
|---|---|---|
| Extra small | < 576px | Small phones |
| Small | ≥ 576px | Phones |
| Medium | ≥ 768px | Tablets |
| Large | ≥ 992px | Laptops |
| Extra large | ≥ 1200px | Desktops |
| XXL | ≥ 1400px | Large monitors |

### Viewport Meta Tag (Required for Mobile)

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

Without this, mobile browsers zoom out to show the full desktop-sized page.

### Responsive Images

```css
img {
    max-width: 100%;   /* never wider than its container */
    height: auto;      /* maintain aspect ratio */
}
```

### CSS Variables (Custom Properties)

```css
:root {
    --primary:   #1a73e8;
    --secondary: #ea4335;
    --font-size: 16px;
    --spacing:   1rem;
}

button {
    background: var(--primary);
    font-size:  var(--font-size);
    padding:    var(--spacing);
}

/* Override in dark mode */
@media (prefers-color-scheme: dark) {
    :root {
        --primary: #8ab4f8;
    }
}
```

---

## 16. JavaScript — The Basics

**JavaScript** is the programming language of the web. It runs in the browser and makes pages **interactive** — responding to clicks, updating content without reloading, fetching data, animating elements.

### Adding JavaScript to HTML

```html
<!-- Internal script (in body, near bottom) -->
<body>
    <p>Content</p>
    <script>
        console.log("Hello from JS!");
    </script>
</body>

<!-- External script (recommended) -->
<script src="script.js"></script>

<!-- Defer loading (modern best practice) -->
<script src="script.js" defer></script>
<!-- defer: HTML parses fully, then script runs -->

<!-- Async loading -->
<script src="analytics.js" async></script>
<!-- async: script downloads and runs as soon as ready -->
```

### Variables — let, const, var

```javascript
// const — cannot be reassigned (preferred default)
const name = "Alice";
const PI   = 3.14159;

// let — can be reassigned (use when value changes)
let score = 0;
score = 100;      // OK

// var — function-scoped, hoisted (avoid in modern JS)
var x = 5;

// Block scope
{
    let block = "only here";   // only accessible in this block
    var global = "everywhere"; // accessible outside (bad practice)
}
```

### Data Types in JavaScript

```javascript
// Primitive types
let num     = 42;            // Number (integers AND floats)
let decimal = 3.14;          // same type — Number
let text    = "Hello";       // String
let flag    = true;          // Boolean
let nothing = null;          // null — intentional absence
let undef;                   // undefined — declared but not assigned
let big     = 9007199254740991n;  // BigInt — huge integers
let sym     = Symbol("id");  // Symbol — unique identifier

// Complex types
let arr = [1, 2, 3];         // Array
let obj = { name: "Alice" }; // Object
```

### Operators

```javascript
// Arithmetic
5 + 3   // 8
5 - 3   // 2
5 * 3   // 15
5 / 3   // 1.666...  (always floating point)
5 % 3   // 2  (modulo)
2 ** 3  // 8  (exponentiation)

// String concatenation
"Hello" + " " + "World"   // "Hello World"
`Hello, ${name}!`          // template literal

// Assignment
x = 5;   x += 3;   x -= 2;   x *= 4;   x /= 2;
x++;     x--;

// Comparison
x == y    // equal (with type coercion — AVOID)
x === y   // strict equal (no coercion — ALWAYS USE THIS)
x != y    // not equal (with coercion)
x !== y   // strict not equal (ALWAYS USE THIS)
x > y;    x < y;    x >= y;    x <= y;

// Logical
x && y    // AND
x || y    // OR
!x        // NOT

// Nullish coalescing
x ?? "default"   // use x if not null/undefined, else "default"

// Optional chaining
user?.address?.city   // safely access nested properties
```

### `===` vs `==` — Always Use Strict Equality

```javascript
// == coerces types — unexpected behavior
0  == false   // true  ← dangerous!
"" == false   // true  ← dangerous!
1  == "1"     // true  ← dangerous!
null == undefined  // true  ← dangerous!

// === checks both value AND type
0   === false  // false ← correct
""  === false  // false ← correct
1   === "1"    // false ← correct
null === undefined // false ← correct
```

### Conditionals

```javascript
let score = 85;

if (score >= 90) {
    console.log("A");
} else if (score >= 80) {
    console.log("B");
} else {
    console.log("C");
}

// Ternary
const grade = score >= 60 ? "Pass" : "Fail";

// Switch
switch (day) {
    case "Monday":
        console.log("Start of week");
        break;
    case "Friday":
        console.log("End of week");
        break;
    default:
        console.log("Midweek");
}
```

### Loops

```javascript
// for loop
for (let i = 0; i < 5; i++) {
    console.log(i);
}

// while loop
let i = 0;
while (i < 5) {
    console.log(i++);
}

// for...of — iterate over array values
const names = ["Alice", "Bob", "Charlie"];
for (const name of names) {
    console.log(name);
}

// for...in — iterate over object keys
const student = { name: "Alice", age: 20 };
for (const key in student) {
    console.log(key, student[key]);
}

// Array methods (cleaner than loops)
names.forEach(name => console.log(name));
const upper = names.map(name => name.toUpperCase());
const long  = names.filter(name => name.length > 3);
const total = [1,2,3,4,5].reduce((acc, x) => acc + x, 0);
```

---

## 17. JavaScript — Functions

### Function Declaration

```javascript
function greet(name) {
    return `Hello, ${name}!`;
}

console.log(greet("Alice"));  // Hello, Alice!
```

### Function Expression

```javascript
const greet = function(name) {
    return `Hello, ${name}!`;
};
```

### Arrow Functions (ES6) — Modern Syntax

```javascript
// Full arrow function
const greet = (name) => {
    return `Hello, ${name}!`;
};

// Concise — single expression, implicit return
const greet   = name => `Hello, ${name}!`;
const square  = x => x * x;
const add     = (a, b) => a + b;
const nothing = () => console.log("nothing");

// Multiline arrow function
const process = (x, y) => {
    const sum = x + y;
    return sum * 2;
};
```

### Default Parameters

```javascript
function greet(name = "World") {
    return `Hello, ${name}!`;
}

greet("Alice")  // "Hello, Alice!"
greet()         // "Hello, World!"
```

### Rest Parameters

```javascript
function sum(...numbers) {
    return numbers.reduce((total, n) => total + n, 0);
}

sum(1, 2, 3, 4, 5)  // 15
```

### Closures

A closure is a function that remembers its surrounding scope even after the outer function has finished:

```javascript
function makeCounter() {
    let count = 0;
    return function() {
        count++;
        return count;
    };
}

const counter = makeCounter();
counter()  // 1
counter()  // 2
counter()  // 3
```

---

## 18. JavaScript — The DOM

The **DOM (Document Object Model)** is a programming interface for HTML documents. When the browser loads HTML, it creates a **tree of objects** representing every element.

```
Document
└── html
    ├── head
    │   ├── title → "My Page"
    │   └── meta
    └── body
        ├── h1 → "Hello"
        ├── p  → "World"
        └── div.container
            ├── ul
            │   ├── li → "Item 1"
            │   └── li → "Item 2"
            └── button → "Click me"
```

JavaScript can **read and modify** every node in this tree.

### Selecting Elements

```javascript
// By ID — returns single element (or null)
const title = document.getElementById("title");

// By CSS selector — returns FIRST match (or null)
const btn   = document.querySelector("button");
const card  = document.querySelector(".card");
const main  = document.querySelector("#main");
const email = document.querySelector("input[type='email']");

// By CSS selector — returns ALL matches (NodeList)
const items = document.querySelectorAll("li");
const cards = document.querySelectorAll(".card");

// Older methods (still work but querySelector is preferred)
const byClass = document.getElementsByClassName("highlight");
const byTag   = document.getElementsByTagName("p");
```

### Reading and Modifying Content

```javascript
const heading = document.querySelector("h1");

// Read and write text content (no HTML)
heading.textContent          // "Hello"
heading.textContent = "Goodbye";

// Read and write HTML content (parses HTML tags)
heading.innerHTML            // "<em>Hello</em>"
heading.innerHTML = "<em>Goodbye</em>";

// Read and write form input values
const input = document.querySelector("input");
input.value          // current value in the field
input.value = "new value";
```

### Reading and Modifying Attributes

```javascript
const img = document.querySelector("img");

img.getAttribute("src")         // get attribute value
img.setAttribute("src", "new.jpg") // set attribute
img.removeAttribute("alt")      // remove attribute
img.hasAttribute("alt")         // check if exists → boolean

// Common attributes as direct properties
img.src     = "photo.jpg";
img.alt     = "A photo";
link.href   = "https://example.com";
input.value = "Alice";
input.disabled = true;
checkbox.checked = true;
```

### Reading and Modifying CSS

```javascript
const box = document.querySelector(".box");

// Inline styles
box.style.color           = "red";
box.style.backgroundColor = "blue";     // camelCase!
box.style.fontSize        = "18px";
box.style.display         = "none";     // hide element
box.style.display         = "";         // restore display

// CSS classes (preferred — keep style in CSS)
box.classList.add("active");
box.classList.remove("active");
box.classList.toggle("active");      // add if absent, remove if present
box.classList.contains("active");   // true / false
box.classList.replace("old", "new");
```

### Creating and Removing Elements

```javascript
// Create a new element
const newItem = document.createElement("li");
newItem.textContent = "New item";
newItem.classList.add("item");

// Add to DOM
const list = document.querySelector("ul");
list.appendChild(newItem);             // add at end
list.prepend(newItem);                 // add at start
list.insertBefore(newItem, list.firstChild);  // insert before specific child

// Remove from DOM
newItem.remove();
list.removeChild(newItem);

// Clone an element
const clone = newItem.cloneNode(true);  // true = deep clone (with children)

// Replace an element
list.replaceChild(newItem, oldItem);
```

### Traversing the DOM

```javascript
const item = document.querySelector("li");

item.parentElement          // parent
item.children               // HTMLCollection of direct children
item.firstElementChild      // first child element
item.lastElementChild       // last child element
item.nextElementSibling     // next sibling
item.previousElementSibling // previous sibling
item.closest(".container")  // nearest ancestor matching selector
```

---

## 19. JavaScript — Events

**Events** are things that happen in the browser — user clicks, key presses, form submissions, page loads, and more. JavaScript can listen for events and respond.

### addEventListener — The Right Way

```javascript
const button = document.querySelector("button");

button.addEventListener("click", function(event) {
    console.log("Button clicked!");
    console.log(event.target);  // the element that triggered the event
});

// With arrow function
button.addEventListener("click", (e) => {
    e.target.textContent = "Clicked!";
});

// Remove listener
const handler = () => console.log("clicked");
button.addEventListener("click", handler);
button.removeEventListener("click", handler);  // must be same function reference
```

### Common Event Types

```javascript
// Mouse events
element.addEventListener("click",       handler);  // left click
element.addEventListener("dblclick",    handler);  // double click
element.addEventListener("mousedown",   handler);  // button pressed
element.addEventListener("mouseup",     handler);  // button released
element.addEventListener("mouseover",   handler);  // mouse enters
element.addEventListener("mouseout",    handler);  // mouse leaves
element.addEventListener("mousemove",   handler);  // mouse moves

// Keyboard events
document.addEventListener("keydown",    e => console.log(e.key));
document.addEventListener("keyup",      e => console.log(e.key));
document.addEventListener("keypress",   handler);  // deprecated

// Form events
form.addEventListener("submit",         handler);
input.addEventListener("change",        handler);  // value changed + unfocused
input.addEventListener("input",         handler);  // every keystroke
input.addEventListener("focus",         handler);  // element gains focus
input.addEventListener("blur",          handler);  // element loses focus

// Window/Document events
window.addEventListener("load",         handler);  // entire page loaded (images too)
document.addEventListener("DOMContentLoaded", handler);  // HTML parsed, before images
window.addEventListener("resize",       handler);
window.addEventListener("scroll",       handler);

// Touch events (mobile)
element.addEventListener("touchstart",  handler);
element.addEventListener("touchend",    handler);
```

### The Event Object

```javascript
button.addEventListener("click", (event) => {
    event.target          // element that triggered the event
    event.currentTarget   // element the listener is attached to
    event.type            // "click", "keydown", etc.
    event.timestamp       // when event occurred

    // Mouse events
    event.clientX         // X position relative to viewport
    event.clientY         // Y position relative to viewport
    event.pageX           // X position relative to page

    // Keyboard events
    event.key             // "Enter", "ArrowUp", "a", etc.
    event.code            // "KeyA", "Enter", "Space" etc.
    event.ctrlKey         // true if Ctrl was held
    event.shiftKey        // true if Shift was held
    event.altKey          // true if Alt was held

    // Prevent default browser behavior
    event.preventDefault();  // stop form submission, link navigation, etc.

    // Stop event propagation (bubbling)
    event.stopPropagation();
});
```

### Event Delegation

Instead of adding listeners to many elements, add one to the parent:

```javascript
// ❌ Adding listener to each item — inefficient
document.querySelectorAll("li").forEach(li => {
    li.addEventListener("click", handler);
});

// ✅ Event delegation — one listener on parent
const list = document.querySelector("ul");
list.addEventListener("click", (e) => {
    if (e.target.tagName === "LI") {
        console.log("Clicked:", e.target.textContent);
    }
});
```

Works even for elements added to the DOM later!

### DOMContentLoaded — Run Code After HTML is Ready

```javascript
// Option 1 — DOMContentLoaded event
document.addEventListener("DOMContentLoaded", () => {
    // DOM is ready — safe to query elements
    const button = document.querySelector("button");
    button.addEventListener("click", handler);
});

// Option 2 — defer attribute on script tag (modern best practice)
// <script src="script.js" defer></script>
// With defer, script runs after HTML is parsed automatically
```

---

## 20. JavaScript — Forms and Validation

### Accessing Form Data

```javascript
const form = document.querySelector("form");

form.addEventListener("submit", (event) => {
    event.preventDefault();   // STOP the form from submitting to server

    // Access form elements
    const name  = document.querySelector("#name").value;
    const email = document.querySelector("#email").value;

    // Or through the form object
    const name  = form.elements["name"].value;
    const email = form.elements["email"].value;

    console.log(name, email);
});
```

### Client-Side Validation

```javascript
form.addEventListener("submit", (event) => {
    event.preventDefault();

    const name  = document.querySelector("#name").value.trim();
    const email = document.querySelector("#email").value.trim();
    const age   = parseInt(document.querySelector("#age").value);

    const errors = [];

    if (name.length < 2) {
        errors.push("Name must be at least 2 characters");
    }

    if (!email.includes("@") || !email.includes(".")) {
        errors.push("Please enter a valid email");
    }

    if (isNaN(age) || age < 0 || age > 120) {
        errors.push("Please enter a valid age");
    }

    if (errors.length > 0) {
        document.querySelector("#error-message").innerHTML =
            errors.map(e => `<p>${e}</p>`).join("");
        return;
    }

    // Validation passed — process the form
    console.log("Form submitted:", { name, email, age });
});
```

### Real-Time Validation

```javascript
const emailInput = document.querySelector("#email");

emailInput.addEventListener("input", () => {
    const value = emailInput.value.trim();
    const isValid = /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value);

    if (isValid) {
        emailInput.style.borderColor = "green";
    } else {
        emailInput.style.borderColor = "red";
    }
});
```

---

## 21. JavaScript — fetch() and APIs

`fetch()` lets JavaScript make HTTP requests without reloading the page — the foundation of modern web apps.

### Basic fetch() — GET Request

```javascript
// fetch returns a Promise
fetch("https://api.example.com/data")
    .then(response => response.json())   // parse JSON from response body
    .then(data => {
        console.log(data);
        // update the DOM with data
        document.querySelector("#output").textContent = data.message;
    })
    .catch(error => {
        console.error("Fetch failed:", error);
    });
```

### async/await — Cleaner Syntax (Modern Standard)

```javascript
async function loadData() {
    try {
        const response = await fetch("https://api.example.com/data");

        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }

        const data = await response.json();
        console.log(data);
        return data;
    } catch (error) {
        console.error("Error:", error);
    }
}

loadData();
```

### POST Request with fetch()

```javascript
async function createUser(userData) {
    const response = await fetch("https://api.example.com/users", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(userData)
    });

    const result = await response.json();
    return result;
}

createUser({ name: "Alice", email: "alice@example.com" });
```

### Using a Public API — Complete Example

```javascript
async function searchMovies(query) {
    const apiKey = "your_api_key";
    const url    = `https://api.themoviedb.org/3/search/movie?query=${query}&api_key=${apiKey}`;

    const response = await fetch(url);
    const data     = await response.json();

    const container = document.querySelector("#results");
    container.innerHTML = "";   // clear previous results

    data.results.forEach(movie => {
        const card = document.createElement("div");
        card.classList.add("card");
        card.innerHTML = `
            <h3>${movie.title}</h3>
            <p>${movie.release_date}</p>
            <p>Rating: ${movie.vote_average}/10</p>
        `;
        container.appendChild(card);
    });
}

document.querySelector("#search-btn").addEventListener("click", () => {
    const query = document.querySelector("#search").value;
    if (query) searchMovies(query);
});
```

### Promises vs async/await

```javascript
// Promises (older style)
fetch(url)
    .then(r => r.json())
    .then(data => process(data))
    .catch(err => console.error(err));

// async/await (modern — same thing, cleaner)
try {
    const r    = await fetch(url);
    const data = await r.json();
    process(data);
} catch(err) {
    console.error(err);
}
```

---

## 22. JavaScript — Local Storage

`localStorage` lets you store data in the browser that **persists across sessions**.

```javascript
// Store data (values must be strings)
localStorage.setItem("name",  "Alice");
localStorage.setItem("score", "100");

// Retrieve data
const name  = localStorage.getItem("name");   // "Alice"
const score = localStorage.getItem("score");  // "100" (string!)
const missing = localStorage.getItem("xyz");  // null

// Remove item
localStorage.removeItem("name");

// Clear all localStorage
localStorage.clear();

// Storing objects — must stringify/parse
const user = { name: "Alice", age: 20 };
localStorage.setItem("user", JSON.stringify(user));

const stored = JSON.parse(localStorage.getItem("user"));
console.log(stored.name);   // "Alice"
```

### sessionStorage

Works exactly like `localStorage` but data is cleared when the tab is closed:

```javascript
sessionStorage.setItem("token", "abc123");
sessionStorage.getItem("token");
sessionStorage.removeItem("token");
```

| | localStorage | sessionStorage |
|---|---|---|
| **Persistence** | Until explicitly cleared | Until tab/window closes |
| **Shared across tabs** | Yes | No |
| **Size limit** | ~5–10MB per origin | ~5MB per origin |
| **Accessible via** | JS only (not sent to server) | JS only |

---

## 23. Problem Set 8 — Homepage

The Week 8 problem set asks you to build a personal homepage using HTML, CSS, and JavaScript.

### Requirements

- At least **4 different pages** linked together
- **A `index.html`** as the main page
- Use of **Bootstrap** or custom CSS for styling
- At least one use of JavaScript (interaction)
- Responsive design that works on mobile

### Recommended File Structure

```
homepage/
├── index.html
├── about.html
├── projects.html
├── contact.html
├── styles/
│   └── styles.css
├── scripts/
│   └── main.js
└── images/
    └── profile.jpg
```

### Navigation Template

```html
<nav class="navbar">
    <div class="nav-brand">
        <a href="index.html">My Portfolio</a>
    </div>
    <ul class="nav-links">
        <li><a href="index.html">Home</a></li>
        <li><a href="about.html">About</a></li>
        <li><a href="projects.html">Projects</a></li>
        <li><a href="contact.html">Contact</a></li>
    </ul>
    <button class="hamburger" id="menu-btn">☰</button>
</nav>
```

### Mobile Navigation Toggle (JavaScript)

```javascript
const menuBtn = document.getElementById("menu-btn");
const navLinks = document.querySelector(".nav-links");

menuBtn.addEventListener("click", () => {
    navLinks.classList.toggle("open");
});
```

### Hero Section HTML

```html
<section class="hero">
    <div class="hero-content">
        <h1>Hi, I'm <span class="highlight">Alice</span></h1>
        <p>CS50 student · Aspiring developer · Problem solver</p>
        <a href="projects.html" class="btn">View My Work</a>
        <a href="contact.html" class="btn btn-outline">Contact Me</a>
    </div>
    <div class="hero-image">
        <img src="images/profile.jpg" alt="Profile photo">
    </div>
</section>
```

### Project Cards

```html
<section class="projects">
    <h2>My Projects</h2>
    <div class="project-grid">
        <div class="project-card">
            <img src="images/project1.png" alt="Mario game screenshot">
            <div class="card-content">
                <h3>Mario</h3>
                <p>A CS50 recreation of the classic Mario pyramid puzzle.</p>
                <div class="tags">
                    <span class="tag">C</span>
                    <span class="tag">Algorithms</span>
                </div>
                <a href="#" class="btn">View Code</a>
            </div>
        </div>
    </div>
</section>
```

### Contact Form with JavaScript Validation

```html
<form id="contact-form">
    <div class="form-group">
        <label for="name">Name</label>
        <input type="text" id="name" name="name" required>
    </div>
    <div class="form-group">
        <label for="email">Email</label>
        <input type="email" id="email" name="email" required>
    </div>
    <div class="form-group">
        <label for="message">Message</label>
        <textarea id="message" name="message" rows="5" required></textarea>
    </div>
    <button type="submit" class="btn">Send Message</button>
    <p id="form-status"></p>
</form>
```

```javascript
document.getElementById("contact-form").addEventListener("submit", (e) => {
    e.preventDefault();

    const name    = document.getElementById("name").value.trim();
    const email   = document.getElementById("email").value.trim();
    const message = document.getElementById("message").value.trim();
    const status  = document.getElementById("form-status");

    if (!name || !email || !message) {
        status.textContent = "Please fill in all fields.";
        status.style.color = "red";
        return;
    }

    status.textContent = `Thanks, ${name}! Your message was received.`;
    status.style.color = "green";
    e.target.reset();
});
```

### Complete CSS Reset and Base Styles

```css
/* CSS Reset */
*, *::before, *::after {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

/* Base styles */
:root {
    --primary:    #1a73e8;
    --secondary:  #ea4335;
    --text:       #202124;
    --light:      #f8f9fa;
    --white:      #ffffff;
    --shadow:     0 2px 8px rgba(0,0,0,0.12);
    --radius:     8px;
    --transition: 0.3s ease;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    font-size:   16px;
    line-height: 1.6;
    color:       var(--text);
    background:  var(--white);
}

/* Utility classes */
.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
}

.btn {
    display:         inline-block;
    padding:         12px 24px;
    background:      var(--primary);
    color:           white;
    border:          none;
    border-radius:   var(--radius);
    text-decoration: none;
    font-size:       1rem;
    cursor:          pointer;
    transition:      background var(--transition);
}

.btn:hover {
    background: #1557b0;
}

img {
    max-width: 100%;
    height: auto;
}
```

---

## 24. Quick Reference Cheat Sheet

### HTML Quick Reference

```html
<!-- Document structure -->
<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Title</title><link rel="stylesheet" href="styles.css">
</head><body><!-- content --><script src="script.js" defer></script></body></html>

<!-- Common elements -->
<h1>–<h6>  <p>  <a href="">  <img src="" alt="">
<ul><li>  <ol><li>  <table><tr><th><td>
<div>  <span>  <form action="" method="">
<input type="text/email/password/submit" name="">
<button type="submit/button/reset">
<header><nav><main><section><article><aside><footer>
```

### CSS Quick Reference

```css
/* Selectors */
element  .class  #id  *  a, b  a b  a > b  a + b

/* Box model */
width height  padding margin  border border-radius

/* Flexbox */
display: flex; justify-content: center; align-items: center;
flex-direction: row|column; flex-wrap: wrap; gap: 16px; flex: 1;

/* Grid */
display: grid; grid-template-columns: repeat(3, 1fr);
gap: 16px; grid-column: span 2;

/* Typography */
font-size: 1rem; font-weight: bold; font-family: Arial, sans-serif;
text-align: center; line-height: 1.6; color: #333; text-decoration: none;

/* Common utilities */
display: none|block|flex|grid;  position: relative|absolute|fixed;
top|right|bottom|left: 0;  z-index: 10;  overflow: hidden;
cursor: pointer;  opacity: 0.5;  transition: all 0.3s ease;
border-radius: 8px;  box-shadow: 0 2px 8px rgba(0,0,0,0.12);
```

### JavaScript Quick Reference

```javascript
// Variables
const x = 5;  let y = 10;

// DOM selection
document.querySelector("selector")      // first match
document.querySelectorAll("selector")   // all matches

// DOM manipulation
el.textContent = "text";
el.innerHTML   = "<b>html</b>";
el.classList.add("class");  .remove()  .toggle()
el.style.color = "red";
el.setAttribute("attr", "val");

// Events
el.addEventListener("click", (e) => { e.preventDefault(); });

// fetch
const data = await fetch(url).then(r => r.json());

// Common methods
console.log()  console.error()  console.warn()
JSON.stringify(obj)  JSON.parse(str)
parseInt("42")  parseFloat("3.14")  isNaN(x)
setTimeout(() => {}, 1000)   setInterval(() => {}, 1000)
```

### HTTP Quick Reference

```
GET    — retrieve a resource         200 OK
POST   — create / submit data        201 Created
PUT    — replace a resource          301 Moved Permanently
PATCH  — partially update            302 Found (redirect)
DELETE — remove a resource           304 Not Modified

                                     400 Bad Request
                                     401 Unauthorized
                                     403 Forbidden
                                     404 Not Found
                                     500 Internal Server Error
```

### Key Rules for Week 8

| Rule | Why It Matters |
|---|---|
| Always include `<!DOCTYPE html>` | Prevents browser quirks mode |
| Always include viewport meta tag | Required for mobile responsiveness |
| Always include `alt` on images | Accessibility and SEO |
| Put `<script>` at bottom or use `defer` | Ensures HTML is parsed before JS runs |
| Use `===` not `==` in JavaScript | Avoids type coercion surprises |
| Always `preventDefault()` on form submit | Stops page reload when handling with JS |
| Use `const` by default, `let` when changing | Prevents accidental reassignment |
| Use `box-sizing: border-box` universally | Makes sizing intuitive |
| Use CSS classes not inline styles | Keeps style in CSS, logic in JS |
| Check `if (!response.ok)` after fetch | HTTP errors don't throw — you must check |

---

*CS50 Week 8 Notes · Harvard University · David J. Malan*
