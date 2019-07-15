#ifndef SEND_H
#define SEND_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "result.h"
#include "utils.h"
#include "queue.h"

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

typedef struct s_thread_watcher {
	pthread_t thread;
	t_status status;
	t_queue results;
	t_queue global_results;
} t_thread_watcher;

#endif