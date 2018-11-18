/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: print_tensor_2d.c
Version: 181118a
Description: Print the given 2D tensor
**************************************/

#include "header.h"

void print_tensor_2d(tensor_2d *ptr_tensor_2d, size_t data_structure_sz)
{
	size_t i = 0;
	size_t j = 0;
	
	switch (data_structure_sz) {
	case 1:
		for (i = 0; i < ptr_tensor_2d->row; i++) {
			for (j = 0; j < ptr_tensor_2d->col; j++) {
				printf("%d\t", (*((char *)(ptr_tensor_2d->buf) + (i * ptr_tensor_2d->row + j))));
			}
			printf("\n");
		}
		break;

	case 4:
		for (i = 0; i < ptr_tensor_2d->row; i++) {
			for (j = 0; j < ptr_tensor_2d->col; j++) {
				printf("%d\t", (*((int *)(ptr_tensor_2d->buf) + (i * ptr_tensor_2d->row + j))));
			}
			printf("\n");
		}
		break;

	case 8:
		for (i = 0; i < ptr_tensor_2d->row; i++) {
			for (j = 0; j < ptr_tensor_2d->col; j++) {
				printf("%.2f\t", (*((double *)(ptr_tensor_2d->buf) + (i * ptr_tensor_2d->row + j))));
			}
			printf("\n");
		}
		break;

	default:
		break;
	}
	

}