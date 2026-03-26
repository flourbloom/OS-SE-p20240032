/* file_creator_sys.c */
#include <fcntl.h>  // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h> // write(), close()
#include <string.h> // strlen()

int main()
{
    // YOUR CODE HERE
    // 1. Open/create "output.txt" using open()
    int dst = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst < 0)
    {
        write(2, "Error opening file", 18);
        return 1;
    }
    // 2. Write "Hello from Operating Systems class!\n" using write()
    write(dst, "Hello from Operating Systems class!\n", 37);
    // 3. Close the file using close()
    close(dst);
    // 4. Print "File created successfully!\n" to the terminal using write()
    write(1, "File created successfully!\n", 28);

    return 0;
}

// Use open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644) to create the file.
// Use write(fd, text, length) to write to the file.
// Use write(1, msg, length) to print the confirmation to the terminal (fd 1 = stdout).
// Use close(fd) to close the file.