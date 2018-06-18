// Realizar un variador de velocidad PWM a lazo abierto para un motor DC,
// que acepte comando del tipo :Dnnn, nnn de 0 a 100%.
// EJ06: Idem ejercicio 3, pero a lazo cerrado (tipo P o PI), midiendo el
// período de rotación del motor con sensor y módulo Input Capture. En esta caso
// habrá una consigna de velocidad V.

#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "lib/AVRDuino/interrupts.h"
#include "lib/AVRDuino/pwm.h"
#include "lib/AVRDuino/timers.h"
#include "lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

volatile uint16_t anterior;
volatile uint16_t actual;
volatile uint16_t period;

void IC_handler(void);

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {

  anterior = 0;
  period = 0;
  stdin = stdout = &uart_io;
  UART_init(checkData);
  setPin(9, OUTPUT); // PIN de salida OCR1A
  setPin(10, OUTPUT);
  setPin(8, INPUT);

  setPin(13, OUTPUT);

  pwm = newPWM1();
  pwm.regist(&pwm);
  // seteo por defecto del TIMER1 en modo fast pwm con prescaler x8
  pwm.freq(10 khz); // ICR1 inicial = 200 (16Mhz/8 = 2Mhz, -> 2000 Khz / {200} =
  // 10 Khz)
  pwm.dutyA(pt100(5));
  struct timer1 timer = newTimer1();
  timer.prescaler = x8;
  timer.interrupts = input_capture;
  timer.inputFlank = RISING;
  timer.InputCaptureHandler = IC_handler;
  timer.regist(&timer);
  sei(); // Habilitación global de interrupciones
  while (1) {
    togglePin(13);
    // emulamos señal periodica del motor
    _delay_us(40000);
  }
  return 0;
}

void IC_handler(void) {
  // obtenemos timestamp actual
  actual = ICR1;
  // Calculamos la diferencia con la anterior
  period = actual - anterior;
  // dutycycle inversamente proporcional al periodo

  pwm.dutyA((V - period));
  printf("%u\n", (V - period));
  // resguardamos el valor de ICR1 para compararlo en la proxima interrupcion
  anterior = actual;
};
