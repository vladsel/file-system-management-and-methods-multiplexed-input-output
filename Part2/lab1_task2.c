#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SIZEBUF (1024)

int main(int argc, char** argv, char** envp)
{
	if (argc < 2)
	{
		printf("One argument is required");
		exit(1);
	}

	struct timeval timeout;
	timeout.tv_usec = 0;
	ssize_t readSize;
	char buf[SIZEBUF];
	fd_set rfds;

	while (1)
	{
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);

		timeout.tv_sec = 5;

		switch (select(1, &rfds, NULL, NULL, &timeout))
		{
		case -1:
			dprintf(STDERR_FILENO, "Select error\n%s\n", strerror(errno));
			exit(1);
		case 0:
			dprintf(STDERR_FILENO, "Timeout error (%s)\n", argv[1]);
			break;
		default:
			if ((readSize = read(STDIN_FILENO, buf, SIZEBUF)) > 0)
			{
				ssize_t sizeArg = strlen(argv[1]);

				if (
					write(STDOUT_FILENO, buf, readSize - 1) != readSize - 1
					|| write(STDOUT_FILENO, " (", 2) != 2
					|| write(STDOUT_FILENO, argv[1], sizeArg) != sizeArg
					|| write(STDOUT_FILENO, ")\n", 2) != 2
					)
				{
					dprintf(STDERR_FILENO, "Write error\n%s\n", strerror(errno));
					exit(1);
				}
			}
			else
			{
				dprintf(STDERR_FILENO, "Read error\n%s\n", strerror(errno));
				exit(1);
			}

			break;
		}
	}

	exit(0);
}
