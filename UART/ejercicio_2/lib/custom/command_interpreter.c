#include "command_interpreter.h"

void checkData(char data[]) {
  char temp[5];
  uint8_t arg;
  switch (data[1]) {
  case 'T':
    for (size_t i = 2; i < UARTcount; i++) {
      temp[i - 2] = data[i];
    }
    arg = atoi(temp);
    if (arg < 1 || arg > 99) {
      printf("El periodo no puede ser mayor a 99 ni menor a 1\n");
    } else {
      T = arg;
      printf("Nuevo periodo = %d\n", T);
    }
    break;
  default:
    printf("Command not found :(\n");
    break;
  }
}
