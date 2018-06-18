// Realizar un control PULSO_DIRECCIÓN de un driver de motor PaP para posicionar
// un eje lineal que cuenta además con un sensor de fin de carrera para
// referenciar el origen. El controlador debe seguir los estados típicos en ejes
// servocontrolados. Inicialmente debe estar en estado Desactivado, con /ENABLE
// =1 Un comando :W1 lo lleva al estado Activado , (/ENABLE=0). Un comando :W0
// lo llevará nuevamente al estado Reposo si fuera necesario. Una vez activado,
// el eje debe ser referenciado. Para esto existe una maniobra de “homing”, la
// más común realizar un retroceso a velocidad moderada, detener al detectar un
// cambio de estado en un Final de Carrera FC (sensor óptico, inductivo etc),
// esperar unos 100 ms y avanzar a velocidad muy reducida hasta que el FC vuelve
// a cambiar de estado. Este punto es habitualmente la posición 0, y el eje
// queda Referenciado. Un comando :H iniciará la maniobra de homing, que
// solamente se podrá ejecutar si el eje está activado.
#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/interrupts.h"
#include "./lib/AVRDuino/timers.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);
volatile enum estados estado = desactivado;

void findecarrera1();
void findecarrera2();

int main(void) {

  stdout = stdin = &uart_io;

  UART_init(checkData);

  DriveArray STPArray1 = {8, 9, 10, 0, 0, 0, 1.8, 3};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAParray[0] = &PAP1;

  setPCInt(6);
  setPCInt(7);

  sei();

  setPin(13, OUTPUT);
  printf("Setup complete\n");

  while (1) {
    switch (estado) {
    case activado:
      pinOff(PAParray[0]->motor->enable);
      break;
    case desactivado:
      pinOn(PAParray[0]->motor->enable);
      break;
    default:
      estado = desactivado;
      break;
    }
  }
  return 0;
}

void findecarrera1() {
  if (readDPin(2)) {
    togglePin(13);
    raceEnd(0, START);
  };
}
void findecarrera2() {
  if (readDPin(3)) {
    togglePin(13);
    raceEnd(0, END);
  };
};

ISR(PCINT2_vect) {
  _delay_ms(15);
  findecarrera1();
  findecarrera2();
};
