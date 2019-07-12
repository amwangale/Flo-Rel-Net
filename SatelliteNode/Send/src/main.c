#include "../includes/send.h";

t_node configure(t_node node) {
	node.sender.running = true;

	register(node);
	
	return (node);
}

initialize_recieve_buffers(t_node *node) {
	// new hash
		// for each index
			// new ring buffer;
				// listen_for_data(index);
}

initialize_devices(t_node *node) {
	// for each device
		// new hash
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

				if (result)
					if ((packet = strip_result(result)));
						transmit_result(packet);
				
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