// #define POLOLU
#define NUM_STEPPERS 1

// volatile int count[NUM_STEPPERS];
// volatile int delay;
// STEPPER *PAParray[NUM_STEPPERS];

#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/A4988_interrups.h"
#include "./lib/AVRDuino/core.h"
#include <util/delay.h>
#define FALSE 0
#define TRUE 1

int main(void) {
  // DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 30};
  // pololu STP1 = newPololuFA(STPArray1);
  // STEPPER PAP1;
  // PAP1.motor = &STP1;
  // PAP1.enabled = 0;
  // PAParray[0] = &PAP1;

  setPin(13, OUTPUT);

  // Pausado hasta aprender a hacer PWM
  while (1) {
    /* code */
    togglePin(13);
    _delay_ms(500);
  }
}
