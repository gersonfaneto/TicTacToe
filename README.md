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
## License

Released under [MIT][license-url] by:

- [Gerson Ferreira dos Anjos Neto][@gersonfaneto]
- [Nathielle Cerqueira Alves][@NathielleA]
- [Yasmin Cordeiro de Souza Meira][@yasmincsme]

## Referências
- [Site da Placa](https://www.terasic.com.tw/cgi-bin/page/archive.pl?Language=English&CategoryNo=205&No=836&PartNo=1#contents)

<!-- prettier-ignore-start -->

<!-- NOTE: Links... -->

[@gersonfaneto]: https://github.com/gersonfaneto
[@NathielleA]: https://github.com/NathielleA
[@yasmincsme]: https://github.com/yasmincsme

[license-url]: https://github.com/gersonfaneto/TicTacToe/blob/main/LICENSE

<!-- prettier-ignore-end -->
