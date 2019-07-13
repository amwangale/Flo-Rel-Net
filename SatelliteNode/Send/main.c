#include "../includes/send.h"

t_node configure(t_node node) {
	node.sender.running = true;

	register(node);
	
	return (node);
}

t_header *strip_header(void *data) {
	t_header header;

	header = new_header();
	memcpy(&header, data, sizeof(header));
	return (header);
}

t_status recieve(t_node *node) {
	int index;
	t_queue queue;
	t_header *header;

	while (node->status.running) {
		if ((data = recv())) {
			if ((header = strip_header(&data))) {
				if ((index = get(node->receive_hash, header->id))) {
					if ((queue = get(node->receive_hash, index))) {
						if ((message = strip_message(&data))) {
							push_back(queue, message);
						}
					}
				}
			}
			node->results_hash
		}
		sleep(1);
	}

	return (node->status.running);
}

bool listen_for_data(t_thread_watcher *watcher) {
	t_item item;

	while (watcher->status.running) {
		data = pop_front(watcher->results);
		if (data) {
			
		}
		sleep(1);
	}

	pthread_exit(&watcher.status);
	return (true);
}

bool device_connecting(t_node *node) {
	return (node->hash)
}

bool collect_data() {
	t_result result;

	set_header(&result);
	while (true) {
		if ((data = recv())) {
			result->message
		}
	}

	pthread_exit(&watcher.status);
}

initialize_recieve_buffers(t_node *node) {
	int error;
	t_queue queue;
	t_thread_watcher watcher;
	
	watcher = new_thread_watcher();
	node->results_hash = new_hash(node->neighbor_count);

	for (int i = 0; i < node->neighbor_count; i++) {
		if (!hash->get(i)) {
			if ((queue = new_queue())) {
				if (!results_hash->set(i, queue)) {
					printf("Failed to create results queue");
				} else {
					error = pthread_create(&watcher->thread, NULL, listen_for_data, &watcher);
					if (error)  {
						printf("Pthread failed to create\n");
					} else {
						pthread_join(watcher->thread, &error);
					}
				}
			}
		}
	}
	// listen_for_data(index);
}

initialize_devices(t_node *node) {
	// for each device
		// new hash
			// new thread
				// collect_data(device);
}

fetch_top_result(t_node *node) {
	t_item item;
	t_result result;

	item = node.results.pop_front();
	if (item) {
		result = memccpy(&result, item.data, sizeof(float * PACKET_SIZE));
	}

	return (result);
}

t_node go_online(t_node node) {
	t_result result;
	t_packet packet;

	if initialize_devices(&node.results).status.success {
		if initialize_recieve_buffers(&node.results).status.success {
			while (node.running) {
				result = fetch_top_result(node.results);

				if (result) transmit_result(result.buffer);
				
				sleep(1);
			}
		} else {

		}
	} else {

	}

	return (node);
}

int main(argc, **argv) {
	t_node node;

	if (argc == 2) {
		if (node = new_node(argv));
			if configure(node).status
				if go_online(node).status.success
					return (0);
		return (1);
	} else {
		printf("Node ID required for testing");
	}
	return (0);
}