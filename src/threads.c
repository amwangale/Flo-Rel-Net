#include "../includes/threads.h"
#include "../includes/node.h"
#include "../includes/utils.h"

t_thread_watcher *new_thread_watcher(t_node *node) {
	t_thread_watcher *twr;

	if (!(twr = (t_thread_watcher*)calloc(1, sizeof(t_thread_watcher))))
		return (NULL);
	twr->status.running = true;
	twr->results = new_queue();
	twr->node = node;
	return (twr);
}
