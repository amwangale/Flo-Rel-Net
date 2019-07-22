#include "../includes/node.h"
#include "../includes/receive.h"
#include "../includes/simulate.h"

t_message *strip_message(t_result *result) {
	t_message *message;

	message = new_message();
	for (int i = 0; i < MESSAGE_COUNT; i++) {
		memcpy(
			&message->buffer[i],
			&result->message.buffer[i],
			sizeof(float21)
		);
	}

	return (message);
}

t_header *strip_header(t_result *result) {
	t_header *header;

	if (!(header = new_header(0)))
		return (NULL);

	header->id = result->header.id;

	header->flags.transmission = result->header.flags.transmission;
	header->flags.panic = result->header.flags.panic;
	header->flags.failure = result->header.flags.failure;
	header->flags.disconnect = result->header.flags.disconnect;
	header->flags.device_id = result->header.flags.device_id;

	return (header);
}

/*
void rx_callback(rxData *rx) {
	rx->buf is the buffer we're
	looking for;

	we can strip other header
	information from the rx
	protocol, but we just want
	the buffer for this example

	we take the buffer like we
	do below in receiving() and
	transform it the same way;

	we convert to a result, strip
	the header, strip the message,
	and send it to the correct
	bucket so that bucket's
	thread can handle it;

	we don't care if the thread
	fails, we just want the
	message to go somewhere;

	and we stop when everything
	else stops;
}
*/

void *receiving(void *arg) {
	unsigned int index;

	t_header *header;
	t_result *result;
	t_queue *queue;
	t_message *message;
	t_status *parent_status;
	t_thread_watcher *watcher;

	watcher = arg;
	
	// printf("running receiver %d\n", watcher->status.running);
	// printf("success %d\n", watcher->status.success);
	// printf("failure %d\n", watcher->status.failure);
	
	/*
	begins a continuous loop of
	receving transmissions;

	instead of entering the run
	loop below, we just call
	receive and let the rx
	callback fire every time we
	receive a result;

	examples are commented out
	below so we can simulate
	what the transaction will
	look like

	LoRa_receive(&node->modem);
	*/
	while (watcher->status.running) {
		if ((result = simulate_receive(watcher->node))) {
			if ((header = strip_header(result))) {
				
				printf("neighbors exist? %s, %d\n",
					&watcher->node->neighbor_map? "true":"false",
					header->id
				);

				index = *((int*)get(watcher->node->neighbor_map, header->id));
				if ((queue = (t_queue*)get(watcher->node->receive_hash, index))) {
					if ((message = strip_message(result))) {
						push_back(queue, message);
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
		result = NULL;

		parent_status = get_status(watcher->node);
		if (parent_status)
			if (parent_status->running == false)
				watcher->status.running = false;
	}

	pthread_exit(&watcher->status);
	return (NULL);
}