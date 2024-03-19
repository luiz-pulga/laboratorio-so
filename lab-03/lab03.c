#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>

#define PILHA_TAM 65536

volatile sig_atomic_t variavelFlag = 0;

void sinalizarPai(int sinal) {
    variavelFlag = 1;
}

int atividadeDoFilho(void* argumento) {
    printf("[Filho] Iniciado.\n");
    sleep(1);
    printf("[Filho] Sinalizando o processo pai.\n");
    kill(getppid(), SIGUSR1);
    return 0;
}

int main() {
    char* pilha;
    pid_t pid;
    struct sigaction sa;

    sa.sa_handler = &sinalizarPai;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    pilha = malloc(PILHA_TAM);
    if (!pilha) {
        perror("Falha ao alocar pilha");
        exit(EXIT_FAILURE);
    }

    printf("[Pai] Criando processo filho...\n");
    pid = clone(&atividadeDoFilho, pilha + PILHA_TAM,
                SIGCHLD | CLONE_VM, NULL);
    if (pid == -1) {
        perror("Falha ao criar processo filho");
        exit(EXIT_FAILURE);
    }

    while (!variavelFlag) {
        pause();
    }

    printf("[Pai] Sinal recebido do filho. Processo filho completou sua execução.\n");

    free(pilha);
    return EXIT_SUCCESS;
}
