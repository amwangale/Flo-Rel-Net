#include "../includes/florel.h"
#include "../includes/node.h"
#include "../includes/send.h"
#include "../includes/simulate.h"
#include "../includes/init.h"
#include "../includes/receive.h"

bool register_node(t_node *node) {
	// YODO broadcast to other nodes
	if (!node) {
		printf("Node does not exist\n");
		return (false);
	} else {
		printf("Node exists\n");
		node->neighbor_count = 5;
		node->device_count = 3;
		
		printf("segf %i\n", node->device_hash.size);
		new_hash(&node->device_hash, node->device_count);
		new_hash(&node->results_hash, node->neighbor_count);
		new_hash(&node->receive_hash, node->neighbor_count);
		new_hash(&node->neighbor_map, node->neighbor_count);

		node->global_results = *new_queue();
		return (true);
	}
}

void *listen_for_data(void *arg) {
	int retry;
	bool result;

	t_item *data;
	t_status *parent_status;
	t_thread_watcher *watcher;

	watcher = arg;
	while (watcher->status.running) {
		retry = 5;
		data = pop_front(&watcher->results);
		if (data) {
			while (retry > 0) {
				result = push_back(&watcher->node->global_results, data->data);
				
				if (result == 0) {
					retry--;
				} else {
					retry = 0;
				}

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

void *send_and_receive(void *arg) {
	unsigned int index;

	t_result *result;
	t_status *parent_status;
	t_thread_watcher *watcher;

	t_header *header;
	t_queue *queue;
	t_message *message;

	watcher = arg;
	while (watcher->status.running) {
		if ((result = simulate_receive(watcher->node))) {
			if ((header = strip_header(result))) {
				
				// printf("neighbors exist? %s, %d\n",
				// 	&watcher->node->neighbor_map? "true":"false",
				// 	header->id
				// );

				index = *((int*)get(watcher->node->neighbor_map, header->id));
				if ((queue = (t_queue*)get(watcher->node->receive_hash, index))) {
					if ((message = strip_message(result))) {
						if (push_back(queue, message) == false) {
							free_message(message);
						}
					} else {
						printf("Failed to interpret message\n");
					}
				} else {
					printf("Failed to get queue\n");
				}
			} else {
				printf("Failed to iterpret header\n");
			}
		} else {
			printf("No data received\n");
		}

		sleep(1);

		if ((result = fetch_top_result(&watcher->node->global_results))) {
			if (transmit_result(watcher->node, result) == false) {
				printf("Failed to send result\n");
			} else {
				printf("Result sent\n");
			}
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