import node
import random
from result import Result, MESSAGE_COUNT

def collect_data():
	return random.uniform(1.0, 10.0)

def random_result(node):
	result = Result(header={
		'id':random.randint(0, node.neighbor_count),
		'flags':{
			'transmission':1,
			'panic':0,
			'failure':0,
			'disconnect':0,
			'device_id':random.randint(0, node.device_count)
		}
	})

	for i in range(len(result.message)):
		result.message[i] = collect_data()

	return result or None

def receive(node):
	return random_result(node)

def transmission(result):
	print("\nHEADER ||", result.header)
	for i in range(MESSAGE_COUNT):
		print(result.message[i], end="")
	return True