#include "../includes/result.h"

t_flags *new_flags(void) {
	t_flags *flags;

	if (!(flags = (t_flags*)calloc(1, sizeof(t_flags))))
		return (NULL);
	return (flags);
}

t_header *new_header(short id) {
	t_header *header;

	if (!(header = (t_header*)calloc(1, sizeof(t_header))))
		return (NULL);
	header->flags = *new_flags();
	header->id = id;
	return (header);
}

t_message *new_message(void) {
	t_message *message;

	if (!(message = (t_message*)calloc(1, sizeof(t_message))))
		return (NULL);
	return (message);
}

void free_header(t_header *header) {
	if (header) {
		free(&header->flags);
		free(header);
	}
}

void free_message(t_message *message) {
	if (message) {
		for (int i = 0; i < MESSAGE_COUNT; i++) {
			free_float21(&message->buffer[i]);
		}

		free(message);
	}
}

void free_result(t_result *result) {
	if (result) {
		free_header(&result->header);
		free_message(&result->message);
		free(result);
	}
}

t_result *new_result(short id) {
	t_result *result;

	if (!(result = (t_result*)calloc(1, sizeof(t_result))))
		return (NULL);
	result->header = *new_header(id);
	result->message = *new_message();
	return (result);
}

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
	h->value |= header.flags.device_id;
	h->value <<= 7;	

	h->value |= header.id;

	value = float21_to_float(*h);
	free(h);
	
	return (value);
}

bool set_header(t_result *result) {
	if (result) {
		result->header.flags.transmission = 1;
		return (true);
	}
	return (false);
}

bool set_message(t_message message, void *data) {
	(void)message;
	(void)data;
	// memcpy(&message)
	return (true);
}