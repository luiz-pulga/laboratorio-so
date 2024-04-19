#include <stdio.h>
#include <pthread.h>

int registro_pessoas[2][10000];
int contagem[2] = {0, 0};
int sentido_atual;
int momento_atual;
int tempo_saida;

void *processar_escada() {
    int sentido_contrario;
    int posicao[2] = {0, 0};

    momento_atual = registro_pessoas[sentido_atual][0];

    while (posicao[0] < contagem[0] || posicao[1] < contagem[1]) {
        sentido_contrario = 1 - sentido_atual;

        if (posicao[sentido_atual] < contagem[sentido_atual] && (posicao[sentido_contrario] >= contagem[sentido_contrario] || registro_pessoas[sentido_atual][posicao[sentido_atual]] <= tempo_saida)) {
            momento_atual = (tempo_saida > registro_pessoas[sentido_atual][posicao[sentido_atual]]) ? tempo_saida : registro_pessoas[sentido_atual][posicao[sentido_atual]];
            posicao[sentido_atual]++;
        } else {
            tempo_saida = momento_atual + 10;
            momento_atual = (posicao[sentido_contrario] < contagem[sentido_contrario]) ? registro_pessoas[sentido_contrario][posicao[sentido_contrario]] : tempo_saida;
            posicao[sentido_contrario]++;
            sentido_atual = sentido_contrario;
        }
    }

    tempo_saida = momento_atual + 10;
    return NULL;
}

int main() {
    FILE *arquivo_entrada, *arquivo_saida;

    arquivo_entrada = fopen("input.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 0;
    }

    int total_pessoas;
    fscanf(arquivo_entrada, "%d", &total_pessoas);

    int instante, direcao_lida;
    for (int i = 0; i < total_pessoas; i++) {
        fscanf(arquivo_entrada, "%d %d", &instante, &direcao_lida);

        if (i == 0) {
            sentido_atual = direcao_lida;
        }

        registro_pessoas[direcao_lida][contagem[direcao_lida]] = instante;
        contagem[direcao_lida]++;
    }

    fclose(arquivo_entrada);

    pthread_t id_thread;
    pthread_create(&id_thread, NULL, processar_escada, NULL);
    pthread_join(id_thread, NULL);

    arquivo_saida = fopen("output.txt", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        return 0;
    }

    fprintf(arquivo_saida, "%d\n", tempo_saida);
    fclose(arquivo_saida);

    printf("%d\n", tempo_saida);
    
    return 0;
}
