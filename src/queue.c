#include "../includes/queue.h"

bool push_back(t_queue *queue, void *data) {
	t_queue item;

	if ((item = new_item())) {
		// TODO checks
		memcpy(&item->data, data, sizeof(t_result));
		item->next = queue->back;
		queue->back = item;
		queue->back->prev = item;
		return (true);
	} else {
		return (false);
	}
}