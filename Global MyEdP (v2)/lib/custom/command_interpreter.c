#include "command_interpreter.h"

void checkData(char data[]) {
  char temp[4];
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
  case 'A':
    switch (data[2]) {
    case '0':
      estado = disabled;
      pinOff(ENA);
      printf("%s\n", data);
      break;
    case '1':
      estado = enabled;
      pinOn(ENA);
      printf("%s\n", data);
      break;
    default:
      printf("wrong argument\n");
    }
    break;
  case 'D':
    switch (estado) {
    case enabled:
      if (UARTcount > 5) {
        printf("Argumment too long, duty cycle = %u\n", pwm.dutyA(NaN));
      } else if (UARTcount < 3) {
        printf("No argument, duty cycle = %u\n", pwm.dutyA(NaN));
      } else {
        pwm.dutyA(pt1000(arg));
        printf("%s\n", data);
      }
      break;
    case disabled:
      printf(":d\r");
      break;
    case error:
      printf("esto no deberia verse :( \n");
      break;
    default:
      printf(":d\r");
      break;
    }
    break;
  case 'T':
    if (arg >= 100 && arg <= 1000) {
      pwm.freq((int)(1000.0 / (float)arg));
    } else {
      printf("%d is out of bounds :(", arg);
    }
    printf("%s\n", data);
    break;
  default:
    printf("Command not Found\n");
    break;
  }
}
