def initialize_send_receive(node):
	return False

def initialize_receive_buffers(node):

	for n in range(node.neighor_count):
		watcher = Watcher(n, target=listen_for_data)
		
		if node.receive_hash.set(n, watcher.results)
			watcher.thread.start()

	return False

def initialize_devices(node):
	return False

def initialize_lora(node):
	return False

def initialize(node):
	if initialize_lora(node):
		if not initialize_devices(node):
			return False
		if not initialize_receive_buffers(node):
			return False
		if not initialize_send_receive(node):
			return False
		return True
	return False