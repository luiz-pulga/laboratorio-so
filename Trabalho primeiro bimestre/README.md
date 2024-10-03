Teste 1:

![image](https://github.com/user-attachments/assets/cf598e8a-926f-48a5-976f-964560627931)

Teste 2:

![image](https://github.com/user-attachments/assets/310d6c56-64fd-462e-961e-3ea4c31666c2)

Explicação sobre o código:

-> O código cria NUM_PLAYERS threads (definido como 5) para simular múltiplos jogadores que buscam pelo tesouro. Cada thread é criada usando pthread_create(), e a função player_search é passada como a função a ser executada por cada thread.

![image](https://github.com/user-attachments/assets/0529ccc6-ed7b-4192-aaf9-e70d132ecdd9)

![image](https://github.com/user-attachments/assets/fbcfadb8-2f91-4449-818e-13aa428e3953)

-> Um mutex (pthread_mutex_t mutex) é utilizado para proteger o acesso à variável found, que indica se o tesouro foi encontrado. fazendo com que condições de corrida não aconteçam, onde múltiplas threads poderiam tentar acessar ou modificar a variável ao mesmo tempo.

![image](https://github.com/user-attachments/assets/0791a3e5-53bc-4de7-816b-565c6ad779c2)

-> As threads se comunicam com a variável found, que é uma variável compartilhada. Cada thread verifica se found é 1 antes de continuar suas buscas. Quando um jogador encontra o tesouro, ele atualiza a variável e imprime uma mensagem no console.

-> Não há a necessidade de uma implementação de semáforos, já que apenas um jogador pode encontrar o tesouro.
