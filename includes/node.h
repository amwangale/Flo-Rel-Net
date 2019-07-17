#ifndef NODE_H
#define NODE_H

#include "utils.h"
#include "send.h"
#include "hash.h"

#ifndef NODE_ID_WIDTH
	#define NODE_ID_WIDTH 10
#endif

typedef struct s_locks {
	pthread_mutex_t status_lock;
} t_locks;

typedef struct s_node {
	unsigned int id: NODE_ID_WIDTH;
	t_status status;
	t_hash device_hash;
	t_hash results_hash;
	t_hash receive_hash;

	LoRa_ctl modem;

	t_locks locks;
} t_node;

bool get_status(t_node *node) {
	bool result;

	result = false;
	if (pthread_mutex_trylock(&node->locks.status_lock)) {
		result = node->status.running;
		pthread_mutex_unlock(&node->locks.status_lock);
	}

	return (result);
}

t_node new_node(char **argv) {
	// TODO needs devices
	t_node node;

	if (!(node = calloc(1, sizeof(t_node))))
		return (NULL);
	return (node);
}

#endif