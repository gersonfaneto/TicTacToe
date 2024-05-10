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
- [Documentação utilizada](#documentação-utilizada)
- [Desenvolvimento](#desenvolvimento)
  - [Conexão remota com a placa DE1-SoC](#conexão-remota-com-a-placa-de1-soc)
  - [Detectando o mouse](#detectando-o-mouse)
  - [Construção da lógica do jogo](#construção-da-lógica-do-jogo)
- [Inicializando o projeto do jogo](#inicializando-o-projeto-do-jogo)
- [Jogabilidade](#jogabilidade)
  - [Como jogar](#como-jogar)
  - [Resultados](#resultados)
- [Testes](#testes)
- [Conclusão](#conclusão) 
- [Tutor](#tutor)
- [Equipe](#equipe)
- [Referências](#referências)

## Introdução

Este documento apresenta a documentação do projeto de um Jogo da Velha desenvolvido em linguagem C para ser executado em um ambiente de terminal, em modo texto, em sistema operacional Linux. O jogo foi implementado para permitir a interação de dois jogadores, utilizando um mouse conectado a uma das portas USB do Kit de desenvolvimento DE1-SoC, para que, a partir do mouse, cada um dos dois jogadores possa selecionar as posições no tabuleiro a cada jogada. 

Além disso, como auxílio, os botões disponíveis na placa foram utilizados para funções de controle, como iniciar e parar o jogo. Na próxima seção, serão discutidos os detalhes da implementação do jogo, incluindo a estrutura do código, as funções principais e os algoritmos utilizados para controlar o fluxo do jogo e validar as jogadas dos jogadores. 

Como também será abordado o processo de conexão do mouse ao terminal utilizando mapeamento de memória e a leitura de arquivos no sistema Linux. Incluindo informações sobre como o jogo detecta e processa os movimentos do mouse para permitir que os jogadores façam suas jogadas.

Não obstante, outro ponto para esclarecimento será a utilização dos botões da placa para iniciar e parar o jogo, explicando como esses dispositivos foram integrados ao código e como são utilizados pelos jogadores durante a partida. Por fim, serão discutidos os testes e resultados obtidos do projeto, bem como os desafios encontrados durante o desenvolvimento e as respectivas soluções adotadas para superá-los.

## Hardware Utilizado

O hardware programável utilizado para o projeto foi a placa de desenvolvimento DE1-SoC, projetada em torno do FPGA System-on-Chip (SoC) da Altera. Este SoC combina núcleos Cortex-A9 dual-core com lógica programável. O sistema inclui um processador rígido (HPS) baseado em ARM, periféricos e interfaces de memória integradas ao FPGA.

![Imagem da DE1-SoC](https://www.terasic.com.tw/attachment/archive/836/image/top45_01.jpg)

### Especificações FPGA

Categoria|Especificações|
|--------|-------|
|CPU|
|GPU|
|Memória|64MB (32Mx16) SDRAM|

## Documentação utilizada

## Arquitetura

## Desenvolvimento

Iniciou-se o desenvolvimento do projeto do Jogo da Velha com uma análise detalhada dos requisitos para determinar o que seria necessário para conectar o mouse ao jogo e detectar seus movimentos pelo terminal. Como foi idealizado, cada jogada deveria ser capturada por um mouse conectado à placa DE1-SoC, o que exigiu uma abordagem cuidadosa para integrar o hardware e o software de maneira eficaz.

### Conexão remota com a placa DE1-SoC

Com relação à conexão com a placa, foi estabelecida via SSH (Secure Shell), um protocolo de rede que permite acesso remoto a sistemas Linux. Isso possibilitou o controle e monitoramento do jogo a partir de um computador externo, simplificando o processo de desenvolvimento e depuração.

O  Secure  Shell  oferece  ao  usuário  a  capacidade  de  conectar-se  remotamente  a outro computador com segurança, pois os dados utilizados na rede serão criptografados. O protocolo SSH tem como principal finalidade o login remoto, porém pode ser utilizado  como  túnel  criptográfico  para  outros  propósitos,  como  copiar  arquivos, proteção de conexões de e-mail e execução de programas remotos.

Um servidor SSH permite que vários clientes SSH conectem-se a ele. O cliente precisa conhecer o endereço IP (ou hostname) do servidor (nesse caso, o IP da placa utilizada) e a porta em que está escutando. O cliente se autentica para acessar a sessão. O processo de conexão ocorre em três etapas: o cliente envia uma solicitação de autenticação para o servidor e recebe uma chave de host. O servidor determina se o cliente pode se conectar, verificando as credenciais fornecidas. Se o cliente for autenticado e autorizado, a sessão SSH é estabelecida entre os dois hosts.

### Detectando o mouse

Para obter os eventos do mouse, exploramos o sistema de arquivos do Linux, especialmente o arquivo "mice". Esse arquivo é parte do subsistema de entrada do Linux e fornece uma interface para acessar os eventos gerados pelos dispositivos de entrada, como o mouse. Ao ler o arquivo "mice", nosso programa pode capturar informações sobre movimentos do mouse, cliques e outras interações do usuário em tempo real.

Uma das principais responsabilidades de um sistema operacional é gerenciar os dispositivos de entrada e saída (E/S). Isso inclui enviar comandos aos dispositivos, lidar com interrupções, tratar possíveis erros e fornecer uma interface para que os programas possam acessar esses dispositivos por meio de chamadas de sistema (system calls) para leitura e gravação.

O sistema de E/S do Linux segue uma abordagem semelhante à de outros sistemas UNIX. Os drivers de dispositivos são apresentados aos usuários como  arquivos regulares, a fim de abstrair o resto do sistema ou o usuário das particularidades do hardware, simplificando essa interação. Assim, o acesso a um dispositivo é feito da mesma maneira que a abertura de um arquivo. Porém, estes arquivos que fornecem acesso a um dispositivo são denominados de arquivos especiais e estão associados a um diretório que se encontra dentro de /dev (no Linux, diretórios são tratados como arquivos). Esses arquivos especiais são vinculados aos drivers de dispositivo correspondentes.

Logo, as permissões de leitura e escrita nos dispositivos são tratadas da mesma forma que nos arquivos normais. No entanto, em dispositivos como alto-falantes, apenas a escrita é permitida, enquanto em dispositivos como mouses, apenas a leitura é possível.

Com relação a essa etapa do desenvolvimento, a modularização do código foi crucial para garantir uma organização clara e eficiente. O código foi separado em funções distintas, cada uma responsável por uma parte específica do processo. Como exemplo, foram criadas funções separadas para inicializar o mouse, ler eventos do mouse e interpretar esses eventos para determinar as ações do jogador no jogo, entre outros.

### Construção da lógica do jogo

Após entender o formato das coordenadas do mouse, pudemos utilizar esses dados para construir o tabuleiro do Jogo da Velha no terminal e detectar qual quadrante foi escolhido por cada jogador. É importante notar que um único evento de hardware pode gerar múltiplos eventos de entrada, como um único movimento do mouse que pode resultar em eventos separados para movimentos nos eixos X e Y, além de eventos para pressionamento de botões.

Com respeito a seleção do quadrante pelos jogadores, foi determinado o uso de um cursor, representado pelo símbolo "@" (arroba), que é exibido pela função printf exatamente no local onde está as coordenadas do mouse no terminal. Assim é possível visualizar mais facilmente aonde está localizado o mouse e selecionar a posição no tabuleiro.

A aparência do tabuleiro, juntamente com o visual dos outros elementos do jogo, foram todos construídos a partir de caracteres de texto. Do tipo String, o tabuleiro e os outros elementos são exibidos 'printando' linha a linha de acordo com as coordenadas da janela do terminal. 

A lógica do Jogo da Velha foi implementada, seguindo as regras tradicionais do jogo, onde os jogadores alternam entre colocar suas marcações (X ou O) em células vazias do tabuleiro na tentativa de formar uma linha horizontal, vertical ou diagonal. Essa lógica foi integrada à detecção de movimentos do mouse e à aparência do tabuleiro e outros elementos do jogo no modo texto do terminal.  

Por fim, foram realizados ajustes finais para garantir que o jogo funcionasse corretamente, corrigindo quaisquer bugs ou problemas de desempenho que surgissem durante os testes.

Sendo assim, o projeto do Jogo da Velha foi concluído, sendo captados então os resultados obtidos através dos testes realizados e fornecendo uma experiência de jogo interativa e realista, onde os jogadores podem competir entre si em um ambiente de terminal.

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

O Jogo da Velha possui uma jogabilidade simples e rápida de compreender.

### Como jogar

Jogado em um tabuleiro 3x3. O jogador "X" é o primeiro a jogar e deve escolher uma célula vazia para colocar sua marca "X". Em seguida, o jogador "O" (player 2) faz sua jogada, escolhendo outra célula vazia para colocar sua marca "O". Os jogadores alternam suas jogadas até que alguém consiga formar uma linha horizontal, vertical ou diagonal com suas marcas.

Para fazer uma jogada, o jogador deve selecionar a posição desejada no tabuleiro. Nesse jogo, a seleção é feita usando o mouse conectado à placa DE1-SoC. Basta mover o cursor do mouse para a posição desejada e clicar para colocar a marca na célula selecionada.

O objetivo é conseguir três marcas iguais em linha antes do adversário. Se todas as células do tabuleiro forem preenchidas e nenhum jogador conseguir formar uma linha, o jogo termina em empate.

### Resultados



## Testes



## Conclusão 



## License

Released under [MIT][license-url] by:

- [Gerson Ferreira dos Anjos Neto][@gersonfaneto]
- [Nathielle Cerqueira Alves][@NathielleA]
- [Yasmin Cordeiro de Souza Meira][@yasmincsme]

## Referências
- [Site da Placa](https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&CategoryNo=205&No=836&PartNo=1#contents)
- https://periodicos.unesc.net/ojs/index.php/sulcomp/article/view/304/311
- https://www.fct.unesp.br/Home/Departamentos/Cartografia/uel---sistemas_operacionais_sistemas_linux.pdf

<!-- prettier-ignore-start -->

<!-- NOTE: Links... -->

[@gersonfaneto]: https://github.com/gersonfaneto
[@NathielleA]: https://github.com/NathielleA
[@yasmincsme]: https://github.com/yasmincsme

[license-url]: https://github.com/gersonfaneto/TicTacToe/blob/main/LICENSE

<!-- prettier-ignore-end -->
