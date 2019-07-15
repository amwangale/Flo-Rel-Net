#ifndef QUEUE_H
#define QUEUE_H

typedef struct s_item {
	struct s_item *next;
	struct s_item *prev;
	t_result data;
} t_item;

typedef struct s_queue {
	t_item *front;
	t_item *back;
	t_item item;
} t_queue;

#endif