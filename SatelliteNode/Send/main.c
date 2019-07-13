#include "../includes/send.h"

bool register(t_node node) {
	// TODO
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

bool collect_data() {
	t_result result;

	set_header(&result);
	while (true) {
		if ((data = recv())) {
			set_message(result->message, &data);
		}
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