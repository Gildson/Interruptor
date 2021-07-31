#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//variável global
volatile int cont = 0;

//interrupção de comparação
ISR(TIMER1_COMPA_vect){
  PORTD ^= 0b00100000;
  cont++;
}

int main(){
  
  //contadores
  TCCR1A = 0b00000000;
  //o bit 3 habilita o CTC
  TCCR1B = 0b00001101;
  
  OCR1A = 15624;//(16M/(prescaler*ts))-1 onde,
  //ts é o tempo que eu quero que cada interrupção seja chamada.

  //Habilito o overflow
  TIMSK1 = 0b00000010;
  
  //habilita a interrupção global
  sei();
  
  Serial.begin(9600);

  while(1){
    //imprime no Monitor serial
    Serial.println(cont);
    _delay_ms(1000);
  }
}