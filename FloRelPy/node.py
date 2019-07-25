from hash import Hash
from utils import Status
from init import initialize
from multiprocessing import Lock, Queue

class Node:
	def __init__(self, id,
		neighbor_count=0,
		device_count=0
	):
		self.id = id

		self.neighbor_count = neighbor_count
		self.device_count = device_count

		self.global_results = Queue()

		self.device_hash = Hash(self.device_count)
		self.results_hash = Hash(self.neighbor_count)
		self.receive_hash = Hash(self.neighbor_count)
		self.neighbor_map = Hash(self.neighbor_count)

		self.mutex = Lock()
		self.status = Status(running=True)

	def get_status(self):
		with self.mutex:
			return self.status

	def fetch_top_result(self):
		return self.global_results.get()

	def run(self):
		while self.status.running:
			pass
		return True

	def go_online(self):
		if initialize(self):
			return self.run()
		else:
			print("Node failed to initialize")
		return False
