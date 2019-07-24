class Hash:
	def __init__(self, size=0):
		self.size = size
		self.hash = {}
		self.mutex = Lock()

	def get(self, key):
		item = None

		if key:
			with self.mutex:
				item = self.hash[key]

		return item