#include "../includes/florel.h"
#include "../includes/queue.h"

t_item *new_item(void) {
	t_item *item;

	if (!(item = (t_item*)calloc(1, sizeof(t_item))))
		return (NULL);
	return (item);
}

t_queue *new_queue(void) {
	t_queue *queue;

	if (!(queue = (t_queue*)calloc(1, sizeof(t_queue))))
		return (NULL);
	return (queue);
}

bool push_back(t_queue *queue, void *data) {
	/*
	cannot call this function with non-void *
	data;

	don't ask, I don't know why;
	*/
	t_item *item;

	if ((item = new_item())) {
		if (!pthread_mutex_trylock(&queue->lock.lock)) {
			// TODO checks
			memcpy(&item->data, data, sizeof(t_result));
			item->next = queue->back;
			queue->back = item;
			queue->back->prev = item;
			pthread_mutex_unlock(&queue->lock.lock);
			printf("Pushed back data\n");
			return (true);
		}
	}

	return (false);
}

t_item *pop_front(t_queue *queue) {
	t_item *item;

	item = NULL;
	if (!pthread_mutex_trylock(&queue->lock.lock)) {
		if (!(queue->front || queue->back)) return (NULL);
		if (queue->front == queue->back) return (NULL);

		item = queue->front;
		queue->front = queue->front->prev;
		queue->front->next = NULL;
		item->next = NULL;
		item->prev = NULL;

		pthread_mutex_unlock(&queue->lock.lock);
		return (item);
	}

	return (NULL);
}