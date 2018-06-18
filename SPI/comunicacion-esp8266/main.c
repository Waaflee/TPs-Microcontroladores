#include "./lib/AVRDuino/core.h"
#include <stdio.h>
#include <util/delay.h>

void sendToDAC(uint16_t valor);
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

int spiecho(int c) {
  SPDR = c;
  while (!(SPSR & (1 << SPIF))) {
  };
  return 0;
};

int spiread() {
  while (!(SPSR & (1 << SPIF))) {
  };
  return SPDR;
};

int main(void) {

  setPin(10, OUTPUT);
  while (1) {

    SPInit(master, x16); // baudrate = 1000000

    for (uint16_t i = 0; i < 4096; i++) {
      sendToDAC(i);
    }
  }
  return 0;
}

void sendToDAC(uint16_t valor) {
  uint8_t aux;
  pinOff(SS); // Habilita MCP4821
  aux = 0b01110000 |
        ((valor & 0xF00) >> 8);  // 4 bits de control y b11 a b8 de valor
  spiecho(aux);                  // transmite por SPI
  aux = (uint8_t)(valor & 0xFF); // b7 a b0 de valor
  spiecho(aux);                  // transmite por SPI
  _delay_us(1);
  pinOn(SS); // deshabilita MCP4821
  _delay_us(1);
  pinOff(8);    //
  _delay_us(2); // Pulso invertido en LDA de MCP4821
  pinOn(8);     //
}
