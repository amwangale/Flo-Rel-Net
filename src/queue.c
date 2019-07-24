#include "../includes/florel.h"
#include "../includes/queue.h"

t_item *new_item(void *data, size_t size) {
	if (!data || !size) return (false);

	t_item *item;
	if (!(item = (t_item*)calloc(1, sizeof(t_item))))
		return (NULL);
	
	item->next = NULL;
	item->prev = NULL;

	printf("%p %ld\n", data, size);
	sleep(1);
	printf("\n");
	memcpy(&item->data, &data, size);
	printf("\n");
	return (item);
}

t_queue *new_queue(void) {
	t_queue *queue;

	if (!(queue = (t_queue*)calloc(1, sizeof(t_queue))))
		return (NULL);
	return (queue);
}

bool push_back(t_queue *queue, void *data, size_t size) {
	/*
	cannot call this function with non-void *
	data;

	don't ask, I don't know why;
	*/
	if (queue && data && size) {
		t_item *item;

		if ((item = new_item(data, size))) {
			if (!pthread_mutex_trylock(&queue->lock.lock)) {
				// TODO checks
				if (!queue->front) {
					printf("NO Q F\n");
					queue->front = item;
					item->prev = queue->back;
				} else if (!queue->back) {
					printf("NO Q B\n");
					queue->back = item;
					item->next = queue->front;
					queue->front->prev = item;
				} else {
					printf("BOTH Q\n");
					queue->back->prev = item;
					item->next = queue->back;
					queue->back = item;
				}

				pthread_mutex_unlock(&queue->lock.lock);
				printf("Pushed back data\n");
				return (true);
			}
		}
	}

	return (false);
}

t_item *pop_front(t_queue *queue) {
	t_item *item;

	item = NULL;
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
			return (item);
		}
	}

	return (item);
}