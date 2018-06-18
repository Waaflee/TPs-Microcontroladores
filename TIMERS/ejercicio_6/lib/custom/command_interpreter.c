#include "command_interpreter.h"

void checkData(char data[]) {
  char temp[10];
  uint16_t arg;

  // evitamos repetición de codigo precalculando el valor numerico de la orden
  // asignada, ambien corroboramos que haya argumentos suficientes (longitud de
  // cadena recibida) como para proceder

  if (UARTcount >= 3) {
    /* code */
    for (size_t i = 2; i < UARTcount; i++) {
      temp[i - 2] = UARTData[i];
    }
    arg = atoi(temp);
  } else if (UARTcount < 1) {
    printf("Error not enought arguments\n");
    return;
  }
  switch (data[1]) {
  case 'V':
    // La velocidad se espera en forma porcentual
    V = pt100(arg);
    printf("%s\n", data);
    break;
  default:
    printf("Command not Found\n");
    break;
  }
}
