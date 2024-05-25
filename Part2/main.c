#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("\ndeveloper: String identifier missing\n");
        return(1);
    }
    
    char buf[SIZE] = {};
    ssize_t readBytes = -1, retVal = -1;
    
    struct timeval timeout;
    timeout.tv_usec = 0;
    timeout.tv_sec = 0;
    
    fd_set inputs, fdsTest;
    FD_ZERO(&inputs);
    FD_SET(STDIN_FILENO, &inputs);
    
    while (1) {
        
        fdsTest = inputs;
        timeout.tv_sec = 5;
        
        retVal = select(1, &fdsTest, NULL, NULL, &timeout);
        
        if (retVal == 0)
            dprintf(STDERR_FILENO, "Timeout expired --> %s\n", argv[1]);
        else if (retVal < 0) {
            dprintf(STDERR_FILENO, "\ndeveloper: Select error\n");
            dprintf(STDERR_FILENO, "strerror: %s\n", strerror(errno));
            return 1;
        }
        else {
            readBytes = read(STDIN_FILENO, buf, SIZE);
            if (readBytes > 0) {
                buf[readBytes - 1] = ' ';
                strcat(buf, "--> ");
                strcat(buf, argv[1]);
                strcat(buf, "\n");
                readBytes += sizeof("--> ") + sizeof(argv[1]) + sizeof("\n");
                buf[readBytes] = '\0';
                
                if (write(STDOUT_FILENO, buf, readBytes) != readBytes) {
                    dprintf(STDERR_FILENO, "\ndeveloper: Writing error\n");
                    dprintf(STDERR_FILENO, "strerror: %s\n", strerror(errno));
                    return 1;
                }
                memset(buf, 0, sizeof(buf));
            }
            else {
                dprintf(STDERR_FILENO, "\ndeveloper: Reading error\n");
                dprintf(STDERR_FILENO, "strerror: %s\n", strerror(errno));
                return 1;
            }
        }
    }
    
    return 0;
}
