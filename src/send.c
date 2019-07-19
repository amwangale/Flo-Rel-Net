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