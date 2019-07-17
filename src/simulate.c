#include "../includes/node.h"
#include "../includes/result.h"
#include "../includes/utils.h"
#include "../includes/simulate.h"

t_result *simulate_random_result(t_node node) {
	float point;
	float21 data;
	t_result *result;

	if (!(result = new_result(node.id)))
		return (NULL);
	
	result->header->flags.transmission = 1;

	point = 5.0;
	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		data = *float_to_float21((
			(float)rand() / (float)(RAND_MAX)
		) * point);

		result->message.buffer[BITDEX(i)] = data;
	}

	return (result);
}

t_result simulate_receive(t_node node) {
	t_result result;

	result = *simulate_random_result(node);
	return (result);
}

float simulate_collect_data(void) {
	return ((float)rand() / (float)(RAND_MAX));
}

bool simulate_transmission(t_result result) {
	/*
	
	*/
	printf("HEADER || %f\n [", (float)*result.header);
	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		printf("%f ", (float)*result->message[BITDEX(i)]);
	}
	printf("]\n");

	return (true);
}