/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: init_tensor_2d.c
Version: 181118a
Description: Memory allocation for 2D tensor with init ializing 0
**************************************/

#include "header.h"

tensor_2d* init_tensor_2d(size_t row, size_t col, size_t data_structure_sz)
{
	size_t i = 0;
	tensor_2d *res = malloc(sizeof(tensor_2d));
	res->row = row;
	res->col = col;
	res->buf = calloc((res->row * res->col), data_structure_sz);

	return res;
}