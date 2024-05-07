## M.I. Sistemas Digitais - Problema 1

### Tabuleiro

<!-- prettier-ignore-start -->
```markdown
   ___    _          _        
  / _ \  | |        | |       
 | | | | | |        | |       
 | |_| | | |        | |       
  \___/  | |        | |       
  _____  | |  _____  | |  _____  
 |_____| | | |_____| | | |_____| 
         | |   ___   | | __  __
         | |  / _ \  | | \ \/ /
         | | | | | | | |  \  / 
         | | | |_| | | |  /  \ 
         | |  \___/  | | /_/\_\
  _____  | |  _____  | |  _____  
 |_____| | | |_____| | | |_____| 
         | |   ___   | |   ___  
         | |  / _ \  | |  / _ \ 
         | | | | | | | | | | | |
         | | | |_| | | | | |_| |
         | |  \___/  | |  \___/ 
         |_|         |_|        
  ___  
 / _ \ 
| | | |
| |_| |
 \___/ 
__  __ 
\ \/ / 
 \  /  
 /  \  
/_/\_\ 
```
<!-- prettier-ignore-end -->

### Mouse

- O arquivo `/dev/input/mice` registra os eventos de todos os dispositivos tipos "mouse".

- A codificação é feita em 3 bytes:

  - Byte 0 :: Flags que representam o estado atual do dispositivo. O quinto bit (esquerda → direita) é
    fixo em 1 e os 3 últimos bits representam, respectivamente, os botões esquerdo, direito e do meio
    do mouse.

  - Bytes 1 e 2 :: Coeficiente de deslocamento nos eixos X e Y, respectivamente, variando entre -127 a 127.

### Referências

- [Documentação do Kernel do Linux][linux-kernel-docs].

- Códigos de Escape ANSI:

  - [Wikipedia][ansi-escape-code-wiki].

  - [Resumo][ansi-escape-code-gist]

- Detecção dos eventos do mouse:

  - [Linux Today][mouse-linux-today].
  - [Stack Overflow][mouse-stack-overflow]
  - [Linux Questions][mouse-linux-questions]

<!-- prettier-ignore-start -->

<!-- NOTE: Links... -->

[linux-kernel-docs]: https://www.kernel.org/doc/html/v4.12/index.html

[ansi-escape-code-wiki]: https://en.wikipedia.org/wiki/ANSI_escape_code
[ansi-escape-code-gist]: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

[mouse-linux-today]: https://www.linuxtoday.com/blog/linux-mouse-drivers/
[mouse-stack-overflow]: https://stackoverflow.com/questions/20595716/control-mouse-by-writing-to-dev-input-mice
[mouse-linux-questions]: https://www.linuxquestions.org/questions/linux-hardware-18/reading-mouse-movement-451908/

<!-- prettier-ignore-end -->