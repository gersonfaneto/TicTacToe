## M.I. Sistemas Digitais - Problema 1

### Tabuleiro

<!-- prettier-ignore-start -->
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
       
<!-- prettier-ignore-end -->

### Mouse

- O arquivo `/dev/input/mice` registra os eventos de todos os dispositivos tipos "mouse".

- A codificação é feita em 3 bytes:

  - Byte 0 :: Flags que representam o estado atual do dispositivo. O quinto bit (esquerda → direita) é
    fixo em 1 e os 3 últimos bits representam, respectivamente, os botões esquerdo, direito e do meio
    do mouse.

  - Bytes 1 e 2 :: Coeficiente de deslocamento nos eixos X e Y, respectivamente, variando entre -127 a 127.
