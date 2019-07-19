#ifndef UTILS_H
#define UTILS_H

#include "florel.h"

#ifndef BIT_WIDTH
	#define BIT_WIDTH 21
#endif

typedef struct s_status {
	bool running;
	bool success;
	bool failure;
} t_status;

typedef struct s_float21 {
	unsigned int sign: 1;
	unsigned int value: 20;
} float21;

t_status 	*new_status(void);
float21 	*new_float21(void);
float 		float21_to_float(float21 num);
float21 	*float_to_float21(float num);

#endif