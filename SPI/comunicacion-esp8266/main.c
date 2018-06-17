#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/uart.h"
#include <stdio.h>
#include <util/delay.h>

void commads(char data[]);

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
  SPDR = c;
  while (!(SPSR & (1 << SPIF))) {
  };
  return 0;
};

int spiread(FILE *stream) {
  while (!(SPSR & (1 << SPIF))) {
  };
  return SPDR;
};

FILE spi_io = FDEV_SETUP_STREAM(spiecho, spiread, _FDEV_SETUP_RW);
FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {

  stdout = stdin = &uart_io;
  UARTInit(commads);
  setPin(10, OUTPUT);
  while (1) {

    SPInit(master, x16); // baudrate = 1000000
    for (uint16_t i = 0; i < 4096; i++) {
      fprintf(&spi_io, "%d", i);
      _delay_us(20);
    }
  }
  return 0;
}

void commads(char data[]){

};
