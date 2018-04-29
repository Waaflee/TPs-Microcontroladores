// #define POLOLU
#define NUM_STEPPERS 1

#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/A4988_interrups.h"
#include "./lib/AVRDuino/core.h"
#include <util/delay.h>
#define FALSE 0
#define TRUE 1
#define READ 2
int main(void) {
  setPin(10, OUTPUT);
  setPin(13, OUTPUT);
  setPin(READ, INPUT);

  // PCICR = _BV(PCIE0);
  // PCMSK0 = _BV(PORTB3);
  setPCInt(READ);
  sei();

  while (1) {
    // if (readDPin(11)) {
    //   togglePin(10);
    // }
    togglePin(13);
    _delay_ms(500);
  }
}

ISR(PCINT1_vect) {
  _delay_ms(10);
  if (readDPin(READ)) {
    togglePin(10);
  }
}
