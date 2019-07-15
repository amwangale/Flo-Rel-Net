#ifndef UTILS_H
#define UTILS_H

#ifndef BIT_WIDTH
	#define BIT_WIDTH 21
#endif

typedef struct s_status {
	enum {
		running,
		success,
		failure
	} status;
} t_status;

typedef struct s_float21 {
	unsigned int sign: 1;
	unsigned int value: 20;
} float21;

float21 *new_float21(void) {
	float21 *f;

	if (!(f = (float21*)calloc(1, sizeof(float21))))
		return (NULL);
	return (f);
}

float21 *float_to_float21(float num) {
	if (num > pow(2, 10)) return (NULL);

	float21 *f;
	double value;
	double fraction;
	double integral;

	value = 0;
	f = new_float21();
	fraction = modf(num, &integral);
	f->sign = (num >> 32) & 0x1;
	f->value |= integral;
	f->value <<= 10; // half-size

	while (num > 0x3FF) {
		num /= 10;
	}

	f->value |= num;

	return (f);
}

#endif