// Nessa biblioteca que adicionamos já tem uma série de macros que correspondem
// ao endereçamento dos pinos.
// Ele será utilizado para que possamos fazer a configuração direta dos registradores
// que armazenam os estados e configurações dos pinos usando a mesma nomenclatura descrita
// no datasheet do ATmega328P: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf 
#include <avr/io.h>

// Assim como propomos no código simplificado (simple_blink):
int main(void) {
    // Configuramos o pino 13 (Sexto bit de um registrador de 1 byte) como sendo 1
    // usando bitshifting e bitwise. Vejamos:
    // 1 << DDB5, ou seja, 1 << 5 = 00100000
    // 
    // Sendo xxxxxxxx o estado atual do DDRB (Data Direction Register B, ou Registrador
    // de Direção de Dados da porta B), ao aplicarmos a operação or bit a bit - representada 
    // por "|" em C - saberemos que, ao final, DDRB é igual a xx1xxxxx.
    // 
    // Mas por que tanta certeza?
    // Vejamos a tabela-verdade do OR:
    //   +---+---+-------+
    //   | A | B | A OR B|
    //   +---+---+-------+
    //   | 0 | 0 |   0   |   -> Dessa tabela, percebemos que sempre quando B = 1, A OR B = 1. 
    //   | 0 | 1 |   1   |      
    //   | 1 | 0 |   1   |
    //   | 1 | 1 |   1   |
    //   +---+---+-------+
    // Ou seja, garantimos que o bit que queremos setar como 1 é 1 pela propriedade da tabela
    // da operação OR, utilizando-se do bitshifting para selecionar aquele bit que queremos alterar.
    // 
    // Caso fique confuso, podemos nos utilizar da aritmética booleana, em que todo valor diferente
    // de 0 é 1 e OR pode ser abstraído como uma soma. Dito isso:
    // A + 1 = 1 ou 2, visto que A pode assumir 0 ou 1. Ou seja, sabermos que A + 1 = 1 independente
    // do valor de A, seguindo a aritmética booleana.
    // Nesses casos em que o valor de um sinal não é importante, representamos com um x, logo:
    // x + 1 = 1.
    //
    // Ou seja, novamente provamos, literalmente por A + B, essa propriedade do OR e como ela é
    // importante para configurarmos o pino que queremos, mas surge a pergunta:
    // E os outros pinos?
    // 
    // Analisemos:
    // Logicamente, usando a tabela-verdade, percebemos que sempre que operamos um sinal com B = 0,
    // teremos o sinal A como resultado, sendo ele A = 1 ou A = 0.
    // Ademais, aritmeticamente, A + 0 = A, sem perda de generalidade, provando a lógica anterior.
    // 
    // Isso nos permite alterar o bit de interesse sem interferir na configuração dos demais. 
    DDRB |= (1 << DDB5);

    while (1) {
        // O PORTB, segundo o datasheet, se refere ao Port B Data Register, ou Registrador de dados
        // da Porta B. Enquanto DDRB dita a direção do dado nesse pino, esse registrador define,
        // basicamente, o que acontece com a eletricidade no pino.
        // 
        // - Como assim?
        // Vejamos no nosso caso: O pino 13 foi configurado como uma saída e, a partir de agora, nós 
        // controlamos o que vai sair por esse pino. O registrador responsável por isso é justamente
        // o PORTB. Sendo 0 e 1 os respectivos sinais alto e baixo que queremos conferir àquele pino.
        // E no caso contrário: O pino 13 foi configurado como uma entrada, portanto, a partir de agora
        // nós devemos ditar como a energia vai entrar por aquele pino.
        // 
        // A discussão de "como entra no pino" nos leva diretamente à dois conceitos:
        // - Alta impedância: Podemos abstrair dizendo que "é como se o pino não estivesse conectado a nada".
        // Ou seja, quando um componente conectado não envia um sinal baixo ou alto, aquele pino está 
        // simplesmente flutuando (maneira técnica de dizer desconectado). Vamos passar a representar esse 
        // sinal como Z pois ele tem importância para várias outras aplicações.
        // 
        // - Resistor Pull-up: Caso não quisermos conferir a propriedade de alta impedância a um pino, nós
        // conectamos fisicamente esse pino aos 5V (que corresponde ao nível alto) passando por um resistor.
        // Ou seja, mesmo que o componente conectado não esteja enviando nada, o pino vai estar recebendo
        // um valor alto, diferente da flutuação que discutimos. Caso se depare com o termo Pull-down, considere
        // apenas que o fio foi conectado ao terra (nível lógico baixo).
        //
        // Voltando ao nosso caso, só nos basta refletir porque utilizamos XOR(exclusive OR), representado
        // como "^", ao invés do OR.
        //
        // Nos basearemos na tabela do XOR:
        //   +---+---+--------+
        //   | A | B | A XOR B|
        //   +---+---+--------+
        //   | 0 | 0 |   0    |
        //   | 0 | 1 |   1    |
        //   | 1 | 0 |   1    |
        //   | 1 | 1 |   0    |
        //   +---+---+--------+
        // Perceba que, aonde operamos com B = 0, a tabela sempre nos retorna o valor de A, enquanto isso, quando
        // operamos com B = 1, obtemos o valor invertido do sinal A. Portanto:
        // - o sinal que queremos configurar, inverte (A ^ 1 = ~A);
        // - o sinal que não queremos mexer, permanece (A ^ 0 = A).
        // 
        // Por que essa propriedade nos é importante nessa aplicação?
        // Aqui nos deparamos com o conceito de toggle, que não é nada além de alternar em estados opostos, ou seja,
        // quando o led estiver ligado, ao passar um segundo, ele desliga e vice-versa. Isso fará que o nosso led
        // blink assim como no código simplificado.
        PORTB ^= (1 << PORTB5);

        // Nessa linha eu não vejo necessidade de nos aprofundarmos, pois, basicamente, estamos programando em
        // assembly, o que não é o intuito da aula. É válido citar também que nem mesmo o próprio arduino
        // faz o delay dessa forma. O intuito aqui é ilustrar o que o delay (função bloqueante)faz e apresentar
        // um pouco da linguagem da máquina, podendo discutir também sobre o clock e seus ciclos.
          
        for (uint32_t i = 0; i < 2285714UL; i++) {
        __asm__ __volatile__ ("nop\n\t");
        }
    }

    return 0;
}