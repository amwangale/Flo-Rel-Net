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

#ifndef BITDEX // BIT INDEX
	#define BITDEX(i) i / BIT_WIDTH
#endif

typedef struct s_item {
	struct s_item *next;
	struct s_item *prev;
	t_result data;
} t_item;

typedef struct s_queue {
	t_item *front;
	t_item *back;
	t_item item;
} t_queue;

typedef struct s_message {
	float21 buffer[MESSAGE_SIZE / BIT_WIDTH];
} t_message;

typedef struct s_result {
	t_header header;
	t_message message;
} t_result;

typedef struct s_thread_watcher {
	pthread_t thread;
	t_status status;
	t_queue results;
	t_queue global_results;
} t_thread_watcher;

#endif