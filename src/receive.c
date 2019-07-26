#include "../includes/node.h"
#include "../includes/receive.h"
#include "../includes/simulate.h"

t_message *strip_message(char **data) {
	t_message *message;

	if (!(message = new_message()))
		return (NULL);

	for (int i = 0; i < MESSAGE_COUNT; i++) {
		memcpy(&message->buffer[i], *data, sizeof(float21));
		**data >>= sizeof(float21);
	}

	return (message);
}

t_header *strip_header(char **data) {
	t_header *header;

	if (!(header = new_header(0)))
		return (NULL);

	/*filling the flags bit field*/
	memcpy(header, &(*data), sizeof(t_header));
	**data >>= sizeof(t_header);

	return (header);
}

void rx_callback(rxData *data) {
	/*
	rx->buf is the buffer we're
	looking for;

	we can strip other header
	information from the rx
	protocol, but we just want
	the buffer for this example

	we take the buffer and
	transform it into a data
	model we can manipulate;

	we convert to a result, strip
	the header, strip the message,
	and send it to the correct
	bucket so that bucket's
	thread can handle it;

	we don't care if the thread
	fails, we just want the
	message to go somewhere;

	and we stop when everything
	else stops;
	*/

	int index;

	t_node *node;
	t_queue *queue;
	char *rx_buffer;

	t_header *header;
	t_result *result;
	t_message *message;

	rx_buffer = (char*)data->buf;
	if ((header = strip_header(&rx_buffer))) { // || &
		node = (t_node*)data->userPtr;
		index = *((int*)get(node->neighbor_map, header->id));
		
		if ((queue = (t_queue*)get(node->receive_hash, index))) {
			if ((message = strip_message(&rx_buffer))) {
				result = new_result(header->id);
				memcpy(&result->header, header, sizeof(t_header));
				memcpy(&result->message, message, sizeof(t_message));
				push_back(queue, result, sizeof(t_result));
			}
		}
	}
}