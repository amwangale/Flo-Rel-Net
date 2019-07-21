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
	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		if ((data = float_to_float21((
			(float)rand() / (float)(RAND_MAX)
		) * point))) {
			result->message.buffer[BITDEX(i)] = *data;
		} else {
			printf("Failed to convert float\n");
		}

	}

	return (result);
}

t_result *simulate_receive(t_node *node) {
	t_result *result;

	result = simulate_random_result(node);
	printf("Received simulated result\n");

	return (result);
}

float simulate_collect_data(void) {
	float data;

	data = ((float)rand() / (float)(RAND_MAX)) * 5.0;
	printf("Collected simulated data %f\n", data);

	return (data);
}

bool simulate_transmission(t_result *result) {
	float header;

	header = header_to_float(result->header);
	
	printf("HEADER || %f\n [\n", header);
	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		printf("%f ", float21_to_float(result->message.buffer[BITDEX(i)]));
	}
	printf("\n]\n");

	return (true);
}