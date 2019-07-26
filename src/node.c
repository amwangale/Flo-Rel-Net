#include "../includes/florel.h"
#include "../includes/utils.h"
#include "../includes/node.h"

t_status *get_status(t_node *node) {
	t_status *result;

	result = NULL;
	if (!pthread_mutex_trylock(&node->lock.lock)) {
		result = &node->status;
		pthread_mutex_unlock(&node->lock.lock);
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
	node->id = id;

	node->status = *new_status(true);

	return (node);
}