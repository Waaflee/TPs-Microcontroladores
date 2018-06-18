// Realizar un variador de velocidad PWM a lazo abierto para un motor DC,
// que acepte comando del tipo :Dnnn, nnn de 0 a 100%.

#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "lib/AVRDuino/interrupts.h"
#include "lib/AVRDuino/pwm.h"
#include "lib/AVRDuino/timers.h"
#include "lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <avr/interrupt.h>
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdin = stdout = &uart_io;
  UART_init(checkData);
  setPin(9, OUTPUT); // PIN de salida OCR1A

  sei(); // Habilitación global de interrupciones
  pwm = newPWM1();
  pwm.regist(&pwm);
  // seteo por defecto del TIMER1 en modo fast pwm con prescaler x8
  pwm.freq(10 khz); // ICR1 inicial = 200 (16Mhz/8 = 2Mhz, -> 2000 Khz / {200} =
                    // 10 Khz)

  while (1) {
  }
  return 0;
}
