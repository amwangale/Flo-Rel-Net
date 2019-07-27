#include "../includes/florel.h"
#include "../includes/send.h"
#include "../includes/receive.h"
#include "../includes/init.h"
#include "../includes/threads.h"
#include "../sx1278-LoRa-RaspberryPi/incl/LoRa.h"

bool initialize_receive_buffers(t_node *node) {
	t_thread_watcher *watcher;

	for (unsigned int i = 0; i < node->neighbor_count; i++) {
		if ((watcher = new_thread_watcher(node))) {
			if (!set(
				&node->receive_hash, i,
				(void**)watcher->results, sizeof(t_queue)
			)) {
				printf("Failed to create results queue\n");
			} else {
				if (pthread_create(
					&watcher->thread, NULL,
					listen_for_data, watcher
				)) {
					printf("Pthread failed to create\n");
				} else {
					sleep(1);
				}
			}
		}
	}

	return (true);
}

bool initialize_devices(t_node *node) {
	t_thread_watcher *watcher;

	for (unsigned int i = 0; i < node->device_count; i++) {
		if ((watcher = new_thread_watcher(node))) {
			if (!set(
				&node->device_hash, i,
				(void**)watcher->results, sizeof(t_queue)
			)) {
				printf("Failed to create device queue %i\n", i);
			} else {
				if (pthread_create(
					&watcher->thread, NULL,
					collect_device_data, watcher
				)) {
					return (false);
				} else {
					sleep(1);
				}
			}
		}
	}

	return (true);
}

bool initialize_sender(t_node *node) {
	int error;
	t_thread_watcher *watcher;

	if ((watcher = new_thread_watcher(node))) {
		error = pthread_create(
			&watcher->thread, NULL,
			sending, watcher
		);

		if (error)  {
			printf("Pthread failed to create\n");
			return (false);
		}
	} else {
		printf("Failed to create sender thread\n");
		return (false);
	}

	return (true);
}

bool initialize_lora(t_node *node) {
	if (!node) return (false);

	float21 buffer[PACKET_SIZE / BIT_WIDTH];

    // See for typedefs, enumerations and there values in LoRa.h header file
	node->modem.spiCS = 0; // Raspberry SPI CE pin number
    
    node->modem.rx.callback = rx_callback;
    node->modem.rx.data.buf = (char*)buffer;

	node->modem.tx.callback = tx_callback;
    node->modem.tx.data.buf = (char*)buffer;

    node->modem.eth.preambleLen = 6;
    node->modem.eth.bw = BW62_5; // Bandwidth 62.5KHz
    node->modem.eth.sf = SF12; // Spreading Factor 12
    node->modem.eth.ecr = CR8; // Error coding rate CR4/8
    node->modem.eth.freq = 900000000; // 900.0MHz
    node->modem.eth.resetGpioN = 4; // GPIO4 on lora RESET pi
    node->modem.eth.dio0GpioN = 17; // GPIO17 on lora DIO0 pin to control Rxdone and Txdone interrupts
    node->modem.eth.outPower = OP20; // Output power
    node->modem.eth.powerOutPin = PA_BOOST; // Power Amplifire pin
    node->modem.eth.AGC = 1; // Auto Gain Control
    node->modem.eth.OCP = 240; // 45 to 240 mA. 0 to turn off protection
    node->modem.eth.implicitHeader = 0; // Explicit header mode
    node->modem.eth.syncWord = 0x12;
    node->modem.eth.CRC = 1;//Turn on CRC checking

    return (true);
    
    // For detail information about SF, Error Coding Rate, Explicit header, Bandwidth, AGC, Over current protection and other features refer to sx127x datasheet https://www.semtech.com/uploads/documents/DS_SX1276-7-8-9_W_APP_V5.pdf
}

bool initialize(t_node *node) {
	if (initialize_lora(node)) {
		printf("LoRa initialized\n");

		if (initialize_devices(node)) {
			printf("Devices initialized\n");
		} else {
			node->status.failure = true;
			return (false);
		}

		if (initialize_receive_buffers(node)) {
			printf("Receive buffers initialized\n");
		} else {
			node->status.failure = true;
			return (false);
		}

		if (initialize_sender(node)) {
			printf("Send/Receive initialized\n");
		} else {
			node->status.failure = true;
			return (false);
		}

		#ifndef TESTING
			LoRa_begin(&node->modem);
		#endif
		printf("LoRa started\n");
		
		node->status.success = true;
		return (true);
	} else {
		node->status.failure = true;
	}

	return (false);
}