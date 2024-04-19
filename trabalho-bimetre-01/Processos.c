#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int agenda[2][10000];
int contagens[2] = {0, 0};
int sentido_atual;
int tempo_corrente;

int funcionamento_escada() {
    int sentido_oposto;
    int posicoes[2] = {0, 0};
    int tempo_ultima_pessoa = 0;

    tempo_corrente = agenda[sentido_atual][0];

    while (posicoes[0] < contagens[0] || posicoes[1] < contagens[1]) {
        sentido_oposto = 1 - sentido_atual;

        if (posicoes[sentido_atual] < contagens[sentido_atual] && (agenda[sentido_atual][posicoes[sentido_atual]] <= tempo_ultima_pessoa || posicoes[sentido_oposto] >= contagens[sentido_oposto])) {
            tempo_corrente = agenda[sentido_atual][posicoes[sentido_atual]];
            tempo_ultima_pessoa = tempo_corrente + 10;
            posicoes[sentido_atual]++;
        } else if (posicoes[sentido_oposto] < contagens[sentido_oposto]) {
            tempo_corrente = agenda[sentido_oposto][posicoes[sentido_oposto]];
            tempo_ultima_pessoa = tempo_corrente + 10;
            posicoes[sentido_oposto]++;
            sentido_atual = sentido_oposto;
        }
    }

    return tempo_ultima_pessoa;
}

int main() {
    FILE *entrada, *saida;

    entrada = fopen("input.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 0;
    }

    int quantidade_pessoas;
    fscanf(entrada, "%d", &quantidade_pessoas);

    int instante, direcao;
    for (int i = 0; i < quantidade_pessoas; i++) {
        fscanf(entrada, "%d %d", &instante, &direcao);

        if (i == 0) {
            sentido_atual = direcao;
        }

        agenda[direcao][contagens[direcao]] = instante;
        contagens[direcao]++;
    }

    fclose(entrada);

    pid_t pid = fork();

    if (pid == 0) {
        exit(funcionamento_escada());
    } else {
        int status;
        wait(&status);

        saida = fopen("output.txt", "w");
        if (saida == NULL) {
            printf("Erro ao abrir arquivo de saída.\n");
            return 0;
        }

        fprintf(saida, "%d\n", WEXITSTATUS(status));
        fclose(saida);

        printf("O tempo final é: %d segundos.\n", WEXITSTATUS(status));
    }

    return 0;
}
