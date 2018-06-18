// Realizar un oscilador con semiperíodo ajustable por consignas por UART de
// tipo “:Txx”, con xx tiempo en décimas de segundo de 1 a 99 ((0,1 9,9
// segundos). La recepción de datos no debe detener el funcionamiento del
// oscilador. while(1) { S=1;_delay_ms(T);S=0;_delay_ms(T);} //S pin de salida

#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

void delay_ds(uint8_t T);

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdout = stdin = &uart_io;
  UART_init(checkData);
  sei();
  T = 10;

  setPin(13, OUTPUT);

  while (1) {
    pinOn(13);
    delay_ds(T);
    pinOff(13);
    delay_ds(T);
  }
  return 0;
}

void delay_ds(uint8_t T) {
  for (size_t i = 0; i < T; i++) {
    _delay_ms(100);
  }
}
