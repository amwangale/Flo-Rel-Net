class Queue:
	def __init__(self, length=0):
		self.length = length
		self.inner_queue = []
		self.mutex = Lock()

	def push_front(self, item):
		with self.mutex:
			self.inner_queue.insert(0, item)

	def pop_back(self):
		item = None
		with self.mutex:
			item = self.inner_queue.pop()
		return item