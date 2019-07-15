#include "../includes/node.h"
#include "../includes/result.h"
#include "../includes/utils.h"

t_result *simulate_random_result(t_node node) {
	float point;
	float21 *data;
	t_result *result;

	if (!(result = new_result(node.id)))
		return (NULL);
	
	result->header->flags.transmission = 1;

	point = 5.0;
	for (int i = 0; i < MESSAGE_SIZE; i += BIT_WIDTH) {
		data = float_to_float21((
			(float)rand() / (float)(RAND_MAX)
		) * point);

		result->message.buffer[BITDEX(i)] = data;
	}

	return (result);
}

t_result *simulate_receive(t_node node) {
	t_result *result;

	result = simulate_random_result(node);
	return (result);
}