#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/A4988_interrups.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/uart.h"
#include <util/delay.h>
#define FALSE 0
#define TRUE 1

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);
volatile char uData;

#define NUM_STEPPERS 1
volatile int count[NUM_STEPPERS];
volatile int delay;
STEPPER *PAParray[NUM_STEPPERS];

int main(void) {
  stdout = stdin = &uart_io;
  UART_init();

  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 30};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAParray[0] = &PAP1;

  setPCInt(9);
  setPCInt(8);

  setTimer0(T0_PRESCALER_1024);
  // sei();

  setSpeed(1200, &PAP1);
  rotateNSteps(1500, &PAP1, FORWARD);

  setPin(13, OUTPUT);
  char message;
  int i = 0;
  while (1) {
    /* code */
    togglePin(13);
    _delay_ms(5000);
    printf("%s %d\n", "Holii\r", i++);
  }
  return 0;
}

// Timer0 overflow interruption, checks enabled steppers setep's left and
// moves them accordingly until there is no one left.
ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {
  // increases each stepper's count assigned variable
  for (uint8_t i = 0; i < NUM_STEPPERS; i++) {
    count[i]++;
    // check if current stepper is enabled
    if (PAParray[i]->enabled) {
      // check if current stepper has any steps left (checking could be merged
      // with above's conditional but I think this way is more readable).
      if (PAParray[i]->motor->stepps > 0) {
        // Calculates amount of overflows until next stepp accordingly to
        // current stepper's RPM
        delay = (60.0 / (float)PAParray[i]->motor->RPM) * 61.0;
        // in order to emulate a square shaped wave, the stepper's step pin will
        // turn on in the middle of the dealy and turn off again at it's end.
        if (count[i] >= delay / 2) {
          pinOn(PAParray[i]->motor->step);
          if (count[i] >= delay) {
            PAParray[i]->motor->stepps--;
            pinOff(PAParray[i]->motor->step);
            count[i] = 0;
            // Checks current direction and upgrades position accordingly
            if (PAParray[i]->motor->direction) {
              PAParray[i]->motor->location++;
            } else {
              PAParray[i]->motor->location--;
            }
            // if there are not stepps left the current stepper will be
            // disabled.
            if (PAParray[i]->motor->stepps == 0) {
              PAParray[i]->enabled = FALSE;
              pinOff(PAParray[i]->motor->enable);
            }
          }
        }
      }
    }
  }
}

ISR(PCINT0_vect) {
  _delay_ms(10);
  if (readDPin(8) || readDPin(9)) {
    stopPololu(PAParray[0]);
    rotateNSteps(5, PAParray[0], !PAParray[0]->motor->direction);
  }
}

ISR(USART_RX_vect) {
  togglePin(3);
  // char ReceivedByte;
  // ReceivedByte =
  //     UDR0; // Fetch the recieved byte value into the variable "ByteReceived"
  // UDR0 = ReceivedByte;
  // uData = uread(&uart_io);
  printf("%s", "Recibido");
  // printf("%c\n", uData);
  // char Dato;
  // Dato = uread(&uart_io);
  // switch (Dato) {
  // case 0:
  //   togglePin(3);
  //   break;
  // default:
  //   togglePin(3);
  // }
}
