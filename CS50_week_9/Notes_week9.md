# CS50 — Week 9: Flask

**Harvard University** · David J. Malan  
**Topic:** Building dynamic web applications with Python and Flask — routing, Jinja2 templates, forms, sessions, databases, and APIs.

---

## Table of Contents

1. [Static vs Dynamic Web Applications](#1-static-vs-dynamic-web-applications)
2. [Flask — What and Why](#2-flask--what-and-why)
3. [Installation and Project Setup](#3-installation-and-project-setup)
4. [Routes and URL Rules](#4-routes-and-url-rules)
5. [The Request Object](#5-the-request-object)
6. [Return Values and Responses](#6-return-values-and-responses)
7. [Jinja2 — Templates](#7-jinja2--templates)
8. [Jinja2 — Template Syntax Deep Dive](#8-jinja2--template-syntax-deep-dive)
9. [Template Inheritance — Layout System](#9-template-inheritance--layout-system)
10. [Forms — GET Requests](#10-forms--get-requests)
11. [Forms — POST Requests](#11-forms--post-requests)
12. [Redirect and url_for](#12-redirect-and-url_for)
13. [Sessions](#13-sessions)
14. [Cookies](#14-cookies)
15. [Databases with SQLite](#15-databases-with-sqlite)
16. [Flask with the CS50 Library](#16-flask-with-the-cs50-library)
17. [JSON APIs with Flask](#17-json-apis-with-flask)
18. [Error Handling](#18-error-handling)
19. [Flask Configuration and Environment Variables](#19-flask-configuration-and-environment-variables)
20. [Problem Set 9 — Finance](#20-problem-set-9--finance)
21. [Quick Reference Cheat Sheet](#21-quick-reference-cheat-sheet)

---

## 1. Static vs Dynamic Web Applications

### Static Websites

In Week 8, every file you served was pre-written:

```
Browser requests: /index.html
Server responds:  sends the exact file — same content every time
```

```
Client                 File Server
  │──── GET /index.html ────────────►│
  │◄─── index.html (always identical)│
```

### Dynamic Web Applications

With Flask, the server **runs Python code** and builds a response on the fly:

```
Client                         Flask Server (Python)
  │                                    │
  │─── GET /profile?user=alice ───────►│
  │                               queries database
  │                               runs Python logic
  │                               builds HTML for alice
  │◄─── HTML tailored for alice ──────│
```

The response **changes** based on:
- Who is logged in
- What's in the database
- Query parameters in the URL
- Time, random values, external API calls

### The Shift from Week 8 to Week 9

| Week 8 | Week 9 |
|---|---|
| HTML, CSS, JavaScript | Python (Flask) + HTML templates |
| Static files | Dynamic, server-generated pages |
| Client-side only | Server-side logic |
| No persistent data | SQLite database |
| Calls external APIs | Flask can BE the API |

---

## 2. Flask — What and Why

**Flask** is a **micro web framework** for Python. "Micro" means it provides the essentials — routing, request handling, templates — without forcing structure or bundling things you may not need.

```
Flask sits between the browser and your Python code:

Browser ──── HTTP request ────► Flask ──► your Python function
Browser ◄─── HTTP response ───  Flask ◄── return value from your function
```

### Flask vs Django

| | Flask | Django |
|---|---|---|
| **Size** | Micro — minimal, unopinionated | Full framework — batteries included |
| **Learning curve** | Gentle | Steeper |
| **Flexibility** | High — choose your own tools | Opinionated — Django's way or the highway |
| **Best for** | APIs, small-medium apps, learning | Large apps, CMS, enterprise patterns |
| **CS50 uses** | ✅ Flask | ✗ |

### What Flask Gives You

- **Routing** — map URLs to Python functions
- **Request handling** — read query params, form data, JSON bodies, files
- **Response building** — return HTML, JSON, redirects, files
- **Template engine** — Jinja2 for dynamic HTML
- **Development server** — run locally with one command
- **Session management** — per-user data across multiple requests
- **Extension ecosystem** — Flask-Login, Flask-SQLAlchemy, Flask-CORS, etc.

---

## 3. Installation and Project Setup

### Installing Flask

```bash
pip install Flask

# Or install the CS50 library which includes Flask
pip install cs50
```

### Minimal Flask App

```python
# app.py
from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"
```

That's it — a complete working web application in 5 lines.

### Running Flask

```bash
# Method 1 — flask CLI (recommended)
flask run

# With debug mode (auto-reloads on file save, shows detailed error pages)
flask --debug run

# Specify a different port
flask run --port 8080

# Method 2 — run the file directly
# Add this to app.py first:
# if __name__ == "__main__":
#     app.run(debug=True)
python app.py
```

When you run `flask run`, Flask automatically looks for a file named `app.py` or `wsgi.py`.

### Debug Mode

```python
# In debug mode:
# 1. Server restarts automatically when you save a file
# 2. Detailed error pages with stack traces shown in browser
# 3. Interactive debugger in browser (Werkzeug debugger)
# NEVER run debug mode in production — it exposes your code!
```

### Environment Variables

```bash
# Tell Flask which file is your app (if not app.py)
export FLASK_APP=main.py          # macOS / Linux
set FLASK_APP=main.py             # Windows (cmd)
$env:FLASK_APP = "main.py"        # Windows (PowerShell)

# Enable debug mode via environment
export FLASK_DEBUG=1
```

### Recommended Project Structure (CS50 Finance style)

```
project/
├── app.py                  ← main Flask application
├── helpers.py              ← helper functions (login_required, apology, etc.)
├── finance.db              ← SQLite database file
├── requirements.txt        ← list of pip dependencies
├── .env                    ← secret keys (NEVER commit to git)
├── .gitignore
├── static/
│   ├── styles.css
│   ├── script.js
│   └── favicon.ico
└── templates/
    ├── layout.html         ← base template (nav + footer)
    ├── index.html
    ├── login.html
    ├── register.html
    ├── buy.html
    ├── sell.html
    ├── history.html
    └── apology.html
```

Flask automatically looks for templates in `templates/` and static files in `static/` — no configuration needed.

---

## 4. Routes and URL Rules

A **route** maps a URL path to a Python function. The function is called a **view function**.

### Basic Routes

```python
from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return "<h1>Home Page</h1>"

@app.route("/about")
def about():
    return "<h1>About Us</h1>"

@app.route("/contact")
def contact():
    return "<p>Email us at hello@example.com</p>"
```

The `@app.route("/")` decorator tells Flask: "when a request comes in for `/`, call `index()`."

```
Decorator syntax:
@app.route("/path")   ← registers this function as a route handler
def function_name():  ← Flask calls this when /path is requested
    return "response"
```

### Dynamic URL Parameters

```python
# <variable> captures part of the URL as a parameter
@app.route("/user/<username>")
def profile(username):
    return f"<h1>Profile: {username}</h1>"

# /user/alice  →  username = "alice"
# /user/bob    →  username = "bob"

# Type converters — guarantee the right type
@app.route("/post/<int:post_id>")
def post(post_id):
    return f"Post number {post_id}"    # post_id is an int, not a string

@app.route("/price/<float:amount>")
def price(amount):
    return f"${amount:.2f}"
```

### Type Converters

| Converter | Description | Example URL |
|---|---|---|
| `string` | Default — any text without a slash | `/user/<string:name>` |
| `int` | Positive integers only | `/post/<int:id>` |
| `float` | Positive floating-point numbers | `/price/<float:amount>` |
| `path` | Like string but accepts slashes | `/files/<path:filepath>` |
| `uuid` | UUID strings | `/item/<uuid:item_id>` |

If the URL doesn't match the type (e.g., `/post/hello` for an `int` route), Flask automatically returns 404.

### Specifying HTTP Methods

By default, routes only accept `GET`. Add `methods` to accept others:

```python
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        # handle form submission
        return "Logging in..."
    else:
        # show the login form
        return render_template("login.html")
```

### Trailing Slash Rules

```python
@app.route("/projects/")    # canonical URL with trailing slash
def projects():
    return "Projects"
# /projects  → Flask redirects to /projects/ automatically

@app.route("/about")        # no trailing slash
def about():
    return "About"
# /about    → serves the page
# /about/   → 404 Not Found
```

---

## 5. The Request Object

Flask's `request` object contains everything the browser sent — method, URL, form data, headers, cookies.

```python
from flask import Flask, request

app = Flask(__name__)
```

### Request Attributes

```python
@app.route("/info")
def info():
    request.method        # "GET", "POST", "PUT", etc.
    request.url           # full URL: "http://localhost:5000/info?name=alice"
    request.path          # just the path: "/info"
    request.host          # "localhost:5000"
    request.remote_addr   # client IP address: "127.0.0.1"
    request.headers       # dict-like object of HTTP headers
    request.content_type  # "application/json", "multipart/form-data", etc.
    request.is_json       # True if Content-Type is application/json
```

### Query String Parameters — GET

```
URL: /search?q=cats&page=2
               │        │
               │        └── page = "2"
               └─────────── q    = "cats"
```

```python
@app.route("/search")
def search():
    q    = request.args.get("q")        # "cats"
    page = request.args.get("page", 1)  # "2", or default 1 if not in URL

    # .get() returns None if key absent — SAFE
    # Direct dict access raises KeyError if key absent — UNSAFE
    q = request.args["q"]   # ← KeyError if ?q= missing, avoid this
```

### Form Data — POST

```python
@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username")   # None if not submitted
    password = request.form.get("password")
    remember = request.form.get("remember")   # None if checkbox unchecked
```

### JSON Body

```python
@app.route("/api/data", methods=["POST"])
def receive_data():
    data = request.get_json()       # parses JSON body → Python dict
    if not data:
        return "No data", 400
    name = data.get("name")
    age  = data.get("age")
```

### File Uploads

```python
@app.route("/upload", methods=["POST"])
def upload():
    file = request.files.get("photo")
    if file and file.filename:
        file.save(f"uploads/{file.filename}")
        return "Uploaded!"
```

### Summary: request.args vs request.form

| | `request.args` | `request.form` |
|---|---|---|
| **Used for** | GET query string parameters | POST form body data |
| **Where data lives** | URL: `/search?q=cats` | Request body (hidden from URL) |
| **When to use** | Search, filters, pagination | Login, registration, form submissions |
| **Safe with `.get()`** | ✅ | ✅ |

---

## 6. Return Values and Responses

A Flask view function can return several different types of responses.

### Return a String or HTML

```python
@app.route("/")
def index():
    return "Hello, World!"                    # plain text

@app.route("/html")
def html():
    return "<h1>Hello</h1><p>World</p>"      # inline HTML
```

### Return with a Status Code

```python
@app.route("/")
def index():
    return "OK", 200              # 200 is the default — usually omit

@app.route("/created")
def created():
    return "Resource created!", 201

@app.route("/broken")
def broken():
    return "Something went wrong", 500
```

### Return a Rendered Template

```python
from flask import render_template

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/profile/<name>")
def profile(name):
    return render_template("profile.html", username=name, age=20)
    # keyword arguments become variables available inside the template
```

### Return JSON

```python
from flask import jsonify

@app.route("/api/user")
def get_user():
    return jsonify({
        "name":  "Alice",
        "email": "alice@example.com",
        "age":   20
    })
    # automatically sets Content-Type: application/json
    # works with dicts AND lists
```

### Return a Redirect

```python
from flask import redirect, url_for

@app.route("/old-page")
def old():
    return redirect("/new-page")                 # redirect to URL string

@app.route("/home")
def home():
    return redirect(url_for("index"))            # redirect using function name
```

### make_response — Custom Headers and Cookies

```python
from flask import make_response

@app.route("/custom")
def custom():
    response = make_response("<h1>Custom Response</h1>")
    response.status_code = 200
    response.headers["X-Custom-Header"] = "value"
    response.set_cookie("username", "alice")
    return response
```

---

## 7. Jinja2 — Templates

**Jinja2** is Flask's built-in template engine. It lets you write HTML files with placeholders that Flask fills in dynamically with Python values.

### Why Templates?

Without templates, building HTML in Python is painful:

```python
# ❌ Without templates — messy, unreadable, unmaintainable
@app.route("/user/<name>")
def user(name):
    return f"""
    <!DOCTYPE html><html><head><title>{name}</title></head>
    <body><h1>Hello, {name}!</h1><p>Welcome back.</p></body></html>
    """
```

With templates, HTML stays in `.html` files:

```python
# ✅ With templates — clean separation of Python and HTML
@app.route("/user/<name>")
def user(name):
    return render_template("user.html", name=name)
```

```html
<!-- templates/user.html -->
<!DOCTYPE html>
<html>
<head><title>{{ name }}</title></head>
<body>
    <h1>Hello, {{ name }}!</h1>
    <p>Welcome back.</p>
</body>
</html>
```

### render_template

```python
from flask import render_template

render_template("page.html")                           # no variables
render_template("page.html", name="Alice")             # one variable
render_template("page.html", name="Alice", age=20)     # multiple variables
render_template("page.html", user=user_dict)           # pass a dict
render_template("page.html", items=my_list)            # pass a list
render_template("page.html", **context)                # unpack a dict
```

### How Variables Are Passed

```python
# Python (app.py)
return render_template("index.html", title="Home", score=42, items=["a","b"])
```

```html
<!-- Jinja2 template (index.html) -->
<h1>{{ title }}</h1>        <!-- "Home" -->
<p>Score: {{ score }}</p>   <!-- 42 -->
<li>{{ items[0] }}</li>     <!-- "a" -->
```

### Auto-Escaping — Security Built In

Jinja2 automatically **escapes HTML characters** in `{{ }}` to prevent XSS attacks:

```python
# If name = "<script>alert('hacked')</script>"
render_template("page.html", name=name)
```

```html
<!-- Rendered safely — the tag is escaped, not executed: -->
Hello, &lt;script&gt;alert('hacked')&lt;/script&gt;!
```

To intentionally render raw HTML (only when you trust the source):

```html
{{ raw_html_content | safe }}
```

---

## 8. Jinja2 — Template Syntax Deep Dive

### The Three Delimiter Types

```
{{ ... }}   Expression  — evaluate and output the result
{% ... %}   Statement   — control flow: if, for, block, extends...
{# ... #}   Comment     — not rendered in the HTML output at all
```

### Expressions — `{{ }}`

```html
<!-- Variables -->
<h1>{{ title }}</h1>
<p>{{ user.name }}</p>          <!-- access dict key or object attribute -->
<p>{{ items[0] }}</p>           <!-- list index -->

<!-- Arithmetic inside expressions -->
<p>{{ 5 + 3 }}</p>              <!-- 8 -->
<p>{{ price * 1.1 }}</p>        <!-- price + 10% -->

<!-- Filters — transform values with | -->
<p>{{ name | upper }}</p>       <!-- ALICE -->
<p>{{ name | length }}</p>      <!-- 5 -->

<!-- Inline conditional -->
<p>{{ "Even" if num % 2 == 0 else "Odd" }}</p>

<!-- Default value if variable is None or undefined -->
<p>{{ name | default("Guest") }}</p>
```

### Jinja2 Filters

Filters transform values using the pipe `|` operator.

| Filter | Example | Output |
|---|---|---|
| `upper` | `{{ "hello" \| upper }}` | `HELLO` |
| `lower` | `{{ "HELLO" \| lower }}` | `hello` |
| `title` | `{{ "hello world" \| title }}` | `Hello World` |
| `length` | `{{ [1,2,3] \| length }}` | `3` |
| `default` | `{{ none \| default("N/A") }}` | `N/A` |
| `int` | `{{ "42" \| int }}` | `42` |
| `float` | `{{ "3.14" \| float }}` | `3.14` |
| `round(n)` | `{{ 3.14159 \| round(2) }}` | `3.14` |
| `abs` | `{{ -5 \| abs }}` | `5` |
| `safe` | `{{ html \| safe }}` | raw HTML rendered |
| `join(sep)` | `{{ list \| join(", ") }}` | `"a, b, c"` |
| `first` | `{{ list \| first }}` | first item |
| `last` | `{{ list \| last }}` | last item |
| `sort` | `{{ list \| sort }}` | sorted list |
| `reverse` | `{{ list \| reverse }}` | reversed list |
| `truncate(n)` | `{{ text \| truncate(50) }}` | first 50 chars... |

### If Statements — `{% if %}`

```html
{% if user %}
    <p>Welcome, {{ user.name }}!</p>
{% elif guest %}
    <p>Welcome, guest!</p>
{% else %}
    <p>Please log in.</p>
{% endif %}


<!-- Checking for empty list -->
{% if items %}
    <p>{{ items | length }} items found.</p>
{% else %}
    <p>No items found.</p>
{% endif %}
```

### For Loops — `{% for %}`

```html
<!-- Basic loop -->
<ul>
{% for item in items %}
    <li>{{ item }}</li>
{% endfor %}
</ul>

<!-- Loop with index (1-based) -->
<ol>
{% for item in items %}
    <li>{{ loop.index }}. {{ item }}</li>
{% endfor %}
</ol>

<!-- Loop over a dict -->
{% for key, value in user.items() %}
    <p>{{ key }}: {{ value }}</p>
{% endfor %}

<!-- Fallback for empty list — {% else %} on a for loop -->
{% for item in items %}
    <li>{{ item }}</li>
{% else %}
    <li>No items to show.</li>
{% endfor %}
```

### Loop Variables

Inside any `{% for %}` block, Jinja2 provides a special `loop` object:

| Variable | Description |
|---|---|
| `loop.index` | Current iteration (1-indexed) |
| `loop.index0` | Current iteration (0-indexed) |
| `loop.first` | `True` on the first iteration |
| `loop.last` | `True` on the last iteration |
| `loop.length` | Total number of items in the iterable |
| `loop.revindex` | Iterations remaining from the end (1-indexed) |

```html
{% for row in rows %}
    <tr class="{{ 'odd' if loop.index % 2 == 1 else 'even' }}">
        {% if loop.first %}<th>{{ row }}</th>{% else %}<td>{{ row }}</td>{% endif %}
    </tr>
{% endfor %}
```

### Setting Variables — `{% set %}`

```html
{% set total = items | length %}
{% set greeting = "Good morning" if hour < 12 else "Good evening" %}

<p>{{ greeting }}, you have {{ total }} items.</p>
```

### Comments — `{# #}`

```html
{# This is a Jinja2 comment — does not appear in the rendered HTML #}

{#
    Multi-line comment
    Useful for temporarily disabling template code
#}
```

---

## 9. Template Inheritance — Layout System

Template inheritance lets you define a **single base layout** and have every page extend it — nav and footer live in one place only.

### The Problem Without Inheritance

```
Without inheritance:
├── index.html    ← full <html>, duplicated <nav>, duplicated <footer>
├── about.html    ← full <html>, duplicated <nav>, duplicated <footer>
├── contact.html  ← full <html>, duplicated <nav>, duplicated <footer>

Change the nav → must update every single file.
```

### Solution: Base Template + Child Templates

```
With inheritance:
├── layout.html    ← <html>, <nav>, <footer> live HERE only
├── index.html     ← extends layout, fills in content block
├── about.html     ← extends layout, fills in content block
└── contact.html   ← extends layout, fills in content block

Change the nav → update layout.html only. Done.
```

### layout.html — The Base Template

```html
<!-- templates/layout.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewp
