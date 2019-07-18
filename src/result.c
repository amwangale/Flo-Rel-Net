#include "../includes/result.h"

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