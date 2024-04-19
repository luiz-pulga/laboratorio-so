#include <stdio.h>
#include <pthread.h>

int registro_pessoas[2][10000];
int contagem[2] = {0, 0};
int sentido_atual;
int momento_atual;
int duracao_processo;

void *processar_escada() {

  // Definindo variáveis locais
  int sentido_contrario;
  int posicao[2] = {0, 0};
  int tempo_saida = 0;

  momento_atual = registro_pessoas[sentido_atual][0];

  while (posicao[0] < contagem[0] || posicao[1] < contagem[1]) {
    sentido_contrario = 1 - sentido_atual;

    int pode_partir = registro_pessoas[sentido_atual][posicao[sentido_atual]] <= tempo_saida;

    if (pode_partir) {
      momento_atual = registro_pessoas[sentido_atual][posicao[sentido_atual]];
      posicao[sentido_atual]++;
    } 
    else {
      int proxima_saida_contraria = registro_pessoas[sentido_contrario][posicao[sentido_contrario]];
      momento_atual = (tempo_saida > proxima_saida_contraria) ? tempo_saida : proxima_saida_contraria;
      posicao[sentido_contrario]++;
    }

    tempo_saida = momento_atual + 10;
    sentido_atual = 1 - sentido_atual;
  }

  duracao_processo = tempo_saida + 10;
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

  fprintf(arquivo_saida, "%d\n", duracao_processo);
  fclose(arquivo_saida);

  printf("%d\n", duracao_processo);

return 0;
}
