#include "../includes/florel.h"
#include "../includes/node.h"
#include "../includes/send.h"
#include "../includes/simulate.h"
#include "../includes/init.h"
#include "../includes/receive.h"

bool register_node(t_node *node) {
	/*
	here we would want to broadcast a
	signal to all of our neighbors
	letting them know we are about to
	come online, meaning a minimal
	initialization step would probably
	have to come before this function;
	*/
	if (!node) {
		printf("Node does not exist\n");
		return (false);
	} else {
		printf("Node exists\n");
		return (true);
	}
}

void *listen_for_data(void *arg) {
	/*
	And endless loop, registered to
	the thread watcher's results queue;

	we want to keep checking if the
	receive callback is depositing
	data so we can do interesting things
	like immediately hand the data to the
	send node or segfault when the data
	is the wrong size;
	*/
	t_item *data;
	t_status *parent_status;
	t_thread_watcher watcher;

	if (arg) {
		memcpy(&watcher, (t_thread_watcher*)arg, sizeof(t_thread_watcher));

		while (watcher.status.running) {
			if ((data = pop_front(watcher.results))) {
				push_back(
					&watcher.node->global_results,
					&data->data, sizeof(t_result)
				);
				sleep(1);
			}

			parent_status = get_status(watcher.node);
			if (parent_status)
				if (parent_status->running == false)
					watcher.status.running = false;
		}
	}

	pthread_exit(0);
	return (NULL);
}

bool device_connecting(t_node *node) {
	(void)node;
	return (true);
}

void *collect_device_data(void *arg) {
	int size;
	float data;

	float21 *f;
	t_result *result;
	t_status *parent_status;
	t_thread_watcher watcher;

	if (arg) {
		memcpy(&watcher, (t_thread_watcher*)arg, sizeof(t_thread_watcher));

		while (watcher.status.running) {
			size = 0;

			#ifdef TESTING
				result = new_result(rand() % watcher.node->device_count);
			#endif

			while (size < MESSAGE_COUNT) {
				#ifdef TESTING
					if ((data = simulate_collect_data())) {
						if ((f = float_to_float21((float)data))) {
							memcpy(
								&result->message.buffer[size],
								f, sizeof(float21)
							);
							size++;
						}
					}
				#endif
			}

			push_back(
				&watcher.node->global_results,
				(void**)&result, sizeof(t_result)
			);

			parent_status = get_status(watcher.node);
			if (parent_status)
				if (parent_status->running == false)
					watcher.status.running = false;
		}
	}

	pthread_exit(0);
	return (NULL);
}

t_node *run(t_node *node) {
	printf("Running node\n");
	while (node->status.running == true) {
		// regularly check on threads
		// read input from keyboard
	}

	return (node);
}

t_node *go_online(t_node *node) {
	if (initialize(node))
		node = run(node);
	return (node);
}

t_node *configure(t_node *node, char *id) {
	/*
	in reality, we should also be
	configuring devices here,
	registering them to our hash,
	and making sure they are
	connected!
	*/
	node->id = atoi(id);

	node->neighbor_count = 5;
	node->device_count = 3;

	new_hash(&node->device_hash, node->device_count);
	new_hash(&node->results_hash, node->neighbor_count);
	new_hash(&node->receive_hash, node->neighbor_count);
	new_hash(&node->neighbor_map, node->neighbor_count);
	
	node->status.running = true;

	if (register_node(node)) {
		printf("Node registered\n");
		return (node);
	} else {
		printf("Failed to register node\n");
		return (NULL);
	}
}

int main(int argc, char **argv) {
	srand((unsigned int)time(NULL));
	t_node node;

	if (argc == 2) {
		if (configure(&node, argv[1])) {
			if (get_status(go_online(&node))->success) {
				free_node(&node);
				return (0);
			} else {
				printf("Failed to go online\n");
				return (-1);
			}
		} else {
			printf("Failed to configure node\n");
			return (-1);
		}
	} else {
		printf("Node ID required for testing\n");
		return (1);
	}
	return (0);
}