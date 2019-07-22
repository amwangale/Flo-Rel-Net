#include "../includes/node.h"
#include "../includes/result.h"
#include "../includes/simulate.h"

bool transmit_result(t_node *node, t_result *result) {
	(void)node;

	if (result) {
		/*
		// manually stoping RxCont mode
		LoRa_stop_receive(node->modem);
		*/
		
		result->header.flags.transmission = 1;

		/*
		// copy data we'll sent to buffer
		memcpy(node->modem.tx.data.buf, result, sizeof(t_result));
		LoRa_send(&node->modem);
		*/
		
		simulate_transmission(result);
		sleep(1);
		
		/*
		LoRa_receive(&node->modem);
		*/
		
		return (true);
	}

	return (false);
}

t_result *fetch_top_result(t_queue *global_results) {
	t_item *item;
	t_result *result;

	result = new_result(0);
	if ((item = pop_front(global_results)))
		result = memcpy(result, &item->data, sizeof(float) * PACKET_SIZE);

	return (result);
}

void *sending(void *arg) {
	t_result *result;
	t_status *parent_status;
	t_thread_watcher *watcher;

	watcher = arg;

	// printf("running sender %d\n", watcher->status.running);
	// printf("success %d\n", watcher->status.success);
	// printf("failure %d\n", watcher->status.failure);

	while (watcher->status.running) {
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

	free_result(result);

	pthread_exit(&watcher->status);
	return (NULL);
}