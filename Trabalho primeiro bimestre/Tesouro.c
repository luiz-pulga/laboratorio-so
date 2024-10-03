#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_PLAYERS 5
#define FIELD_SIZE 15

// Estrutura para representar o campo de busca
typedef struct {
    int x;
    int y;
} Position;

// Variáveis globais
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger a busca
int found = 0; // Variável que indica se o tesouro foi encontrado
Position treasure_position; // Posição do tesouro

// Função que gera uma posição aleatória no campo
Position generate_random_position() {
    Position pos;
    pos.x = rand() % FIELD_SIZE; // Gerar posição aleatória entre 0 e FIELD_SIZE - 1
    pos.y = rand() % FIELD_SIZE;
    return pos;
}

// Função executada por cada jogador
void* player_search(void* arg) {
    int player_id = *(int*)arg;
    Position guess;

    while (!found) { // Continua enquanto o tesouro não for encontrado
        // Gerar uma posição aleatória para procurar o tesouro
        guess = generate_random_position();

        // Trava o mutex para verificar a posição
        pthread_mutex_lock(&mutex);

        if (found) { // Verifica novamente se o tesouro foi encontrado para sair
            pthread_mutex_unlock(&mutex); // Destrava antes de sair
            break;
        }

        // Verificar se o tesouro está nessa posição
        if (guess.x == treasure_position.x && guess.y == treasure_position.y) {
            printf("Jogador %d encontrou o tesouro na posição (%d, %d)!\n", player_id, guess.x, guess.y);
            found = 1; // Tesouro encontrado, o jogo acaba
        } else {
            printf("Jogador %d procurou na posição (%d, %d) e não encontrou nada.\n", player_id, guess.x, guess.y);
        }

        pthread_mutex_unlock(&mutex); // Destrava o mutex após a busca

        sleep(1); // Pequena pausa para simular o tempo de busca
    }

    return NULL;
}

int main() {
    pthread_t players[NUM_PLAYERS];
    int player_ids[NUM_PLAYERS];

    // Inicializa a semente de geração de números aleatórios
    srand(time(NULL));

    // Gera a posição aleatória do tesouro
    treasure_position = generate_random_position();
    printf("O tesouro está escondido em algum lugar do campo %dx%d...\n", FIELD_SIZE, FIELD_SIZE);

    // Cria as threads para cada jogador
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player_ids[i] = i + 1; // Ids dos jogadores (começando de 1)
        if (pthread_create(&players[i], NULL, player_search, &player_ids[i]) != 0) {
            perror("Erro ao criar a thread do jogador");
            return 1;
        }
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++) {
        pthread_join(players[i], NULL);
    }

    printf("Fim do jogo! O tesouro foi encontrado.\n");

    return 0;
}
