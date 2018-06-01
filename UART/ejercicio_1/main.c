#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/A4988_interrups.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/uart.h"
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdout = stdin = &uart_io;
  UARTcount = 0;
  UART_init();

  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 1};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAP1.ID = 0;
  PAParray[0] = &PAP1;

  DriveArray STPArray2 = {5, 6, 7, 0, 0, 0, 1.8, 1};
  pololu STP2 = newPololuFA(STPArray2);
  STEPPER PAP2;
  PAP2.motor = &STP2;
  PAP2.enabled = 0;
  PAP2.ID = 1;
  PAParray[1] = &PAP2;

  setPCInt(9);
  setPCInt(8);

  setTimer0(T0_PRESCALER_8);
  // sei() incluida en el setTimer0 dado que si utilizamos el timere
  // inherentemente vamos a querer las interrupciones.

  PAPsInit(8);

  setPin(13, OUTPUT);
  while (1) {
    /* code */
    togglePin(13);
    _delay_ms(5000);
  }
  return 0;
}

ISR(PCINT0_vect) {
  _delay_ms(15);
  if (!readDPin(8)) {
    raceEnd(0, START);
  }
  if (readDPin(9)) {
    raceEnd(0, END);
  }
}
