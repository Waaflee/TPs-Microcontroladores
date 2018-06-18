#include "command_interpreter.h"

void checkData(char data[]) {
  switch (data[1]) {
  case 'W':
    switch (data[2]) {
    case '0':
      break;
    case '1':
      break;
    default:
      printf("ingrese 0 para desabilitar o 1 para habilitar\n");
      break;
    }
    break;
  case 'H':
    switch (estado) {
    case activado:
      PAPsInit(5);
      break;
    case desactivado:
      printf("El motor esta desactivado, no se puede referenciar\n");
      printf("Para habilitarlo ingrese :W1\n");
      break;
    }
    break;
  default:
    printf("Command not found");
    break;
  }
}
