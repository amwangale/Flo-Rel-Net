#include "../includes/utils.h"

float21 *new_float21(void) {
	float21 *f;

	if (!(f = (float21*)calloc(1, sizeof(float21))))
		return (NULL);
	return (f);
}

t_status *new_status(void) {
	t_status *status;
	
	if (!(status = (t_status*)calloc(1, sizeof(t_status))))
		return (NULL);
	return (status);
}

float float21_to_float(float21 num) {
	float value;
	float mantissa;
	float fraction;

	// drop the last 10 bits
	fraction = (float)((num.value << 10) >> 10);
	// drop 100 places
	fraction /= 100;

	mantissa = (float)(num.value >> 10);

	value = mantissa
		+ fraction
		* (num.sign & 1)? 1.0 : -1.0;

	return (value);
}

float21 *float_to_float21(float num) {
	if (num > pow(2, 10)) return (NULL);

	float21 *f;
	double fraction;
	double integral;

	f = new_float21();
	fraction = modf(num, &integral);
	f->sign = ((unsigned int)num >> 31) & 0x1;
	f->value |= (int)integral;
	f->value <<= 10; // half-size

	while (fraction > 0x3FF) {
		fraction /= 10;
	}

	f->value |= (int)fraction;

	return (f);
}