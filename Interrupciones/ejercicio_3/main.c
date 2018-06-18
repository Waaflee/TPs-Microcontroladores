// Realizar un programa en ATmega328P con salida en PB5, y dos entradas en PB3 y
// PB4. El autómata tendrá dos estados, Activado y Desactivado. Inicialmente
// estará Activado, y en este estado deberá producir una señal de 1Hz, Duty
// Cycle 70% en PB5. Al pulsar PB4 debe pasar a modo Desactivado, y en tal
// estado poner la salida en 0. Al pulsar PB3 debe volver al estado Activado y
// generar la señal de 1Hz.

#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/interrupts.h"
#include <util/delay.h>
void intHandler();
enum estados { activado, desactivado };
volatile enum estados estado = activado;

int main(void) {

  setPin(13, OUTPUT);
  setPin(12, INPUT);
  setPin(11, INPUT);

  setPCInt(12);
  setPCInt(11);
  sei();
  pinOff(13);

  while (1) {
    switch (estado) {
    case activado:
      pinOn(13);
      _delay_ms(700);
      pinOff(13);
      _delay_ms(300);
      break;
    case desactivado:
      pinOff(13);
      break;
    default:
      estado = activado;
      break;
    }
  }
  return 0;
}
void intHandler() {
  _delay_ms(10);
  if (readDPin(12)) {
    estado = desactivado;
  } else if (readDPin(11)) {
    estado = activado;
  }
};

ISR(PCINT0_vect) { intHandler(); };
