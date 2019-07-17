#ifndef QUEUE_H
#define QUEUE_H

#include "result.h"
#include "utils.h"

typedef struct s_item {
	struct s_item *next;
	struct s_item *prev;
	t_result data;
} t_item;

typedef struct s_queue {
	t_item *front;
	t_item *back;
} t_queue;

t_item *new_item(void) {
	t_item *item;

	if (!(item = (t_item*)calloc(1, sizeof(t_item))))
		return (NULL);
	return (item);
}

bool 	push_back(t_queue *queue, void *data);
t_item *pop_front(t_queue *queue);

#endif