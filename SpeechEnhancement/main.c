/****************************************************************************
Dveloper: Sungjun Yoon
E-mail: sjyoon1671@gmail.com
Github: https://github.com/vujadeyoon
Integrated Development Environment(IDE): Microsoft Visual Studio 2017

Title: main.c
Version: 181118a
Description: Speech enhancement (Spectral subtraction for noise reduction)

Noisy signal -> Windowing -> Estimated noise ------
			        г№  				          бщ
			         -------------> DFT -----> Magnitude
							        бщ            г№
							       Phase          г№
						  	        бщ            г№			
Cleaned speech <------ OLA <------ IDFT <----------		
****************************************************************************/

#include "header.h"

int main(int argc, char *argv[])
{
	const char *name_file_noisy = argv[1];      // "speech_noisy.raw";
	const char *name_file_cleaned = argv[2];    // "speech_cleaned.raw";
	const size_t frame_sz = atoi(argv[3]);      // 256
	const size_t base_frame_sz = atoi(argv[4]); // 5
	FILE *fin = NULL;
	FILE *fout = NULL;
	tensor_1d *sig_in = NULL;  // Input signal
	tensor_1d *sig_out = NULL; // Output signal
	size_t i = 0;
	size_t j = 0;
	size_t n = 0;
	size_t k = 0;
	size_t len = 0;
	
	tensor_1d *win_hamming = NULL;
	tensor_1d *w1 = NULL;
	tensor_1d *w2 = NULL;
	tensor_1d *w = NULL;

	tensor_1d_complex *w1_dft = NULL;
	tensor_1d_complex *w2_dft = NULL;
	tensor_1d_complex *w1_dft2 = NULL;
	tensor_1d_complex *w2_dft2 = NULL;
	tensor_1d_complex *w1_idft = NULL;
	tensor_1d_complex *w2_idft = NULL;
	double cumsum_real = 0.0;
	double cumsum_imag = 0.0;

	tensor_1d *noise_cumsum = NULL;
	tensor_1d *noise_estimated = NULL;
	errno_t err_in = 0;
	errno_t err_out = 0;

	err_in = fopen_s(&fin, name_file_noisy, "rb");
	err_out = fopen_s(&fout, name_file_cleaned, "wb");
	if (err_in != 0 || err_out != 0) {
		puts("File open is failed\n");
		return -1;
	}

	// Read a noisy file and calculate a length of the file
	fseek(fin, SEEK_SET, SEEK_END);
	len = ftell(fin) / sizeof(short);
	fseek(fin, SEEK_SET, SEEK_SET);
	
	sig_in = init_tensor_1d(len, sizeof(short));
	fread((short *)(sig_in->buf), sizeof(short), len, fin);

	// Get a haaning window function
	win_hamming = get_window(frame_sz, hanning);
	
	// Apply hanning window to sig_in (Windowing)
	w1 = init_tensor_1d(len, sizeof(double));
	w2 = init_tensor_1d(len - frame_sz, sizeof(double));
	for (i = 0; i < len / frame_sz; i++) {
		for (n = 0; n < frame_sz; n++) {
			*((double *)(w1->buf) + (i*frame_sz + n)) = *((double *)(win_hamming->buf) + n) * ((double) *((short *)(sig_in->buf) + (i*frame_sz + n)));
		}
	}
	for (i = 0; i < (len / frame_sz) - 1; i++) {
		for (n = 0; n < frame_sz; n++) {
			*((double *)(w2->buf) + (i * frame_sz + n)) = (*((double *)(win_hamming->buf) + n)) * ((double) (*((short *)(sig_in->buf) + ((frame_sz / 2) + i * frame_sz + n))));
			
			
		}
	}	

	// DFT
	w1_dft = init_tensor_1d_complex(len);
	for (i = 0; i < len / frame_sz; i++) {
		for (k = 0; k < frame_sz; k++) {
			cumsum_real = 0;
			cumsum_imag = 0;
			for (n = 0; n < frame_sz; n++) {
				cumsum_real += (*((double *)(w1->buf) + (i * frame_sz + n))) * cos(2 * M_PI * k * n / frame_sz);
				cumsum_imag += (*((double *)(w1->buf) + (i * frame_sz + n))) * (-sin(2 * M_PI * k * n / frame_sz));
			}
			
			(*((double *)(w1_dft->real->buf) + (i * frame_sz + k))) = cumsum_real; // real
			(*((double *)(w1_dft->imag->buf) + (i * frame_sz + k))) = cumsum_imag; // imag
			(*((double *)(w1_dft->mag->buf) + (i * frame_sz + k))) = (sqrt(pow((*((double *)(w1_dft->real->buf) + (i * frame_sz + k))), 2) + pow((*((double *)(w1_dft->imag->buf) + (i * frame_sz + k))), 2)));
			(*((double *)(w1_dft->phase->buf) + (i * frame_sz + k))) = atan2((*((double *)(w1_dft->imag->buf) + (i * frame_sz + k))), (*((double *)(w1_dft->real->buf) + (i * frame_sz + k))));
		}
	}

		
	w2_dft = init_tensor_1d_complex(len - frame_sz);
	for (i = 0; i < (len / frame_sz) - 1; i++) {
		for (k = 0; k < frame_sz; k++) {
			cumsum_real = 0;
			cumsum_imag = 0;
			for (n = 0; n < frame_sz; n++) {
				cumsum_real += (*((double *)(w2->buf) + (i * frame_sz + n))) * cos(2 * M_PI * k * n / frame_sz);
				cumsum_imag += (*((double *)(w2->buf) + (i * frame_sz + n))) * (-sin(2 * M_PI * k * n / frame_sz));
			}

			(*((double *)(w2_dft->real->buf) + (i * frame_sz + k))) = cumsum_real; // real
			(*((double *)(w2_dft->imag->buf) + (i * frame_sz + k))) = cumsum_imag; // imag
			(*((double *)(w2_dft->mag->buf) + (i * frame_sz + k))) = (sqrt(pow((*((double *)(w2_dft->real->buf) + (i * frame_sz + k))), 2) + pow((*((double *)(w2_dft->imag->buf) + (i * frame_sz + k))), 2)));
			(*((double *)(w2_dft->phase->buf) + (i * frame_sz + k))) = atan2((*((double *)(w2_dft->imag->buf) + (i * frame_sz + k))), (*((double *)(w2_dft->real->buf) + (i * frame_sz + k))));
		}
	}

	// Estimate a noisy signal
	noise_cumsum = init_tensor_1d(frame_sz, sizeof(double));
	noise_estimated = init_tensor_1d(frame_sz, sizeof(double));

	for (k = 0; k < frame_sz; k++) {
		for (i = 0; i < base_frame_sz; i++) {
			(*((double *)(noise_cumsum->buf) + (k))) += (*((double *)(w1_dft->mag->buf) + (i * frame_sz + k)));
		}
		(*((double *)(noise_estimated->buf) + (k))) = (*((double *)(noise_cumsum->buf) + (k))) / base_frame_sz;
	}

	// Noise reduction
	w1_dft2 = init_tensor_1d_complex(len);
	memcpy(w1_dft2->mag->buf, w1_dft->mag->buf, w1_dft2->mag->row * sizeof(double));
	memcpy(w1_dft2->phase->buf, w1_dft->phase->buf, w1_dft2->phase->row * sizeof(double));

	for (i = 0; i < (len / frame_sz); i++) {
		for (k = 0; k < frame_sz; k++) {
			(*((double *)(w1_dft2->mag->buf) + (i * frame_sz + k))) -= (*((double *)(noise_estimated->buf) + (k)));
			if ((*((double *)(w1_dft2->mag->buf) + (i * frame_sz + k))) < 0) {
				(*((double *)(w1_dft2->mag->buf) + (i * frame_sz + k))) = 0;
			}
		}
	}

	w2_dft2 = init_tensor_1d_complex(len - frame_sz);
	memcpy(w2_dft2->mag->buf, w2_dft->mag->buf, w2_dft2->mag->row * sizeof(double));
	memcpy(w2_dft2->phase->buf, w2_dft->phase->buf, w2_dft2->phase->row * sizeof(double));
	for (i = 0; i < (len / frame_sz) - 1; i++) {
		for (k = 0; k < frame_sz; k++) {
			(*((double *)(w2_dft2->mag->buf) + (i * frame_sz + k))) -= (*((double *)(noise_estimated->buf) + (k)));
			if ((*((double *)(w2_dft2->mag->buf) + (i * frame_sz + k))) < 0) {
				(*((double *)(w2_dft2->mag->buf) + (i * frame_sz + k))) = 0;
			}
		}
	}

	for (i = 0; i < len; i++) {
		(*((double *)(w1_dft2->real->buf) + (i))) = (*((double *)(w1_dft2->mag->buf) + (i))) * (cos((*((double *)(w1_dft2->phase->buf) + (i)))));
		(*((double *)(w1_dft2->imag->buf) + (i))) = (*((double *)(w1_dft2->mag->buf) + (i))) * (sin((*((double *)(w1_dft2->phase->buf) + (i)))));
	}

	for (i = 0; i < (len - frame_sz); i++) {
		(*((double *)(w2_dft2->real->buf) + (i))) = (*((double *)(w2_dft2->mag->buf) + (i))) * (cos((*((double *)(w2_dft2->phase->buf) + (i)))));
		(*((double *)(w2_dft2->imag->buf) + (i))) = (*((double *)(w2_dft2->mag->buf) + (i))) * (sin((*((double *)(w2_dft2->phase->buf) + (i)))));
	}
	
	// IDFT
	w1_idft = init_tensor_1d_complex(len);
	for (i = 0; i < len / frame_sz; i++) {
		for (k = 0; k < frame_sz; k++) {
			cumsum_real = 0;
			cumsum_imag = 0;
			for (n = 0; n < frame_sz; n++) {
				cumsum_real += ((*((double *)(w1_dft2->real->buf) + (i * frame_sz + n))) * cos(2 * M_PI * n * k / frame_sz) - (*((double *)(w1_dft2->imag->buf) + (i * frame_sz + n))) * sin(2 * M_PI * n * k / frame_sz));
				cumsum_imag += ((*((double *)(w1_dft2->real->buf) + (i * frame_sz + n))) * sin(2 * M_PI * n * k / frame_sz) - (*((double *)(w1_dft2->imag->buf) + (i * frame_sz + n))) * cos(2 * M_PI * n * k / frame_sz));
			}
			(*((double *)(w1_idft->real->buf) + (i * frame_sz + k))) = (cumsum_real / frame_sz);
			(*((double *)(w1_idft->imag->buf) + (i * frame_sz + k))) = (cumsum_imag / frame_sz);
		}
	}
	
	w2_idft = init_tensor_1d_complex(len - frame_sz);
	for (i = 0; i < (len / frame_sz) - 1; i++) {
		for (k = 0; k < frame_sz; k++) {
			cumsum_real = 0;
			cumsum_imag = 0;
			for (n = 0; n < frame_sz; n++) {
				cumsum_real += ((*((double *)(w2_dft2->real->buf) + (i * frame_sz + n))) * cos(2 * M_PI * n * k / frame_sz) - (*((double *)(w2_dft2->imag->buf) + (i * frame_sz + n))) * sin(2 * M_PI * n * k / frame_sz));
				cumsum_imag += ((*((double *)(w2_dft2->real->buf) + (i * frame_sz + n))) * sin(2 * M_PI * n * k / frame_sz) - (*((double *)(w2_dft2->imag->buf) + (i * frame_sz + n))) * cos(2 * M_PI * n * k / frame_sz));
			}
			(*((double *)(w2_idft->real->buf) + (i * frame_sz + k))) = (cumsum_real / frame_sz);
			(*((double *)(w2_idft->imag->buf) + (i * frame_sz + k))) = (cumsum_imag / frame_sz);
		}
	}

	// OLA
	w = init_tensor_1d(len, sizeof(double));
	for (i = 0; i < len; i++) {
		if ((i < (frame_sz / 2)) || ((len - (frame_sz / 2)) <= i)) {
			(*((double *)(w->buf) + (i))) = (*((short *)(sig_in->buf) + (i)));
		}
		else {
			(*((double *)(w->buf) + (i))) = (*((double *)(w1_idft->real->buf) + (i))) + (*((double *)(w2_idft->real->buf) + (i - (frame_sz / 2))));
		}
	}

	// write the clead signal
	sig_out = init_tensor_1d(len, sizeof(short));
	for (i = 0; i < len; i++) {
		(*((short *)(sig_out->buf) + (i))) = ((*((double *)(w->buf) + (i))) >= 0) ? (short)((*((double *)(w->buf) + (i))) + 0.5) : (short)((*((double *)(w->buf) + (i))) - 0.5);
	}
	fwrite((short *)sig_out->buf, sizeof(short), len, fout);

	// Free all dynamic memories.
	free_tensor(sig_in);
	free_tensor(sig_out);
	free_tensor(win_hamming);
	free_tensor(w1);
	free_tensor(w2);
	free_tensor(w);
	free_tensor_1d_complex(w1_dft);
	free_tensor_1d_complex(w2_dft);
	free_tensor_1d_complex(w1_dft2);
	free_tensor_1d_complex(w2_dft2);
	free_tensor_1d_complex(w1_idft);
	free_tensor_1d_complex(w2_idft);
	free_tensor(noise_estimated);
	free_tensor(noise_cumsum);
	fclose(fin);
	fclose(fout);
}