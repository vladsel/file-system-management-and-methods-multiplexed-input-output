#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SIZEBUF (512)
#define CHMOD (0644)

int funcCopy(const char* filename1, const char* filename2, ssize_t* sizeWroteDownPionter) {
	int file1;
	int file2;
	ssize_t readSize;
	ssize_t sizeWroteDown = 0;
	char buf[SIZEBUF];

	file1 = open(filename1, O_RDONLY);
	if (file1 == -1)
	{
		return -1;
	}

	file2 = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, CHMOD);
	if (file2 == -1)
	{
		close(file1);
		return -2;
	}

	while ((readSize = read(file1, buf, SIZEBUF)) > 0)
	{
		sizeWroteDown += readSize;

		for (ssize_t i = 0; i < readSize; i++)
		{
			if (buf[i] >= 'a' && buf[i] <= 'z')
			{
				buf[i] += 'A' - 'a';
			}
		}

		if (write(file2, buf, readSize) != readSize)
		{
			close(file1);
			close(file2);
			*sizeWroteDownPionter = sizeWroteDown;
			return -3;
		}
	}

	close(file1);
	close(file2);
	*sizeWroteDownPionter = sizeWroteDown;

	return (readSize == -1) ? -4 : 0;
}

int main(int argc, char** argv, char** envp)
{
	if (argc < 3)
	{
		printf("Two arguments are required");
		exit(1);
	}

	ssize_t sizeWroteDown = 0;
	int result = funcCopy(argv[1], argv[2], &sizeWroteDown);

	switch (result)
	{
	case 0:
		printf("Size of wrote down bytes = %li\n", sizeWroteDown);
		exit(0);
	case -1:
		printf("File1 opening error\n");
		break;
	case -2:
		printf("File2 opening error\n");
		break;
	case -3:
		printf("Writing error\n");
		break;
	case -4:
		printf("Last reading error\n");
		break;
	default:
		break;
	}

	printf("%s\n", strerror(errno));
	exit(1);
}
