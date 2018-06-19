// :Pnnn posición absoluta en pasos.
// :Fnnn avance en pasos
// :Bnnn retroceso en pasos
// :Tnnn tiempo entre pasos, décimas de ms
// :Mx x=0 paso completo, x=1 medio paso
// (pin 2 de A4988 o DRV8825)
// :Ennn error admisible (en pasos)
// Por ejemplo :E10 es +/- 10 pasos
// :S Consulta ESTADO. Devuelve palabra de
// estado en formato Hexadecimal.

#include "command_interpreter.h"

void checkData(char data[]) {
  char temp[10];
  uint16_t arg;

  // evitamos repetición de codigo precalculando el valor numerico de la orden
  // asignada, ambien corroboramos que haya argumentos suficientes (longitud de
  // cadena recibida) como para proceder

  if (UARTcount >= 3) {
    for (size_t i = 2; i < UARTcount; i++) {
      temp[i - 2] = UARTData[i];
    }
    arg = atoi(temp);
  } else if (UARTcount < 1) {
    printf("Error not enought arguments\n");
    return;
  }

  switch (data[1]) {
  case 'W':
    switch (data[2]) {
    case '0':
      estado = desactivado;
      break;
    case '1':
      estado = activado;
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
    case homing:
      printf("Homing actualmente en proceso...\n");
    }
    break;
  case 'P':
    if (estado == posicionado) {
      goToabs(arg, PAParray[0]);
    } else {
      printf("Debes realizar homing antes, ejecuta :H\n");
    }
    break;
  case 'F':
    rotateNSteps(arg, PAParray[0], FORWARD);
    break;
  case 'B':
    rotateNSteps(arg, PAParray[0], BACKWARD);
    break;
  case 'T':
    ICR1 = 200 * arg;
    break;
  case 'S':
    switch (estado) {
    case activado:
      printf("61-63-74-69-76-61-64-6f\n");
      break;
    case desactivado:
      printf("64-65-73-61-63-74-69-76-61-64-6f\n");
      break;
    }
    break;
  case 'M':
    switch (data[2]) {
    case '0':
      pinOff(PAParray[0]->motor->MS2);
      break;
    case '1':
      pinOn(PAParray[0]->motor->MS2);
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
