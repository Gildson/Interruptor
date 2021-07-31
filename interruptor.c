#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//global variables
volatile int cont = 0;

//interruption by comparison
ISR(TIMER1_COMPA_vect){
  PORTD ^= 0b00100000;
  cont++;
}

int main(){
  
  //counts
  TCCR1A = 0b00000000;
  //o bit 3 habilita o CTC
  TCCR1B = 0b00001101;
  
  OCR1A = 15624;//(16M/(prescaler*ts))-1 onde,
  //ts is the time that every interruption is call

  //Enable the COMPA
  TIMSK1 = 0b00000010;
  
  //Enable global interruption
  sei();
  
  Serial.begin(9600);

  while(1){
    //print in the Monitor serial
    Serial.println(cont);
    _delay_ms(1000);
  }
}
