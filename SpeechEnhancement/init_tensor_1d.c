/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: init_tensor_1d.c
Version: 181118a
Description: Memory allocation for 1D tensor with init ializing 0
**************************************/

#include "header.h"

tensor_1d *init_tensor_1d(size_t row, size_t data_structure_sz)
{
	// Initialize array with 0 using calloc function because memset function doesn't work for double array
	size_t i = 0;
	tensor_1d *res = malloc(sizeof(tensor_1d));
	res->row = row;
	res->buf = calloc(res->row, data_structure_sz);

	return res;
}