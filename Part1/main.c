#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 64

void lastError(int *fh1, int *fh2, const char *lastErr) {
    printf("%s", lastErr);
    close(*fh1);
    close(*fh2);
    printf("strerror: %s, errno = %d\n", strerror(errno), errno);
    exit(1);
}

int main(int argc, char **argv) {
    
	int fh1 = -1, fh2 = -1;
	char buf[SIZE + 1] = { 0 };
	ssize_t readBytes = -1, writenBytes = -1, countedBytes = 0;

	if (argv[1] == NULL || argv[2] == NULL) {
        printf("developer: No filenames were passed as a command line argument\n");
        exit(1);
    }
	fh1 = open(argv[1], O_RDONLY);
	fh2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fh1 == -1 || fh2 == -1)
        lastError(&fh1, &fh2, "developer: Error opening files: fh1 = -1 or fh2 = -1\n");

	while ((readBytes = read(fh1, buf, SIZE)) > 0) {
		buf[readBytes] = '\0'; //Null-terminator
		
        for (size_t i = 0; i < readBytes; i++)
			if (buf[i] >= 'a' && buf[i] <= 'z')
				buf[i] += 'A' - 'a';
        
        writenBytes = write(fh2, buf, readBytes);
        countedBytes += writenBytes;
        
        if (writenBytes != readBytes)
            lastError(&fh1, &fh2, "developer: Error writing file: writenBytes != readBytes\n");
        
        memset(buf, 0, sizeof(buf));
	}
     
    if (readBytes < 0)
        lastError(&fh1, &fh2, "developer: Error reading file: readBytes < 0\n");
    
    close(fh1);
	close(fh2);
    
    printf("\nThe size of overwritten bytes from %s to %s is %ld\n", argv[1], argv[2], countedBytes);

	return 0;
}
