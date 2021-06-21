#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    char cad[80];
    int p;
    int salir = 0;

    while (!salir)
    {
        printf("> ");
        scanf("%s", cad);

        if (strcmp(cad, "shutdown") == 0)
        {
            salir = 1;
            printf("Saliendo\n");
        }
        else
        {

            p = fork();
            if (p == 0)
            {
                execlp(cad, cad, NULL);
            }

            wait(NULL);
        }
    }

    return salir;
}