/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: header.h
Version: 181118a
**************************************/

#ifndef _HEADER_H_
#define _HEADER_H_

typedef unsigned char BYTE;

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <Windows.h>
#include <wingdi.h>
#include <crtdbg.h>

#include "matrix_computations.h"
#include "digital_signal_processing.h"
// #include "image_processing.h"

#define EPS 2.204e-16

#define COMMAND_SIZE 256
#define COMMAND_CONSOLE_LINES 80
#define COMMAND_CONSOLE_COLS 220

struct TIME {
	time_t startTime, endTime;
	double gapTime;	int hours, minutes, seconds;
};

void error(char *error_statement);

#endif // #ifndef _HEADER_H_
