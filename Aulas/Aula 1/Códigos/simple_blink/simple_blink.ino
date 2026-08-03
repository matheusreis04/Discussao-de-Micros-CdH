/*
Definição -> espaço de código.
Definimos uma macro, ou seja, onde o pré-processador ler "LED" ele vai trocar pelo valor 13. 
Como sugestão, vejam outras macros que podem ser criadas com #define.
*/
#define LED 13

/*
Para entendermos ambos setup() e loop(), vejamos primeiro o que elas fazem:
- setup() roda uma única vez -> sugerido para configurar pinos (entrada, saída, UART, SPI e I2C).
- loop() roda ininterruptamente -> sugerido para rotina da sua aplicação.

Portanto, podemos imaginar que temos o seguinte código sendo executado por debaixo dos panos:

int main(void){
    ...
    setup();
  
    while(1){
       loop();
       ...
    }
}

- Por que dizemos sugerido?
Nada lhe impede de usar pinMode() no loop() para configurar os pinos e também nada lhe impede
de adicionar um laço no próprio setup() fazendo sua rotina retida completamente nele.

- Então por que organizar dessa forma?
É a maneira lógica de organizar as coisas, sendo possível dessa forma, demonstrar para o estudante
(é preciso lembrar que o Arduino nasceu como uma iniciativa educacional) onde deve ficar suas 
configurações e aonde devem ficar suas rotinas. É válido comparar com o próprio código gerado pelo 
CubeMX da ST, em que os códigos são organizados de maneira semelhantes ao codigo acima, apenas 
sem dispor das abstrações setup() e loop().

Dito isso, analisemos o código passo a passo:
*/


void setup(){
    // Setamos o LED como saída pois iremos seu nível lógico futuramente
    pinMode(LED, OUTPUT); // Aconselho fortemente sempre consultar a documentação de tudo com o que
                          // você trabalha: 
                          // https://docs.arduino.cc/language-reference/pt/en/functions/digital-io/pinMode/
}

void loop(){
    // Mantemos o LED em valor alto -> Led do usuário ligado
    digitalWrite(LED, HIGH); // https://docs.arduino.cc/language-reference/pt/fun%C3%A7%C3%B5es/digital-io/digitalwrite/
    
    // Colocamos o sistema em espera por 1 segundo inteiro, sem fazer mais nada.
    delay(1000); // https://docs.arduino.cc/language-reference/pt/en/functions/time/delay/

    // Mantemos o LED em valor baixo -> Led do usuário desligado
    digitalWrite(LED, LOW);

    // Esperamos mais um segundo esperando que ele retorne para o início do laço, ligando o LED novamente
    // e criando o nosso blink led!
    delay(1000);
}