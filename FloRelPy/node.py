class Node:
	def __init__(self):
		self.global_results = Queue()


		self.mutex = Lock()
		self.status = Status(running=True)

	def get_status(self):
		with self.mutex:
			return self.status

	def fetch_top_result(self):
		return self.global_results.pop_front()
