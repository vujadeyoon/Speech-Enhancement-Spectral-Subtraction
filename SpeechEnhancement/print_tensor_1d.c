/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: print_tensor_1d.c
Version: 181118a
Description: Print the given 1D tensor
**************************************/

#include "header.h"

void print_tensor_1d(tensor_1d *ptr_tensor_1d, size_t data_structure_sz)
{
	size_t i = 0;
	
	switch (data_structure_sz) {
	case 1:
		for (i = 0; i < ptr_tensor_1d->row; i++) {
			printf("%d\t", (*((char *)(ptr_tensor_1d->buf) + (i))));
		}
		break;
	
	case 2:
		for (i = 0; i < ptr_tensor_1d->row; i++) {
			printf("%d\t", (*((short *)(ptr_tensor_1d->buf) + (i))));
		}
		break;

	case 4:
		for (i = 0; i < ptr_tensor_1d->row; i++) {
			printf("%d\t", (*((int *)(ptr_tensor_1d->buf) + (i))));
		}
		break;

	case 8:
		for (i = 0; i < ptr_tensor_1d->row; i++) {
			printf("%.2f\t", (*((double *)(ptr_tensor_1d->buf) + (i))));
		}
		break;

	default:
		break;
	}
}