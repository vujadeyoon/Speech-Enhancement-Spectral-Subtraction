/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: init_tensor_1d_complex.c
Version: 181118a
Description: Memory allocation for 1D complex tensor with init ializing 0
**************************************/

#include "header.h"

tensor_1d_complex *init_tensor_1d_complex(size_t row)
{
	tensor_1d_complex *res = malloc(sizeof(tensor_1d_complex));
	res->row = row;
	res->real = init_tensor_1d(res->row, sizeof(double));
	res->imag = init_tensor_1d(res->row, sizeof(double));
	res->mag = init_tensor_1d(res->row, sizeof(double));
	res->phase = init_tensor_1d(res->row, sizeof(double));

	return res;
}