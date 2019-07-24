#include "../includes/florel.h"
#include "../includes/send.h"
#include "../includes/receive.h"
#include "../includes/init.h"
#include "../includes/threads.h"
#include "../sx1278-LoRa-RaspberryPi/incl/LoRa.h"

bool initialize_recieve_buffers(t_node *node) {
	int error;
	t_queue *queue;
	t_thread_watcher *watcher;
	
	if ((watcher = new_thread_watcher(node))) {
		new_hash(&node->results_hash, node->neighbor_count);

		for (unsigned int i = 0; i < node->neighbor_count; i++) {
			// checking if index exists
			if (!get(node->receive_hash, i)) {
				if ((queue = new_queue())) {
					if (!set(node->results_hash, i, queue)) {
						printf("Failed to create results queue\n");
					} else {
						error = pthread_create(
							&watcher->thread, NULL,
							listen_for_data, watcher
						);
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
	int error;
	t_queue *queue;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		new_hash(&node->device_hash, node->device_count);

		for (unsigned int i = 0; i < node->device_count; i++) {
			if (!get(node->device_hash, i)) {
				if ((queue = new_queue())) {
					if (!set(node->device_hash, i, queue)) {
						printf("Failed to create device queue %i\n", i);
					} else {
						error = pthread_create(
							&watcher->thread, NULL,
							&collect_device_data, watcher
						);
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

bool initialize_receiver(t_node *node) {
	int error;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		new_hash(&node->neighbor_map, node->neighbor_count);

		for (unsigned int i = 0; i < node->neighbor_count; i++) {
			if (!get(node->neighbor_map, i)) {
				if (!set(node->neighbor_map, i, (void*)&i)) {
					printf("Failed to create device queue %i\n", i);
				}
			}
		}

		error = pthread_create(
			&watcher->thread, NULL,
			&receiving, watcher
		);

		if (error)  {
			printf("Pthread failed to create\n");
		} else {
			// pthread_join(watcher->thread, (void*)&error);
		}
	} else {
		printf("Failed to create receiver thread\n");
		return (false);
	}

	return (true);
}

bool initialize_sender(t_node *node) {
	int error;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		error = pthread_create(
			&watcher->thread, NULL,
			&sending, watcher
		);
		if (error)  {
			printf("Pthread failed to create\n");
			return (false);
		} else {
			// pthread_join(watcher->thread, (void*)&error);
		}
	} else {
		printf("Failed to create sender thread\n");
		return (false);
	}

	return (true);
}

bool initialize_send_receive(t_node *node) {
	int error;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		new_hash(&node->neighbor_map, node->neighbor_count);

		for (unsigned int i = 0; i < node->neighbor_count; i++) {
			if (!get(node->neighbor_map, i)) {
				if (!set(&node->neighbor_map, i, (void*)&i)) {
					printf("Failed to create device queue %i\n", i);
				}
			}
		}

		error = pthread_create(
			&watcher->thread, NULL,
			&send_and_receive, watcher
		);
		if (error)  {
			printf("Pthread failed to create\n");
			return (false);
		} else {
			// pthread_join(watcher->thread, (void*)&error);
		}
	} else {
		printf("Failed to create sender thread\n");
		return (false);
	}

	return (true);
}

bool initialize_lora(t_node *node) {
	if (!node) return (false);

	/*
	LoRa_ctl modem;
	float21 buffer[PACKET_SIZE / BIT_WIDTH];

    // See for typedefs, enumerations and there values in LoRa.h header file
    modem.spiCS = 0; // Raspberry SPI CE pin number
    
    modem.rx.callback = rx_callback;
    modem.rx.data.buf = buffer;

	modem.tx.callback = tx_callback;
    modem.tx.data.buf = buffer;

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
		printf("LoRa initialized\n");
		
		/*
		LoRa_begin(&node->modem);
		*/

		if (initialize_devices(node)) {
			printf("Devices initialized\n");
			/*			
			if (initialize_sender(node)) {
				printf("Sender initialized\n");
			} else {
				node->status.failure = true;
				return (false);
			}
			*/
		} else {
			node->status.failure = true;
			return (false);
		}

		if (initialize_recieve_buffers(node)) {
			printf("Receive buffers initialized\n");
			/*
			if (initialize_receiver(node)) {
				printf("Receiver initialized\n");
			} else {
				node->status.failure = true;
				return (false);
			}
			*/
		} else {
			node->status.failure = true;
			return (false);
		}

		if (initialize_send_receive(node)) {
			printf("Send/Receive initialized\n");
		} else {
			node->status.failure = true;
			return (false);
		}
		node->status.success = true;
		return (true);
	} else {
		node->status.failure = true;
	}

	return (false);
}