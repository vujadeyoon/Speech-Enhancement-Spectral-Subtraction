/*************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Title: matrix_computations.h
Version: 181118a (Ver.2.0a)
Description: The matrix_computation_ver.2.0 supports generic c codes. 
	     Thus, some user-defined types and functions such as buffer in the matrix_computation_ver.1.0 are removed.
Todo list: SVD
**************************************/

#ifndef _MATRIX_COMPUTATIONS_H_
#define _MATRIX_COMPUTATIONS_H_

typedef struct {
	void *buf;
	size_t row;
} tensor_1d;

typedef struct {
	void *buf;
	size_t row;
	size_t col;
} tensor_2d;

typedef struct {
	tensor_1d *real;
	tensor_1d *imag;
	tensor_1d *mag;
	tensor_1d *phase;
	size_t row;
} tensor_1d_complex;

tensor_1d* init_tensor_1d(size_t row, size_t data_structure_sz);
tensor_2d* init_tensor_2d(size_t row, size_t col, size_t data_structure_sz);
tensor_1d_complex *init_tensor_1d_complex(size_t row);

void free_tensor(tensor_1d *ptr_tensor_1d);
void free_tensor_1d_complex(tensor_1d_complex *ptr_tensor_1d_complex);

void print_tensor_1d(tensor_1d *ptr_tensor_1d, size_t data_structure_sz);
void print_tensor_2d(tensor_2d *ptr_tensor_2d, size_t data_structure_sz);

#endif // #ifndef _MATRIX_COMPUTATIONS_H_
