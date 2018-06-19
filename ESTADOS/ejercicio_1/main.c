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
#include "./lib/AVRDuino/pwm.h"
#include "./lib/AVRDuino/timers.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);
volatile enum estados estado = desactivado;
struct pwm1 pwm;
void findecarrera1();
void findecarrera2();
void motor();
int main(void) {

  stdout = stdin = &uart_io;

  UART_init(checkData);
  setPin(11, OUTPUT);
  DriveArray STPArray1 = {2, 3, 4, 0, 5, 0, 1.8, 10};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAParray[0] = &PAP1;

  // struct timer1 timer = newTimer1();
  setTimer0(x8);
  // timer.prescaler = x8;
  // timer.interrupts = match_A;
  // timer.MAHandler = motor;
  // timer.regist(&timer);
  setPin(5, OUTPUT);
  // pwm = newPWM1();
  // pwm.regist(&pwm);
  // pwm.dutyA(0);
  // pwm.freq(10);

  setPCInt(6);
  setPCInt(12);
  // T1_MBHandler = motor;

  sei();

  setPin(13, OUTPUT);

  while (1) {
    switch (estado) {
    case activado:
      pinOff(PAParray[0]->motor->enable);
      break;
    case desactivado:
      pinOn(PAParray[0]->motor->enable);
      break;
    case homing:
      break;
    case posicionado:
      break;
    default:
      estado = desactivado;
      break;
    }
  }
  return 0;
}

void findecarrera1() {
  if (readDPin(12)) {
    togglePin(13);
    raceEnd(0, START);
  };
}
void findecarrera2() {
  if (readDPin(6)) {
    togglePin(13);
    raceEnd(0, END);
  };
};

ISR(PCINT2_vect) {
  _delay_ms(10);
  findecarrera2();
};

ISR(PCINT0_vect) {
  _delay_ms(10);
  findecarrera1();
};

void motor() {
  if (PAParray[0]->motor->stepps-- > 0) {
    pwm.dutyA(pt100(95));

  } else {
    pwm.dutyA(0);
    PAParray[0]->enabled = FALSE;
    pinOn(PAParray[0]->motor->enable);
  }
}
// ISR(TIMER1_COMPA_vect) { motor(); };
