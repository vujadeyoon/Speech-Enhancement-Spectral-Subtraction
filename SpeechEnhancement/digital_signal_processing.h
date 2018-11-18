/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: digital_signal_processing.h
Version: 181118a
**************************************/

#ifndef _DIGITAL_SIGNAL_PROCESSING_H_
#define _DIGITAL_SIGNAL_PROCESSING_H_

typedef enum {
	hanning = 0
} window_kernel;

tensor_1d *get_window(size_t tap, window_kernel win);

#endif // #ifndef _DIGITAL_SIGNAL_PROCESSING_H_