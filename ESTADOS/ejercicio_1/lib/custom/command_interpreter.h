#pragma once
#include "../AVRDuino/core.h"
#include "../AVRDuino/uart.h"
#include "../AVRDuino/A4988.h"
#include "../AVRDuino/timers.h"
#include "../AVRDuino/interrupts.h"

enum estados {activado, desactivado};
volatile extern enum estados estado;

void checkData(char data[]);
