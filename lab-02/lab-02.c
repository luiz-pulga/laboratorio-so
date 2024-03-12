#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_SIZE 256

int main() {
    int fds[2];
    pid_t filho_pid;
    char mensagemdoPai[BUFF_SIZE] = "Salve filho";
    char buffer[BUFF_SIZE];

    if (pipe(fds) != 0) {
        fprintf(stderr, "Falha ao criar o pipe\n");
        return 1;
    }

    filho_pid = fork();
    if (filho_pid < 0) {
        fprintf(stderr, "Falha no fork\n");
        return 1;
    }

    if (filho_pid == 0) {
        close(fds[1]);
        if (read(fds[0], buffer, BUFF_SIZE) > 0) {
            printf("Filho recebeu a mensagem: '%s'\n", buffer);
        }
        close(fds[0]);
        printf("Saindo do processo filho.\n");
    } else {
        close(fds[0]);
        write(fds[1], mensagemdoPai, strlen(mensagemdoPai)+1);
        printf("Pai mandou a mensagem.\n");
        close(fds[1]);
        wait(NULL);
        printf("Saindo do processo pai.\n");
    }

return 0;
}
