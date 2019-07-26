#include "../includes/florel.h"
#include "../includes/queue.h"

bool new_item(t_item **item, void **data, size_t size) {
	if (!data || !size || *item)
		return (false);
	if (!(*item = (t_item*)calloc(1, sizeof(t_item))))
		return (false);
	
	(*item)->next = NULL;
	(*item)->prev = NULL;

	(*item)->data = *data;
	return (true);
}

bool new_queue(t_queue **queue) {
	if (!(*queue = (t_queue*)calloc(1, sizeof(t_queue))))
		return (false);
	return (true);
}

bool push_back(t_queue **queue, void **data, size_t size) {
	t_item *item;

	if (*queue && data && size) {
		if (new_item(&item, data, size)) {
			if (!pthread_mutex_trylock(&(*queue)->lock.lock)) {

				if (!(*queue)->front) {
					(*queue)->front = item;
					item->prev = (*queue)->back;
				} else if (!(*queue)->back) {
					(*queue)->back = item;
					item->next = (*queue)->front;
					(*queue)->front->prev = item;
				} else {
					(*queue)->back->prev = item;
					item->next = (*queue)->back;
					(*queue)->back = item;
				}
				
				pthread_mutex_unlock(&(*queue)->lock.lock);
				
				return (true);
			}
		}
	}

	return (false);
}

t_item *pop_front(t_queue *queue) {
	t_item *item = NULL;

	if (queue) {
		if (!pthread_mutex_trylock(&queue->lock.lock)) {
			if (!(queue->front || queue->back)) return (NULL);
			if (queue->front == queue->back) return (NULL);

			item = queue->front;
			queue->front = queue->front->prev;
			queue->front->next = NULL;
			item->next = NULL;
			item->prev = NULL;

			pthread_mutex_unlock(&queue->lock.lock);
		}
	}

	return (item);
}