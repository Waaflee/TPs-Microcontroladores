#pragma once
#include "../AVRDuino/core.h"
#include "../AVRDuino/uart.h"
#include "../AVRDuino/A4988.h"
#include "../AVRDuino/interrupts.h"
#include "../AVRDuino/pwm.h"
#include "../AVRDuino/timers.h"

struct pwm1 pwm;

void checkData(char data[]);
