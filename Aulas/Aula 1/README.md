# Aula 1 - O que é um microcontrolador, o que ele faz e como ele faz?
A aula foi iniciada com a seguinte pergunta:

## **"O que é um Arduino?"**

Dentre as respostas, aquela que mais se destaca é aquela que descreve a plataforma como um **microcontrolador**. Isso se dá pela própria procura dos kits de desenvolvimento ao invés do microcontrolador em si, visto que os primeiros são mais comerciais e procurados em relação aos segundos. No entanto, o curso tem justamente o intuito de apresentar esses conceitos e diferenciar o que é cada coisa.

Com isso em mente, abrimos o datasheet do Arduino Uno R3 e o ATmega328p, demonstrando a utilidade do kit e o que ele dispunha, demonstrando sua utilidade.

## Blink Led
Com isso, apresentado o Arduino, partimos para um código simples de Blink Led, basicamente o "Hello World!" dos microcontroladores. A abordagem consistia em demonstrar a camada de abstração que o Arduino propunha, como as funções setup(), loop(), pinMode(), delay() e digitalWrite(). 

Após essa pequena introdução da estrutura e funções básicas da aplicação, miramos em destrinchar o que cada função faz em seu cerne. Com isso, nos apoiamos no datasheet do ATmega328p e utilizando bitshifting e bitwise, sendo possível concluir a aplicação.

**Obs**.: Ao invés de usar um timer para fazer o delay, preferi usar o nop como bloqueante para não ter que entrar na discussão dos temporizadores.

## Palavras chave
- Microcontrolador
- Kit de desenvolvimento
- Registradores
- Bitshift
- Bitwise
- Arduino
- STM32
