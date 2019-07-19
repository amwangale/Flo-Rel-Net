#include "../includes/result.h"

float header_to_float(t_header header) {
	float value;
	float21 *h;

	h = new_float21();
	h->sign = 1;

	h->value |= header.flags.transmission;
	h->value <<= 1;
	h->value |= header.flags.panic;
	h->value <<= 1;
	h->value |= header.flags.failure;
	h->value <<= 1;
	h->value |= header.flags.disconnect;
	h->value <<= 1;
	h->value |= header.flags.programmable;
	h->value <<= 1;

	h->value <<= 10;
	h->value |= header.id;

	value = float21_to_float(*h);
	free(h);
	
	return (value);
}

bool set_header(t_result *result) {
	if (result) {
		if (&result->header) {
			result->header.flags.transmission = 1;
			return (true);
		}
	}
	return (false);
}

bool set_message(t_message message, void *data) {
	(void)message;
	(void)data;
	// memcpy(&message)
	return (true);
}