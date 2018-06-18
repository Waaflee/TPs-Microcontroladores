// EJ04: Generar en OC1A una onda senoidal de 50Hz con PWM a 10kHz.
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/pwm.h"
#include "./lib/AVRDuino/timers.h"
#include <util/delay.h>
// DELAY = 100 para tener 50Hz y 1000 para tener 5HZ
#define DELAY 1000

int main(void) {
  setPin(9, OUTPUT);  // PIN de salida OCR1A
  setPin(10, OUTPUT); // PIN de salida OCR1A
  setPin(13, OUTPUT);
  // sei(); // Habilitación global de interrupciones
  // struct timer1 timer = newTimer1();
  // timer.prescaler = x1;
  // timer.interrupts = timer.regist(&timer);

  struct pwm1 pwm = newPWM1();
  pwm.regist(&pwm);
  pwm.freq(10 khz);
  pwm.dutyA(0);
  pwm.dutyB(0);

  while (1) {
    for (size_t i = 0; i < 100; i++) {
      pwm.dutyA(i);
      pwm.dutyB(100 - i);
      _delay_us(DELAY);
    }
    for (size_t i = 100; i > 0; i--) {
      pwm.dutyA(i);
      pwm.dutyB(100 - i);
      _delay_us(DELAY);
    }
    togglePin(13);
  }
  return 0;
}
