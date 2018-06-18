#pragma once
#include "../AVRDuino/core.h"
#include "../AVRDuino/timers.h"
#include "../AVRDuino/uart.h"
#include "../AVRDuino/A4988.h"


enum estados {activado, desactivado};
volatile extern enum estados estado;

void Conditional_PaPsInit(uint16_t speed);

void checkData(char data[]);
