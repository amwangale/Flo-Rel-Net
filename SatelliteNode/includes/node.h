typedef struct s_locks {
	pthread_mutex_t status_lock;
} t_locks;

typedef struct s_node {
	short id: NODE_ID_SIZE;
	t_status status;
	t_hash device_hash;
	t_hash results_hash;
	t_hash receive_hash;
	t_sender sender;

	t_locks locks;
} t_node;

bool get_status(t_node *node) {
	bool result;

	result = false;
	if (pthread_mutex_trylock(node->locks->status_lock)) {
		result = node->status.running;
		pthread_mutex_unlock(node->locks->status_lock);
	}

	return (result);
}

t_node new_node(char **argv) {
	// TODO needs devices
}