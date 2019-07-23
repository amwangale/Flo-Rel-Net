#ifndef RESULT_H
#define RESULT_H

#include "florel.h"
#include "utils.h"

#ifndef HEADER_SIZE
	#define HEADER_SIZE BIT_WIDTH
#endif

#ifndef MESSAGE_SIZE
	#define MESSAGE_SIZE MHZ - HEADER_SIZE
#endif

#ifndef PACKET_SIZE
	#define PACKET_SIZE HEADER_SIZE + MESSAGE_SIZE
#endif

#ifndef HEADER_COUNT
	#define HEADER_COUNT HEADER_SIZE / BIT_WIDTH
#endif

#ifndef MESSAGE_COUNT
	#define MESSAGE_COUNT MESSAGE_SIZE / BIT_WIDTH
#endif

#ifndef PACKET_COUNT
	#define PACKET_COUNT MESSAGE_COUNT + HEADER_COUNT
#endif

typedef struct s_flags {
	unsigned int transmission: 1;
	unsigned int panic: 1;
	unsigned int failure: 1;
	unsigned int disconnect: 1;
	unsigned int device_id: 7;
} t_flags;

typedef struct s_header {
	t_flags flags;
	unsigned int id: 10;
} t_header;

typedef struct s_message {
	float21 buffer[MESSAGE_COUNT];
} t_message;

typedef struct s_result {
	t_header header;
	t_message message;
} t_result;

t_flags 	*new_flags(void);
t_header 	*new_header(short id);

t_message 	*new_message(void);
void 		free_message(t_message *message);

t_result 	*new_result(short id);
void 		free_result(t_result *result);

float 		header_to_float(t_header header);

#endif