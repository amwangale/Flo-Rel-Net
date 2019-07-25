import main # yes, I know... it's strange
from threads import Watcher
from multiprocessing import Value

def initialize_send_receive(node):
	watcher = Watcher(node.id, node, target=main.send_and_receive)
	
	for n in range(node.neighbor_count):
		node.neighbor_map.set(n, n)

	watcher.thread.start()
	return True

def initialize_receive_buffers(node):
	for n in range(node.neighbor_count):
		watcher = Watcher(n, node,
			target=main.listen_for_data
		)

		if node.receive_hash.set(n, watcher):
			watcher.thread.start()

	return True

def initialize_devices(node):
	for d in range(node.device_count):
		watcher = Watcher(
			d, node,
			target=main.collect_device_data
		)

		if node.device_hash.set(d, watcher):
			watcher.thread.start()
			
	return True

def initialize_lora(node):
	if not node: return False
	return True

def initialize(node):
	if initialize_lora(node):
		print("LoRa initialized")

		if not initialize_devices(node):
			return False
		print("Devices initialized")

		if not initialize_receive_buffers(node):
			return False
		if not initialize_send_receive(node):
			return False
		return True
	return False