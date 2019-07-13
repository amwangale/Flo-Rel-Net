#include "../includes/send.h"

bool register(t_node node) {
	// TODO broadcast to other nodes
	return (true);
}

t_node configure(t_node node) {
	node.sender.running = true;

	if (register(node)) return (node);
	else return (null);
}

bool listen_for_data(t_thread_watcher *watcher) {
	t_item item;

	while (watcher->status.running) {
		retry = 5;
		data = pop_front(watcher->results);
		if (data) {
			while (!push_back(watcher->node->results, data) && retry--) {
				sleep(1);
			}
		}
		if (get_status(node->status)->status.running == false)
			watcher->status.running = false;
	}

	pthread_exit(&watcher.status);
	return (true);
}

bool device_connecting(t_node *node) {
	return (node->hash);
}

bool set_header(t_result *result) {
	result.flags->transmission = 1;
	return (true);
}

bool set_message(t_message message, void *data) {

	return (true);
}

bool get_status(t_node *node) {
	bool result;

	result = false;
	if (pthread_mutex_trylock(node->locks->status_lock)) {
		result = node->status.running;
		pthread_mutex_unlock(node->locks->status_lock);
	}

	return (result);
}

bool collect_data(t_thread_watcher *watcher) {
	int size;
	int retry;

	float21 f;
	t_result result;

	while (watcher->status.running) {
		size = 0;
		retry = 5;
		while (size < MESSAGE_SIZE && retry) {
			// receive bound to device
			if ((data = recv())) {
				f = float_to_float21((float)data);
				result->message.buffer[size / BIT_WIDTH] = f;
				size += BIT_WIDTH;
			} else {
				retry--;
			}
		}

		if (size >= MESSAGE_SIZE) {
			retry = 5;
			while (!push_back(watcher->node->results, data) && retry--) {
				sleep(1);
			}
		} else {
			watcher->status.running = false;
		}

		if (get_status(node->status)->status.running == false)
			watcher->status.running = false;
	}

	pthread_exit(&watcher.status);
}



t_result fetch_top_result(t_node *node) {
	t_item item;
	t_result result;

	item = node.results.pop_front();
	if (item) {
		result = memccpy(&result, item.data, sizeof(float * PACKET_SIZE));
	}

	return (result);
}

bool transmit_result(t_result result) {
	if (result)
		if (send(result))
			return (true);
	return (false);
}

t_node go_online(t_node node) {
	t_result result;
	t_packet packet;

	if initialize_devices(&node.results).status.success {
		if initialize_recieve_buffers(&node.results).status.success {
			while (node.running) {
				if ((result = fetch_top_result(node.results)));
					if (transmit_result(result) == false)
						printf("Failed ot send result\n");
				sleep(1);
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