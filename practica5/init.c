#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXPROC 6

int main()
{
	pid_t pid[MAXPROC];
	int status;

	int i;

	for (i = 0; i < MAXPROC; i++)
	{
		pid[i] = fork();

		if (pid[i] == 0)
		{
			execlp("xterm", "xterm", "-e", "./getty", NULL);
		}
	}

	while (1)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			printf("exited, status=%d\n", WEXITSTATUS(status));

			int local_pid = fork();

			if (local_pid == 0)
			{
				execlp("xterm", "xterm", "-e", "./getty", NULL);
			}
		}
		else if (WIFSIGNALED(status))
		{
			printf("killed by signal %d\n", WTERMSIG(status));
			kill(0, SIGKILL);
		}
	}

	wait(NULL);
}