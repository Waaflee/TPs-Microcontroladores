// Ejercicio 4 : Realizar un programa en ATmega328P con tres salidas
//     : PB5,
//       PB2 y PB1,
//       y 2 entradas en PB3 / PCINT3 y en PD2 / PCINT18 /
//           INT0.Cada salida será manejada por una tarea distinta
//               .La salida PB5 será manejada en la tarea principal y oscilará
//                   permanentemente a 1 Hz.La salida PB2 será manejada por una
//                       rutina de servicio de interrupción del tipo
//                       PCI(Pin Change Interrupt),
//       que producirá 10 ciclos a
//       2 Hz.La salida PB1 será manejada por una rutina de servicio de
//       interrupción del tipo External INT,
//       que producirá 15 ciclos a
//       2 Hz.Esta interrupción deberá tendrá prioridad sobre la anterior.
////////////////////////////////////////////////////////////////////////////////

#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/A4988_interrups.h"
#include "./lib/AVRDuino/core.h"
#include <util/delay.h>
#define FALSE 0
#define TRUE 1

int main(void) {
  setPin(2, INPUT);
  setPin(11, INPUT);

  setPin(9, OUTPUT);
  setPin(10, OUTPUT);
  setPin(13, OUTPUT);

  pinOff(9);
  pinOff(10);
  pinOff(13);

  setPCInt(11);

  EICRA |= _BV(ISC01);
  EIMSK |= _BV(INT0); // ENABLE INT0

  sei();
  while (1) {
    /* code */
    togglePin(13);
    _delay_ms(500);
  }
}

ISR(PCINT0_vect, ISR_NOBLOCK) {
  _delay_ms(10);
  if (readDPin(11)) {
    for (uint8_t i = 0; i < 10 + 1; i++) {
      togglePin(10);
      _delay_ms(250);
    }
  }
}
ISR(INT0_vect) {
  _delay_ms(10);
  if (readDPin(2)) {
    for (uint8_t i = 0; i < 15 + 1; i++) {
      togglePin(9);
      _delay_ms(250);
    }
  }
}
