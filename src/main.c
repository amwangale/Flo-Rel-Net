#include "../includes/florel.h"

bool register_node(t_node *node) {
	// YODO broadcast to other nodes
	(void)node;
	return (true);
}

t_node *configure(t_node *node) {
	node->status.running = true;

	if (register_node(node)) return (node);
	else return (NULL);
}

bool listen_for_data(t_thread_watcher *watcher) {
	t_item *data;
	t_status *parent_status;
	int retry;

	while (watcher->status.running) {
		retry = 5;
		data = pop_front(&watcher->results);
		if (data) {
			while (!push_back(
				*watcher->node->global_results,
				(void*)data->data
			) && retry--) {
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
	return (true);
}

bool device_connecting(t_node *node) {
	(void)node;
	return (true);
}

bool collect_data(t_thread_watcher *watcher) {
	int size;
	int retry;
	float data;

	float21 *f;
	t_result result;
	t_status *parent_status;

	while (watcher->status.running) {
		size = 0;
		retry = 5;
		while (size < MESSAGE_SIZE && retry) {
			// receive bound to device
			if ((data = simulate_collect_data())) {
				f = float_to_float21((float)data);
				result->message.buffer[BITDEX(size)] = f;
				size += BIT_WIDTH;
			} else {
				retry--;
			}
		}

		if (size >= MESSAGE_SIZE) {
			retry = 5;
			while (!push_back(
				watcher->node->global_results, result
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
}

t_result fetch_top_result(t_node node) {
	t_item item;
	t_result result;

	if ((item = pop_front(&node->global_results)))
		result = memcpy(&result, &item.data, sizeof(float * PACKET_SIZE));

	return (result);
}

t_node run(t_node *node) {
	t_result *result;

	while (node->running) {
		if ((result = fetch_top_result(node->results)));
			if (transmit_result(result->item) == false)
				printf("Failed to send result\n");
		sleep(1);
		result = NULL;
	}
}

t_node go_online(t_node node) {
	if (initialize_lora(&node)) {
		LoRa_begin(&modem);

		if (initialize_devices(&node).status.success) {
			if (initialize_recieve_buffers(&node).status.success) {
				node = run(&node);
			} else {
				node->status.failure = true;
			}
		} else {
			node->status.failure = true;
		}		
	} else {
		node->status.failure = true;
	}

	return (node);
}

int main(argc, **argv) {
	srand((unsigned int)time(NULL));
	t_node node;

	if (argc == 2) {
		if (node = new_node(argv));
			if (configure(node).status)
				if (get_status(go_online(node)).success)
					return (0);
		return (1);
	} else {
		printf("Node ID required for testing\n");
	}
	return (0);
}