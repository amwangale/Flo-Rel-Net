#include "../includes/queue.h"

bool push_back(t_queue *queue, void *data) {
	t_item *item;

	if ((item = new_item())) {
		// TODO checks
		memcpy(&item->data, data, sizeof(t_result));
		item->next = queue->back;
		queue->back = item;
		queue->back->prev = item;
		return (true);
	}

	return (false);
}

t_item *pop_front(t_queue *queue) {
	t_item *item;

	if (!(queue->front || queue->back)) return (NULL);
	if (queue->front == queue->back) return (NULL);

	item = queue->front;
	queue->front = queue->front->prev;
	queue->front->next = NULL;
	item->next = NULL;
	item->prev = NULL;

	return (item);
}