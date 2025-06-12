# Custom Terminal (MyShell)

## Functionalities

This project implements a simple custom terminal (shell) in C with the following features:

- **Colored Prompt:** Displays a colored prompt showing the username, hostname, and current working directory.
- **Command Input:** Reads user input in raw mode, supporting basic line editing (backspace).
- **Built-in Commands:**
  - `cd [dir]` – Change the current directory. If no directory is given, goes to the home directory. Supports `cd ..` for parent directory.
  - `ls` – Lists files in the current directory.
  - `echo [args...]` – Prints the given arguments to the terminal.
  - `pwd` – Prints the current working directory.
  - `whoami` – Prints the current user's username.
  - `exit` – Exits the shell.
- **Unknown Command Handling:** Prints an error message for unrecognized commands.

## How to Clone

Clone the repository using:

```sh
git clone https://github.com/SHREYAS-2004/XShell.git
cd XShell
```

## How to Run

1. **Build the project** (requires GCC):

   ```sh
   gcc -o myshell main.c terminal.c utils.c exec.c commands.c
   ```

2. **Run the shell:**

   ```sh
   ./myshell
   ```

You will see a colored prompt. Enter commands as described above.

---
