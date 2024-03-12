Perguntas Teoricas:

1. Você é capaz de identificar os trechos executados por pai e filho?

  R: No recurso fork, no caso da funcao retornar 0, isso indica que deve ser executada a funcao filho. No caso de retornar um valor positivo maior do que 0, sera executada a funcao pai. E no ultimo caso de retornar um numero negativo, quer dizer que ocorreu um erro na funcao.
  No caso do codigo da tarefa, a funcao filho executara a parte: 
  else if (pid == 0) { /* child process */
   printf("I am the child %d\n",pid);
   execlp("/bin/ls","ls",NULL); 
  E a funcao pai executara a parte:
  else { /* parent process */
 /* parent will wait for the child to complete */
   printf("I am the parent %d\n",pid);
   wait(NULL); 

2. Quantos processos serão criados?

  R: Serao criados 3 processos novos, o primeiro getpid exibira o processo pai e o segundo exibira o processo pai e o filho. No segundo e terceiro fork(), serao criadas mais uma funcao filho para cada.

![image](https://github.com/luiz-pulga/laboratorio-so/assets/162224053/6800e553-9516-426f-b686-d1b4ae1dd72f)
