from utils import Status
from multiprocessing import Process, Queue

class Watcher:
	def __init__(self, id, node, target=None):
		self.node = node
		self.results = Queue()
		self.status = Status(running=True)
		self.thread = Process(target=target, args=(self,))

	def check_status(self):
		parent_status = self.node.get_status()
		if parent_status:
			return parent_status.running
		return True