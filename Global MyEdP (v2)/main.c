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
void int0handler();
volatile enum states estado =
    disabled; // estado, variable global. Es la cargamos en memoria para que la
              // interrupcion INT0 pueda utilizarla

int main(void) {
  stdin = stdout = &uart_io;
  UART_init(checkData);

  setPin(ENA, OUTPUT); // PIN de habilitación
  setPin(9, OUTPUT);   // PIN de salida OCR1A
  setPin(2, INPUT);    // Pin INT0 para las interrupciones
  setPin(13, OUTPUT); // Condirmación visual de que sucedio la interrupcion INT0

  sei(); // Habilitación global de interrupciones
  pwm = newPWM1();
  pwm.regist(&pwm);
  // seteo por defecto del TIMER1 en modo fast pwm con prescaler x8
  pwm.freq(10 khz); // ICR1 inicial = 200 (16Mhz/8 = 2Mhz, -> 2000 Khz / {200} =
                    // 10 Khz)

  setINT(2, RISING,
         int0handler); // habilitacion de interrupcion INT0 por flanco de
                       // subida, y asignacion de ISR handler

  while (1) {
    switch (estado) {
    case enabled:
      break;
    case disabled:
      break;
    case error:
      printf(":ERR\r");
      cli();
      return 1;
      break;
    default:
      estado = disabled;
      break;
    }
  }
  return 0;
}

void int0handler() {
  _delay_ms(15);
  if (readDPin(2)) {
    togglePin(13);
    estado = error; // en caso de sobrecarga detectamos el error y cambiamos el
                    // estado de la maquina
  }
}
