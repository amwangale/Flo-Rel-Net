#include "../includes/florel.h"
#include "../includes/result.h"
#include "../includes/node.h"

t_result *simulate_random_result(t_node *node) {
	float point;
	float21 *data;
	t_result *result;

	if (!(result = new_result(node->id)))
		return (NULL);
	
	result->header.flags.transmission = 1;
	result->header.flags.panic = 0;
	result->header.flags.failure = 0;
	result->header.flags.disconnect = 0;
	result->header.flags.device_id = 1;

	point = 5.0;
	for (int i = 0; i < MESSAGE_COUNT; i++) {
		if ((data = float_to_float21((
			(float)rand() / (float)(RAND_MAX)
		) * point))) {
			result->message.buffer[i] = *data;
		} else {
			printf("Failed to convert float\n");
		}
	}

	return (result);
}

t_result *simulate_receive(t_node *node) {
	t_result *result;
	if (!(result = simulate_random_result(node)))
		return (NULL);
	return (result);
}

float simulate_collect_data(void) {
	float data;

	data = ((float)rand() / (float)(RAND_MAX)) * 5.0;
	printf("Collected simulated data %f\n", data);

	return (data);
}

bool simulate_transmission(t_result *result) {
	unsigned int header;

	header = (unsigned int)header_to_float(result->header);
	
	printf("\nHEADER || ");
	for (int i = 0; i < BIT_WIDTH; i++) {
		printf("%i", (header & 0x1)? 1: 0);
		header >>= 1;
	}
	printf(" [\n");
	for (int i = 0; i < MESSAGE_COUNT; i++) {
		// printf(" %f", float21_to_float(result->message.buffer[i]));
	}
	printf("\n]\n");

	return (true);
}