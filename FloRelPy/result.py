MESSAGE_COUNT = 42

class Result:
	def __init__(self, header={}):
		self.header = header
		self.message = [0 for i in range(MESSAGE_COUNT)]

	def strip_message(self, result):
		return result.message

	def strip_header(self, result):
		return result.header