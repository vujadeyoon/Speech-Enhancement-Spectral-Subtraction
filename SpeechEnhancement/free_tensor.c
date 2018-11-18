/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: free_tensor.c
Version: 181118a
Description: Free the tensor
**************************************/

#include "header.h"

void free_tensor(tensor_1d *ptr_tensor_1d) {
	free(ptr_tensor_1d->buf);
	free(ptr_tensor_1d);
}