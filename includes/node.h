#ifndef NODE_H
#define NODE_H

#include "hash.h"
#include "queue.h"
#include "utils.h"
#include "florel.h"

#ifndef NODE_ID_WIDTH
	#define NODE_ID_WIDTH 10
#endif

typedef struct s_locks {
	pthread_mutex_t status_lock;
} t_locks;

typedef struct s_node {
	unsigned int id: NODE_ID_WIDTH;
	unsigned int neighbor_count;
	unsigned int device_count;

	t_status status;
	t_hash device_hash;
	t_hash results_hash;
	t_hash receive_hash;
	t_queue global_results;

	LoRa_ctl modem;
	t_locks locks;
} t_node;

t_status 	*get_status(t_node *node);
t_node 		*new_node(char **argv);

#endif