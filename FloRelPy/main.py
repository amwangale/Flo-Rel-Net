import sys
import node
import time
import random
import simulate
from send import transmit_result
from multiprocessing import Lock
from result import Result, MESSAGE_COUNT

def register_node(node):
	return True

def configure(node):
	node.status.running = True
	if register_node(node):
		return True
	return False

def listen_for_data(watcher):
	while watcher.status.running:
		data = watcher.results.get()
		if data:
			watcher.node.global_results.put(data)

		time.sleep(1)
		watcher.check_status()

def collect_device_data(watcher):
	while watcher.status.running:
		size = 0
		result = Result({
			'id':watcher.node.id,
			'flags':{
				'transmission':1,
				'panic':0,
				'failure':0,
				'disconnect':0,
				'device_id':random.randint(0, watcher.node.device_count)
			}
		})

		while size < MESSAGE_COUNT:
			data = simulate.collect_data()
			if data:
				result.message[size] = data
				size += 1

		watcher.node.global_results.put(result)
		time.sleep(1)
		watcher.check_status()

def send_and_receive(watcher):
	while watcher.status.running:
		result = simulate.receive(watcher.node)
		if result:
			header = result.strip_header(result)
			if header:
				index = watcher.node.neighbor_map.get(header['id'])
				thread = watcher.node.receive_hash.get(index)
				if thread:
					print("Received data")
					thread.results.put(result)

		time.sleep(1)

		result = watcher.node.fetch_top_result()
		if result:
			print("Sending data")
			transmit_result(result)

		watcher.check_status()

if __name__ == "__main__":
	if len(sys.argv) == 2:
		node = node.Node(
			id=sys.argv[1],
			neighbor_count=5,
			device_count=3
		)

		if configure(node):
			if node.go_online():
				sys.exit(0)
			else:
				print("Node failed to go online")
		else:
			print("Node configuration failed")
	else:
		print("Node ID required for testing")
	sys.exit(1)