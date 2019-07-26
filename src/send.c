#include "../includes/node.h"
#include "../includes/result.h"
#include "../includes/simulate.h"

bool transmit_result(t_node *node, t_result *result) {
	(void)node;

	if (result) {
		#ifndef TESTING	
			// manually stoping RxCont mode
			LoRa_stop_receive(&node->modem);
		
			result->header.flags.transmission = 1;

			// copy data we'll sent to buffer
			memcpy(node->modem.tx.data.buf, result, sizeof(t_result));

			LoRa_send(&node->modem);
			sleep(1);
			LoRa_receive(&node->modem);
		#endif

		return (true);
	}

	return (false);
}

t_result *fetch_top_result(t_queue *global_results) {
	t_item *item;
	t_result *result;

	result = new_result(0);
	if ((item = pop_front(global_results))) {
		memcpy(&result->header, item->data, sizeof(t_header));
		for (int i = 0; i < PACKET_COUNT; i++) {
			memcpy(
				&result->message.buffer[i],
				item->data, sizeof(float21)
			);
		}
	}

	return (result);
}

void tx_callback(txData *data) {
	(void)data;
	//
}

void *sending(void *arg) {
	t_result *result;
	t_status *parent_status;
	t_thread_watcher watcher;

	memcpy(&watcher, (t_thread_watcher*)arg, sizeof(t_thread_watcher));
	while (watcher.status.running) {
		if ((result = fetch_top_result(&watcher.node->global_results)))
			transmit_result(watcher.node, result);

		parent_status = get_status(watcher.node);
		if (parent_status)
			if (parent_status->running == false)
				watcher.status.running = false;
	}

	pthread_exit(&watcher.status);
	return (NULL);
}