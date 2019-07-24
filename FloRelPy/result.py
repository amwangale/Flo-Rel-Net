class Result:
	def __init__(self):
		self.header = {}
		self.message = []

	def strip_message(self, result):
		return result.message

	def strip_header(self, result):
		return result.header