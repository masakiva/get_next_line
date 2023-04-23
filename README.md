# Get Next Line

`get_next_line` is a function that reads a file descriptor (`fd`) line by line, until the end of the file or an error occurs. It can be used to read from a file, the standard input (`STDIN_FILENO`), or a network socket.
It is the second project I made in 42 school.
This repository contains the source code for `get_next_line`. The code is written in C and should work on any platform that supports the standard C library.

### Example of main function

To use `get_next_line` in your program, you need to include the `get_next_line.h` header file and link your program with the `get_next_line` source code. Here's an example program that reads lines from a file:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file %s\n", argv[1]);
        return (1);
    }
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

In this example, `get_next_line` is called in a loop to read lines from the file descriptor `fd`. The function returns `1` when a line is read successfully, `0` when the end of the file is reached, and `-1` when an error occurs.

The second parameter of `get_next_line` is a pointer to a `char*` variable that will be set to the read line. The line is allocated on the heap, so it should be freed by the caller when it's no longer needed.

### Compilation
You have to set the BUFFER_SIZE variable at compilation time. It can be any integer.

```bash
clang -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c
```

### How it works

`get_next_line` reads a file descriptor line by line using a static buffer to hold the read data. When called for the first time, the function reads data from the file descriptor into the buffer until it finds a newline character (`'\n'`) or reaches the end of the buffer. If a newline character is found, the function copies the data up to the newline character into a new buffer and returns `1`. If the end of the buffer is reached, the function allocates a new buffer twice the size of the previous buffer, copies the data from the previous buffer into the new buffer, and reads more data from the file descriptor into the new buffer. The function repeats this process until a newline character is found or the end of the file is reached.

If the end of the file is reached, the function returns `0`. If an error occurs (e.g., the file descriptor is invalid), the function returns `-1`.

### Bonus part
The function in the `bonus_srcs` directory is the same as in the `srcs` directory, except that it can handle multiple file descriptors at the same time. This is made by using a linked list of file descriptor structures, each containing a buffer and a pointer to the next structure in the list.
