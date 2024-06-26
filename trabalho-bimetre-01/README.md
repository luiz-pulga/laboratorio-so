Print Threads
![image](https://github.com/luiz-pulga/laboratorio-so/assets/162224053/15a6f57d-19a9-4d7f-8bdf-7241f7cbf0b3)

Print Processos
![image](https://github.com/luiz-pulga/laboratorio-so/assets/162224053/82abe861-9593-4cb2-be6b-b15f8f043cef)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  Resposta das Perguntas:

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

    R:

Threads: A thread unica processa apenas uma pessoa por vez e utiliza uma márgem de segurança de 10 segundos. Dessa maneira, torna-se possível o controle de fluxo no código. Além disso, ele usa a variável tempo_ultima_pessoa para controlar quem e quando acessou recentemente.

Processos: Esse método também usa margem de 10 segundos de segurança, porém acaba se escorando mais no controle de tempo e dos processos pai e filho. O pai sempre vai esperar o filho terminar sua execução para começar.

2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

    R:

Threads: Utiliza da variável sentido_atual para garantir que apenas um sentido seja utilizado por vez.

Processos: Asim como em Threads, a variável sentido_atual determina a direção que está ativa. O processo segue essa direção até que não haja mais pessoas ou seja necessário alternar devido a uma pessoa esperando na direção oposta.

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

    R:

Devido ao compartilhamento de memoria e a comunicação facilitada, as threads apresentam um melhor desempenho. Como elas compartilham seu estado atual, há mais facilidade em manipular as variáveis. No caso dos processos, é necessária a utilização de mecanismos interprocessos, o que acaba requisitando maior uso de recursos e tempo
