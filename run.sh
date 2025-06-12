#!/bin/sh

echo "Compiling XShell..."

gcc -o XShell \
    main.c exec.c terminal.c utils.c \
    commands/cd.c commands/ls.c commands/pwd.c commands/user.c \
    commands/mkdir.c commands/echo.c commands/rmdir.c


if [ $? -eq 0 ]; then
    echo "✅ Build successfull. Run it with ./XShell"
else
    echo "❌ Build failed."
fi 