#include "../includes/node.h"
#include "../includes/receive.h"
#include "../includes/simulate.h"

t_message *strip_message(t_result *result) {
	t_message *message;
	message = new_message();

	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		memcpy(
			&message->buffer[BITDEX(i)],
			&result->message.buffer[i],
			sizeof(float21)
		);
	}

	return (message);
}

t_header *strip_header(void *data) {
	t_header *header;

	header = new_header(0);
	memcpy(&header, data, sizeof(header));
	return (header);
}

void *receiving(void *arg) {
	int index;
	int neighbor_id;

	t_queue *queue;
	t_header *header;
	t_result *result;
	t_message *message;
	t_status *parent_status;
	t_thread_watcher *watcher;

	watcher = arg;
	printf("%i\n", watcher->status.running);
	while (watcher->status.running) {
		/*
		LoRa_receive(&node->modem);
		*/
		if ((result = simulate_receive(watcher->node))) {
			if ((header = strip_header(result))) {
				if ((index = *(int*)get(watcher->node->neighbor_map, header->id))) {
					if ((queue = (t_queue*)get(watcher->node->receive_hash, index))) {
						if ((message = strip_message(result))) {
							push_back(queue, message);
						}
					}
				}
			}
		}
		result = NULL;

		parent_status = get_status(watcher->node);
		if (parent_status)
			if (parent_status->running == false)
				watcher->status.running = false;
	}

	pthread_exit(&watcher->status);
	return (NULL);
}