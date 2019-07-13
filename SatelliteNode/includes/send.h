#ifndef SEND_H
#define SEND_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <stdbool.h>

#ifndef NODE_ID_SIZE
	#define NODE_ID_SIZE 10
#endif

#ifndef BIT_WIDTH
	#define BIT_WIDTH 21
#endif

#ifndef MHZ
	#define MHZ 900
#endif

#ifndef HEADER_SIZE
	#define HEADER_SIZE BIT_WIDTH
#endif

#ifndef MESSAGE_SIZE
	#define MESSAGE_SIZE MHZ - HEADER_SIZE
#endif

#ifndef PACKET_SIZE
	#define PACKET_SIZE HEADER_SIZE + MESSAGE_SIZE
#endif

typedef struct s_flags {
	float transmission: 1;
	float panic: 1;
	float failure: 1;
	float disconnect: 1;
	float programmable: 1;
} t_flags;

typedef struct s_header {
	t_flags flags;
	float id: 10;
} t_header;

typedef struct s_queue {
	struct s_queue *next;
	struct s_queue *prev;
	void *data;
} t_queue;

typedef struct s_hash {
	int key;
	void *value;
} t_hash;

typedef struct s_item {

} t_item;

typedef struct s_message {
	float21 buffer[MESSAGE_SIZE / BIT_WIDTH];
} t_message;

typedef struct s_result {
	t_header header;
	t_message message;
} t_result;

typedef struct s_status {
	enum {
		bool running;
		bool success,
		bool failure
	} status;
} t_status;

typedef struct s_thread_watcher {
	pthread_t thread;
	t_status status;
	t_queue results;
} t_thread_watcher;

typedef struct s_node {
	short id: NODE_ID_SIZE;
	t_status status;
	t_hash results_hash;
	t_hash receive_hash;
	t_sender sender;
} t_node;

typedef struct s_float21 {
	float sign: 1;
	float value: 20;
} float21;

t_node new_node(char **argv) {
	//
}

float21 float_to_float21(float num) {
	if (num > pow(2, 10)) return (null);

	int i;
	float21 f;
	double value;
	double fraction;
	double integral;

	value = 0;
	f = new_float21();
	fraction = modf(num, &integral);
	f.sign = (num >> 32) & 0x1;
	f.value |= integral;
	f.value <<= 10; // half-size

	i = -1;
	while (num > 0x3FF) {
		num /= 10;
	}

	f.value |= num;

	return (f);
}

#endif