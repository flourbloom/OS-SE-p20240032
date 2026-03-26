/* file_reader_sys.c */
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char buffer[256];
    ssize_t bytesRead;

    // YOUR CODE HERE
    // 1. Open "output.txt" for reading using open()
    int file = open("output.txt", O_RDONLY);
    if (file < 0)
    {
        write(2, "Error opening file", 18);
        return 1;
    }
    // 2. Read content into buffer using read() in a loop
    while ((bytesRead = read(file, buffer, sizeof(buffer))) > 0)
    {
        // 3. Write the content to the terminal (fd 1) using write()
        write(1, buffer, bytesRead);
    }
    // 4. Close the file using close()
    close(file);
    return 0;
}
// Use open("output.txt", O_RDONLY) to open the file for reading.
// Use read(fd, buffer, sizeof(buffer)) to read data into a buffer. It returns the number of bytes read.
// Use write(1, buffer, bytesRead) to print the data to the terminal.
// Loop until read() returns 0 (end of file).