# 🐙 Git & GitHub — Complete Notes

> A clean reference guide for everyday Git workflows, from setup to push.

---

## ⚙️ Initial Setup (One-Time Global Config)

```bash
git config --global user.name "AS"
git config --global user.email "aryansuryasgowda@gmail.com"
```

> 🌍 These settings apply **globally** across all repositories on your machine.

```bash
git config --list       # 📋 View all current config settings
git --version           # 🔍 Check installed Git version
```

---

## 📥 Cloning a Repository

```bash
git clone "https://github.com/username/repo.git"
```

> 📦 Downloads the entire repository (all files + history) to your local machine.

---

## 🧭 Navigation (Terminal Basics)

```bash
cd folder-name    # ➡️  Move into a folder
cd ..             # ⬅️  Go back one level
ls                # 📂 List all files and folders in current directory
```

---

## 📊 Checking Status

```bash
git status
```

> 🔎 Shows what's changed, what's staged, and whether your local repo matches the remote (GitHub).

---

## 📝 The Core Workflow — Stage → Commit → Push

### 1️⃣ Stage Files

```bash
git add README.md       # Add a specific file
git add .               # Add ALL changed files at once
```

> ✅ Staging tells Git: *"include these changes in the next commit."*

### 2️⃣ Commit Changes

```bash
git commit -m "Your descriptive message here"
```

> 💾 A commit saves a **snapshot** of your staged changes with a message explaining what you did.

### 3️⃣ Push to GitHub

```bash
git push origin main        # Push to remote
git push                    # Shorthand after -u is set
```

> 🚀 Sends your committed changes to the remote repository on GitHub.

---

## 🆕 Starting a Brand New Repository

Use this flow when creating a repo from scratch locally and linking it to GitHub:

```bash
git init                                                              # 🏗️  Initialize a new local Git repo
git add README.md                                                     # Stage your file(s)
git commit -m "first commit"                                          # Make your first commit
git remote add origin https://github.com/aryansuryas/ruff.git        # 🔗 Link to remote GitHub repo
git remote -v                                                         # 👁️  Verify the remote URL
git branch -M main                                                    # ✏️  Rename branch to 'main'
git push -u origin main                                               # 🚀 Push & set upstream tracking
```

> ⚡ After `git push -u origin main`, future pushes just need `git push`.

---

## 🌿 Branching & Merging

```bash
git branch                      # 📋 List all local branches (current branch has *)
git branch -m main              # ✏️  Rename current branch to 'main'
git checkout -b as              # 🌱 Create AND switch to a new branch called 'as'
git checkout {branch_name}      # 🔀 Switch to an existing branch
git diff {branch_name}          # 🔍 Compare differences between current and another branch
git pull                        # ⬇️  Fetch + merge latest changes from remote
```

### 🧠 How Branching Works

```
main ──────────────────────────────────▶
         │
         └──▶ as (your new branch)
               ↓ make changes
               ↓ git add . → git commit
               ↓
         merge back into main
```

### 🔄 Typical Branch Workflow

```bash
git checkout -b as              # 1️⃣ Create & switch to new branch
# ... make your changes ...
git add .                       # 2️⃣ Stage changes
git commit -m "feature done"    # 3️⃣ Commit on your branch
git checkout main               # 4️⃣ Switch back to main
git pull origin main            # 5️⃣ Get latest changes from remote
git merge as                    # 6️⃣ Merge your branch into main
git push origin main            # 7️⃣ Push merged code to GitHub
```

> 💡 **Rule of thumb:** Always `git pull` on `main` before starting new work on a branch — keeps you up to date and avoids merge conflicts!

---

## 🗺️ Overall Workflow at a Glance

```
Make changes to files
        ↓
   git add .
        ↓
git commit -m "message"
        ↓
  git push origin main
        ↓
   ✅ Changes live on GitHub!
```

---

## 📌 Master Cheat Sheet

| Command | What it does |
|---|---|
| `git config --global user.name "Name"` | 🌍 Set global username |
| `git config --global user.email "email"` | 🌍 Set global email |
| `git config --list` | 📋 View all config |
| `git --version` | 🔍 Check Git version |
| `git clone <url>` | 📥 Clone a repo |
| `git status` | 📊 Check repo status |
| `git add .` | ✅ Stage all changes |
| `git add <file>` | ✅ Stage a specific file |
| `git commit -m "msg"` | 💾 Commit with message |
| `git push origin main` | 🚀 Push to GitHub |
| `git push` | 🚀 Push (after upstream set) |
| `git init` | 🏗️ Init new local repo |
| `git remote add origin <url>` | 🔗 Link to GitHub |
| `git remote -v` | 👁️ Verify remote URL |
| `git pull` | ⬇️ Pull latest from remote |
| `git branch` | 🌿 List all branches |
| `git branch -m main` | ✏️ Rename branch to main |
| `git branch -M main` | ✏️ Force rename to main |
| `git checkout -b <name>` | 🌱 Create + switch to new branch |
| `git checkout <branch>` | 🔀 Switch to existing branch |
| `git merge <branch>` | 🔀 Merge branch into current |
| `git diff <branch>` | 🔍 Compare branches |
| `git push -u origin main` | 🚀 Push & set upstream |

---

> 💡 **Tip:** Always run `git status` before and after staging to make sure you're committing exactly what you intend!
