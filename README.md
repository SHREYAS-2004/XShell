# Custom Terminal (XShell)

## Functionalities

This project implements a custom terminal (shell) in C with the following features:

- **Colored Prompt:** Displays a colored prompt showing the username, hostname, and current working directory.
- **Command Input:** Reads user input in raw mode, supporting basic line editing (backspace).
- **Custom Commands:**
  - `cd [dir]` – Change the current directory. If no directory is given, goes to the home directory. Supports `cd ..` for parent directory.
  - `ls` – Lists files in the current directory.
  - `echo [args...]` – Prints the given arguments to the terminal.
  - `pwd` – Prints the current working directory.
  - `whoami` – Prints the current user's username.
  - `exit` – Exits the shell.
  - `mkdir` - Creates a directory.
  - `rmdir` - Removes an empty directory.
- **Unknown Command Handling:** Prints an error message for unrecognized commands.

## Compatibility:

This project uses - `termios` - for terminal control and works on all Unix and Unix-like systems, including macOS. **It does not support Windows.**

## How to Clone

Clone the repository using:

```sh
git clone https://github.com/SHREYAS-2004/XShell.git
cd XShell
```

## How to Run

1. **Build the project** (requires GCC):

   ```sh
   chmod +x run.sh
   ./run.sh
   ```

2. **Run the shell:**

   ```sh
   ./XShell
   ```

You will see a colored prompt. Enter commands as described above.

---
