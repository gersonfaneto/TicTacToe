<!-- prettier-ignore -->
```markdown
                           _____ _     _____         _____          
                          |_   _(_) __|_   _|_ _  __|_   _|__   ___ 
                            | | | |/ __|| |/ _` |/ __|| |/ _ \ / _ \
                            | | | | (__ | | (_| | (__ | | (_) |  __/
                            |_| |_|\___||_|\__,_|\___||_|\___/ \___|
```
<div align="center">
<h1> Problema #1 - Jogo da Velha </h1>
</div>

<div align="center">

</div>

> Documentação do projeto da disciplina TEC 499 - Sistemas Digitais, de desenvolvimento em linguagem C do clássico Jogo da Velha.

## Índice

- [Introdução](#introdução)
- [Hardware utilizado](#hardware-utilizado)
  - [Principais Especificações FPGA](#principais-especificações-fpga)
  - [Principais Especificações HPS](#principais-especificações-hps)
  - [Periféricos utilizados](#periféricos-utilizados)
  - [Arquitetura do ARM Cortex-A9](#arquitetura-do-arm-cortex-a9)
- [Documentação utilizada](#documentação-utilizada)
- [Desenvolvimento](#desenvolvimento)
  - [Conexão remota com a placa DE1-SoC](#conexão-remota-com-a-placa-de1-soc)
  - [Detectando o mouse](#detectando-o-mouse)
    - [Modularização do código](#modularização-do-código)
  - [Implementação da lógica e exibição do jogo](#implementação-da-lógica-e-exibição-do-jogo)
    - [Identificação das coordenadas e exibição do tabuleiro](#identificação-das-coordenadas-e-exibição-do-tabuleiro)
    - [Lógica de funcionamento do jogo](#lógica-de-funcionamento-do-jogo)
    - [Bibliotecas utilizadas](#bibliotecas-utilizadas)
    - [Compilação e Makefile](#compilação-e-makefile)
- [Inicializando o projeto do jogo](#inicializando-o-projeto-do-jogo)
- [Jogabilidade](#jogabilidade)
- [Resultados e Conclusão](#resultados-e-conclusão)
- [Tutor](#tutor)
- [Equipe](#equipe)
- [Referências](#referências)

## Introdução

Este relatório visa apresentar a documentação do projeto que tem como objetivo desenvolver um Jogo da Velha desenvolvido programado em linguagem C para ser executado em um ambiente de terminal, em modo texto, em sistema operacional Linux. O jogo foi implementado para permitir a interação de dois jogadores, utilizando um mouse conectado a uma das portas USB do Kit de desenvolvimento DE1-SoC, para que, a partir do mouse, cada um dos dois jogadores possa selecionar as posições no tabuleiro a cada jogada. 

Nas seções seguintes, serão discutidos os detalhes da implementação do jogo, incluindo a estrutura do código, as funções principais e os algoritmos utilizados para controlar o fluxo do jogo e validar as jogadas dos jogadores. 

Como também será abordado o processo de conexão do mouse ao terminal, incluindo informações sobre como o jogo detecta e processa os movimentos do mouse para permitir que os jogadores façam suas jogadas.

Não obstante, outro ponto para esclarecimento será a utilização dos botões da placa para iniciar e parar o jogo, explicando como esses dispositivos foram integrados ao código e como são utilizados pelos jogadores durante a partida. Por fim, serão discutidos os testes e resultados obtidos do projeto, bem como os desafios encontrados durante o desenvolvimento e as respectivas soluções adotadas para superá-los.

## Hardware Utilizado

O hardware programável utilizado para o projeto foi a placa de desenvolvimento DE1-SoC, projetada em torno do FPGA System-on-Chip (SoC) da Altera. Este SoC combina núcleos Cortex-A9 dual-core com lógica programável. O sistema inclui um processador rígido (HPS) baseado em ARM, periféricos e interfaces de memória integradas ao FPGA. A placa contém uma distribuição Linux embarcada.

</p>
<div align="center">
   <img width="500px" src="resources\DE1-SoC.png" />
    <p> Figura 1. Kit de desenvolvimento DE1-SoC.</p>
</div>


### Principais Especificações FPGA

Categoria|Especificações|
|--------|-------|
|CPU| Altera Cyclone® V SE 5CSEMA5F31C6N
|Memória|64MB SDRAM (barramento 16-bits)|
|Portas USB| USB-Blaster II
|Periféricos| 4 botões, 10 chaves, 10 LEDs vermelhos, display de 7 segmentos 
---
### Principais Especificações HPS

Categoria|Especificações|
|--------|-------|
|CPU|800MHz Dual-core ARM Cortex-A9 MPCore
|Memória|1GB DDR3 SDRAM (barramento 32-bits)
|Rede| 1 Gb Ethernet PHY com conector RJ45
|Portas USB| 2 portas USB Host, normal tipo A
---
### Periféricos utilizados

</p>
<div align="center">
   <img width="500px" src="resources\DE1-p.jpeg" />
    <p> Figura 2. Periféricos utilizados do DE1-SoC.</p>
</div>

Dos periféricos da FPGA, utilizou-se a entrada de rede Ethernet para conexão remota, as portas USB para conectar o mouse e um dos botões (push-buttons) para iniciar ou encerrar o jogo. O botão escolhido para essa finalidade foi o Push-button[0] (representado no código como B0). O botão envia um nível lógico baixo quando pressionado e nível lógico alto quando não.

Nome|FPGA Pin No.|Description|I/O Standard|
|--------|-------|--------|---------|
|KEY[0]| PIN_AA14| Push-button[0]| 3.3V
|KEY[1]| PIN_AA15| Push-button[1]| 3.3V
|KEY[2]| PIN_W15| Push-button[2]| 3.3V
|KEY[3]| PIN_Y16| Push-button[3]| 3.3V



### Arquitetura do ARM Cortex-A9

O processador do kit de desenvolvimento é o ARM Cortex-A9 800MHz MPCore, possui a Arquitetura do Conjunto de Instruções (ISA) ARMv7. Por ser dual-core suporta multiprocessamento e recebe instruções por palavras com o comprimento de 32 bits.

Embora o HPS e o FPGA possam operar de forma independente, eles são fortemente acoplados por meio de uma interconexão de sistema de alta largura de banda construída a partir de pontes de barramento de alto desempenho. Tanto a malha FPGA quanto o HPS podem acessar um ao outro por meio dessas pontes de interconexão.

O processador ARM pode acessar o FPGA usando a ponte HPS para FPGA ou a ponte Lightweight HPS para FPGA. Essas pontes são mapeadas para regiões no espaço de memória do ARM. Quando um componente do lado do FPGA é conectado a uma dessas pontes, os registradores mapeados de memória do componente estão disponíveis para leitura e gravação pelo processador ARM na região de memória da ponte. Ou seja, essas pontes permitem que o processador solicite ou envie dados para a FPGA e também transferir os dados para a memória do HPS.

O código em linguagem C, ao ser executado, se comunica com a placa FPGA. Programas executados no processador ARM no sistema operacional DE1-SoC-UP-Linux podem acessar periféricos de hardware que são implementados no FPGA.

Esses dispositivos de entrada e saída conectados à placa são acessados na memória, pois são mapeados em diretórios específicos, a partir dos drivers que serão explicados na sessão de Desenvolvimento. Eles podem ser acessados por permissão concedida pelo Linux.

## Documentação utilizada

> Datasheet da DE-SoC: Esse documento contém todas as informações relacionadas ao kit de desenvolvimento, incluindo os recursos e características de design da placa, instruções para seu uso e descrição dos periféricos. Além de fornecer exemplos de projetos avançados implementados na placa DE1-SoC, que abrangem os recursos dos periféricos conectados ao FPGA.

> Documento de orientação ao uso de Linux* em placas DE-series: Descreve uma versão do Linux* disponível para uma variedade de sistemas embarcados que apresentam um dispositivo Intel® Cyclone® V System-on-Chip (SoC). O documento mostra como o Linux pode ser armazenado em uma memória microSD* que pode ser inserida na placa DE1-SoC e inicializada pelo processador ARM. E também como podem ser desenvolvidos programas de software que rodam no processador ARM no Linux, e fazem uso dos recursos de hardware na placa DE1-SoC. Esses recursos incluem periféricos no Hard Processor System (HPS) e periféricos de hardware personalizados implementados no FPGA (Field-Programmable Gate Array) no dispositivo SoC.

## Desenvolvimento

Iniciou-se o desenvolvimento do projeto do Jogo da Velha com uma análise detalhada dos requisitos para determinar o que seria necessário para conectar o mouse ao jogo e detectar seus movimentos pelo terminal. Como foi idealizado, cada jogada deveria ser capturada por um mouse conectado à placa DE1-SoC, o que exigiu uma abordagem cuidadosa para integrar o hardware e o software de maneira eficaz.

### Conexão remota com a placa DE1-SoC

Com relação à conexão com a placa, foi estabelecida via SSH (Secure Shell), um protocolo de rede que permite acesso remoto a sistemas Linux. Isso possibilitou o controle e monitoramento do jogo a partir de um computador externo, simplificando o processo de desenvolvimento e depuração.

</p>
<div align="center">
   <img width="500px" src="resources\ssh-conection.png" />
    <p> Figura 3. Conexão ssh com a placa via terminal.</p>
</div>

O  Secure  Shell  oferece  ao  usuário  a  capacidade  de  conectar-se  remotamente  a outro computador com segurança, pois os dados utilizados na rede serão criptografados. O protocolo SSH tem como principal finalidade o login remoto, porém pode ser utilizado  como  túnel  criptográfico  para  outros  propósitos,  como  copiar  arquivos, proteção de conexões de e-mail e execução de programas remotos.

Um servidor SSH permite que vários clientes SSH conectem-se a ele. O cliente precisa conhecer o endereço IP (ou hostname) do servidor (nesse caso, o IP da placa utilizada) e a porta em que está escutando. O cliente se autentica para acessar a sessão. O processo de conexão ocorre em três etapas: o cliente envia uma solicitação de autenticação para o servidor e recebe uma chave de host. O servidor determina se o cliente pode se conectar, verificando as credenciais fornecidas. Se o cliente for autenticado e autorizado, a sessão SSH é estabelecida entre os dois hosts.

### Detectando o mouse

Para obter os eventos do mouse, exploramos o sistema de arquivos do Linux, especialmente o arquivo "mice". Esse arquivo é parte do subsistema de entrada do Linux e fornece uma interface para acessar os eventos gerados pelos dispositivos de entrada, como o mouse. Ao ler o arquivo "mice", nosso programa pode capturar informações sobre movimentos do mouse, cliques e outras interações do usuário em tempo real.

Uma das principais responsabilidades de um sistema operacional é gerenciar os dispositivos de entrada e saída (E/S). Isso inclui enviar comandos aos dispositivos, lidar com interrupções, tratar possíveis erros e fornecer uma interface para que os programas possam acessar esses dispositivos por meio de chamadas de sistema (system calls) para leitura e gravação.

O sistema de E/S do Linux segue uma abordagem semelhante à de outros sistemas UNIX. Os drivers de dispositivos são apresentados aos usuários como  arquivos regulares, a fim de abstrair o resto do sistema ou o usuário das particularidades do hardware, simplificando essa interação. Assim, o acesso a um dispositivo é feito da mesma maneira que a abertura de um arquivo. Porém, estes arquivos que fornecem acesso a um dispositivo são denominados de arquivos especiais e estão associados a um diretório que se encontra dentro de `/dev` (no Linux, diretórios são tratados como arquivos). Esses arquivos especiais são vinculados aos drivers de dispositivo correspondentes.

</p>
<div align="center">
   <img width="500px" src="resources\linux-dev-input-files.png" />
    <p> Figura 4. Diretórios presentes no /dev e /dev/input.</p>
</div>

Logo, as permissões de leitura e escrita nos dispositivos são tratadas da mesma forma que nos arquivos normais. No entanto, em dispositivos como alto-falantes, apenas a escrita é permitida, enquanto em dispositivos como mouses, apenas a leitura é possível. O caminho do arquivo utilizado no projeto para realizar essa leitura foi:

```C
  #include MOUSE_DEVICE_PATH "/dev/input/mice"
```
- #### Modularização do código:

Com relação a essa etapa do desenvolvimento, a modularização do código foi crucial para garantir uma organização clara e eficiente. O código foi separado em funções distintas, cada uma responsável por uma parte específica do processo. Como exemplo, foram criadas funções separadas para inicializar o mouse, ler eventos do mouse e interpretar esses eventos para determinar as ações do jogador no jogo, entre outros.

Nas pastas principais, em *src/app/* estão localizadas as funções para leitura dos eventos do mouse, para aparência do jogo e para manipulação das janelas do terminal. Em *src/common* estão as funções para a lógica do jogo, alias para tipagens e para controle da exibição de texto no terminal.

### Implementação da lógica e exibição do jogo

Após entender o formato das coordenadas do mouse, pudemos utilizar esses dados para construir o tabuleiro do Jogo da Velha no terminal e conectar à lógica do funcionamento do jogo, a partir da detecção de qual quadrante foi escolhido por cada jogador.

- #### Identificação das coordenadas e exibição do tabuleiro

É importante notar que um único evento de hardware pode gerar múltiplos eventos de entrada, como um único movimento do mouse que pode resultar em eventos separados para movimentos nos eixos X e Y, além de eventos para pressionamento de botões da placa.  Então, foi necessário tratar esse evento de movimento para determinar como o tabuleiro seria exibido no terminal.

O terminal é dividido em colunas e linhas, onde cada elemento dessas posições é um caracter de texto. Portanto, ele pode ser interpretado como um gráfico cartesiano onde os valores do eixo x são as colunas e os valores do eixo y são as linhas. Ao fazer a primeira leitura do arquivo de entrada do mouse, a posição determinada como inicial é a coordenada central dessa janela. 

A partir do conhecimento de quais são as coordenadas desse ponto central, foram determinados onde ficariam os extremos e pontos do tabuleiro do jogo (números da figura), para serem ligados um ao outro formando a visualização dessa matriz, como mostrado na animação a seguir.

</p>
<div align="center">
   <img width="300px" src="resources\board-make-gif.gif" />
    <p> Figura 4. Posições para as linhas e colunas do tabuleiro do jogo a partir do ponto central.</p>
</div>

Em seguida, na função de iniciar a matriz é armazenado a posição das quatro colunas e quatro linhas do tabuleiro. Assim, foi possível posicionar e exibir os caracteres para formação do matriz do tabuleiro, como repesentado na figura a seguir.

Com respeito a seleção do quadrante pelos jogadores, foi determinado o uso de um cursor, representado pelo símbolo "@" (arroba), que é exibido pela função printf exatamente no local onde está as coordenadas do mouse no terminal. Assim é possível visualizar mais facilmente aonde está localizado o mouse e selecionar a posição no tabuleiro.

</p>
<div align="center">
   <img width="500px" src="resources\game-void-board.png" />
    <p> Figura 5. Visualização do tabuleiro vazio do jogo e a indicação dos jogadores acima.</p>
</div>

A aparência do tabuleiro, juntamente com o visual dos outros elementos do jogo, foram todos construídos a partir de caracteres de texto. Do tipo String, o tabuleiro e os outros elementos são exibidos 'printando' linha a linha de acordo com as coordenadas da janela do terminal.

</p>
<div align="center">
   <img width="500px" src="resources\start-menu.png" />
    <p> Figura 6. Visualização do menu inicial do jogo.</p>
</div>

- #### Lógica de funcionamento do jogo

A lógica do Jogo da Velha foi implementada, seguindo as regras tradicionais do jogo, onde os jogadores alternam entre colocar suas marcações (X ou O) em células vazias do tabuleiro na tentativa de formar uma linha horizontal, vertical ou diagonal. Essa lógica foi integrada à detecção de movimentos do mouse, ao botão de iniciar e sair da partida e à aparência do tabuleiro.

</p>
<div align="center">
   <img width="800px" src="resources\mermaid-diagram-2024-05-11-015756.svg" />
    <p> Figura 7. Fluxograma da lógica do jogo.</p>
</div>

O jogo é iniciado na sua tela de *start* e, nesse momento, verifica-se o acionamento do botão. Se o jogo for iniciado (*state_game = 1*), o tabuleiro vazio é exibido e o primeiro jogador pode realizar a sua jogada, escolhendo a posição a partir do mouse. 

As coordenadas do mouse da posição escolhida são verificadas para saber se foram válidas ou não. Caso não sejam válidas - ou seja, o usuário clicou no lado de fora do tabuleiro - uma mensagem de erro é exibida. Se foram válidas, é feita uma segunda verificação, se a posição escolhida está vazia. Estando vazia a matriz é atualizada com a nova jogada, se estiver ocupada uma mensagem de erro aparece na tela.

Já se o jogo não for iniciado (*state_game = 0*), o menu inicial continua a ser exibido até que o botão seja acionado. E, nesse momento, as variáveis são reencetadas e a matriz do tabuleiro é iniciada, deixando todas as suas posições vazias.

O estado do jogo é verificado a todo momento. Logo, quando o botão de iniciar ou encerrar o jogo for apertado, para que essas ações sejam executadas de forma instantânea no terminal, pensou-se em controlar esse processo com uma máquina de estados finito. 

> Como mostrado no Diagrama de transição de estados da Figura, há duas situações do jogo: Parado e Rodando. Esses estados mudam de acordo com o pressionamento do botão, se mantendo no mesmo estado se o botão não for pressionado. A saída do estado Parado é *state_game = 0* e do estado Rodando é *state_game = 1*. Essas são as saídas da função que verifica o acionamento do botão.

</p>
<div align="center">
   <img width="600px" src="resources\state-machine-button.svg" />
    <p> Figura 8. Diagrama de transição da máquina de estados para controle do acionamento do botão.</p>
</div>

- #### Bibliotecas utilizadas

O uso de bibliotecas auxiliaram diversos processos na implementação do sistema, algumas delas já são padrões da linguagem C, outras foram escolhidas por serem úteis em determinadas funções.

1. **stdio.h**: Esta biblioteca fornece funcionalidades básicas de entrada e saída padrão.

2. **string.h**: Esta biblioteca fornece funções para manipulação de strings. Ela é utilizada para operações relacionadas a strings, como comparação, concatenação e busca.

3. **unistd.h**: Esta biblioteca fornece acesso a várias constantes e funções do sistema operacional relacionadas ao POSIX (Portable Operating System Interface). É utilizada para funções de sistema, como sleep(), que é usada para pausar a execução do programa por um determinado número de segundos.

4. **intelfpgaup/XX.h**: Biblioteca específica que fornece funcionalidades relacionadas ao hardware da placa Intel FPGA. Ela é utilizada para acessar os botões da placa, possibilitando a interação do usuário com o jogo. O XX.h deve ser substituído pelo nome do driver a ser acessado, nesse caso o KEY.h, usado para acesso à porta dos botões da placa. Como representado na tabela a baixo, que informa os módulos disponibilizados pelo De1-SoC para o acesso dos dispositivos da placa.

</p>
<div align="center">
   <img width="400px" src="resources\kernel-modules.jpeg" />
    <p> Figura 9. Módulos disponibilizados pelo De1-SoC para o acesso dos dispositivos da placa.</p>
</div>

5. **sys/ioctl.h**: Realiza o fornecimento de funções para controle de dispositivos de E/S no sistema. É utilizada para realizar operações de controle sobre dispositivos de E/S.

6. **errno.h**: Define a variável global errno, é usada para verificar e interpretar erros que ocorrem durante a execução do programa.

7. **fcntl.h**: Esta biblioteca fornece acesso a funções para manipulação de descritores de arquivos. É utilizada para operações relacionadas a arquivos, como abrir, fechar e manipular descritores de arquivos.

8. **signal.h**: Esta biblioteca fornece acesso a funções relacionadas ao tratamento de sinais no sistema. É utilizada para definir manipuladores de sinal para lidar com eventos específicos, como interrupções de teclado ou sinais de terminação. Utilizada para verificar se o sistema está rodando para que o jogo possa continuar ou para ser interrompido.

- #### Compilação e Makefile

Um Makefile é um arquivo de configuração usado em projetos de desenvolvimento de software para automatizar o processo de compilação. Ele contém instruções sobre como o projeto deve ser compilado, quais arquivos fonte devem ser usados, quais opções de compilação devem ser aplicadas e como os arquivos gerados devem ser organizados.

O Makefile é especialmente útil na linguagem C, onde é comum ter muitos arquivos fonte e dependências complexas entre eles. Ajudando a evitar a necessidade de compilar manualmente cada arquivo fonte e garantir que apenas os arquivos alterados sejam recompilados, economizando tempo e simplificando o processo de compilação.

O Makefile fornecido no projeto possui como suas principais seções:

- **Definições de variáveis**: Define variáveis para o compilador a ser usado, o nome do executável final, diretórios relacionados à compilação, entre outros.
  
- **Targets (Alvos)**: Define diferentes alvos para a compilação, como `build`, `run`, `clean`, `format`, etc. Cada alvo corresponde a uma tarefa específica a ser executada.
  
- **Regras de compilação**: Especifica como compilar os arquivos fonte em objetos e como vinculá-los para criar o executável final. Isso é feito por meio de regras que definem as dependências entre os arquivos e as ações necessárias para compilá-los.
  
- **Comandos auxiliares**: Fornece comandos auxiliares para executar tarefas adicionais, como formatação de código ou geração de banco de dados de compilação.

---

Por fim, foram realizados ajustes finais para garantir que o jogo funcionasse corretamente, corrigindo quaisquer bugs ou problemas de desempenho que surgissem durante os testes.

Sendo assim, o projeto do Jogo da Velha foi concluído, sendo captados então os resultados obtidos através dos testes realizados e fornecendo uma experiência de jogo  onde os jogadores podem competir entre si em um ambiente de terminal.

## Inicializando o projeto do jogo

Algumas etapas são nescessárias para a conexão via terminal com o kit de desenvolvimento DE1-SoC, compilação do código de execução e a inicialização do projeto:

1. Abrir o terminal;

2. Comando para conexão via SSH:
  ```bash
    ssh usuario@id_da_placa
  ```

3. Colocar a senha de acesso;

4. Abrir a pasta onde está localizado o projeto:
  ```bash
  cd diretório_do_projeto
  ```

5. Compilar o projeto, a partir do Makefile, com o comando:
  ```bash
  make build
  ```

6. Iniciar o projeto com o comando:
  ```bash
  make run
  ```

## Jogabilidade

O Jogo da Velha possui uma jogabilidade simples e rápida de compreender. Jogado em um tabuleiro 3x3. O jogador "X" é o primeiro a jogar e deve escolher uma célula vazia para colocar sua marca "X". Em seguida, o jogador "O" (player 2) faz sua jogada, escolhendo outra célula vazia para colocar sua marca "O". Os jogadores alternam suas jogadas até que alguém consiga formar uma linha horizontal, vertical ou diagonal com suas marcas. Segue exemplo de uma partida completa do jogo.

</p>
<div align="center">
   <img width="300px" src="resources\game-example.gif" />
    <p> Figura 10. Exemplo de jogada.</p>
</div>

Inicia-se o jogo apertando o botão B0 da placa. Para fazer uma jogada, o jogador deve selecionar a posição desejada no tabuleiro. Nesse caso, a seleção é feita usando o mouse conectado à placa DE1-SoC. Basta mover o cursor do mouse para a posição desejada e clicar para posicionar a marca na célula selecionada.

O objetivo é conseguir três marcas iguais em linha antes do adversário. Se todas as células do tabuleiro forem preenchidas e nenhum jogador conseguir formar uma linha, o jogo termina em empate. Para reiniciar uma partida, basta somente apertar novamento o botão de início.

## Resultados e Conclusão 

Nesta documentação, exploramos detalhadamente o desenvolvimento do projeto do Jogo da Velha, implementado em linguagem C para execução em um ambiente de terminal usando a placa DE1-SoC.

Indo deste de a análise dos requisitos do projeto, especificações da arquitetura e funcionamento da placa, destacando a integração do mouse como dispositivo de entrada e os controles utilizando os botões da placa, a conexão via SSH, utilização do sistema de arquivos do Linux para capturar os eventos do mouse, até a explicação da jogabilidade do jogo.

É importante também, citar os principais desafios encontrados no decorrer do desenvolvimento, como: lidar com a exibição da interface do jogo em modo texto, saber como ler e captar corretamente as coordenadas do mouse e problemas de compilação.

A seguir, demonstrações dos testes finais realizados, seus respectivos resultados e exibindo o funcionamento real do jogo da velha desenvolvido:

- Vitória do Jogador 1:

</p>
<div align="center">
   <img width="450px" src="resources\player-1-wins.gif" />
</div>

- Vitória do Jogador 2:

</p>
<div align="center">
   <img width="450px" src="resources\player-1-win.gif" />
</div>

- Empate:

</p>
<div align="center">
   <img width="450px" src="resources\player-1-win.gif" />
</div>

- Mensagens de erro, click fora ou na linha do tabuleiro:

</p>
<div align="center">
   <img width="450px" src="resources\player-1-win.gif" />
</div>



Com este projeto, foi demonstrado a aplicação prática de conceitos de programação e integração de hardware e software. O Jogo da Velha implementado na placa DE1-SoC oferece uma maneira divertida e educativa de explorar as capacidades de programação e desenvolvimento de sistemas embarcados e ajuda na melhor compreensão da arquitetura de um computador.

## License

Released under [MIT][license-url] by:

- [Gerson Ferreira dos Anjos Neto][@gersonfaneto]
- [Nathielle Cerqueira Alves][@NathielleA]
- [Yasmin Cordeiro de Souza Meira][@yasmincsme]

## Referências
- [Datasheet da Placa DE1-SoC](https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&CategoryNo=205&No=836&PartNo=1#contents)

- https://periodicos.unesc.net/ojs/index.php/sulcomp/article/view/304/311

- https://www.fct.unesp.br/Home/Departamentos/Cartografia/uel---sistemas_operacionais_sistemas_linux.

- https://www.kernel.org/doc/html/v4.18/input/index.html

- [Using Linux* on DE-series Board. For Quartus® Prime 21.1](https://github.com/fpgacademy/Tutorials/releases/download/v21.1/Linux_with_ARM_A9.pdf)

- https://learnxinyminutes.com/docs/make

<!-- prettier-ignore-start -->

<!-- NOTE: Links... -->

[@gersonfaneto]: https://github.com/gersonfaneto
[@NathielleA]: https://github.com/NathielleA
[@yasmincsme]: https://github.com/yasmincsme

[license-url]: https://github.com/gersonfaneto/TicTacToe/blob/main/LICENSE

<!-- prettier-ignore-end -->
