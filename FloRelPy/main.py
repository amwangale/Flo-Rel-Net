register_node(node):
	return True

listen_for_data(watcher):
	while watcher.status.running:
		data = watcher.results.pop_front()
		if data:
			watcher.node.global_results.push_back(data)
			sleep(1)

		watcher.check_status()

collect_device_data(watcher):
	while watcher.status.running:
		size = 0
		result = Result()

		while size < MESSAGE_COUNT:
			data = simulate_collect_data()
			if data:
				result.message.buffer[size] = data
				size += 1

		watcher.node.global_results.push_back(result)
		watcher.check_status()

send_and_receive(watcher):
	while watcher.status.running:
		result = simulate_receive(watcher.node)
		if result:
			header = result.strip_header():
			if header:
				index = watcher.node.neighbor_map.get(header.id)
				queue = watcher.node.receive_hash.get(index)
				if queue:
					queue.push_back(result)

		result = watcher.node.fetch_top_result()
		if result:
			watcher.node.transmit_result(result)

		watcher.check_status()

if __name__ == "__main__":
	if len(sys.argv) == 2:
		node = Node(
			id=sys.argv[1],
			neighbor_count=5,
			device_count=3
		)

		if configure(node):
			if node.go_online():
				return 0