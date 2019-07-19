#ifndef RESULT_H
#define RESULT_H

#include "utils.h"

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

t_flags *new_flags(void);
t_header *new_header(short id);
t_message *new_message(void);
t_result *new_result(short id);
float 	header_to_float(t_header header);

#endif