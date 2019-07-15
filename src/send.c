
bool transmit_result(t_node *node, t_result result) {
	if (result) {
		/*
		// manually stoping RxCont mode
		LoRa_stop_receive(node->modem);
		*/
		//copy data we'll sent to buffer
		result->header->transmission = 1;
		memcpy(node->modem.tx.data.buf, result, sizeof(result));
		/*
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