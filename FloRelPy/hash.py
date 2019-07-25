from multiprocessing import Lock

class Hash:
	def __init__(self, size=0):
		self.size = size
		self.hash = {}
		self.mutex = Lock()

	def get(self, key):
		item = None
		with self.mutex:
			if key in self.hash:
				item = self.hash[key]
		return item

	def set(self, key, value):
		with self.mutex:
			self.hash[key] = value
			return True
		return False