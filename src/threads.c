#include "../includes/threads.h"

t_thread_watcher *new_thread_watcher(t_node *node) {
	t_thread_watcher *twr;

	if (!(twr = (t_thread_watcher*)calloc(1, sizeof(t_thread_watcher))))
		return (NULL);
	twr->status = *new_status();
	twr->results = *new_queue();
	twr->node = node;
	return (twr);
}
