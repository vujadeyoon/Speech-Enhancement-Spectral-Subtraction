/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: free_tensor_1d_complex.c
Version: 181118a
Description: Free the 1D complex tensor
**************************************/

#include "header.h"

void free_tensor_1d_complex(tensor_1d_complex *ptr_tensor_1d_complex) {
	free(ptr_tensor_1d_complex->real);
	free(ptr_tensor_1d_complex->imag);
	free(ptr_tensor_1d_complex->mag);
	free(ptr_tensor_1d_complex->phase);
	free(ptr_tensor_1d_complex);
}