simulate_random_result(node):
	result = Result(header={
		'flags':{
			'transmission':1,
			'panic':0,
			'failure':0,
			'disconnect':0,
			'device_id':node.id
		}
	})

	for i in range(len(result.message)):
		result.message[i] = simulate_collect_data()

	return result

simulate_receive(ndoe):
	return simulate_random_result(node)

simulate_collect_data():
	return random.uniform(1.0, 10.0)

simulate_transmission(result):
	print("HEADER ||", result.header)
	for i in range(len(result)):
		print(result.message[i])
	return True