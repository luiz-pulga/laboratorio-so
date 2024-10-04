Explicação sobre o código:

-> O código cria NUM_PLAYERS threads (definido como 5) para simular múltiplos jogadores que buscam pelo tesouro. Cada thread é criada usando pthread_create(), e a função player_search é passada como a função a ser executada por cada thread. Na função player_search(), a lógica de repetição (while (!found)) garante que os jogadores continuem a busca até que o tesouro seja encontrado. O sleep(1) é usado para simular um tempo de espera entre as tentativas de busca para evitar uma possível conclusão automática e melhorar o entendimento dos logs.

![image](https://github.com/user-attachments/assets/0529ccc6-ed7b-4192-aaf9-e70d132ecdd9)

![image](https://github.com/user-attachments/assets/fbcfadb8-2f91-4449-818e-13aa428e3953)

-> Um mutex (pthread_mutex_t mutex) é utilizado para proteger o acesso à variável found, que indica se o tesouro foi encontrado. fazendo com que condições de corrida não aconteçam, onde múltiplas threads poderiam tentar acessar ou modificar a variável ao mesmo tempo. Sem o mutex, as threads poderiam alterar found de forma concorrente, o que poderia resultar em uma situação onde mais de uma thread "encontra" o tesouro. Antes de qualquer thread verificar ou modificar a variável found, ela deve travar o mutex. Isso garante que enquanto uma thread estiver verificando ou atualizando a variável, nenhuma outra thread pode fazê-lo.

![image](https://github.com/user-attachments/assets/a8965797-c2e7-4ebe-ba3d-97d4dbb57e77)

-> As threads se comunicam com a variável found. Cada thread verifica se found é 1 antes de continuar suas buscas. Quando um jogador encontra o tesouro, ele atualiza a variável e imprime uma mensagem no console. A variável found e o acesso ao campo de busca são recursos compartilhados, e a sincronização evita que múltiplas threads interfiram no funcionamento correto do sistema.

-> O semáforo é inicializado com o valor MAX_PLAYERS_SEARCHING (neste caso, 2), o que significa que apenas dois jogadores podem estar buscando o tesouro no campo simultaneamente. Se dois jogadores já estiverem no campo, os outros terão que esperar até que um jogador saia. Mensagens são exibidas para indicar quando um jogador entra no campo para realizar uma busca e quando ele sai do campo após a tentativa de busca.

![image](https://github.com/user-attachments/assets/4ebcef4c-1a05-45a4-a67b-30a3e0c9985d)

![image](https://github.com/user-attachments/assets/c71b1317-2f3d-4d58-a58a-373e9a290e45)

-> A função pthread_join() no main() garantirá que todas as threads terminem antes que o programa finalize.

-> o código já lida com erros na criação de threads usando perror() para imprimir uma mensagem de erro se pthread_create() falhar.
