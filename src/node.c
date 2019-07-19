#include "../includes/node.h"

t_status *get_status(t_node *node) {
	t_status *result;

	result = NULL;
	if (pthread_mutex_trylock(&node->locks.status_lock)) {
		result = &node->status;
		pthread_mutex_unlock(&node->locks.status_lock);
	}

	return (result);
}

t_node *new_node(char **argv) {
	// TODO needs devices
	t_node *node;
	unsigned int id;

	if (!(node = (t_node*)calloc(1, sizeof(t_node))))
		return (NULL);
	
	id = atoi(argv[1]);
	node->id |= id;

	return (node);
}