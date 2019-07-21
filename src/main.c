#include "../includes/florel.h"
#include "../includes/node.h"
#include "../includes/send.h"
#include "../includes/simulate.h"
#include "../includes/init.h"

bool register_node(t_node *node) {
	// YODO broadcast to other nodes
	if (!node) {
		printf("Node does not exist\n");
		return (false);
	} else {
		printf("Node exists\n");
		node->neighbor_count = 1;
		node->device_count = 1;
		
		node->results_hash = *new_hash(2);
		node->device_hash = *new_hash(2);
		node->receive_hash = *new_hash(2);
		node->neighbor_map = *new_hash(2);

		node->global_results = *new_queue();
		return (true);
	}
}

void *listen_for_data(void *arg) {
	bool retry;

	t_item *data;
	t_status *parent_status;
	t_thread_watcher *watcher;

	watcher = arg;
	while (watcher->status.running) {
		retry = 5;
		data = pop_front(&watcher->results);
		if (data) {
			while (retry > 0) {
// retry = push_back(&watcher->node->global_results, (void*)data->data);// == false)? 1 : 5;
				sleep(1);
			}
			data = NULL;
		}

		parent_status = get_status(watcher->node);
		if (parent_status)
			if (parent_status->running == false)
				watcher->status.running = false;
	}

	pthread_exit(&watcher->status);
	return (NULL);
}

bool device_connecting(t_node *node) {
	(void)node;
	return (true);
}

void *collect_device_data(void *arg) {
	int size;
	int retry;
	float data;
	t_thread_watcher *watcher;

	float21 *f;
	t_result *result;
	t_status *parent_status;

	watcher = arg;
	while (watcher->status.running) {
		size = 0;
		retry = 5;
		while (size < MESSAGE_SIZE && retry) {
			// receive bound to device
			if ((data = simulate_collect_data())) {
				f = float_to_float21((float)data);
				result->message.buffer[BITDEX(size)] = *f;
				size += BIT_WIDTH;
			} else {
				retry--;
			}
		}

		if (size >= MESSAGE_SIZE) {
			retry = 5;
			while (!push_back(
				&watcher->node->global_results, result
			) && retry--) {
				sleep(1);
			}
			result = NULL;
		}

		parent_status = get_status(watcher->node);
				if (parent_status)
					if (parent_status->running == false)
						watcher->status.running = false;
	}

	pthread_exit(&watcher->status);
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

t_node *configure(t_node *node) {
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
	t_node *node;

	if (argc == 2) {
		if ((node = new_node(argv))) {
			if (configure(node)) {
				if (get_status(go_online(node))->success) {
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
			printf("Failed to crete node\n");
			return (-1);
		}
	} else {
		printf("Node ID required for testing\n");
		return (1);
	}
	return (0);
}