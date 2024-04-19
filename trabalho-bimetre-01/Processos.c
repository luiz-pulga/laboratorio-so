#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int agenda[2][10000];
int contagens[2] = {0, 0};
int sentido_atual;
int tempo_corrente;

int funcionamento_escada() {

  // Definição de variáveis locais
  int sentido_oposto;
  int posicoes[2] = {0, 0};
  int tempo_ultima_pessoa = 0;

  tempo_corrente = agenda[sentido_atual][0];

  while (posicoes[0] < contagens[0] || posicoes[1] < contagens[1]) {
    sentido_oposto = 1 - sentido_atual;

    if (agenda[sentido_atual][posicoes[sentido_atual]] <= tempo_ultima_pessoa) {
      tempo_corrente = agenda[sentido_atual][posicoes[sentido_atual]];
      posicoes[sentido_atual]++;
    } 
    else {
      int proximo_tempo_oposto = agenda[sentido_oposto][posicoes[sentido_oposto]];
      tempo_corrente = (tempo_ultima_pessoa > proximo_tempo_oposto) ? tempo_ultima_pessoa : proximo_tempo_oposto;
      posicoes[sentido_oposto]++;
    }

    tempo_ultima_pessoa = tempo_corrente + 10;
    sentido_atual = 1 - sentido_atual;
  }

  return tempo_ultima_pessoa + 10;
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
    int resultado = funcionamento_escada();
    return 0;
  } else {
    wait(NULL);

    saida = fopen("output.txt", "w");
    if (saida == NULL) {
      printf("Erro ao abrir arquivo de saída.\n");
      return 0;
    }

    int resultado_final = funcionamento_escada();
    fprintf(saida, "%d\n", resultado_final);
    fclose(saida);

    printf("%d\n", resultado_final);
  }


return 0;
}
