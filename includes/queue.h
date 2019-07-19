#ifndef QUEUE_H
#define QUEUE_H

#include "result.h"

typedef struct s_item {
	struct s_item *next;
	struct s_item *prev;
	t_result data;
} t_item;

typedef struct s_queue {
	t_item *front;
	t_item *back;
} t_queue;

bool 	push_back(t_queue *queue, void *data);
t_item *pop_front(t_queue *queue);

#endif