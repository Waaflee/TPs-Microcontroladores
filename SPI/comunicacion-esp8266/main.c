// #include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
// #include "./lib/AVRDuino/uart.h"
// #include "lib/custom/command_interpreter.h"
#include <stdio.h>
#include <util/delay.h>
// FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

#define SS 10
enum SPI_prescaler {
  x4 = 0,
  x16 = _BV(SPR0),
  x64 = _BV(SPR1),
  x128 = _BV(SPR1) | _BV(SPR0)
};
enum SPI_mode { slave = 0, master = _BV(MSTR) };

void SPInit(enum SPI_mode mode, enum SPI_prescaler PS) {
  // Set MOSI and SCK output, all others input
  DDRB = (1 << DDB3) | (1 << DDB5);
  // Enable SPI, Master, set clock rate
  SPCR = (1 << SPE) | mode | PS;
}

int spiecho(char c, FILE *stream) {
  pinOn(SS);
  SPDR = c;
  while (!(SPSR & (1 << SPIF))) {
  };
  return 0;
  pinOff(SS);
};
int spiread(FILE *stream) {
  pinOn(SS);
  while (!(SPSR & (1 << SPIF))) {
  };
  return SPDR;
  pinOff(SS);
};

FILE spi_io = FDEV_SETUP_STREAM(spiecho, spiread, _FDEV_SETUP_RW);
int main(void) {
  stdout = stdin = &spi_io;

  setPin(10, OUTPUT);
  while (1) {
    SPInit(master, x16);
    printf("%s\n", "HOLIIIIIIII");
    _delay_ms(200);
  }
  return 0;
}
