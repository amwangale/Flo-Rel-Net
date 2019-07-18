#include "../includes/init.h"

bool initialize_recieve_buffers(t_node *node) {
	int *error;
	t_queue *queue;
	t_thread_watcher *watcher;
	
	if ((watcher = new_thread_watcher(node))) {
		node->results_hash = *new_hash(node->neighbor_count);

		for (unsigned int i = 0; i < node->neighbor_count; i++) {
			// checking if index exists
			if (!get(node->receive_hash, i)) {
				if ((queue = new_queue())) {
					if (!set(node->results_hash, i, queue)) {
						printf("Failed to create results queue");
					} else {
						error = pthread_create(&watcher->thread, NULL, &listen_for_data, &watcher);
						if (error)  {
							printf("Pthread failed to create\n");
						} else {
							pthread_join(watcher->thread, (void*)&error);
						}
					}
				}
			}
		}
	}

	return (true);
}

bool initialize_devices(t_node *node) {
	int *error;
	t_queue *queue;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		node->device_hash = *new_hash(node->device_count);

		for (unsigned int i = 0; i < node->device_count; i++) {
			if (!get(node->device_hash, i)) {
				if ((queue = new_queue())) {
					if (!set(node->device_hash, i, queue)) {
						printf("Failed to create device queue");
					} else {
						error = &pthread_create(&watcher->thread, NULL, &collect_device_data, &watcher);
						if (error)  {
							printf("Pthread failed to create\n");
						} else {
							pthread_join(watcher->thread, (void*)&error);
						}	
					}
				}
			}
		}
	}

	return (true);
}


bool initialize_lora(t_node *node) {
	(void)node;
	/*
	LoRa_ctl modem;
	float21 buffer[PACKET_SIZE / BIT_WIDTH];

    // See for typedefs, enumerations and there values in LoRa.h header file
    modem.spiCS = 0; // Raspberry SPI CE pin number
    
    modem.rx.callback = rx_f;
    modem.rx.data.buf = buffer;

    modem.eth.preambleLen = 6;
    modem.eth.bw = BW62_5; //Bandwidth 62.5KHz
    modem.eth.sf = SF12; //Spreading Factor 12
    modem.eth.ecr = CR8; //Error coding rate CR4/8
    modem.eth.freq = PACKET_SIZE * 1000000; // 900.0MHz
    modem.eth.resetGpioN = 4;// GPIO4 on lora RESET pi
    modem.eth.dio0GpioN = 17;// GPIO17 on lora DIO0 pin to control Rxdone and Txdone interrupts
    modem.eth.outPower = OP20;// Output power
    modem.eth.powerOutPin = PA_BOOST;// Power Amplifire pin
    modem.eth.AGC = 1;// Auto Gain Control
    modem.eth.OCP = 240;// 45 to 240 mA. 0 to turn off protection
    modem.eth.implicitHeader = 0;// Explicit header mode
    modem.eth.syncWord = 0x12;

    node->modem = modem;
    */

    return (true);
    // For detail information about SF, Error Coding Rate, Explicit header, Bandwidth, AGC, Over current protection and other features refer to sx127x datasheet https://www.semtech.com/uploads/documents/DS_SX1276-7-8-9_W_APP_V5.pdf
}

bool initialize(t_node *node) {
	if (initialize_lora(node)) {
		LoRa_begin(&node->modem);

		if (initialize_devices(node)) {
			if (initialize_recieve_buffers(node)) {
				node->status.success = true;
				return (true);
			} else {
				node->status.failure = true;
			}
		} else {
			node->status.failure = true;
		}		
	} else {
		node->status.failure = true;
	}

	return (false);
}