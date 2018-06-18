// EJ01 : Realizar Blink de un led de 1 segundo con Timer 1, en una ISR
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/timers.h"
#include <util/delay.h>

void blink();
volatile uint8_t count;
volatile uint8_t delay;

int main(void) {
  count = 0;
  delay = 30;
  struct timer1 timer = newTimer1();
  timer.interrupts = overflow;
  timer.prescaler = x8;
  timer.OverflowHandler = blink;
  timer.regist(&timer);

  // TCCR1B = _BV(CS01);
  // TIMSK1 = _BV(TOIE1);
  // TCNT1 = 0;
  // Es lo mismo que arriba

  sei();

  setPin(13, OUTPUT);
  while (1) {
  }
  return 0;
}

void blink() {
  count++;
  if (count >= delay) {
    togglePin(13);
    count = 0;
    delay = delay == 30 ? 31 : 30;
  }
};
