#include "../includes/florel.h"

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