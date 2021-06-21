#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int retorno = 0;

int main()
{
    int p, status;
    char usr[80];
    char passwd[80];

    while (!retorno)
    {
        printf("User: ");
        scanf("%s", usr);
        printf("Password: ");
        scanf("%s", passwd);

        if (1) // Si el usuario y contraseña son correctos
        {
            p = fork();
            if (p == 0)
            {
                execlp("./sh", "./sh", NULL);
            }
            else
            {
                waitpid(p, &status, WUNTRACED);
                if (WIFEXITED(status))
                {
                    printf("exited, status=%d\n", WEXITSTATUS(status));
                    if (WEXITSTATUS(status) == 1) {
                        kill(getppid(), SIGUSR2);
                    }
                }
            }
        }
        else
        {
            fprintf(stderr, "Wrong user/password\n");
        }
    }

    return retorno;
}