/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: get_window.c
Version: 181118a
Description: Get a window function
**************************************/

#include "header.h"

tensor_1d *get_window(size_t tap, window_kernel win)
{
	size_t i = 0;
	tensor_1d *window = init_tensor_1d(tap, sizeof(double));

	switch (win) {
	case hanning:
		for (i = 0; i < tap; i++) {
			*((double *)(window->buf) + i) = (0.54 - 0.46*cos(2 * M_PI*(i + 1) / tap)) / 1.08;
		}
		break;

	default:
		break;
	}

	return window;
}