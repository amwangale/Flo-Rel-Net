

bool initialize_recieve_buffers(t_node *node) {
	int error;
	t_queue queue;
	t_thread_watcher watcher;
	
	if (watcher = new_thread_watcher())
		if (node->results_hash = new_hash(node->neighbor_count))

			for (int i = 0; i < node->neighbor_count; i++) {
				if (!hash->get(i)) {
					if ((queue = new_queue())) {
						if (!set(node->results_hash, i, queue)) {
							printf("Failed to create results queue");
						} else {
							error = pthread_create(&watcher->thread, NULL, listen_for_data, &watcher);
							if (error)  {
								printf("Pthread failed to create\n");
							} else {
								pthread_join(watcher->thread, &error);
							}
						}
					}
				}
			}

	return (true);
}

bool initialize_devices(t_node *node) {
	int error;
	t_queue queue;
	t_thread_watcher watcher;

	if (watcher = new_thread_watcher())
		if (node->device_hash = new_hash(node->device_count))
			
			for (int i = 0; i < node->device_count; i++) {
				if (!get(node->device_hash, i)) {
					if ((queue = new_queue())) {
						if (!set(node->device_hash, i, queue)) {
							printf("Failed to create device queue");
						} else {
							error = pthread_create(&watcher->thread, NULL, collect_device_data, &watcher);
							if (error)  {
								printf("Pthread failed to create\n");
							} else {
								pthread_join(watcher->thread, &error);
							}	
						}
					}
				}
			}

	return (true);
}