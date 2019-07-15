#include "../includes/send.h"

t_message *strip_message(void *data) {
	float15 f;
	t_message message;

	f = new_float15();
	meassage = new_message();

	while (i < MESSAGE_SIZE) {
		memcpy(
			message->buffer[i / BIT_WIDTH],
			&data[i], sizeof(float21)
		);
		i += BIT_WIDTH;
	}

	return (message);
}

t_header *strip_header(void *data) {
	t_header header;

	header = new_header();
	memcpy(&header, data, sizeof(header));
	return (header);
}

t_status receive(t_node *node) {
	int index;
	t_queue queue;
	t_header *header;

	while (node->status.running) {
		/*
		if ((data = recv())) {
		*/
		if ((data = simulate_receive(node))) {
			if ((header = strip_header(&data))) {
				if ((index = get(node->receive_hash, header->id))) {
					if ((queue = get(node->receive_hash, index))) {
						if ((message = strip_message(&data))) {
							push_back(queue, message);
						}
					}
				}
			}
		}
		sleep(1);
	}

	return (node->status.running);
}