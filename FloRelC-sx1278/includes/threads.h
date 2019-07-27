#ifndef THREADS_H
#define THREADS_H

#include "utils.h"
#include "queue.h"
#include "node.h"

typedef struct s_thread_watcher {
	pthread_t thread;
	t_status status;
	t_queue *results;

	// parent
	t_node *node;
} t_thread_watcher;

t_thread_watcher 	*new_thread_watcher(t_node *node);
void 				*collect_device_data(void *arg);
void 				*listen_for_data(void *arg);

#endif