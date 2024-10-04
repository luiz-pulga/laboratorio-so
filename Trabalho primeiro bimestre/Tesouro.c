#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define NUM_PLAYERS 5
#define FIELD_SIZE 10
#define MAX_PLAYERS_SEARCHING 2  // Máximo de jogadores que podem buscar no campo ao mesmo tempo

// Estrutura para representar o campo de busca
typedef struct {
    int x;
    int y;
} Position;

// Variáveis globais
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger a variável 'found'
sem_t players_sem;  // Semáforo para controlar quantos jogadores podem buscar ao mesmo tempo
int found = 0;      // Variável que indica se o tesouro foi encontrado
Position treasure_position;  // Posição do tesouro

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

    while (!found) {  // Continua enquanto o tesouro não for encontrado
        // Os jogadores aguardam a liberação do semáforo para entrar no campo e buscar
        sem_wait(&players_sem);  // Limita o número de jogadores que podem buscar simultaneamente
        
        // Exibe uma mensagem quando o jogador entra no campo
        printf("Jogador %d entrou no campo para buscar o tesouro.\n", player_id);

        // Gerar uma posição aleatória para procurar o tesouro
        guess = generate_random_position();

        // Trava o mutex para verificar a posição
        pthread_mutex_lock(&mutex);

        if (found) {  // Verifica novamente se o tesouro foi encontrado para sair rapidamente
            pthread_mutex_unlock(&mutex);  // Destrava antes de sair
            sem_post(&players_sem);  // Libera um "slot" no semáforo para outro jogador buscar
            printf("Jogador %d saiu do campo, pois o tesouro já foi encontrado.\n", player_id);
            break;
        }

        // Verificar se o tesouro está nessa posição
        if (guess.x == treasure_position.x && guess.y == treasure_position.y) {
            printf("Jogador %d encontrou o tesouro na posição (%d, %d)!\n", player_id, guess.x, guess.y);
            found = 1;  // Tesouro encontrado, o jogo acaba
        } else {
            printf("Jogador %d procurou na posição (%d, %d) e não encontrou nada.\n", player_id, guess.x, guess.y);
        }

        pthread_mutex_unlock(&mutex);  // Destrava o mutex após a busca

        // Exibe uma mensagem quando o jogador sai do campo
        printf("Jogador %d saiu do campo após a busca.\n", player_id);

        sem_post(&players_sem);  // Libera um "slot" no semáforo para outro jogador buscar

        sleep(1);  // Pequena pausa para simular o tempo de busca
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

    // Inicializa o semáforo com o número máximo de jogadores que podem buscar simultaneamente
    sem_init(&players_sem, 0, MAX_PLAYERS_SEARCHING);

    // Cria as threads para cada jogador
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player_ids[i] = i + 1;  // IDs dos jogadores (começando de 1)
        if (pthread_create(&players[i], NULL, player_search, &player_ids[i]) != 0) {
            perror("Erro ao criar a thread do jogador");
            return 1;
        }
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_PLAYERS; i++) {
        pthread_join(players[i], NULL);
    }

    // Destrói o semáforo após o fim do jogo
    sem_destroy(&players_sem);

    printf("Fim do jogo! O tesouro foi encontrado.\n");

    return 0;
}
