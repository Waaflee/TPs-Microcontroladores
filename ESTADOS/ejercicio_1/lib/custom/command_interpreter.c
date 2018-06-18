#include "command_interpreter.h"

void checkData(char data[]) {
  switch (data[1]) {
  case 'W':
    switch (data[2]) {
    case '0':
      estado = desactivado;
      TCCR0B = 0;
      break;
    case '1':
      estado = activado;
      setTimer0(x8);
      break;
    default:
      printf("ingrese 0 para desabilitar o 1 para habilitar\n");
      break;
    }
    break;
  case 'H':
    switch (estado) {
    case activado:
      Conditional_PaPsInit(8);
      break;
    case desactivado:
      printf("El motor esta desactivado, no se puede referenciar\n");
      printf("Para habilitarlo ingrese :W1\n");
      break;
    }
    break;
  default:
    printf("Command not found\n");
    break;
  }
}

void Conditional_PaPsInit(uint16_t speed) {
  switch (estado) {
  case activado:
    PAPsInit(speed);
    break;
  case desactivado:
    break;
  default:
    break;
  }
}
