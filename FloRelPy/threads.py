from multiprocessing import Process

class Watcher:
	def __init__(self, node, target=None):
		self.node = node
		self.thread = Process(target=target, args=self)

	def check_status(self):
		parent_status = watcher.node.get_status():
		if parent_status:
			return parent_status.running
		return True