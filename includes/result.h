#ifndef RESULT_H
#define RESULT_H

#include "utils.h"
#include "florel.h"

typedef struct s_flags {
	unsigned int transmission: 1;
	unsigned int panic: 1;
	unsigned int failure: 1;
	unsigned int disconnect: 1;
	unsigned int programmable: 1;
} t_flags;

typedef struct s_header {
	t_flags flags;
	unsigned int id: 10;
} t_header;

typedef struct s_message {
	float21 buffer[MESSAGE_SIZE / BIT_WIDTH];
} t_message;

typedef struct s_result {
	t_header header;
	t_message message;
} t_result;

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

t_result *new_result(short id) {
	t_result *result;

	if (!(result = (t_result*)calloc(1, sizeof(t_result))))
		return (NULL);
	result->header = *new_header(id);
	result->message = *new_message();
	return (result);
}

#endif