#include "../includes/threads.h"
#include "../includes/node.h"
#include "../includes/utils.h"

t_thread_watcher *new_thread_watcher(t_node *node) {
	t_thread_watcher *twr;

	if (!(twr = (t_thread_watcher*)calloc(1, sizeof(t_thread_watcher))))
		return (NULL);
	if (!(memcpy(twr->results, new_queue(), sizeof(t_queue))))
		return (NULL);

	twr->status.running = true;
	twr->node = node;

	return (twr);
}
